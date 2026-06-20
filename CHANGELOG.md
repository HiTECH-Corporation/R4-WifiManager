# Changelog

All notable changes to this project will be documented in this file.

The format is inspired by Keep a Changelog and semantic versioning conventions.

## [Unreleased]

## [2026.6.20] - 2026-06-20

### Added

- **mDNS Responder**: Added UDP multicast responder for `r4wm.local` domain to enable easy local access without IP addresses.
- **Captive Portal DNS Server**: Implemented a lightweight UDP DNS Server (port 53) to spoof DNS requests, triggering OS-level captive portal login prompts.

### Changed

- **Extreme RAM Optimization**: Completely removed all `String` object usage from internal class definitions and HTTP routing in favor of static `char[]` arrays.
- **Asynchronous HTTP Server**: Rewrote `handleClient()` into a true non-blocking finite state machine (FSM), preventing slowloris attacks and loop blocking.
- **HTTP 302 Redirect**: Replaced 200 OK responses with standard HTTP 302 Redirects for unrecognized paths to fully comply with Apple, Android, and Windows Captive Portal specifications.

### Fixed

- Resolved critical bug where device failed to leave AP mode after saving credentials due to `strcmp` reading past non-null-terminated magic bytes. Switched to `strncmp` for `EEPROMData` struct magic signature validation.

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
