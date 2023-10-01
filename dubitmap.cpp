#include "dubitmap.hpp"
#include <cstring>
#define MIN_ALLOC_CAP 16
#define DUBIT_MASK 0b11

namespace KOS{

/* Resize array if length = capacity */
bool dubitmap::resize(){
    uint8_t* new_arr = new uint8_t[2*this->capacity];
    if(!new_arr) return false;
    std::memcpy(new_arr, this->data, this->capacity*sizeof(uint8_t));
    delete [] this->data;
    this->data = new_arr;
    this->capacity *= 2;
    return true;
}

/* Creates a dubitmap where (X) => 10 and (-) => 11 all other values raise an error*/
dubitmap::dubitmap(std::string in) : capacity((MIN_ALLOC_CAP+in.length())<<2), len(0){
    this->data = new uint8_t[this->capacity];
    for (const char* src_val = in.c_str();src_val && src_val[len];len++)
    {
        if((len>>2)>=(this->capacity>>2)) resize();
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
                std::cout << "Something Went Wrong\n";
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
        else{std::cout << "Something Went Wrong\n";}
    }
}

/* Free data */
dubitmap::~dubitmap(){
    if(this->data){
        delete [] data;
    }
}

uint32_t dubitmap::length() const{
    return len;
}

/* Assignment Operator (creates a copy and hopefully works)*/
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
dubitmap::dubitmap(): capacity(0), len(0), data(nullptr){}

/* Copy Constructor */
dubitmap::dubitmap(const dubitmap& other){
    len = other.len;
    capacity = other.capacity;
    data = new uint8_t[other.capacity>>2];
    memcpy(this->data, other.data, capacity>>2);
}

uint8_t dubitmap::operator()(uint32_t index) const{
    return ((data[index>>2]>>(2*(index&0b11))) &0b11);
}

/* Prints out all the values of the dubitmap in order with spaces in between*/
std::ostream& operator<<(std::ostream& os, const dubitmap& obj) {        
        for(uint32_t i = 0; i<obj.length(); i++){
            os << (static_cast<uint16_t>(obj(i))) << " "; // static_cast(uint8_t) does not work. Not sure but I think compiler views it as a character
        }
        return os;
    }

};