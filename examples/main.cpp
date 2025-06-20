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

    // Load the English locale using static method
    if (!I18n::loadLocale("en")) {
        std::cerr << "Failed to load English locale." << std::endl;
        return 1;
    }

    // Retrieve a translated string using macro
    std::cout << _t("greeting") << std::endl; // Output: Hello, World!

    // Load the Spanish locale
    if (!I18n::loadLocale("es")) {
        std::cerr << "Failed to load Spanish locale." << std::endl;
        return 1;
    }

    // Retrieve a translated string in Spanish using macro
    std::cout << _t("greeting") << std::endl; // Output: ¡Hola, Mundo!

    // Dynamic string interpolation example using macro
    std::cout << _f("personalized_greeting", {{"name", "Alice"}}) << std::endl; // Output: Hello, Alice!

    return 0;
}