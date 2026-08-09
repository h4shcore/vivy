# vivy

A fast, minimalist, GPU-accelerated image viewer built with **C++20** and **SDL2**.

Designed to be lightweight and seamlessly blend into keyboard-driven tiling window managers (dwm,Hyprland, Niri, Sway, i3, bspwm) and Wayland/X11 desktop setups.

---

## Features

- **GPU Accelerated:** Fast rendering via `SDL_Renderer` and hardware textures.
- **Cursor-Centric Zoom:** Smooth zooming directly relative to your mouse pointer.
- **Pan & Drag:** Smooth mouse dragging for navigating large images.
- **Auto-Fit:** Automatically scales and centers images to fit window bounds upon opening or resizing.
- **Flake Ready:** Run instantly anywhere using Nix without manual dependency setup.

---

## Keybinds & Controls

| Input | Action |
| :--- | :--- |
| **Scroll Wheel** | Zoom in / out relative to cursor |
| **Left Click + Drag** | Pan image |
| **`r`** | Reset zoom and re-center image |
| **`f`** | Toggle borderless fullscreen |
| **`q`** / **`Esc`** | Exit `vivy` |

---

## Quick Start (Nix)

Run `vivy` directly from GitHub without compiling manually:

```bash
nix run github:h4shcore/vivy -- path/to/image.png

```

---

## Building from Source

### Dependencies

* C++20 compiler (`g++` or `clang++`)
* `SDL2`
* `SDL2_image`
* `make`

### Build & Run

```bash
# Clone the repository
git clone [https://github.com/h4shcore/vivy.git](https://github.com/h4shcore/vivy.git)
cd vivy

# Build binary (output saved to build/vivy)
make

# Run with an image
make run ARGS="path/to/image.png"

```
--- 

## License

[MIT](https://www.google.com/search?q=LICENSE)

```
