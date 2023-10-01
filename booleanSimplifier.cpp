#include <iostream>
#include "dubitmap.hpp"
#include <vector>
int main(int argc, char** argv){
    uint32_t inputs = 3;
    uint32_t outputs = 2;
    uint32_t minterms[2][8] = {{7}, {1, 2, 3, 4, 5, 6, 7}};
    uint32_t minterms_len[2] = {1, 7};
    std::vector<KOS::dubitmap> inputs_as_dubits;
    for(uint32_t i = 0; i < outputs;i++){
        for (uint32_t j =0 ; j < minterms_len[i]; j++){
            inputs_as_dubits.push_back(KOS::dubitmap(minterms[i][j]));
        }
    }

    for(uint32_t i = 0; i < inputs_as_dubits.size();i++){
        std::cout<<inputs_as_dubits[i]<< std::endl;
    }

    return 0;
}