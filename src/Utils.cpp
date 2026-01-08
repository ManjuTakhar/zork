#include "../include/Utils.h"
#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>

namespace Zork {
    namespace Utils {
        
        int randomInt(int min, int max) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(min, max);
            return dis(gen);
        }
        
        bool randomBool(double probability) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0.0, 1.0);
            return dis(gen) < probability;
        }
        
        bool fileExists(const std::string& filename) {
            std::ifstream file(filename);
            return file.good();
        }
        
        std::string readFile(const std::string& filename) {
            std::ifstream file(filename);
            if (!file.is_open()) {
                return "";
            }
            
            std::string content;
            std::string line;
            while (std::getline(file, line)) {
                content += line + "\n";
            }
            
            file.close();
            return content;
        }
        
        bool writeFile(const std::string& filename, const std::string& content) {
            std::ofstream file(filename);
            if (!file.is_open()) {
                return false;
            }
            
            file << content;
            file.close();
            return true;
        }
        
        void clearScreen() {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
        }
        
        void printSeparator(char ch, int length) {
            for (int i = 0; i < length; ++i) {
                std::cout << ch;
            }
            std::cout << std::endl;
        }
        
        void printCentered(const std::string& text, int width) {
            int padding = (width - text.length()) / 2;
            for (int i = 0; i < padding; ++i) {
                std::cout << " ";
            }
            std::cout << text << std::endl;
        }
        
        std::string getInput(const std::string& prompt) {
            std::string input;
            std::cout << prompt;
            std::getline(std::cin, input);
            return input;
        }
    }
}
