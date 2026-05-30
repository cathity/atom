# Model Atomu — Projekt Grafika Komputerowa

Wizualizacja 3D modelu atomu z jądrem, elektronami na orbitach, oświetleniem Phonga i teksturowaniem.

---

## Windows (VSCode) — START TUTAJ

**Pełna instrukcja krok po kroku:** [`INSTALACJA_WINDOWS.md`](INSTALACJA_WINDOWS.md)

Skrót:
1. Zainstaluj: Visual Studio 2022 (C++), Git, CMake, VSCode
2. Rozpakuj projekt, otwórz folder w VSCode
3. W terminalu: `build_windows.bat`
4. Uruchom: `build\Release\atom.exe`

---

## macOS / Linux

### Wymagania
- CMake 3.16+, kompilator C++17, Git (do pobrania GLFW/GLM)

```bash
cd Atom
cmake -B build -S .
cmake --build build
./build/atom
```

Na macOS (Homebrew, opcjonalnie): `brew install cmake git`

---

## Sterowanie

| Klawisz | Akcja |
|---------|-------|
| W/A/S/D | Ruch kamery |
| Mysz | Obrót kamery |
| Scroll | Zoom (FOV) |
| Q / E | Obrót modelu atomu |
| R / F | Skalowanie modelu atomu |
| F1 | Filtrowanie NEAREST |
| F2 | Filtrowanie LINEAR |
| F3 | Filtrowanie MIPMAP |
| ESC | Wyjście |

---

## Struktura projektu

```
Atom/
├── src/main.cpp              — główna aplikacja
├── include/                  — Camera.h, Shader.h
├── shaders/                  — shadery GLSL
├── textures/                 — nucleus.png, floor.png
├── external/                 — GLAD, stb_image (w paczce)
├── docs/                     — dokumentacja techniczna PDF
├── CMakeLists.txt
├── build_windows.bat         — skrypt budowania (Windows)
├── INSTALACJA_WINDOWS.md     — instrukcja od zera (Windows)
└── README.md
```

GLFW i GLM pobierane automatycznie przy pierwszej kompilacji (wymagany internet + Git).

---

## Dokumentacja

- [`docs/dokumentacja_techniczna.pdf`](docs/dokumentacja_techniczna.pdf) — opis techniczny projektu
- [`docs/CHECKLIST.md`](docs/CHECKLIST.md) — spełnienie 10 punktów wytycznych
