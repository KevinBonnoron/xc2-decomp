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

      libcxxSite = pkgs.writeText "__config_site" ''
        #ifndef _LIBCPP_CONFIG_SITE
        #define _LIBCPP_CONFIG_SITE

        #define _LIBCPP_HAS_MUSL_LIBC
        #define _LIBCPP_HAS_THREAD_API_PTHREAD

        #endif // _LIBCPP_CONFIG_SITE
      '';

      libcxxHeaders = pkgs.stdenvNoCC.mkDerivation {
        pname = "libcxx-headers";
        version = "3.9.1";
        src = pkgs.fetchurl {
          url = "https://releases.llvm.org/3.9.1/libcxx-3.9.1.src.tar.xz";
          sha256 = "0qbl3afl2p2h87p977lsqr5kykl6cgjpkzczs0g6a3pn53j1bri5";
        };
        dontConfigure = true;
        dontBuild = true;
        installPhase = ''
          mkdir -p $out/include/c++
          cp -r include $out/include/c++/v1
          rm $out/include/c++/v1/CMakeLists.txt $out/include/c++/v1/__config_site.in
          cat ${libcxxSite} include/__config > $out/include/c++/v1/__config
        '';
      };

      muslHeaders = pkgs.stdenvNoCC.mkDerivation {
        pname = "musl-headers";
        version = "1.1.16";
        src = pkgs.fetchurl {
          url = "https://musl.libc.org/releases/musl-1.1.16.tar.gz";
          sha256 = "048h0w4yjyza4h05bkc6dpwg3hq6l03na46g0q1ha8fpwnjqawck";
        };
        dontConfigure = true;
        dontBuild = true;
        installPhase = ''
          make ARCH=aarch64 prefix= DESTDIR=$out install-headers
        '';
      };

      sysroot = pkgs.symlinkJoin {
        name = "nx-sysroot";
        paths = [ libcxxHeaders muslHeaders ];
      };

      check = pkgs.writeShellScriptBin "check" ''
        exec ${pkgs.python3}/bin/python3 "$(git rev-parse --show-toplevel)/tools/check.py" "$@"
      '';

      format = pkgs.writeShellScriptBin "format" ''
        cd "$(git rev-parse --show-toplevel)"
        if [ "''${1:-}" != "--staged" ]; then
          find src include -name '*.h' -o -name '*.cpp' | xargs ${pkgs.clang-tools}/bin/clang-format -i
          exit
        fi
        files=$(git diff --cached --name-only --diff-filter=ACMR -- 'src/*.h' 'src/*.cpp' 'include/*.h' 'include/*.cpp')
        [ -n "$files" ] || exit 0
        partial=$(git diff --name-only -- $files)
        if [ -n "$partial" ]; then
          echo "format: these files also have unstaged changes, stage or stash them before committing:" >&2
          echo "$partial" >&2
          exit 1
        fi
        ${pkgs.clang-tools}/bin/clang-format -i $files
        git add $files
      '';

      # The nixpkgs wrapper adds the host glibc headers, which would shadow musl.
      iwyu = pkgs.runCommand "iwyu-unwrapped" { } ''
        mkdir -p $out/bin
        ln -s ${pkgs.include-what-you-use}/bin/.include-what-you-use-unwrapped $out/bin/include-what-you-use
        ln -s ${pkgs.include-what-you-use}/bin/fix_includes.py $out/bin/fix_includes.py
      '';

      includes = pkgs.writeShellScriptBin "includes" ''
        export PATH=${iwyu}/bin:$PATH
        exec ${pkgs.python3}/bin/python3 "$(git rev-parse --show-toplevel)/tools/includes.py" "$@"
      '';

      setup = pkgs.writeShellScriptBin "setup" ''
        exec ${pkgs.bash}/bin/bash "$(git rev-parse --show-toplevel)/tools/setup.sh" "$@"
      '';
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          clang391
          clang401
          check
          format
          includes
          setup
          ghidra
          hactool
          python3
          llvmPackages.bintools
        ];

        shellHook = ''
          git config core.hooksPath .githooks
          export XC2_SYSROOT=${sysroot}
          mkdir -p "$(git rev-parse --show-toplevel)/work"
          ln -sfn ${sysroot} "$(git rev-parse --show-toplevel)/work/sysroot"
          export XC2_ROM="/mnt/nas/Emulations/roms/switch/Xenoblade Chronicles 2.xci"
          export SWITCH_KEYS="$HOME/.switch/prod.keys"
        '';
      };
    };
}
