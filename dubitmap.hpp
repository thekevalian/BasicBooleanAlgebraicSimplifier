#ifndef _DUBITMAP_H_
#define _DUBITMAP_H_
#include <stdint.h>
#include <string>
#include <iostream>

namespace KOS{
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

            /* Creates a dubitmap where (X) => 10 and (-) => 11 all other values raise an error*/
            dubitmap(std::string in);

            /* Creates a dubitmap where characters (index2) => 10 and (index3) => 11 all other values raise an error*/
            dubitmap(std::string in, char index2, char index3);

            /* Print all the bytes in the dubitmap */
            friend std::ostream& operator<<(std::ostream& os, const dubitmap& obj);

            /* returns length of dubitmap (in dubits) */
            uint32_t length() const;

            /* Appends dubit to the dubitmap*/
            void push_back_dubit(uint8_t new_val);

            /* See the value of a dubit */
            uint8_t operator()(uint32_t index) const;     

            /* Appends a dubitmap */
            dubitmap& operator+=(dubitmap& other);

            /* Appends a dubit */
            dubitmap& operator+=(uint8_t new_val);

            /* Sets index to val */
            void change_dubit(uint32_t index, uint8_t val);

            /* Compare two dubitmaps*/
            bool operator==(const dubitmap& other) const;

    };
};
#endif