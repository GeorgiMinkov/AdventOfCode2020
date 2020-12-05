#include <iostream>
#include <fstream>

std::size_t countNumberOfTrees(const std::string& fileName, const short& step) {
    std::ifstream input;
    input.open(fileName);

    if (!input.is_open()) {
        return -1;
    }

    const char TREE = '#';
    std::string line = "";
    std::size_t count = 0, lineNumber = 1;

    input >> line; // to remove the first row
    const std::size_t LINE_SIZE = line.length();
    while (input >> line) {
        count += (line.at((step * lineNumber++) % LINE_SIZE) == TREE);
    }
    
    input.close();
    
    return count;
}

int main() {
    std::string fileName = "C:\\Users\\g.minkov\\Projects\\Personal\\AdventOfCode2020\\day3\\input.txt";
    std::cout << "Return -> " << countNumberOfTrees(fileName, 3);
    return 0;
}