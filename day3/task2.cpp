#include <iostream>
#include <fstream>

std::size_t partOne(std::ifstream& input, const short& step) {
    const char TREE = '#';

    std::string line = "";

    input >> line; // to remove the first row

    const std::size_t LINE_SIZE = line.length();
    std::size_t count = 0, lineNumber = 1;
    while (input >> line) {
        count += (line.at((step * lineNumber++) % LINE_SIZE) == TREE);
    }

    return count;
}

std::size_t partTwo(std::ifstream& input) {
    const char TREE = '#';
    
    std::string line = "";
    input >> line; // to remove the first row

    const std::size_t LINE_SIZE = line.length();
    std::size_t count = 0, lineNumber = 1, counterIndex = 1;
    while (input >> line) {
        if (lineNumber % 2) {
            ++lineNumber;
            continue;
        }
        
        count += (line.at((counterIndex++) % LINE_SIZE) == TREE);
        ++lineNumber;
    }

    return count;
}

std::size_t countNumberOfTrees(const std::string& fileName, const short& step, const bool& isTask2) {
    std::ifstream input;
    input.open(fileName);

    if (!input.is_open()) {
        return -1;
    }

    std::size_t count = 0;
    if (isTask2) {
        count = partTwo(input);
    } else {
        count = partOne(input, step);
    }
    
    input.close();
    
    return count;
}

std::size_t countNumberOfTrees(const std::string& fileName, const bool& isTask2) {
    return countNumberOfTrees(fileName, 1, isTask2);
}

int task1() {
    std::string fileName = "C:\\Users\\g.minkov\\Projects\\Personal\\AdventOfCode2020\\day3\\input.txt";
    return countNumberOfTrees(fileName, 3, false);
}

int task2() {
    std::string fileName = "C:\\Users\\g.minkov\\Projects\\Personal\\AdventOfCode2020\\day3\\input.txt";
    return countNumberOfTrees(fileName, 1, false) * countNumberOfTrees(fileName, 3, false)
        * countNumberOfTrees(fileName, 5, false) * countNumberOfTrees(fileName, 7, false)
        * countNumberOfTrees(fileName, true);
}

int main() { 
    std::cout << "Return -> " << task2() << std::endl;

    return 0;
}