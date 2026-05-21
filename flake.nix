{
  description = "dev env and build package for vivy (C++ / SDL2)";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        packages.default = pkgs.stdenv.mkDerivation {
          pname = "vivy";
          version = "0.1.0";
          src = ./.;

          # (compilers, build engines)
          nativeBuildInputs = with pkgs; [
            gcc
            cmake
            pkg-config
          ];

          # runtime shared libraries needed by your C++ binary
          buildInputs = with pkgs; [
            SDL2
            SDL2_image
            libwebp
            libpng
            libjpeg
            libtiff
            zlib
          ];
        };

        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            gcc
            gdb
            cmake
            pkg-config
            SDL2
            SDL2_image
            libwebp
            libpng
            libjpeg
            libtiff
            zlib
            clang-tools
          ];
        };
      }
    );
}
