# Checklist — 10 punktów wytycznych GK

| # | Wymaganie | Status | Implementacja |
|---|-----------|--------|---------------|
| 1 | Inicjalizacja OpenGL + okno | OK | `main.cpp`: GLFW 3.3 core, GLAD, depth test |
| 2 | Min. 3 modele 3D | OK | `generateSphere`, `generateCube`, `generateOrbit` |
| 3 | Rzut perspektywiczny | OK | `Camera.h`, `glm::perspective` |
| 4 | Interakcja użytkownika | OK | Kamera WASD+mysz+scroll; obiekt Q/E/R/F |
| 5 | Źródło światła | OK | Point light, ambient+diffuse+specular, animacja pozycji |
| 6 | Cieniowanie | OK | Phong w `fragment_shader.fs` |
| 7 | Teksturowanie | OK | `nucleus.png` (protony), `floor.png` (podłoże), stb_image |
| 8 | Animacja | OK | Obrót jądra, orbity elektronów, ruch światła |
| 9 | Komentarze + PDF | OK | Komentarze PL w kodzie; `docs/dokumentacja_techniczna.pdf` |
| 10 | Filtrowanie obrazu | OK | F1=NEAREST, F2=LINEAR, F3=MIPMAP |

## Uruchomienie testu

```bash
cd Atom/build && ./atom
```

## Oddanie projektu

Do archiwum ZIP włączyć: `src/`, `include/`, `shaders/`, `textures/`, `external/`, `docs/`, `CMakeLists.txt`, `README.md`
