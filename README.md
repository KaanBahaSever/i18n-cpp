# C++ i18n Library

## Overview
This project is a simple header-only internationalization (i18n) library written in C++. It allows for easy localization of applications by loading language files stored in a local folder and supports dynamic string interpolation. The library includes convenient macros for easier usage.

**Key Features:**
- **Header-only**: Just include and use - no compilation required
- **Lightweight**: Designed for simple applications where minimal overhead is important
- **Easy integration**: Perfect for small to medium-sized projects
- **File-based localization**: Uses simple .properties files for translations
- **Dynamic interpolation**: Supports runtime string parameter substitution
- **Static API**: Simple static methods for easy access

**Note**: This library is optimized for simple applications. If your project has very large file sizes or complex internationalization needs, you might want to consider more robust solutions like ICU or gettext.

## Project Structure
```
cpp-i18n-lib
├── include
│   └── i18n
│       └── i18n.hpp
├── locales
│   ├── en
│   │   └── messages.properties
│   ├── es
│   │   └── messages.properties
│   └── fr
│       └── messages.properties
├── examples
│   └── main.cpp
├── CMakeLists.txt
└── README.md
```

## Localization Files
The localization files are stored in the `locales` directory, with subdirectories for each language. Each language has a `messages.properties` file containing key-value pairs for translations.

### Example of `locales/en/messages.properties`
```
greeting=Hello, World!
farewell=Goodbye!
personalized_greeting=Welcome to our application {name}.
balance_message=Your balance is {0} dollars.
error_message=Error: {0} occurred while processing your request.
```

### Example of `locales/es/messages.properties`
```
greeting=¡Hola, Mundo!
farewell=¡Adiós!
personalized_greeting=Bienvenido a nuestra aplicación {name}.
balance_message=Su saldo es de {0} dólares.
error_message=Error: {0} ocurrió mientras procesaba su solicitud.
```

### Example of `locales/fr/messages.properties`
```
greeting=Bonjour le monde!
farewell=Au revoir!
personalized_greeting=Bienvenue dans notre application {name}.
balance_message=Votre solde est de {0} dollars.
error_message=Erreur: {0} s'est produite lors du traitement de votre demande.
```

## Building the Library
To build the library, you can use CMake. Follow these steps:

1. Create a build directory:
   ```
   mkdir build
   cd build
   ```

2. Run CMake to configure the project:
   ```
   cmake ..
   ```

3. Build the project:
   ```
   cmake --build .
   ```

## Usage
To use the i18n library in your project, include the header file and load a locale. The library uses static methods for easy access:

```cpp
#include "i18n/i18n.hpp"

int main() {
    // Load locale
    if (!I18n::loadLocale("en")) {
        std::cerr << "Failed to load locale" << std::endl;
        return 1;
    }

    // Using convenient macros
    std::cout << _t("greeting") << std::endl; // Outputs: Hello, World!

    // Or use static methods directly
    std::cout << I18n::translate("greeting") << std::endl;

    return 0;
}
```

## Convenient Macros
The library provides convenient macros for easier usage:

- `_t(key)` - Short macro for translation (equivalent to `I18n::translate()`)
- `_f(key, values)` - Short macro for interpolation (equivalent to `I18n::interpolate()`)
- `I18N_T(key)` - Alternative macro for translation
- `I18N_F(key, values)` - Alternative macro for interpolation

### Example with Macros
```cpp
// Load locale first
I18n::loadLocale("en");

// Simple translation
std::cout << _t("greeting") << std::endl;

// Interpolation with macros
std::cout << _f("personalized_greeting", {{"name", "John"}}) << std::endl;
```

## Dynamic String Interpolation
The library supports dynamic string interpolation. You can use placeholders in your translation strings and provide values to replace them at runtime.

### Named Placeholders
Use `{name}` format for named placeholders:

```cpp
// Load locale first
I18n::loadLocale("en");

// Using macro with named placeholder
std::cout << _f("personalized_greeting", {{"name", "John"}}) << std::endl; 
// Outputs: Welcome to our application John.

// Or use static method directly
std::cout << I18n::interpolate("personalized_greeting", {{"name", "Alice"}}) << std::endl;
```

### Numbered Placeholders
Use `{0}`, `{1}`, etc. for numbered placeholders:

```cpp
// For messages like "Your balance is {0} dollars."
std::cout << _f("balance_message", {{"0", "150.50"}}) << std::endl;
// Outputs: Your balance is 150.50 dollars.

// For error messages like "Error: {0} occurred while processing your request."
std::cout << _f("error_message", {{"0", "Network timeout"}}) << std::endl;
// Outputs: Error: Network timeout occurred while processing your request.
```

## API Reference

### Static Methods
- `bool I18n::loadLocale(const std::string& locale)` - Load a locale from the locales directory
- `std::string I18n::translate(const std::string& key)` - Get translated string for a key
- `std::string I18n::interpolate(const std::string& key, const std::unordered_map<std::string, std::string>& values)` - Get translated string with interpolated values

### Macros
- `I18N_T(key)` or `_t(key)` - Translate a key
- `I18N_F(key, values)` or `_f(key, values)` - Translate and interpolate a key

## License
This project is licensed under the MIT License. See the LICENSE file for more details.
