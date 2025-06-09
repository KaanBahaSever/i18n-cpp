#include <iostream>
#include <i18n/i18n.hpp>

#include <iostream>
#include <locale>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#endif

void setupUTF8Console() {
#ifdef _WIN32
    // Windows-specific setup
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    // Enable ANSI escape sequence support (Windows 10+)
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    
    // Alternative: Use _setmode for file descriptors
    // _setmode(_fileno(stdout), _O_U8TEXT);
#else
    // Unix/Linux/macOS - usually UTF-8 by default
    // Set locale to UTF-8
    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());
#endif
}

int main() {
    //set console output to UTF-8
    setupUTF8Console();

    // Create an instance of the I18n class
    I18n i18n;

    // Load the English locale
    if (!i18n.loadLocale("en")) {
        std::cerr << "Failed to load English locale." << std::endl;
        return 1;
    }

    // Retrieve a translated string
    std::string greeting = i18n.translate("greeting");
    std::cout << greeting << std::endl; // Output: Hello, World!

    // Load the Spanish locale
    if (!i18n.loadLocale("es")) {
        std::cerr << "Failed to load Spanish locale." << std::endl;
        return 1;
    }

    // Retrieve a translated string in Spanish
    std::string greetingEs = i18n.translate("greeting");
    std::cout << greetingEs << std::endl; // Output: ¡Hola, Mundo!

    // Dynamic string interpolation example
    std::string name = "Alice";
    std::unordered_map<std::string, std::string> params = { {"name", name} };
    std::string personalizedGreeting = i18n.interpolate("personalized_greeting", params);
    std::cout << personalizedGreeting << std::endl; // Output: Hello, Alice!

    return 0;
}