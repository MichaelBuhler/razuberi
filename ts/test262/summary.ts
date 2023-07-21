
const path = await import('node:path')

import { execa } from 'execa'
import { glob } from 'glob'

import { NO_ERROR, TOP_LEVEL_TEST_FOLDERS } from './config.js'

const __dirname = path.dirname(import.meta.url.slice(5))
const packageDir = path.join(__dirname, '..')
const test262Dir = path.join(packageDir, 'node_modules', 'test262')
const testDir = path.join(test262Dir, 'test')
const snapshotDir = path.join(__dirname, 'snapshots')

const columnSpacing = ' '.repeat(3)
const hr = '-------------------------------------------'

console.log('folder      tests    pass    fail   percent')
console.log(hr)

let totalTestCount = 0
let totalPassCount = 0

for await (const folder of TOP_LEVEL_TEST_FOLDERS) {
  const testCount = (await glob('**/*.js', {
    cwd: path.join(testDir, folder)
  })).filter(x => x.indexOf('FIXTURE') === -1).length
  totalTestCount += testCount

  const passCount = (await execa('grep', [
    '-R',     // search recursively 
    '-c',     // count the number of occurences
    NO_ERROR, // the search term
    folder,   // search this folder
  ], {
    cwd: snapshotDir,
    reject: false,    // don't throw an error if grep exits with code 1 because there were 0 occurences found
  })).stdout.trim().split('\n').map(x => parseInt(x.split(':')[1])).reduce((a, b) => a + b, 0)
  totalPassCount += passCount

  const failCount = testCount - passCount
  const percentage = 100 * passCount / testCount

  const cells = [
    folder.padEnd(9),
    String(testCount).padStart(5),
    String(passCount).padStart(5),
    String(failCount).padStart(5),
    percentage.toFixed(2).padStart(6) + '%',
  ]

  console.log(cells.join(columnSpacing))
}

const totalFailCount = totalTestCount - totalPassCount
const percentage = 100 * totalPassCount / totalTestCount

const cells = [
  'total    ',
  String(totalTestCount).padStart(5),
  String(totalPassCount).padStart(5),
  String(totalFailCount).padStart(5),
  percentage.toFixed(2).padStart(6) +'%',
]

console.log(hr)
console.log(cells.join(columnSpacing))