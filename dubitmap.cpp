#include "dubitmap.hpp"
#include <cstring>
#include <assert.h>
#define MIN_ALLOC_CAP 16 // in dubits (MAKE SURE IT IS DIVISIBLE BY FOUR)
#define DUBIT_MASK 0b11

namespace KOS{

/* Resize array if length = capacity */
bool dubitmap::resize(uint32_t new_cap){
    assert(len < new_cap && "Resized Array is larger than capacity");
    uint8_t* new_arr = new uint8_t[2*(new_cap>>2)];
    if(!new_arr) return false;
    std::memcpy(new_arr, this->data, (this->len>>2)*sizeof(uint8_t));
    delete [] this->data;
    this->data = new_arr;
    this->capacity = new_cap;
    return true;
}

/* Creates a dubitmap where (X) => 10 and (-) => 11 all other values raise an error*/
dubitmap::dubitmap(std::string in) : capacity((MIN_ALLOC_CAP+in.length())<<2), len(0){
    this->data = new uint8_t[this->capacity];
    for (const char* src_val = in.c_str();src_val && src_val[len];len++)
    {
        if((len>>2)>=(this->capacity>>2)) resize(capacity*2);
        switch (src_val[len])
        {
            case '0':
                data[len>>2]&= ~(0b11<< (2*(len&DUBIT_MASK)));
                break;
            
            case '1':
                data[len>>2]= (data[len>>2]&~(0b10<< (2*(len&DUBIT_MASK))))|(0b01<< (2*(len&DUBIT_MASK)));
                break;

            case 'X':
                data[len>>2] = (data[len>>2]&~(0b01<< (2*(len&DUBIT_MASK))))|(0b10<< (2*(len&DUBIT_MASK)));
                break;

            case '-':
                data[len>>2]|= 0b11<< (2*(len&DUBIT_MASK));
                break;

            default:
                /* Raise Error*/
                assert(false&&"Unknown Character Detected");
                break;
        }
    }
}

/* Creates a dubitmap where characters (index2) => 10 and (index3) => 11 all other values raise an error*/
dubitmap::dubitmap(std::string in, char index2, char index3) : capacity((MIN_ALLOC_CAP+in.length())<<2), len(0){
    this->data = new uint8_t[this->capacity];
    for (const char* src_val = in.c_str();src_val && src_val[len];len++)
    {
        if(src_val[len]  == '0'){data[len>>2]&= ~(0b11<< (2*(len&DUBIT_MASK)));}
        else if(src_val[len]  == '1'){data[len>>2]= (data[len>>2]&~(0b10<< (2*(len&DUBIT_MASK))))|(0b01<< (2*(len&DUBIT_MASK)));}
        else if(src_val[len] == index2){data[len>>2] = (data[len>>2]&~(0b01<< (2*(len&DUBIT_MASK))))|(0b10<< (2*(len&DUBIT_MASK)));}
        else if (src_val[len] == index3){data[len>>2]|= 0b11<< (2*(len&DUBIT_MASK));}
        else{assert(false && "unknown character detected");}
    }
}

/* Free data */
dubitmap::~dubitmap(){
    if(this->data){
        delete [] data;
    }
}

/* Length getter method: Returns the number of dubits */
uint32_t dubitmap::length() const{
    return len;
}

/* Assignment Operator */
dubitmap& dubitmap::operator=(const dubitmap& other){
    if (this != &other) { // Avoid self-assignment
            // Release any existing resource in 'this'
            delete [] this->data;
            this->data = new uint8_t[other.capacity>>2];
            memcpy(this->data, other.data, capacity>>2);
            this->len = other.len;
            this->capacity = other.len;
        }
        // Allocate new memory and copy data from 'other' to 'this'
        return *this;
}

/* Empty Constructor */
dubitmap::dubitmap(void): capacity(0), len(0), data(nullptr){}

/* Copy Constructor */
dubitmap::dubitmap(const dubitmap& other){
    len = other.len;
    capacity = other.capacity;
    data = new uint8_t[other.capacity>>2];
    memcpy(this->data, other.data, capacity>>2);
}

/* See the value of any dubit */
uint8_t dubitmap::operator()(uint32_t index) const{
    assert(index < len && "Array out of bounds");
    return ((data[index>>2]>>(2*(index&0b11))) &0b11);
}

/* Prints out all the values of the dubitmap in order with spaces in between*/
std::ostream& operator<<(std::ostream& os, const dubitmap& obj) {        
        for(uint32_t i = 0; i<obj.length(); i++){
            os << (static_cast<uint16_t>(obj(i))) << " "; // static_cast(uint8_t) does not work. Not sure but I think compiler views it as a character
        }
        return os;
    }

/* Adds a dubit to the end of the dubitmap*/
void dubitmap::push_back_dubit(uint8_t new_val){
    assert(new_val<4 && "Adding a value to dubitmap that is not two bit representable");
    if(capacity == 0) resize(MIN_ALLOC_CAP);
    if(len + 1 >= capacity) resize(capacity*2);
    len++;
    change_dubit(len-1, new_val);
}

/* Appends the dubitmap */
dubitmap& dubitmap::operator+=(dubitmap& other){
    for(uint32_t i = 0; i< other.len; i++){
        push_back_dubit(other(i));
    }
    
    return *this;
}

/* Adds a dubit to the end of the dubitmap */
dubitmap& dubitmap::operator+=(uint8_t new_val){
    push_back_dubit(new_val);
    return *this;
}

void dubitmap::change_dubit(uint32_t index, uint8_t val){
    assert(index < len && "Out of bounds access");
    switch (val)
        {
            case 0b00:
                data[index>>2]&= ~(0b11<< (2*(index&DUBIT_MASK)));
                break;
            
            case 0b01:
                data[index>>2]= (data[index>>2]&~(0b10<< (2*(index&DUBIT_MASK))))|(0b01<< (2*(index&DUBIT_MASK)));
                break;

            case 0b10:
                data[index>>2] = (data[index>>2]&~(0b01<< (2*(index&DUBIT_MASK))))|(0b10<< (2*(index&DUBIT_MASK)));
                break;

            case 0b11:
                data[index>>2]|= 0b11<< (2*(index&DUBIT_MASK));
                break;

            default:
                /* Raise Error*/
                assert(false && "Adding a value to dubitmap that is not two bit representable");
                break;
        }
}

/* Compare two dubitmaps */
bool dubitmap::operator==(const dubitmap& other) const{
    bool this_len_bigger_than_other = (len>other.len);
    uint32_t highest_len = (this_len_bigger_than_other)?len:other.len;
    uint32_t lowest_len = (this_len_bigger_than_other)?other.len:len;
    while(highest_len!=lowest_len){
        if(this_len_bigger_than_other){
            /* this has a greater length */
            if((*this)(highest_len-1))return false;
        }else{
            /* other has a greater length */
            if((other)(highest_len-1))return false;
        }
        highest_len--;
    }
    for(uint32_t i = 0; i < highest_len;i++){
        if((*this)(i)!=other(i)) return false;
    }
    return true;
}

};