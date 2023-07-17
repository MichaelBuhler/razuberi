
const path = await import('node:path')

import { readFile } from 'node:fs/promises'

// @ts-ignore
import test262Parser from 'test262-parser'

const standardIncludes = ['assert.js', 'sta.js']

const __dirname = path.dirname(import.meta.url.slice(5))
const packageDir = path.join(__dirname, '..')
const test262Dir = path.join(packageDir, 'node_modules', 'test262')
const includesDir = path.join(test262Dir, 'harness')
const testDir = path.join(test262Dir, 'test')

const includesCache: Record<string, string> = {}
async function include (includeFile: string) : Promise<string> {
  return includesCache[includeFile] ??= await readFile(path.join(includesDir, includeFile), 'utf-8')
}

class LoaderError extends Error {
  name = 'LoaderError'
}

export const load = async (testFile: string) : Promise<string> => {
  const testFilename = path.join(testDir, testFile)
  const { contents, attrs: { flags, includes, negative } } = test262Parser.parseFile(await readFile(testFilename, 'utf-8'))

  if (negative) {
    throw new LoaderError('Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.')
  }

  for (const flag of Object.keys(flags)) {
    // https://github.com/tc39/test262/blob/main/INTERPRETING.md#flags
    switch (flag) {
      case 'onlyStrict':
      case 'noStrict':
        // TODO: #17: execute tests in one or both of "strict" and "non-strict" modes
        // 2023-07-16:
        // The 'onlyStrict' and `noStrict` flags are ignored at this time.
        // In effect, all tests are executed without the `"use-strict";\n` directive.
        break;
      case 'module':
        throw new LoaderError(`Modules, and thus tests with the \`module\` flag, are not supported at this time.`)
      case 'raw':
        // raw flags are handled below
        break;
      case 'async':
        throw new LoaderError(`Async/await, event loop, etc. are not implemented, and thus, tests with the \`async\` flag are not supported at this time.`)
      case 'generated':
        // "This flag is specified for informational purposes only and has no bearing on how the test should be interpreted."
        break;
      case 'CanBlockIsFalse':
      case 'CanBlockIsTrue':
        throw new LoaderError(`Agents and Agents Records are not implemented, and thus, tests with the \`${flag}\` flag are not supported at this time.`)
      case 'non-deterministic':
        // ignore this
        break;
      default:
        throw new LoaderError(`Unrecognized \`${flag}\` test flag.`)
    }
  }

  const filesToInclude: string[] = []
  if (!flags.raw) {
    filesToInclude.push(...standardIncludes, ...includes)
  }

  let code = ''
  for (const fileToInclude of filesToInclude) {
    code += await include(fileToInclude) + '\n'
  }
  code += contents

  return code
}
