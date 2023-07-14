# @razuberi/transpiler

Razuberi is a JavaScript/TypeScript -> C++ transpiler. The transpiler is written in TypeScript.

## Installation

```
npm i [-g] @razuberi/transpiler
yarn add [-g] @razuberi/transpiler
pnpm add [-g] @razuberi/transpiler
```

Global install should add `razuberi` to your path, otherwise use `npx razuberi` within your package.
See below for CLI usage, or execute `razuberi --help`.

## Usage

Use this package to convert source files into C++. The transpiler emits C++ code that is designed to be compiled against/linked with `librazuberi`.
See [here](https://github.com/MichaelBuhler/razuberi/blob/master/cpp/README.md) for more information.

## API

The transpiler can be used programmatically. This package exports a `transpile()` function as a named export.

```javascript
import { transpile } from '@razuberi/transpiler'

const javascript = `console.log('Hello, world!)`
const cpp = transpile(javascript)
console.log(cpp)
```

## CLI

The transpiler can be invoked from the command line, or in an npm script.

```
$ cat helloworld.js
console.log('Hello, world!)
$ razuberi helloworld.js --out helloworld.cpp
$ cat helloworld.cpp
```

### Command line options

```
usage: razuberi [-h | --help]
       razuberi <inputFile> [[-o | --out] <outputFile>]
       razuberi --stdin [[-o | --out] <outputFile>]

positional arguments:
  <inputFile>           the input file to transpile. pass "--stdin" to read from `stdin`.

optional arguments:
  -h, --help            show this help message and exit
  --stdin               read from stdin
  -o <outputFile>, --out <outputFile>
                        write C++ output to this file. defaults to `stdout`.
```
