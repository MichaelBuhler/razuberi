
const path = await import('node:path')

import { glob } from 'glob'

const __dirname = path.dirname(import.meta.url.slice(5))
const snapshotDir = path.join(__dirname, 'snapshots')

const testFiles = new Set(await glob('*/**/*.js', {
  cwd: __dirname,
  nodir: true,
  ignore: 'build/**/*',
}))

const snapshotFiles = await glob('**/*.js.md', {
  cwd: snapshotDir,
  nodir: true,
})

for (const snapshotFile of snapshotFiles) {
  testFiles.delete(snapshotFile.slice(0, -3))
}

console.log(Array.from(testFiles).join('\n'))
