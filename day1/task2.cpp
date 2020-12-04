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

int multiplyThreeNumbersWhichSumIs2020() {
    const std::string FILE_NAME = "C:\\Users\\g.minkov\\Projects\\Personal\\aoc\\day1\\input.txt";
    
    std::set<int> inputData = createInput(FILE_NAME);
    for (int number : inputData) {
        std::set<int> duplicate(inputData);
        duplicate.erase(number);

        int sentinel = 2020 - number;

        int result = multiplyTwoNumbersWhichSumIsSentinel(duplicate, sentinel);
        if (result != -1) {
            return result * number;
        }
    }

    return -1;
}

int main () {
    std::cout << "Result -> " << multiplyThreeNumbersWhichSumIs2020() << std::endl;
    return 0;
}