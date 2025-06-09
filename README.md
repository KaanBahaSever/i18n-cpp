# C++ i18n Library

## Overview
This project is a simple header-only internationalization (i18n) library written in C++. It allows for easy localization of applications by loading language files stored in a local folder and supports dynamic string interpolation.

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
To use the i18n library in your project, include the header file and create an instance of the `I18n` class. You can load a locale and retrieve translations as follows:

```cpp
#include "i18n/i18n.hpp"

int main() {
    I18n i18n;
    i18n.loadLocale("en"); // Load English locale

    std::string greeting = i18n.translate("greeting");
    std::cout << greeting << std::endl; // Outputs: Hello

    return 0;
}
```

## Dynamic String Interpolation
The library also supports dynamic string interpolation. You can use placeholders in your translation strings and provide values to replace them at runtime.

### Example
```cpp
std::string message = i18n.interpolate("greeting {name}", {{"name", "John"}});
std::cout << message << std::endl; // Outputs: Hello John
```

## License
This project is licensed under the MIT License. See the LICENSE file for more details.
