#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

short countParametersInsidePassport(std::string passport) {
    std::replace(passport.begin(), passport.end(), ':', ' ');
            
    std::stringstream ss(passport);
    std::string segment = "";
    
    bool toBeInclude = true;
    short count = 0;
    while(ss >> segment) {
        if (toBeInclude) {
            count += segment != "cid";   
        }

        toBeInclude = !toBeInclude;
    }
    return count;
}

std::size_t getCountOfValidPassports(const std::string& fileName) {
    std::ifstream input;
    input.open(fileName);

    short count = 0;
    std::string passport = "";
    std::string line = "";

    int index = 0;
    while (std::getline(input, line)) {
         if (line == "") {
            passport = passport.substr(0, passport.length() - 1);
            
            count += countParametersInsidePassport(passport) == 7;

            passport = "";
         } else {
            passport += line + " ";
         }
    }
    count += passport != "" ? countParametersInsidePassport(passport) == 7 : 0;

    input.close();

    return count;
}

int main() {
    std::cout << "Return -> "
        << getCountOfValidPassports("C:\\Users\\g.minkov\\Projects\\Personal\\AdventOfCode2020\\day4\\input.txt")
        << std::endl;
    return 0;
}