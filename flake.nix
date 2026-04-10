{
  description = "Dev shell for qemu-camp C exercises";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
      in {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            bashInteractive
            coreutils
            findutils
            gnugrep
            gawk
            gnused
            gcc
            gnumake
            inotify-tools
            jq
            curl
            clang-tools
          ];
        };

        devShells.ci = pkgs.mkShell {
          packages = with pkgs; [
            bashInteractive
            coreutils
            gcc
            gnumake
            jq
          ];

          shellHook = ''
            export CI=true
            export DEBIAN_FRONTEND=noninteractive
            export GIT_TERMINAL_PROMPT=0
            export GIT_PAGER=cat
            export PAGER=cat
          '';
        };
      }
    );
}
