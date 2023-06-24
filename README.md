# razuberi

A TypeScript -> C++ transpiler.

## Vision

To be able to compile JavaScript and TypeScript applications that can be 'run anywhere', even baremetal.

## Current State

Previous work was targetting the C programming language. This can be seen in the `/archive` folder.

Working on the C++ lib to implement the js core features.

## How to Test

Funtionality supported by the C++ lib are covered by a simple `test.cpp`. Build and execute like so:

```shell
make
make test
```

## Next Steps

* Get end-to-end "Hello, World" example working.
* Determine/enforce a C++ target level.
* Execute `test262` with one command.
* Compile the C++ components into a archive/lib, a single file that can be linked.
