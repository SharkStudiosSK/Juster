# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.1.0] - 2025-02-XX

### Added
- Initial project structure with CMake build system
- Modular architecture with separate Application, Window, and Renderer classes
- Basic OpenGL rendering with animated triangle demo
- C++17 support with proper dependency management (SDL2, GLEW, OpenGL)
- Build automation script (`build.sh`)
- Project documentation and design documents
- Version tracking and git ignore configuration

### Changed
- Refactored monolithic main.cpp into clean, modular components
- Updated README with build instructions and current project status

### Technical Details
- CMake 3.15+ compatibility
- Cross-platform build support
- Proper resource management and cleanup
- Singleton pattern for application lifecycle
- Namespace organization (`Juster::`)