# Changelog

All notable changes to this project will be documented in this file.

The format is inspired by Keep a Changelog and semantic versioning conventions.

## [Unreleased]

## [2026.6.15] - 2026-06-15

### Fixed

- Resolved variable declaration mismatch (`_lastReconnectTime` replacing `_reconnectTimer`) in header file.
- Corrected `handleClient(WiFiClient &client)` function signature mismatch to ensure proper asynchronous processing.
- Synchronized `WiFiManager.cpp` and `WiFiManager.h` structure for Arduino compilation stability.

### Changed

- Updated library metadata to match Arduino Library Manager best practices.
- Added a wrapper primary header to remove the primary-header warning without breaking existing includes.

## [2026.6.14] - 2026-06-14

### Added

- Professional README structure with badges, architecture diagram, expanded API reference, troubleshooting, and FAQ.
- Contribution guide in `CONTRIBUTING.md`.

### Changed

- Documentation organization and readability for release-grade project presentation.
