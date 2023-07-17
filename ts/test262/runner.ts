
import { spawn } from 'node:child_process'
import { writeFile } from 'node:fs/promises'
const path = await import('node:path')

import test from 'ava'
import { mkdirp } from 'fs-extra'

import { load } from './loader.js'
import { transpile } from '../dist/index.js'

const __dirname = path.dirname(import.meta.url.slice(5))
const buildDir = path.join(__dirname, 'build')
// TODO: in the future, the cpp dirs will need to be distributed with
//       this package, rather than being referenced via '../../cpp'
const cppDir =  path.join(__dirname, '..', '..', 'cpp')
const cppIncludeDir = path.join(cppDir, 'out', 'include')
const cppLibraryDir = path.join(cppDir, 'out', 'lib')

enum STAGE {
  LOAD = 'Load',
  TRANSPILE = 'Transpile',
  COMPILE = 'Compile',
  EXECUTE = 'Execute'
}

export const runner = test.macro({
  title (_, testFile: string) {
    return testFile
  },
  async exec (t, testFile: string) {
    let snapshotMessage = '| Test Stage | Status | Details |\n| :-- | :-- | :-- |\n'
    let append = (stage: STAGE, status: string, details?: string) => snapshotMessage += `| ${stage} | ${status} | ${details||''} |\n`
    const pass = (stage: STAGE) => append(stage, '✅ Pass')
    const fail = (stage: STAGE, details: string) => {
      append(stage, '❌ Fail', details)
      switch (stage) {
       case STAGE.LOAD:
        skip(STAGE.TRANSPILE)
       case STAGE.TRANSPILE:
        skip(STAGE.COMPILE)
       case STAGE.COMPILE:
        skip(STAGE.EXECUTE)
      }
    }
    const skip = (stage: STAGE) => append(stage, '⬜ Skip', '*This stage did not run.*')

    try {
      const basePath = path.join(buildDir, testFile).slice(0, -3)
      await mkdirp(path.dirname(basePath))

      const rawFile = basePath + '.raw.js'
      const cppFile = basePath + '.cpp'
      const exeFile = basePath + '.exe'

      let rawCode: string
      try {
        rawCode = await load(testFile)
        pass(STAGE.LOAD)
      } catch (e) {
        fail(STAGE.LOAD, 'An error occurred while loading the test from the `test262` folder.')
        throw e
      }

      await writeFile(rawFile, rawCode)

      let cppCode: string
      try {
        cppCode = transpile(rawCode)
        pass(STAGE.TRANSPILE)
      } catch (e) {
        fail(STAGE.TRANSPILE, 'An error occurred while transpiling the test with `@razuberi/transpiler`.')
        throw e
      }

      await writeFile(cppFile, cppCode)

      await new Promise<void>((resolve, reject) => {
        const compiler = spawn('g++', [
          '-I', cppIncludeDir, // where to look for headers
          '-L', cppLibraryDir, // where to look for libs
          '-l', 'razuberi',    // load librazuberi.a
          '-o', exeFile,       // write the executable to the temp directory
          '-x', 'c++',         // tell the compiler the input is C++ (because we are reading from stdin)
          '-',                 // read from stdin
        ])

        compiler.stdin.end(cppCode)

        let stderr = ''
        compiler.stderr.on('data', chunk => {
          stderr += String(chunk)
        })

        compiler.on('close', exitCode => {
          if (exitCode === 0) {
            pass(STAGE.COMPILE)
            resolve()
          } else {
            fail(STAGE.COMPILE, 'An error occurred while compiling the test with `g++`.')
            reject(new Error(stderr.trim()))
          }
        })
      })

      await new Promise<void>((resolve, reject) => {
        const program = spawn(exeFile)

        let stderr = ''
        program.stderr.on('data', chunk => {
          stderr += String(chunk)
        })

        program.on('close', exitCode => {
          if (exitCode === 0) {
            pass(STAGE.EXECUTE)
            resolve()
          } else {
            fail(STAGE.EXECUTE, 'An error occurred while executing the test program.')
            reject(new Error(stderr.trim()))
          }
        })
      })

      t.snapshot('No error', snapshotMessage.trim())
    } catch (e) {
      t.snapshot(e, snapshotMessage.trim())
      t.fail()
    }
  }
})
