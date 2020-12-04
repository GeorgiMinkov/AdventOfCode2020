#include <iostream>
#include <set>
#include <fstream>

std::set<int> createInput(std::string fileName) {
    std::ifstream input;
    input.open(fileName);

    std::set<int> inputLine;
    int tmp = 0;
    while (input >> tmp)
    {
        inputLine.insert(tmp);
    }

    input.close();
    return inputLine;
}

int multiplyTwoNumbersWhichSumIsSentinel(const std::set<int>& inputData, const int& sentinel) {
    for (int number : inputData) {
        std::set<int>::iterator elementToCheck = inputData.find(sentinel - number);
        if (elementToCheck != inputData.end()) {
            return *elementToCheck * number;
        }
    }

    return -1;
}

int main () {
    int sentinel = 2020;
    std::cout << "Result -> " << multiplyTwoNumbersWhichSumIsSentinel(
        createInput("C:\\Users\\g.minkov\\Projects\\Personal\\aoc\\day1\\input.txt"), sentinel) << std::endl;
    return 0;
}