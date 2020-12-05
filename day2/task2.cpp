#include <iostream>
#include <algorithm>
#include <fstream>

struct PasswordMeta
{
    short firstIndex;
    short secondIndex;
    char symbol;
    std::string password;
};

std::size_t countCorrectPass(const std::string& fileName ) {
    std::ifstream inputData;
    inputData.open(fileName);

    if (!inputData.is_open()) {
        return -1;
    }

    std::size_t count = 0;

    PasswordMeta data;
    char garbage = ' ';
    while(inputData >> data.firstIndex >> garbage >> data.secondIndex
        >> data.symbol >> garbage >> data.password) {
            short indexCoeff = (data.password.at(data.firstIndex - 1) == data.symbol)
                + (data.password.at(data.secondIndex - 1) == data.symbol);
            count += (indexCoeff == 1); 
    }

    inputData.close();
    return count;
}

int main() {
    std::string fileName = "C:\\Users\\g.minkov\\Projects\\Personal\\AdventOfCode2020\\day2\\input.txt";
    std::cout << "Result -> " << countCorrectPass(fileName) << std::endl;

    return 0;
}
