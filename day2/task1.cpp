#include <iostream>
#include <algorithm>
#include <fstream>

struct PasswordMeta
{
    short minOccurrence;
    short maxOccurence;
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
    while(inputData >> data.minOccurrence >> garbage >> data.maxOccurence
        >> data.symbol >> garbage >> data.password) {
            std::size_t currentPassCount = std::count(data.password.begin(), data.password.end(), data.symbol);
            count = (currentPassCount >= data.minOccurrence && currentPassCount <= data.maxOccurence) ? count + 1 : count; 
    }

    inputData.close();
    return count;
}

int main() {
    std::string fileName = "C:\\Users\\g.minkov\\Projects\\Personal\\AdventOfCode2020\\day2\\input.txt";
    std::cout << "Result -> " << countCorrectPass(fileName) << std::endl;

    return 0;
}
