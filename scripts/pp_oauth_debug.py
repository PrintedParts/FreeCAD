
from pathlib import Path
import re

def show(path, pattern, context=3, max_hits=12):
    p = Path(path)
    if not p.exists():
        print("MISSING:", path)
        return
    lines = p.read_text(encoding="utf-8", errors="ignore").splitlines()
    hits = [i for i,l in enumerate(lines) if re.search(pattern, l)]
    print(f"\n== {path}  hits={len(hits)} for /{pattern}/ ==")
    for n, i in enumerate(hits[:max_hits]):
        a = max(0, i-context)
        b = min(len(lines), i+context+1)
        for j in range(a, b):
            print(f"{j+1:5d}: {lines[j]}")
        print("-----")

print("PWD:", Path.cwd())

# Check constructor logging exists in source
show("src/Gui/UrlSchemeHandler.cpp", r"UrlSchemeHandler constructed|/tmp/PrintedPartsOAuth\.log|fopen|fprintf", context=2)

# Confirm handler is referenced from MainGui.cpp
show("src/Main/MainGui.cpp", r"UrlSchemeHandler|installEventFilter", context=5)

# Confirm CMake forcibly adds UrlSchemeHandler (source list)
show("src/Gui/CMakeLists.txt", r"UrlSchemeHandler\.cpp|target_sources", context=2)

# Confirm build system is compiling it (build.ninja)
bn = Path("build/debug/build.ninja")
if bn.exists():
    txt = bn.read_text(encoding="utf-8", errors="ignore")
    print("\n== build/debug/build.ninja contains UrlSchemeHandler.cpp:", "UrlSchemeHandler.cpp" in txt)
else:
    print("\n== build/debug/build.ninja MISSING (did you configure/build yet?)")

print("\nNEXT: After this, run:")
print("  pixi run build-debug && pixi run install-debug")
print("  then launch FreeCAD.app / PrintedParts.app and we will verify runtime by adding a *guaranteed* visible signal.")
