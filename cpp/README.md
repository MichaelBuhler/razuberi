# razuberi/cpp

The C++ library/runtime for Razuberi programs.

## How it works

Headers are built into `./out/include` via `make headers`.

The library archive is built to `./out/lib/librazuberi.a` via `make lib`.

The Razuberi transpiler emits C++ code, which will `#include` the public API header file. This emitted C++ code will provide a definition for the `void run (globalScope)` function, which is declared (but not defined) within the C++ library.

The emitted C++ program can be compiled (to an object file) by adding `./out/include` to the include search path (via the compiler's `-I` CLI option) so the library header can be found.

The compiled object can be linked to the library by adding `./out/lib` to the library search path (via the compiler's `-L` CLI option) and `razbueri` to the library list (via the compiler's `-L` CLI option) so that the library archive can be found.

All of this can be seen in the `Makefile` in this directory.

## How to test

Currently, there is a not a comprehensive C++ test suite. In the future, we may rely on only end-to-end tests (i.e. transpiled JavaScript tests) to test all C++ runtime features.

For now, `./test.cpp` contains only simple tests from the latest development. Build and execute this test program via `make test`.

## Next steps

* ✅ Compile the C++ components into a archive/lib, a single file that can be linked.
* Achieve 100% implementation of ES1.
* Achieve 100% implementation of ES2.
* Achieve 100% implementation of ES3.
