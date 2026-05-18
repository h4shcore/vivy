{
  description = "dev env for vivy";

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
        pkgs = import nixpkgs {
          inherit system;
        };
      in
      {
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
