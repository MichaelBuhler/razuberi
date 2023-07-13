
import * as path from 'node:path'

import { ArgumentParser } from 'argparse'

const usage = `razuberi [-h | --help]
       razuberi --stdin [[-o | --out] <outputFile>]
       razuberi <inputFile> [[-o | --out] <outputFile>]`

const argParser = new ArgumentParser({
  description: 'Razuberi: a JavaScript -> TypeScript transpiler.',
  usage,
})

const argGroup = argParser.add_mutually_exclusive_group({ required: true })

argGroup.add_argument('inputFile', {
  help: 'the input file to transpile. pass "--stdin" to read from `stdin`.',
  metavar: '<inputFile>',
  nargs: '?',
  type: (arg: string) => path.join(process.cwd(), arg),
})

argGroup.add_argument('--stdin', {
  action: 'store_true',
  help: 'read from stdin',
})

argParser.add_argument('-o', '--out', {
  dest: 'outputFile',
  help: 'write C++ output to this file. defaults to `stdout`.',
  metavar: '<outputFile>',
  nargs: '?',
  type: (arg: string) => path.join(process.cwd(), arg),
})

const args = argParser.parse_args()

let inputFileContents: string
if (args.stdin) {
  const { readFileSync } = await import('node:fs')
  inputFileContents = readFileSync(process.stdin.fd, 'utf-8')
} else {
  const { readFile } = await import('node:fs/promises')
  inputFileContents = await readFile(args.inputFile, 'utf-8')
}

const { transpile } = await import('../lib/transpile.js')

const outputFileContents = transpile(inputFileContents)

if (args.outputFile) {
  const { writeFile } = await import('node:fs/promises')
  await writeFile(args.outputFile, outputFileContents)
} else {
  process.stdout.write(outputFileContents)
}
