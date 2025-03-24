---
name: Allegro++
description: A modern C++ wrapper for the Allegro game library.
license: LGPL-2.1
author: Eduardo Aguiar
email: aguiar@protonmail.ch
repository: https://github.com/eduardoaguiar-oss/allegropp
website: https://github.com/eduardoaguiar-oss/allegropp
version: 1.1
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

---

## Usage

`Allegro++` is a C++ wrapper for the Allegro Game Library, designed to simplify game development by providing a modern, object-oriented interface. The "examples" directory contains simple demonstration programs designed to illustrate how to use Allegro++.

### HebrewCard: A Practical Example
To help you get started with `Allegro++`, the [hebrewcard](https://github.com/eduardoaguiar-oss/hebrewcard) project serves as a functional example of how to use the library in a real-world application. Hebrewcard is an interactive flashcard program designed to help users learn and memorize Hebrew letters. It demonstrates key features of `Allegro++`, including:

- **Window and Rendering Management**: Creating and managing a window, rendering text, and handling display updates.
- **Event Handling**: Processing user input, such as keyboard events, to navigate between flashcards.
- **Resource Management**: Loading and using fonts and other assets.

By exploring the `hebrewcard` source code, you can see how `Allegro++` is used to build a fully functional application. Here’s how you can get started:

1. **Clone the `hebrewcard` repository**:

   ```bash
   git clone https://github.com/eduardoaguiar-oss/hebrewcard.git
   cd hebrewcard
   ```

2. **Build and run `hebrewcard`**:
   Follow the instructions in the `hebrewcard` repository to build and run the project. This will give you hands-on experience with `Allegro++` in action.

3. **Study the code**:
   Review the `hebrewcard` source code to understand how `Allegro++` is integrated into the project. Pay special attention to:
   - How the `Allegro++` library is initialized and configured.
   - How rendering and event handling are implemented.
   - How resources like fonts are managed.

For more details, visit the [Hebrewcard GitHub repository](https://github.com/eduardoaguiar-oss/hebrewcard).

---

## Support the Project

If you find Allegro++ useful, consider donating cryptocurrency. Your contributions help maintain and improve the project.

### Donation Addresses
- **Bitcoin (BTC)**: `bc1qa92rvaru86hr5lup2a6ewqqgnran3p2qf3djah`
- **Litecoin (LTC)**: `LhiBHWgrqysZsoZfiuc3tUyzFRWwmDZipo`
- **Monero (XMR)**: `42DmNUJ3yQ7bByCgkcyx8nVScC7HrJd83DxUYWPqNo7oQaq8Tnu3BqAQ57J7tRGFkW7wYjzukphLLA5gJXaF9paGJ5X17LD`

Thank you for your support! Every contribution makes a difference.

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

Happy coding with Allegro++! 🚀
