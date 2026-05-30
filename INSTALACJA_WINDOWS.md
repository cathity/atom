# Instalacja i uruchomienie od zera — Windows + VSCode

Ten dokument opisuje pelna procedure na **nowym laptopie z Windows 11/10**.
Projekt jest samowystarczalny: GLAD, stb_image, shadery i tekstury sa w paczce.
Przy pierwszej kompilacji CMake pobierze **GLFW** i **GLM** z internetu (wymagany Git).

---

## Krok 1 — Rozpakuj projekt

1. Skopiuj plik `Atom_projekt_GK.zip` na laptop (pendrive, email, chmura).
2. Rozpakuj do np. `C:\Users\TwojeImie\Documents\Atom\`
3. Po rozpakowaniu powinienes widziec m.in.:
   - `src\main.cpp`
   - `include\`
   - `shaders\`
   - `textures\`
   - `external\`
   - `CMakeLists.txt`

**Nie usuwaj folderu `external\`** — zawiera loader OpenGL (GLAD) i biblioteke do obrazow.

---

## Krok 2 — Zainstaluj wymagane programy

Zainstaluj po kolei (wszystkie darmowe):

### A) Visual Studio 2022 Community
- Pobierz: https://visualstudio.microsoft.com/pl/vs/community/
- W instalatorze zaznacz workload: **„Programowanie aplikacji klasycznych w języku C++”**
- Upewnij sie, ze sa zaznaczone: **MSVC**, **Windows SDK**, **CMake tools for Windows**

### B) Git for Windows
- Pobierz: https://git-scm.com/download/win
- Instalacja domyslna (Next, Next…)
- **Potrzebny do pobrania GLFW/GLM przy pierwszej kompilacji**

### C) CMake (jesli nie zainstalowal sie z Visual Studio)
- Pobierz: https://cmake.org/download/
- Wybierz **Windows x64 Installer**
- Przy instalacji zaznacz: **Add CMake to the system PATH**

### D) VSCode
- Pobierz: https://code.visualstudio.com/

### E) Rozszerzenia VSCode (w VSCode: Extensions / Ctrl+Shift+X)
- **C/C++** (Microsoft)
- **CMake Tools** (Microsoft)

---

## Krok 3 — Otworz projekt w VSCode

1. Uruchom VSCode
2. **File → Open Folder…**
3. Wybierz folder `Atom` (ten z `CMakeLists.txt`)
4. Jesli VSCode zapyta o zaufanie — kliknij **Yes, I trust the authors**

---

## Krok 4 — Skompiluj projekt

### Sposob A — skrypt (najprostszy)

1. Otworz terminal w VSCode: **Terminal → New Terminal**
2. Wpisz:

```bat
build_windows.bat
```

3. Pierwsza kompilacja moze trwac **2–5 minut** (pobieranie GLFW i GLM).
4. Po sukcesie zobaczysz komunikat z sciezka do `atom.exe`.

### Sposob B — recznie w terminalu

```bat
cmake -B build -S .
cmake --build build --config Release
```

### Sposob C — CMake Tools w VSCode

1. Na pasku dolnym kliknij **No Kit Selected** → wybierz **Visual Studio Community … amd64**
2. Kliknij **Build** (ikona mlotka) lub **Ctrl+Shift+B**

---

## Krok 5 — Uruchom program

### Z terminala

```bat
build\Release\atom.exe
```

**Wazne:** uruchamiaj `atom.exe` z folderu `build\Release\` (tam sa skopiowane shadery i tekstury).

### Z VSCode (F5)

1. Otworz panel **Run and Debug** (Ctrl+Shift+D)
2. Wybierz **Run atom (Release)**
3. Nacisnij **F5**

---

## Sterowanie w aplikacji

| Klawisz | Akcja |
|---------|-------|
| W / A / S / D | Ruch kamery |
| Mysz | Obrot kamery |
| Scroll | Zoom |
| Q / E | Obrot modelu atomu |
| R / F | Skalowanie modelu |
| F1 | Filtrowanie NEAREST |
| F2 | Filtrowanie LINEAR |
| F3 | Filtrowanie MIPMAP |
| ESC | Wyjscie |

---

## Rozwiazywanie problemow

### „cmake nie jest rozpoznawane…”
- Zrestartuj VSCode i terminal po instalacji CMake
- Lub otworz **Developer Command Prompt for VS 2022** z menu Start

### „Git NOT found” / blad FetchContent
- Zainstaluj Git for Windows (Krok 2B)
- Zamknij i otworz ponownie terminal

### „Cannot open shaders/…” / czarny ekran
- Uruchamiaj exe z `build\Release\`, nie z innego folderu
- Przebuduj: `cmake --build build --config Release`

### Brak karty graficznej / sterownikow OpenGL
- Zaktualizuj sterowniki GPU (Intel / NVIDIA / AMD)

### Antywirus blokuje pobieranie
- Przy pierwszej kompilacji CMake pobiera biblioteki z GitHub — wymagane polaczenie z internetem

---

## Zawartosc paczki (co oddajesz / przenosisz)

```
Atom/
├── src/main.cpp              — kod glowny
├── include/                  — Camera.h, Shader.h
├── shaders/                  — shadery GLSL
├── textures/                 — nucleus.png, floor.png
├── external/glad/            — loader OpenGL
├── external/stb/             — ladowanie PNG
├── docs/                     — dokumentacja PDF
├── CMakeLists.txt
├── build_windows.bat         — skrypt budowania (Windows)
├── README.md
└── INSTALACJA_WINDOWS.md     — ten plik
```

Folder `build/` **nie jest potrzebny** na nowym laptopie — utworzy sie przy kompilacji.

---

## macOS / Linux (opcjonalnie)

```bash
cmake -B build -S .
cmake --build build
./build/atom        # macOS/Linux
```
