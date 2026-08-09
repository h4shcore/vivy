{
  description = "vivy - Minimalist C++20 SDL2 Image Viewer";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      supportedSystems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];
      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;
    in {
      packages = forAllSystems (system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
        in {
          default = pkgs.stdenv.mkDerivation {
            pname = "vivy";
            version = "0.1.0";
            src = ./.;

            nativeBuildInputs = [ pkgs.pkg-config ];
            buildInputs = [
              pkgs.SDL2
              pkgs.SDL2_image
            ];

            buildPhase = "make";

            installPhase = ''
              mkdir -p $out/bin
              cp build/vivy $out/bin/vivy
            '';
          };
        });

      devShells = forAllSystems (system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
        in {
          default = pkgs.mkShell {
            inputsFrom = [ self.packages.${system}.default ];
          };
        });
    };
}
