# razuberi

A TypeScript -> C++ transpiler.

## Vision

To be able to compile JavaScript and TypeScript applications that can be 'run anywhere', even baremetal.

## Current state

Previous work was targetting the C programming language. This can be seen in the `/archive` folder.

Work is now being done on the C++ lib to implement the JS core features. See the `/cpp` forlder for more info, especially the `/cpp/README.md`.

## Next steps

* Get end-to-end "Hello, World" example working.
* Determine/enforce a C++ target level.
* Execute `test262` with one command.
