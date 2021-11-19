#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Sorter.h"

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    std::string str, buff;

    if (file.is_open()) {
        while (!file.eof()) {
            file >> buff;
            str += buff + '\n';
        }
    }

    return str;
}

std::string writeFile(const std::string& path, const std::vector<std::string>& data) {
    std::ofstream file(path);
    std::string str;

    if (file.is_open()) {
        for (const auto& line : data) {
            file << line;
            file << "\n";
        }
    }

    return str;
}


std::vector<std::string> sliceFileText(const std::string& data) {
    std::stringstream ss(data);
    std::vector<std::string> result;

    std::string s;
    while (std::getline(ss, s, '\n')) {
        result.push_back(s);
    }

    return result;
}

int main() {
    auto data = sliceFileText(readFile(R"(..\input.txt)"));

    auto sorter = new Sorter();
    auto result = sorter->Sort(data, 3);
    writeFile(R"(..\output.txt)", result);

    return 0;
}
