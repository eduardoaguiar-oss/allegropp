# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/),
and this project adheres to [Semantic Versioning](https://semver.org/).

## [1.1] - xxx

### Added
- Added this CHANGELOG.md file.
- New function allegropp::init.
- New class "maze".
- Created a new directory named examples, containing usage examples for Allegro++.
- New example program, called "hello_world".
- New example program, called "maze".

### Changed
- .cpp files moved from src/allegropp to src directory.
- bitmap::_init calls allegropp::init.
- display::impl::impl calls allegropp::init.
- font::_init calls allegropp::init.
- font::impl::impl calls al_load_font instead of al_load_ttf_font.
- font::impl::impl: If the font fails to load, it attempts to load the font from the SYSTEM_DEFAULT_FONT_DIR instead.

### Fixed
- Added timer.cpp to the target's source files in CMakeLists.txt.

## [1.0] - 2025-03-23

### Added
- New class `bitmap`.
- New class `color`.
- New class `display`.
- New class `event_queue`.
- New class `event_source`.
- New class `font`.
- New class `keyboard`.
- New class `mouse`.
- New class `sample`.
- New class `timer`.
