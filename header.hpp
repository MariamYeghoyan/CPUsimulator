#ifndef CPU
#define CPU

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>

std::unordered_map<std::string, int> labels;

std::string ReadFile(const std::string& name) {
    std::ifstream file(name);
    if (!file.is_open()) {
        std::cout << "Error while opening the text file.";
        return "-1";
    } 
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}
std::vector<std::string> ReadByLines(const std::string &content) {
    std::vector<std::string> lines;
    std::string::size_type start = 0;
    std::string::size_type pos = content.find('\n', start);

    while (pos != std::string::npos) {
        lines.push_back(content.substr(start, pos - start));
        start = pos + 1;
        pos = content.find('\n', start);
    }
    lines.push_back(content.substr(start));
    return lines;
}

class Registers {
    public:
    int Ayb = 0;
    int Ben = 0;
    int Gim = 0;
    int Da = 0;
    int Ech = 0;
    int Za = 0;

    int memory[32] = {0}; 
};

class Memory {
    public:
    std::vector<std::string> ram;
    const int MEMORY_SIZE = 32;
    void initializememory() {
        ram = std::vector<std::string>(MEMORY_SIZE, "0");
    }
    void dump_memory() {
        for (int i = 0; i < MEMORY_SIZE; ++i) {
            std::cout << "[" << i << "]: " << ram[i] << std::endl;
        }
    }
    void LoadAsmToRam(std::vector<std::string>& program) {
        int i= 0;
        for (std::string instruction : program) {
            ram[i++] = instruction;
        }
    }
};
static Memory ram;
static Registers registers;

void mov(std::string& operand1, std::string& operand2, int count) {

    if (operand2[0] == '[' && operand2[operand2.size() - 1] == ']') {
        int address = std::stoi(operand2.substr(1, operand2.size() - 2));
        if (address < count) {
            throw std::out_of_range("Don't have access on that memory! ");
        }
        else if (operand1 == "Ayb") {
            registers.Ayb = std::stoi(ram.ram[address]);
        } else if (operand1 == "Ben") {
            registers.Ben = std::stoi(ram.ram[address]);
        } else if (operand1 == "Gim") {
            registers.Gim = std::stoi(ram.ram[address]);
        } else if (operand1 == "Da") {
            registers.Da = std::stoi(ram.ram[address]);
        } else if (operand1 == "Ech") {
            registers.Ech = std::stoi(ram.ram[address]);
        } else if (operand1 == "Za") {
            registers.Za = std::stoi(ram.ram[address]);
        }
    } 
    else if (operand1[0] == '[' && operand1[operand1.size() - 1] == ']') {
        int address = std::stoi(operand1.substr(1, operand1.size() - 2));
        if (address < count) {
            throw std::out_of_range("Don't have access on that memory! ");
        }
        else if (operand2 == "Ayb") {
            ram.ram[address] = std::to_string(registers.Ayb);
        } else if (operand2 == "Ben") {
            ram.ram[address] = std::to_string(registers.Ben);
        } else if (operand1 == "Gim") {
            ram.ram[address] = std::to_string(registers.Gim);
        } else if (operand1 == "Da") {
            ram.ram[address] = std::to_string(registers.Da);
        } else if (operand1 == "Ech") {
            ram.ram[address] = std::to_string(registers.Ech);
        } else if (operand1 == "Za") {
            ram.ram[address] = std::to_string(registers.Za);
        }
    }
    else {
        int val;
        if (operand2[0] == '[') {
            int address = std::stoi(operand2.substr(1, operand2.size() - 1));
            val = std::stoi(ram.ram[address]);
        } else {
            try {
                val = std::stoi(operand2);
            } catch (std::invalid_argument&) {
                if (operand2 == "Ayb") {
                    val = registers.Ayb;
                } else if (operand2 == "Ben") {
                    val = registers.Ben;
                } else if (operand2 == "Gim") {
                    val = registers.Gim;
                } else if (operand2 == "Da") {
                    val = registers.Da;
                } else if (operand2 == "Ech") {
                    val = registers.Ech;
                } else if (operand2 == "Za") {
                    val = registers.Za;
                } else {
                    std::cout << "Invalid operand2: " << operand2 << std::endl;
                    return;
                }
            }
        }
        if (operand1[0] == '[' && operand1[operand1.size() - 1] == ']') {
            int address = std::stoi(operand1.substr(1, operand1.size() - 2));
            if (address < count) {
                throw std::out_of_range("Don't have access on that memory! ");
            }
            ram.ram[address] = std::to_string(val);
        } else {
            if (operand1 == "Ayb") {
                registers.Ayb = val;
            } else if (operand1 == "Ben") {
                registers.Ben = val;
            } else if (operand1 == "Gim") {
                registers.Gim = val;
            } else if (operand1 == "Da") {
                registers.Da = val;
            } else if (operand1 == "Ech") {
                registers.Ech = val;
            } else if (operand1 == "Za") {
                registers.Za = val;
            } else {
                std::cout << "Invalid operand1: " << operand1 << std::endl;
            }
        }
    }
}

int getRegValue(std::string& regname) {
    if (regname[0] == '[' && regname[regname.size() - 1] == ']') {
        int adr = std::stoi(regname.substr(1, regname.size() - 2));
        return registers.memory[adr];
    }
    else if (regname == "Ayb") {
        return registers.Ayb;
    }
    else if (regname == "Ben") {
        return registers.Ben;
    }
    else if (regname == "Gim") {
        return registers.Gim;
    }
    else if (regname == "Da") {
        return registers.Da;
    }
    else if (regname == "Ech") {
        return registers.Ech;
    }
    else if (regname == "Za") {
        return registers.Za;
    }
    return -1;
}

void add(int value) {
    registers.Ayb += value;
}

void add(std::string& destination, std::string&source) {
    int sourceVal = getRegValue(source);
    if (sourceVal == -1) {
        try {
            sourceVal = std::stoi(source);
        } catch (std::invalid_argument&) {
            std::cout << "Invalid operand: " << source << std::endl;
            return;
        }
    }
    if (destination[0] == '[' && destination[destination.size() - 1] == ']') {
        int memoryAdr = std::stoi(destination.substr(1, destination.size() - 2));
        int destVal = std::stoi(ram.ram[memoryAdr]);
        destVal += sourceVal;
        ram.ram[memoryAdr] = std::to_string(destVal);
    } 
    else if (source[0] == '[' && source[source.size() - 1] == ']') {
        int memoryAdr = std::stoi(source.substr(1, source.size() - 2));
        int value = std::stoi(ram.ram[memoryAdr]);
        if (destination == "Ayb") {
            registers.Ayb += value;
        }
        else if (destination == "Ben") {
            registers.Ben += value;
        }
        else if (destination == "Gim") {
            registers.Gim += value;
        }
        else if (destination == "Da") {
            registers.Da += value;
        }
        else if (destination == "Ech") {
            registers.Ech += value;
        }
        else if (destination == "Za") {
            registers.Za += value;
        }
    }
    else {
        if (destination == "Ayb") {
            registers.Ayb += sourceVal;
        }
        else if (destination == "Ben") {
            registers.Ben += sourceVal;
        }
        else if (destination == "Gim") {
            registers.Gim += sourceVal;
        }
        else if (destination == "Da") {
            registers.Da += sourceVal;
        }
        else if (destination == "Ech") {
            registers.Ech += sourceVal;
        }
        else if (destination == "Za") {
            registers.Za += sourceVal;
        }
    }
}

void sub(int value) {
    registers.Ayb -= value;
}

void sub(std::string& destination, std::string&source) {
    int sourceVal = getRegValue(source);
    if (sourceVal == -1) {
        try {
            sourceVal = std::stoi(source);
        } catch (std::invalid_argument&) {
            std::cout << "Invalid operand: " << source << std::endl;
            return;
        }
    }
    if (destination[0] == '[' && destination[destination.size() - 1] == ']') {
        int memoryAdr = std::stoi(destination.substr(1, destination.size() - 2));
        int destVal = std::stoi(ram.ram[memoryAdr]);
        destVal -= sourceVal;
        ram.ram[memoryAdr] = std::to_string(destVal);
    } 
    else if (source[0] == '[' && source[source.size() - 1] == ']') {
        int memoryAdr = std::stoi(source.substr(1, source.size() - 2));
        int value = std::stoi(ram.ram[memoryAdr]);
        if (destination == "Ayb") {
            registers.Ayb -= value;
        }
        else if (destination == "Ben") {
            registers.Ben -= value;
        }
        else if (destination == "Gim") {
            registers.Gim -= value;
        }
        else if (destination == "Da") {
            registers.Da -= value;
        }
        else if (destination == "Ech") {
            registers.Ech -= value;
        }
        else if (destination == "Za") {
            registers.Za -= value;
        }
    }
    else {
        if (destination == "Ayb") {
            registers.Ayb -= sourceVal;
        }
        else if (destination == "Ben") {
            registers.Ben -= sourceVal;
        }
        else if (destination == "Gim") {
            registers.Gim -= sourceVal;
        }
        else if (destination == "Da") {
            registers.Da -= sourceVal;
        }
        else if (destination == "Ech") {
            registers.Ech -= sourceVal;
        }
        else if (destination == "Za") {
            registers.Za -= sourceVal;
        }
    }
}

void mul(int value) {
    registers.Ayb *= value;
}

void mul(std::string& operand1, std::string& operand2) {
    int op2Val = getRegValue(operand2);
    if (op2Val == -1) {
        try {
            op2Val = std::stoi(operand2);
        }
        catch (std::invalid_argument&) {
            std::cout << "Invalid argument: " << operand2 << std::endl;
            return;
        }
    }

    if (operand1[0] == '[' && operand1[operand1.size() - 1] == ']') {
        int memoryAdr = std::stoi(operand1.substr(1, operand1.size() - 2));
        int op1Val = std::stoi(ram.ram[memoryAdr]);
        op1Val *= op2Val;
        ram.ram[memoryAdr] = std::to_string(op1Val);
    }
    else if (operand2[0] == '[' && operand2[operand2.size() - 1 == ']']) {
        int memoryAdr = std::stoi(operand2.substr(1, operand2.size() - 2));
        int value = std::stoi(ram.ram[memoryAdr]);
        if (operand1 == "Ayb") {
            registers.Ayb *= value;
        }
        else if (operand1 == "Ben") {
            registers.Ben *= value;
        }
        else if (operand1 == "Gim") {
            registers.Gim *= value;
        }
        else if (operand1 == "Da") {
            registers.Da *= value;
        }
        else if (operand1 == "Ech") {
            registers.Ech *= value;
        }
        else if (operand1 == "Za") {
            registers.Za *= value;
        }
    }
    else {
        if (operand1 == "Ayb") {
            registers.Ayb *= op2Val;
        }
        else if (operand1 == "Ben") {
            registers.Ben *= op2Val;
        }
        else if (operand1 == "Gim") {
            registers.Gim *= op2Val;
        }
        else if (operand1 == "Da") {
            registers.Da *= op2Val;
        }
        else if (operand1 == "Ech") {
            registers.Ech *= op2Val;
        }
        else if (operand1 == "Za") {
            registers.Za *= op2Val;
        }
    }
}

void div(std::string& destination, std::string&source) {
    int sourceVal = getRegValue(source);
    if (sourceVal == -1) {
        try {
            sourceVal = std::stoi(source);
        } catch (std::invalid_argument&) {
            std::cout << "Invalid operand: " << source << std::endl;
            return;
        }
    }
    if (destination[0] == '[' && destination[destination.size() - 1] == ']') {
        int memoryAdr = std::stoi(destination.substr(1, destination.size() - 2));
        int destVal = std::stoi(ram.ram[memoryAdr]);
        destVal /= sourceVal;
        ram.ram[memoryAdr] = std::to_string(destVal);
    } 
    else if (source[0] == '[' && source[source.size() - 1] == ']') {
        int memoryAdr = std::stoi(source.substr(1, source.size() - 2));
        int value = std::stoi(ram.ram[memoryAdr]);
        if (destination == "Ayb") {
            registers.Ayb /= value;
        }
        else if (destination == "Ben") {
            registers.Ben /= value;
        }
        else if (destination == "Gim") {
            registers.Gim /= value;
        }
        else if (destination == "Da") {
            registers.Da /= value;
        }
        else if (destination == "Ech") {
            registers.Ech /= value;
        }
        else if (destination == "Za") {
            registers.Za /= value;
        }
    }
    else {
        if (destination == "Ayb") {
            registers.Ayb /= sourceVal;
        }
        else if (destination == "Ben") {
            registers.Ben /= sourceVal;
        }
        else if (destination == "Gim") {
            registers.Gim /= sourceVal;
        }
        else if (destination == "Da") {
            registers.Da /= sourceVal;
        }
        else if (destination == "Ech") {
            registers.Ech /= sourceVal;
        }
        else if (destination == "Za") {
            registers.Za /= sourceVal;
        }
    }
}

void And(std::string& destination, std::string&source) {
    int sourceVal = getRegValue(source);
    if (sourceVal == -1) {
        try {
            sourceVal = std::stoi(source);
        } catch (std::invalid_argument&) {
            std::cout << "Invalid operand: " << source << std::endl;
            return;
        }
    }
    if (destination[0] == '[' && destination[destination.size() - 1] == ']') {
        int memoryAdr = std::stoi(destination.substr(1, destination.size() - 2));
        int destVal = std::stoi(ram.ram[memoryAdr]);
        destVal &= sourceVal;
        ram.ram[memoryAdr] = std::to_string(destVal);
    } 
    else if (source[0] == '[' && source[source.size() - 1] == ']') {
        int memoryAdr = std::stoi(source.substr(1, source.size() - 2));
        int value = std::stoi(ram.ram[memoryAdr]);
        if (destination == "Ayb") {
            registers.Ayb &= value;
        }
        else if (destination == "Ben") {
            registers.Ben &= value;
        }
        else if (destination == "Gim") {
            registers.Gim &= value;
        }
        else if (destination == "Da") {
            registers.Da &= value;
        }
        else if (destination == "Ech") {
            registers.Ech &= value;
        }
        else if (destination == "Za") {
            registers.Za &= value;
        }
    }
    else {
        if (destination == "Ayb") {
            registers.Ayb &= sourceVal;
        }
        else if (destination == "Ben") {
            registers.Ben &= sourceVal;
        }
        else if (destination == "Gim") {
            registers.Gim &= sourceVal;
        }
        else if (destination == "Da") {
            registers.Da &= sourceVal;
        }
        else if (destination == "Ech") {
            registers.Ech &= sourceVal;
        }
        else if (destination == "Za") {
            registers.Za &= sourceVal;
        }
    }
}

void Or(std::string& destination, std::string&source) {
    int sourceVal = getRegValue(source);
    if (sourceVal == -1) {
        try {
            sourceVal = std::stoi(source);
        } catch (std::invalid_argument&) {
            std::cout << "Invalid operand: " << source << std::endl;
            return;
        }
    }
    if (destination[0] == '[' && destination[destination.size() - 1] == ']') {
        int memoryAdr = std::stoi(destination.substr(1, destination.size() - 2));
        int destVal = std::stoi(ram.ram[memoryAdr]);
        destVal |= sourceVal;
        ram.ram[memoryAdr] = std::to_string(destVal);
    } 
    else if (source[0] == '[' && source[source.size() - 1] == ']') {
        int memoryAdr = std::stoi(source.substr(1, source.size() - 2));
        int value = std::stoi(ram.ram[memoryAdr]);
        if (destination == "Ayb") {
            registers.Ayb |= value;
        }
        else if (destination == "Ben") {
            registers.Ben |= value;
        }
        else if (destination == "Gim") {
            registers.Gim |= value;
        }
        else if (destination == "Da") {
            registers.Da |= value;
        }
        else if (destination == "Ech") {
            registers.Ech |= value;
        }
        else if (destination == "Za") {
            registers.Za |= value;
        }
    }
    else {
        if (destination == "Ayb") {
            registers.Ayb |= sourceVal;
        }
        else if (destination == "Ben") {
            registers.Ben |= sourceVal;
        }
        else if (destination == "Gim") {
            registers.Gim |= sourceVal;
        }
        else if (destination == "Da") {
            registers.Da |= sourceVal;
        }
        else if (destination == "Ech") {
            registers.Ech |= sourceVal;
        }
        else if (destination == "Za") {
            registers.Za |= sourceVal;
        }
    }
}

void Not(std::string& destination) {
    int destinationVal = getRegValue(destination);

    if (destinationVal == -1) {
        std::cout << "Invalid operand: " << destination << std::endl;
        return;
    }

    int result = ~destinationVal;

    if (destination[0] == '[' && destination[destination.size() - 1] == ']') {
        int memoryAdr = std::stoi(destination.substr(1, destination.size() - 2));
        ram.ram[memoryAdr] = std::to_string(result);
    } else {
        if (destination == "Ayb") {
            registers.Ayb = result;
        } else if (destination == "Ben") {
            registers.Ben = result;
        } else if (destination == "Gim") {
            registers.Gim = result;
        } else if (destination == "Da") {
            registers.Da = result;
        } else if (destination == "Ech") {
            registers.Ech = result;
        } else if (destination == "Za") {
            registers.Za = result;
        } else {
            std::cout << "Invalid destination: " << destination << std::endl;
        }
    }
}

std::map<std::string, int> lable(std::vector<std::string>& lines) {
    std::map<std::string, int> labelMap;
    int lineNumber = 0;
    size_t colonPos;

    for (auto& line : lines) {
    
        colonPos = line.find(':');

        if (colonPos != std::string::npos) {
            std::string label = line.substr(0, colonPos);
            labelMap[label] = lineNumber;
            line = line.substr(colonPos + 1);
        }

        lineNumber++;
    }

    return labelMap;
}
void flag(int val)
    {
        int x = 0;
        if(((val >> 15) & 1) == 1){ 
            x = (int) (x | 1);
        } 
        if(val == 0){ 
            x = (int) (x | 2);
        } 
        if(val > 255){ 
            x = (int) (x | 4);
        }
        registers.Za = x;
    }
void cmp(int val1, int val2) {
    int res = val1 - val2;
    registers.Da = res;
    flag(res);
}

void cmp(std::string& operand1, std::string& operand2) {
    int val1 = getRegValue(operand1);
    int val2 = getRegValue(operand2);

    if (val1 == -1) {
        val1 = std::stoi(operand1); 
    }
    if (val2 == -1) {
        val2 = std::stoi(operand2); 
    }
    cmp(val1, val2);
}


void getlineinstructions(std::vector<std::string>& lines, Memory& ram) {
    int line_num = 0;
    std::map<std::string, int> lble = lable(lines);
    int count = lines.size();
    for (int i = 0; i < lines.size(); ++i) {
            std::istringstream iss(lines[i]);
            std::string instruction;
            std::string operand1, operand2;
            int value;
            iss >> instruction;

            if (iss >> operand1) {
                operand1.erase(std::remove(operand1.begin(), operand1.end(), ','), operand1.end());
            }
            else {
                operand1 = "";
            }
            if (iss >> operand2) {
                operand2.erase(std::remove(operand2.begin(), operand2.end(), ','), operand2.end());
            }
            else {
                operand2 = "";
            }
            if (instruction == "mov") {
                mov(operand1, operand2, count);
            }
            else if (instruction == "add") {
                add(operand1, operand2); 
            } 
            else if (instruction == "sub") {
                sub(operand1, operand2);
            }
            else if (instruction == "mul") {
                mul(operand1, operand2);
            }
            else if (instruction == "div") {
                div(operand1, operand2);
            }
            else if (instruction == "and") {
                And(operand1, operand2);
            }
            else if (instruction == "or") {
                Or(operand1, operand2);
            }
            else if (instruction == "not") {
                Not(operand1);
            } 
            else if (instruction == "jmp") {
                i = lble[operand1] - 1;
            }
            else if (instruction == "je") {
                if (registers.Da == 0) {
                    i = lble[operand1] - 1;
                }
            } 
            else if(instruction == "cmp") {
                cmp(operand1, operand2);
            }
            else if (instruction == "jg") {
                if (registers.Da > 0) {
                    i = lble[operand1] - 1;
                }
            }
            else if (instruction == "jl") {
                if (registers.Da < 0) {
                    i = lble[operand1] - 1;
                }
            }
    }
}

#endif