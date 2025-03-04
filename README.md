---
name: Allegro++
description: A modern C++ wrapper for the Allegro game library.
license: LGPL-3.0
author: Eduardo Aguiar
email: aguiar@protonmail.ch
repository: https://github.com/eduardoaguiar-oss/allegropp
website: https://github.com/eduardoaguiar-oss/allegropp
---

# Allegro++

**Allegro++** is a modern C++ wrapper for the [Allegro](https://liballeg.org/) game library, designed to simplify game development by providing an object-oriented interface to Allegro's powerful features. This project aims to make Allegro more accessible and easier to use for C++ developers while maintaining the flexibility and performance of the original library.

---

## Features

- **Object-Oriented Design**: Allegro++ wraps Allegro's C API into intuitive C++ classes, making it easier to manage resources and structure your game code.
- **Cross-Platform**: Like Allegro, Allegro++ works on Windows, macOS, and Linux.
- **Easy Integration**: Designed to work seamlessly with existing Allegro projects or as a standalone library.
- **Modern C++**: Utilizes modern C++ features like RAII, smart pointers, and STL containers for safer and cleaner code.
- **Extensible**: Easily extend Allegro++ to add custom functionality or integrate with other libraries.

---

## Getting Started

### Prerequisites

- **Allegro Library**: Allegro++ requires Allegro 5.x to be installed on your system. Download it from the [official website](https://liballeg.org/).
- **C++ Compiler**: A C++17-compatible compiler (e.g., GCC, Clang, or MSVC).
- **CMake**: For building the project.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/eduardoaguiar-oss/allegropp.git
   cd allegropp
   ```

2. Build the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

3. Install the library (optional):
   ```bash
   sudo cmake --install .
   ```

### Usage

Include the Allegro++ header in your project and link against the library. Here's a simple example:

```cpp
#include <allegropp/allegropp.hpp>

int main() {
    // Initialize Allegro++
    allegropp::Core core;
    if (!core.init()) {
        return -1;
    }

    // Create a display
    allegropp::Display display(800, 600);
    display.setTitle("Allegro++ Example");

    // Main loop
    while (true) {
        // Clear the screen
        display.clear(allegropp::Color::White);

        // Draw something
        display.drawText("Hello, Allegro++!", 100, 100, allegropp::Color::Black);

        // Flip the display
        display.flip();
    }

    return 0;
}
```

---

## Documentation

For detailed documentation, check out the [Wiki](https://github.com/eduardoaguiar-oss/allegropp/wiki). It includes:
- **API Reference**: A complete guide to Allegro++ classes and methods.
- **Tutorials**: Step-by-step guides to help you get started.
- **Examples**: Sample projects demonstrating Allegro++ features.

---

## Contributing

We welcome contributions! If you'd like to contribute to Allegro++, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Submit a pull request with a detailed description of your changes.

Please ensure your code follows the project's coding standards and includes appropriate tests.

---

## License

Allegro++ is released under the **GNU Lesser General Public License (LGPL)**. See the [LICENSE](LICENSE) file for details.

---

## Acknowledgments

- **Allegro Development Team**: For creating the amazing Allegro library.
- **Open-Source Community**: For inspiring and supporting this project.

---

## Contact

For questions, suggestions, or support, feel free to open an issue on GitHub or contact the maintainer:

- **Eduardo Aguiar**: [aguiar@protonmail.ch](mailto:aguiar@protonmail.ch)

---

## Support the Project

If you find Allegro++ useful, consider giving it a ⭐️ on GitHub or contributing to its development. Your support is greatly appreciated!

---

Happy coding with Allegro++! 🚀
