# vivy

A fast, minimalist, GPU-accelerated image viewer built with **C++20** and **SDL2**.

Designed to be lightweight and seamlessly blend into keyboard-driven tiling window managers (dwm, Hyprland, Niri, Sway, i3, bspwm) and Wayland/X11 desktop setups.

---

## Features

- **GPU Accelerated:** Fast rendering via `SDL_Renderer` and hardware textures.
- **Cursor-Centric Zoom:** Smooth zooming directly relative to your mouse pointer.
- **Pan & Drag:** Smooth mouse dragging for navigating large images.
- **Auto-Fit:** Automatically scales and centers images to fit window bounds upon opening or resizing.
- **XDG & Desktop Integration:** Automatically installs a `.desktop` file for file manager and `xdg-open` integration.
- **Flake Ready:** Install or run instantly anywhere using Nix without manual dependency setup.

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

## CLI Options

Running `vivy` without arguments or with help flags displays usage info in your terminal:

```text
Usage:
  vivy <image_path>
  vivy [options]

Options:
  -h, --help     Show usage and control information
  -v, --version  Display version information

```

---

## Installation

### Method 1: Nix (Recommended)

**Run without installing:**

```bash
nix run github:h4shcore/vivy -- path/to/image.png

```

**Install to user profile:**

```bash
nix profile install github:h4shcore/vivy

```

**Local Development Shell:**

```bash
nix develop

```

**NixOS Flake:**
Add `vivy` to your inputs and system packages:

```nix
{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";

    # Add vivy as a flake input
    vivy.url = "github:h4shcore/vivy";
  };

  outputs = { self, nixpkgs, vivy, ... }@inputs: {
    # System or Home Manager output definitions...
  };
}

```

```nix
environment.systemPackages = [
  inputs.vivy.packages.${pkgs.system}.default
];

```

**Home Manager:**
Add `vivy` to your inputs and home packages:

```nix
home.packages = [
  inputs.vivy.packages.${pkgs.system}.default
];

xdg.mimeApps = {
  enable = true;
  defaultApplications = {
    "image/png" = [ "vivy.desktop" ];
    "image/jpeg" = [ "vivy.desktop" ];
    "image/webp" = [ "vivy.desktop" ];
    "image/bmp" = [ "vivy.desktop" ];
  };
};

```

---

### Method 2: Building from Source

#### Dependencies

* C++20 compiler (`g++` or `clang++`)
* `CMake` (>= 3.16)
* `SDL2`
* `SDL2_image`
* `pkg-config`

#### Build & Install

```bash
# Clone the repository
git clone https://github.com/h4shcore/vivy.git
cd vivy

# Configure the build
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Compile binary
cmake --build build

# Run directly
./build/vivy path/to/image.png

# System-wide install (binary + desktop entry)
sudo cmake --install build

```

---

## Setting as Default Viewer (`xdg-open`)

Once installed via Nix or `cmake --install`, set `vivy` as your default image viewer with:

```bash
xdg-mime default vivy.desktop image/png image/jpeg image/webp image/bmp

```

---

## License

[MIT](https://www.google.com/search?q=LICENSE)
