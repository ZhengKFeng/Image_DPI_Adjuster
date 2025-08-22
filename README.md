# Image DPI Adjuster (C++ / Qt)

A simple GUI tool to adjust the DPI of images based on user input.  
Built with **C++** and **Qt Framework**.

## Features
- Open an image (PNG, JPG, etc.)
- Input custom DPI values (X and Y)
- Save the updated image with new DPI metadata

## Requirements
- C++17 or higher
- Qt 6 (or Qt 5) installed
- CMake (optional, if building with CMake)

## Build Instructions

### Using CMake
```bash
mkdir build && cd build
cmake ..
make
./ImageDPIAdjuster
