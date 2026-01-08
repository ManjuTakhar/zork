#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

namespace Zork {
    namespace Utils {
        
        // String utilities
        inline std::string toLower(std::string str) {
            std::transform(str.begin(), str.end(), str.begin(),
                         [](unsigned char c){ return std::tolower(c); });
            return str;
        }
        
        inline std::string trim(const std::string& str) {
            size_t first = str.find_first_not_of(' ');
            if (std::string::npos == first) {
                return str;
            }
            size_t last = str.find_last_not_of(' ');
            return str.substr(first, (last - first + 1));
        }
        
        inline std::vector<std::string> split(const std::string& str, char delimiter = ' ') {
            std::vector<std::string> tokens;
            std::string token;
            for (char ch : str) {
                if (ch == delimiter) {
                    if (!token.empty()) {
                        tokens.push_back(token);
                        token.clear();
                    }
                } else {
                    token += ch;
                }
            }
            if (!token.empty()) {
                tokens.push_back(token);
            }
            return tokens;
        }
        
        inline bool contains(const std::string& str, const std::string& substr) {
            return str.find(substr) != std::string::npos;
        }
        
        inline std::string join(const std::vector<std::string>& vec, const std::string& delimiter) {
            std::string result;
            for (size_t i = 0; i < vec.size(); ++i) {
                result += vec[i];
                if (i < vec.size() - 1) {
                    result += delimiter;
                }
            }
            return result;
        }
        
        // Random number generation
        int randomInt(int min, int max);
        bool randomBool(double probability = 0.5);
        
        // File utilities
        bool fileExists(const std::string& filename);
        std::string readFile(const std::string& filename);
        bool writeFile(const std::string& filename, const std::string& content);
        
        // Console utilities
        void clearScreen();
        void printSeparator(char ch = '=', int length = 60);
        void printCentered(const std::string& text, int width = 60);
        std::string getInput(const std::string& prompt = "> ");
        
        // Color codes (ANSI)
        namespace Color {
            const std::string RESET = "\033[0m";
            const std::string RED = "\033[31m";
            const std::string GREEN = "\033[32m";
            const std::string YELLOW = "\033[33m";
            const std::string BLUE = "\033[34m";
            const std::string MAGENTA = "\033[35m";
            const std::string CYAN = "\033[36m";
            const std::string WHITE = "\033[37m";
            const std::string BOLD = "\033[1m";
        }
    }
}

#endif // UTILS_H
