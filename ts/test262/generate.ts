
import { readFile } from 'node:fs/promises'
const path = await import('node:path')

import { outputFile as writeFile } from 'fs-extra/esm'
import { glob } from 'glob'

const __dirname = path.dirname(import.meta.url.slice(5))
const runnerJs = path.join(__dirname, 'runner.js')
const snapshotJs = path.join(__dirname, 'snapshot.js')
const packageDir = path.join(__dirname, '..')
const test262Dir = path.join(packageDir, 'node_modules', 'test262')

// load the test template file from this directory
const templateFile = path.join(__dirname, 'template.js')
const template = await readFile(templateFile, 'utf-8')

// get all test262 test files, relative to the `test262/test` folder
const testFiles = await glob('**/*.js', {
  cwd: path.join(test262Dir, 'test'),
  nodir: true,
})

// only directories which contain test files are test folders
const testFolders = new Set<string>()
for (const testFile of testFiles) {
  testFolders.add(path.dirname(testFile))
}

// we will output an `ava` test file, for each `test262` test folder
// the `ava` test file will run a test for each `test262` test file in that `test262` test folder
await Promise.all(Array.from(testFolders).map(async testFolder => {
  const outputFolder = path.join(__dirname, testFolder)
  const outputFile = path.join(outputFolder, 'index.js')
  const outputContents = template
    .replace(/\/\*(?:.|\n)*?\*\//, '/*\n * This is a generated file\n */')
    .replace('__RELATIVE_PATH_TO_RUNNER_JS__', path.relative(outputFolder, runnerJs))
    .replace('__RELATIVE_PATH_TO_SNAPSHOT_JS__', path.relative(outputFolder, snapshotJs))
    .replace('__TEST_FOLDER__' , testFolder.split(path.sep).join('/'))
    .replace('__TEST262_DIR__', test262Dir)
  
  await writeFile(outputFile, outputContents)
}))
