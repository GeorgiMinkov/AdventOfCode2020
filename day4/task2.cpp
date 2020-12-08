#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>
#include <string>
#include <regex>

std::map<std::string, std::string> extractValuesFromPassport(std::string passport) {
    std::replace(passport.begin(), passport.end(), ':', ' ');
            
    std::stringstream ss(passport);
    std::string segment = "", key = "", value = "";
    
    std::map<std::string, std::string> passportValues;

    bool isKey = true;
    while(ss >> segment) {
        if (isKey) {
            key = segment;
        } else {
            passportValues.insert(std::pair<std::string, std::string>(key, segment));
        }

        isKey = !isKey;
    }

    return passportValues;
}

bool validateByr(std::string value) {
    int intValue = std::stoi(value);
    return intValue >= 1920 && intValue <= 2002;
}

bool validateIyr(std::string value) {
    int intValue = std::stoi(value);
    return intValue >= 2010 && intValue <= 2020;
}

bool validateEyr(std::string value) {
    int intValue = std::stoi(value);
    return intValue >= 2020 && intValue <= 2030;
}

bool validateHgt(std::string value) {
    if (!std::regex_match(value, std::regex("^([0-9])+(in|cm)$"))) {
        return false;
    }

    int intValue = std::stoi(value.substr(0, value.length() - 2));
    return value.substr(value.length() - 2) == "in" ?
        intValue >= 59 && intValue <= 76
        : intValue >= 150 && intValue <= 193;
}

bool validateHcl(std::string value) {
    return std::regex_match(value, std::regex("^#([a-z]|[0-9]){6}$"));
}

bool validateEcl(std::string value) {
    // when you try to cheat the system
    // std::string codes = "amb blu brn gry grn hzl oth";
    // return codes.find(value) != std::string::npos;

    std::set<std::string> codes;
    std::stringstream ss("amb blu brn gry grn hzl oth");
    std::string tmp = "";
    while (ss >> tmp) {
        codes.insert(tmp);
    }

    return codes.find(value) != codes.end();
}

bool validatePid(std::string value) {
    return std::regex_match(value, std::regex("^([0-9]){9}$"));;
}

std::map<std::string, bool (*)(std::string)> generateValidationRules() {
    std::map<std::string, bool (*)(std::string)> rules;
    rules.insert(std::pair<std::string, bool(*)(std::string)>("byr", &validateByr));
    rules.insert(std::pair<std::string, bool(*)(std::string)>("iyr", &validateIyr));
    rules.insert(std::pair<std::string, bool(*)(std::string)>("eyr", &validateEyr));
    rules.insert(std::pair<std::string, bool(*)(std::string)>("hgt", &validateHgt));
    rules.insert(std::pair<std::string, bool(*)(std::string)>("hcl", &validateHcl));
    rules.insert(std::pair<std::string, bool(*)(std::string)>("ecl", &validateEcl));
    rules.insert(std::pair<std::string, bool(*)(std::string)>("pid", &validatePid));

    return rules;
}

bool validatePassportValues(std::map<std::string, std::string> passposrtValues) {
    passposrtValues.erase("cid");
    if (passposrtValues.size() != 7) {
        return false;
    }

    std::map<std::string, bool (*)(std::string)> passportRules = generateValidationRules();

    std::map<std::string, std::string>::iterator it = passposrtValues.begin();
    for (; it != passposrtValues.end(); ++it) {
        std::map<std::string, bool (*)(std::string)>::iterator pair
            = passportRules.find(it -> first);

        if(pair != passportRules.end()) {
            if (!((pair -> second)(it -> second))) {
                return false;
            }
        }     
    }
    return true;
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
            
            std::map<std::string, std::string> passportValues = extractValuesFromPassport(passport);
            count += validatePassportValues(passportValues);
            passport = "";
         } else {
            passport += line + " ";
         }
    }
    count += passport != "" ?
        validatePassportValues(extractValuesFromPassport(passport)) : 0;

    input.close();

    return count;
}

int main() {
    std::cout << "Return -> "
        << getCountOfValidPassports("C:\\Users\\g.minkov\\Projects\\Personal\\AdventOfCode2020\\day4\\input.txt")
        << std::endl;

        int i = 0;
    while (i < 10) {
        std::cout << "asd";
        ++i;
    }
    
    return 0;
}