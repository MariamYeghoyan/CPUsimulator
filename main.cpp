#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include "header.hpp"

int main() {
    try {
        std::string name = "AssemblyCode.txt";
        std::string content = ReadFile(name);
        std::vector<std::string> lines = ReadByLines(content);

        ram.initializememory();
        ram.LoadAsmToRam(lines);

        std::cout << "Value stored in Ayb is: " << registers.Ayb << std::endl;
        std::cout << "Value stored in Ben is: " << registers.Ben<< std::endl;
        std::cout << "Value stored in Gim is: " << registers.Gim << std::endl;
        std::cout << "Value stored in Da is: " << registers.Da << std::endl;
        std::cout << "Value stored in Ech is: " << registers.Ech << std::endl;
        std::cout << "Value stored in Za is: " << registers.Za << std::endl;
        std::cout << "Memory updated: " << std::endl;

        ram.dump_memory(); 
        getlineinstructions(lines, ram);
        std::cout << std::endl;
        std::cout << "Value stored in Ayb is: " << registers.Ayb << std::endl;
        std::cout << "Value stored in Ben is: " << registers.Ben<< std::endl;
        std::cout << "Value stored in Gim is: " << registers.Gim << std::endl;
        std::cout << "Value stored in Da is: " << registers.Da << std::endl;
        std::cout << "Value stored in Ech is: " << registers.Ech << std::endl;
        std::cout << "Value stored in Za is: " << registers.Za << std::endl;
        }
        catch(const std::out_of_range& e)
        {
            std::cerr << e.what() << '\n';
        }
}