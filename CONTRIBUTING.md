# Contributing to Juster

Thank you for your interest in contributing to Juster! Since we're in early development, your contributions can have a significant impact on the project's direction and success.

## Development Status

As of February 2025, Juster is in early development. This means:

- The codebase is evolving quickly
- APIs and architecture may change substantially
- There are many opportunities to influence the project direction

## How Can I Contribute?

### Code Contributions

1. Fork the repository
2. Create a new branch from `main`:
   ```
   git checkout -b feature/your-feature-name
   ```
   or
   ```
   git checkout -b bugfix/issue-description
   ```
3. Make your changes
4. Commit your changes with clear, descriptive messages
5. Push to your fork
6. Submit a pull request to the `main` branch

### Current Development Priorities

- Core rendering engine
- UI framework implementation
- Timeline system
- File format design
- Tool system architecture

### Design Contributions

We welcome input on:
- User interface design
- User experience workflows
- Logo and branding
- Feature requirements

### Documentation

- Help document the architecture and APIs as they evolve
- Create tutorials and examples
- Improve README and other documentation files

## Development Setup

Follow the [Building from Source](README.md#building-from-source) instructions in the README.

### Dependencies

- C++17 compatible compiler
- CMake 3.15 or higher
- OpenGL 3.3+

## Coding Standards

### C++ Style Guide

- Use 4 spaces for indentation
- Follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) with the following exceptions:
  - Use `.cpp` and `.hpp` file extensions
  - Use `#pragma once` for header guards
- Keep lines under 100 characters when possible
- Document your code using Doxygen-style comments

## Project Structure

```
Juster/
├── src/                  # Source files
│   ├── core/             # Core engine functionality
│   ├── gui/              # User interface components
│   ├── animation/        # Animation engine
│   └── renderer/         # Rendering components
├── include/              # Public headers
├── resources/            # Icons, shaders, etc.
├── docs/                 # Documentation
└── tests/                # Tests (when we have them)
```

## Communication

- Open an issue for discussions about features or bugs
- Tag issues with appropriate labels

Thank you for helping build Juster!
```
