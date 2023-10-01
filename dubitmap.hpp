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
            uint32_t len;
            uint32_t capacity;
            bool resize();
        public:
            dubitmap(const dubitmap& other);
            dubitmap(std::string in);
            dubitmap(std::string in, char index2, char index3);
            dubitmap();
            ~dubitmap();
            friend std::ostream& operator<<(std::ostream& os, const dubitmap& obj);
            uint32_t length() const;
            uint8_t operator()(uint32_t index) const;            
            dubitmap& operator=(const dubitmap& other);
    };
};
#endif