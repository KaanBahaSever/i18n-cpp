#pragma once

#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

class I18n {
public:
    // Delete constructors to prevent instantiation
    I18n() = delete;
    I18n(const I18n&) = delete;
    I18n& operator=(const I18n&) = delete;

    static bool loadLocale(const std::string& locale) {
        std::string filePath = "locales/" + locale + "/messages.properties";
        
        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') {
                continue;
            }
            
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos) {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                
                key.erase(0, key.find_first_not_of(" \t\r\n"));
                key.erase(key.find_last_not_of(" \t\r\n") + 1);
                value.erase(0, value.find_first_not_of(" \t\r\n"));
                value.erase(value.find_last_not_of(" \t\r\n") + 1);
                
                translations[key] = value;
            }
        }
        file.close();
        return true;
    }

    static std::string translate(const std::string& key) {
        auto it = translations.find(key);
        if (it != translations.end()) {
            return it->second;
        }
        return "";
    }

    static std::string interpolate(const std::string& key, const std::unordered_map<std::string, std::string>& values) {
        std::string result = translate(key);
        for (const auto& pair : values) {
            std::string placeholder = "{" + pair.first + "}";
            size_t pos = result.find(placeholder);
            while (pos != std::string::npos) {
                result.replace(pos, placeholder.length(), pair.second);
                pos = result.find(placeholder, pos + pair.second.length());
            }
        }
        return result;
    }

private:
    static std::unordered_map<std::string, std::string> translations;
};

// Define the static member variable
std::unordered_map<std::string, std::string> I18n::translations;

// Simplified macros
#define I18N_T(key) I18n::translate(key)
#define I18N_F(key, ...) I18n::interpolate(key, __VA_ARGS__)

#define _t(key) I18n::translate(key)
#define _f(key, ...) I18n::interpolate(key, __VA_ARGS__)