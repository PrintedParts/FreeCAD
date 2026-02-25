# vehicad — FreeCAD Fork for PrintedParts

This is a fork of [FreeCAD](https://github.com/FreeCAD/FreeCAD) (v1.2.0-dev) that adds PrintedParts OAuth authentication and custom URL scheme handling.

## Build Environment

Uses **pixi** (conda-based) as the package manager. Always use `pixi run` commands — do not use system CMake or Python directly.

```bash
pixi run initialize       # One-time: init git submodules
pixi run configure        # Configure debug build
pixi run build            # Build debug
pixi run install          # Install debug
pixi run freecad          # Run the app (debug)

pixi run configure-release
pixi run build-release
pixi run install-release
pixi run test
```

Build outputs go to `build/debug/` and `build/release/`.

## Key Dependencies

- **Qt 6.8** (Qt6, not Qt5)
- **Python 3.11** + pybind11
- **OpenCASCADE 7.8** (geometry kernel)
- **Coin3D** (3D scene graph)
- Boost, Eigen, TBB 2022

## Source Layout

```
src/
  App/       # Core application, document model
  Gui/       # All Qt GUI code (MainWindow, dialogs, etc.)
  Main/      # Entry points (MainGui.cpp, FreeCADGuiPy.cpp)
  Mod/       # FreeCAD workbenches/modules
build/
  debug/
  release/
scripts/     # Dev/debug utilities
```

## Code Conventions

- **Header guards:** `#pragma once`
- **License header:** `// SPDX-License-Identifier: LGPL-2.1-or-later`
- **Namespaces:** `namespace Gui { ... } // namespace Gui`
- **Qt includes:** `#include <QWidget>` (angle brackets)
- **Local includes:** `#include "MyClass.h"` (quotes)
- All GUI code targets Qt6 (`FREECAD_QT_VERSION=6`)

## PrintedParts Integration (What This Fork Adds)

### New Files
- `src/Gui/OAuthLoginDialog.h/.cpp` — Qt dialog to start the OAuth flow; emits `loginSucceeded(QString payload)`
- `src/Gui/UrlSchemeHandler.h/.cpp` — `QObject` event filter that handles `printedparts://` URI callbacks (macOS `FileOpen` events); emits `oauthCodeReceived(QString code)`

### Integration Points
- `src/Main/MainGui.cpp` — Instantiates `UrlSchemeHandler` early in startup
- `src/Gui/MainWindow.cpp` — Adds "PrintedParts > Sign in..." menu item that opens `OAuthLoginDialog`
- `src/Gui/CMakeLists.txt` — New files force-added to the `FreeCADGui` target via `target_sources`

### Debug Logging
`UrlSchemeHandler` writes debug output to `/tmp/PrintedPartsOAuth.log`.

Use `scripts/pp_oauth_debug.py` to verify the OAuth components compiled correctly.

### TODO
- Replace placeholder `https://example.com/oauth/start` in `MainWindow.cpp` with the real PrintedParts OAuth URL

## CMake Notes

When adding new `.cpp`/`.h` files to `src/Gui/`, add them to `src/Gui/CMakeLists.txt` under the appropriate `target_sources` block. The PrintedParts files use a force-add pattern at the top of that file to ensure inclusion.

## Upstream Relationship

This fork tracks `FreeCAD/FreeCAD` main. Keep custom changes minimal and isolated to avoid merge conflicts. Do not modify upstream workbench code unless necessary.

Official FreeCAD dev docs: https://freecad.github.io/DevelopersHandbook/
