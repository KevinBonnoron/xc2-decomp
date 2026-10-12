{
  description = "Xenoblade Chronicles 2 reverse engineering environment";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };

      mkClang = { version, major, hash }: pkgs.stdenv.mkDerivation {
        pname = "clang-nx";
        inherit version;
        src = pkgs.fetchurl {
          url = "https://releases.llvm.org/${version}/clang+llvm-${version}-x86_64-linux-gnu-debian8.tar.xz";
          inherit hash;
        };
        nativeBuildInputs = [ pkgs.autoPatchelfHook ];
        buildInputs = [ pkgs.ncurses5 pkgs.zlib pkgs.libxml2 pkgs.stdenv.cc.cc.lib ];
        autoPatchelfIgnoreMissingDeps = true;
        installPhase = ''
          mkdir -p $out/bin $out/lib
          cp -r lib/clang $out/lib/
          cp bin/clang-${major} $out/bin/clang-${version}
          ln -s clang-${version} $out/bin/clang++-${version}
        '';
      };

      clang391 = mkClang {
        version = "3.9.1";
        major = "3.9";
        hash = "sha256-2+KtmM2cK3GP37Xcctz5z7kQCdBaWys3RXzMyVhVmyo=";
      };

      clang401 = mkClang {
        version = "4.0.1";
        major = "4.0";
        hash = "sha256-ykik3vTLyd1q8/Rs4dwr2QPSbHrVE4f1eIStHqpY5C8=";
      };

      diffFunc = pkgs.writeShellScriptBin "diff-func" ''
        exec ${pkgs.python3}/bin/python3 "$(git rev-parse --show-toplevel)/tools/diff_func.py" "$@"
      '';
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          clang391
          clang401
          diffFunc
          ghidra
          hactool
          python3
          llvmPackages.bintools
        ];

      };
    };
}
