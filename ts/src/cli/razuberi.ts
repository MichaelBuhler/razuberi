
import * as path from 'node:path'

import { ArgumentParser } from 'argparse'

const argParser = new ArgumentParser({
  description: 'Razuberi: a JavaScript -> TypeScript transpiler.',
  prog: 'razuberi',
})

argParser.add_argument('inputFilename', {
  help: 'a JavaScript/TypeScript file to transpile. only one <input> file is supported at this time.',
  metavar: '<input>',
  type: (arg: string) => path.join(process.cwd(), arg),
})

argParser.add_argument('-o', '--out', {
  default: 'a.cpp',
  dest: 'outputFilename',
  help: 'write output C++ to <file>. defaults to `a.cpp`',
  metavar: '<file>',
  type: (arg: string) => path.join(process.cwd(), arg),
})

const {
  inputFilename,
  outputFilename,
} = argParser.parse_args()

const { readFile } = await import('node:fs/promises')

const inputFileContents = await readFile(inputFilename, 'utf-8')

const { transpile } = await import('../lib/transpile.js')

const outputFileContents = transpile(inputFileContents)

const { writeFile } = await import('node:fs/promises')

await writeFile(outputFilename, outputFileContents)
