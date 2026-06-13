# Contributing

Thank you for helping improve HiTECH R4 WiFi Manager.

## Development Scope

This library targets Arduino Uno R4 WiFi only. Pull requests should preserve this focus and avoid introducing dependencies that break portability for this board.

## How To Contribute

1. Fork the repository.
2. Create a feature branch from `main`.
3. Make focused, minimal changes.
4. Validate behavior with the example sketch in `examples/BasicAutoConnect/BasicAutoConnect.ino`.
5. Open a pull request with a clear description and test notes.

## Coding Guidelines

- Keep architecture non-blocking; avoid introducing `delay()` in runtime logic.
- Preserve backward compatibility for public APIs in `src/WiFiManager.h` whenever possible.
- Prefer small, reviewable commits.
- Keep memory usage stable in hot paths.

## Pull Request Checklist

- [ ] Change is scoped and documented.
- [ ] Example sketch still compiles and runs.
- [ ] Public API changes are reflected in `README.md`.
- [ ] New behavior includes validation notes in the PR description.

## Reporting Issues

When opening an issue, include:

- Board model and core version
- Reproduction steps
- Expected behavior
- Actual behavior
- Serial logs (if available)
