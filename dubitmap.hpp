#ifndef _DUBITMAP_H_
#define _DUBITMAP_H_
#include <stdint.h>
#include <string>
#include <iostream>

namespace KOS{
    
    struct uint2_t{
        uint8_t val;
        uint2_t() : val(0){};
        uint2_t(uint8_t in) : val(in&0b11){};
        uint2_t(uint16_t in) : val(in&0b11){};
        uint2_t(uint32_t in) : val(in&0b11){};
        uint2_t(int32_t in) : val(in&0b11){};
        uint2_t(int8_t in) : val(in&0b11){};
        uint2_t(int16_t in) : val(in&0b11){};
        ~uint2_t(){};
        uint2_t operator+(const uint2_t& a){return (this->val+a.val)&0b11;}
        uint2_t& operator=(const uint2_t& other){val=other.val&0b11; return *this;};
        uint2_t& operator+=(const uint2_t& a){this->val = (this->val+a.val)&0b11; return *this;};
        uint2_t operator-(const uint2_t& a){return (this->val-a.val)&0b11;}
        uint2_t& operator-=(const uint2_t& a){this->val = (this->val-a.val)&0b11; return *this;};
        uint2_t operator<<(const uint8_t& a){return (this->val<<a)&0b11;}
        uint2_t operator<<(const uint2_t& a){return (this->val<<a.val)&0b11;}
        uint2_t& operator<<=(const uint8_t& a){this->val = (this->val<<a)&0b11; return *this;}
        uint2_t& operator<<=(const uint2_t& a){this->val = (this->val<<a.val)&0b11; return *this;}
        uint2_t operator>>(const uint8_t& a){return (this->val>>a)&0b11;}
        uint2_t operator>>(const uint2_t& a){return (this->val>>a.val)&0b11;}
        uint2_t& operator>>=(const uint8_t& a){this->val = (this->val>>a)&0b11; return *this;}
        uint2_t& operator>>=(const uint2_t& a){this->val = (this->val>>a.val)&0b11; return *this;}
        bool operator&&(const uint2_t& a){return this->val&&a.val;};
        bool operator||(const uint2_t& a){return this->val||a.val;};
        bool operator==(const uint2_t& a){return this->val==a.val;};
        bool operator!=(const uint2_t& a){return this->val!=a.val;};
        bool operator<=(const uint2_t& a){return this->val<=a.val;};
        bool operator>=(const uint2_t& a){return this->val>=a.val;};
        bool operator<(const uint2_t& a){return this->val<a.val;};
        bool operator>(const uint2_t& a){return this->val>a.val;};
        uint2_t operator&(const uint2_t& a){return this->val&a.val;};
        uint2_t& operator&=(const uint2_t& a){this->val = this->val&a.val; return *this;};
        uint2_t operator|(const uint2_t& a){return this->val|a.val;};
        uint2_t& operator|=(const uint2_t& a){this->val = this->val|a.val; return *this;};
        friend std::ostream& operator<<(std::ostream& os, const uint2_t& a){os << static_cast<char>(a.val+'0'); return os;};
        explicit operator bool() const{return val!=0;};
    };

    class dubitmap
    {
        private:
            /* data */
            uint8_t* data;
            uint32_t len; /* in dubits */
            uint32_t capacity; /* in dubits (divisible by 4) */
            bool resize(uint32_t new_cap);
        public:

            dubitmap(void);
            dubitmap(const dubitmap& other);
            ~dubitmap();
            dubitmap& operator=(const dubitmap& other);

            /* creates a dubitmap out of a 32 bit value (32 bits -> 32 dubits)*/
            dubitmap(uint32_t in);

            /* creates a dubitmap out of a 16 bit value (16 bits->16 dubits)*/
            dubitmap(uint16_t in);

            /* Creates a dubitmap where (X) => 10 and (-) => 11 all other values raise an error*/
            dubitmap(std::string in);

            /* Creates a dubitmap where characters (index2) => 10 and (index3) => 11 all other values raise an error*/
            dubitmap(std::string in, char index2, char index3);

            /* Print all the bytes in the dubitmap */
            friend std::ostream& operator<<(std::ostream& os, const dubitmap& obj);

            /* returns length of dubitmap (in dubits) */
            uint32_t length() const;

            /* Appends dubit to the dubitmap*/
            void push_back_dubit(uint2_t new_val);

            /* See the value of a dubit */
            uint2_t operator()(uint32_t index) const;     

            /* Appends a dubitmap */
            dubitmap& operator+=(dubitmap& other);

            /* Appends a single dubit */
            dubitmap& operator+=(uint2_t new_val);

            /* Sets index to val */
            void change_dubit(uint32_t index, uint2_t new_val);

            /* Compare two dubitmaps*/
            bool operator==(const dubitmap& other) const;

    };
};
#endif