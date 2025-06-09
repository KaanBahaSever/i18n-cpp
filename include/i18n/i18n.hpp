#pragma once

#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

class I18n {
public:
    I18n() = default;

    bool loadLocale(const std::string& locale) {
        std::string filePath = "locales/" + locale + "/messages.properties";
        
        // Open the file in binary mode to handle different line endings and encodings
        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            // Skip empty lines and comments
            if (line.empty() || line[0] == '#') {
                continue;
            }
            
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos) {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                
                // Trim whitespace from key and value
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

    std::string translate(const std::string& key) const {
        auto it = translations.find(key);
        if (it != translations.end()) {
            return it->second;
        }
        return ""; // Return empty string if key not found
    }

    std::string interpolate(const std::string& key, const std::unordered_map<std::string, std::string>& values) const {
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

    // Static methods for global access
    static I18n& getInstance() {
        static I18n instance;
        return instance;
    }

    static bool loadGlobalLocale(const std::string& locale) {
        return getInstance().loadLocale(locale);
    }

    static std::string translateGlobal(const std::string& key) {
        return getInstance().translate(key);
    }

    static std::string interpolateGlobal(const std::string& key, const std::unordered_map<std::string, std::string>& values) {
        return getInstance().interpolate(key, values);
    }

private:
    std::unordered_map<std::string, std::string> translations;
};

// Convenient macros using static methods
#define _(key) I18n::translateGlobal(key)
#define _f(key, ...) I18n::interpolateGlobal(key, __VA_ARGS__)

// Alternative macro names for clarity
#define I18N_T(key) _(key)
#define I18N_F(key, ...) _f(key, __VA_ARGS__)