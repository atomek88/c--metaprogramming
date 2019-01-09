#include <iostream>
#include <string>
#include <regex>
#include <tkDecls.h>
#include <cstdlib>
#include <numeric>

int main() {
    std::string My_String = "Here are some numbers: 1.23, 4, 5.6, 7.89";
    // regex search
    std::regex reg ( "(\\d+)\\.(\\d+)" );  // ?$   "((\d)+(\.(\d{1,2}?)"
    // repeat counts specific # of occurences, check before and after
    std::smatch result;
    std::regex_search(My_String, result, reg);
    for (size_t i=0; i< result.size(); ++i){
        std::cout << result[i] << " is before the decimal and " << result[i+1] << " is after the decimal" << std::endl;}
    return 0;
}