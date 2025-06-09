# C++ I18n Library

## Overview
This project is a simple header-only internationalization (i18n) library written in C++. It allows for easy localization of applications by loading language files stored in a local folder and supports dynamic string interpolation. The library now includes convenient macros for easier usage.

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
greeting=Hello
farewell=Goodbye
```

### Example of `locales/es/messages.properties`
```
greeting=Hola
farewell=Adiós
```

### Example of `locales/fr/messages.properties`
```
greeting=Bonjour
farewell=Au revoir
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
To use the i18n library in your project, include the header file and load a locale. The library uses a singleton pattern for global access:

```cpp
#include "i18n/i18n.hpp"

int main() {
    // Load locale globally
    I18n::loadGlobalLocale("en");

    // Using convenient macros
    std::cout << _("greeting") << std::endl; // Outputs: Hello

    // Or use static methods directly
    std::cout << I18n::translateGlobal("greeting") << std::endl;

    return 0;
}
```

## Convenient Macros
The library provides convenient macros for easier usage:

- `_(key)` - Short macro for translation (equivalent to `translate()`)
- `_f(key, values)` - Short macro for interpolation (equivalent to `interpolate()`)
- `I18N_T(key)` - Alternative macro for translation
- `I18N_F(key, values)` - Alternative macro for interpolation

### Example with Macros
```cpp
// Simply load locale and use macros
I18n::loadGlobalLocale("en");

// Simple translation
std::cout << _("greeting") << std::endl;

// Interpolation with macros
std::cout << _f("personalized_greeting", {{"name", "John"}}) << std::endl;
```

## Dynamic String Interpolation
The library also supports dynamic string interpolation. You can use placeholders in your translation strings and provide values to replace them at runtime.

### Example
```cpp
// Load locale first
I18n::loadGlobalLocale("en");

// Using macro
std::cout << _f("personalized_greeting", {{"name", "John"}}) << std::endl; // Outputs: Hello John

// Or use static method directly
std::cout << I18n::interpolateGlobal("personalized_greeting", {{"name", "John"}}) << std::endl;
```

## License
This project is licensed under the MIT License. See the LICENSE file for more details.