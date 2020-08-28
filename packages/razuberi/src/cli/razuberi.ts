
import * as fs from 'fs'
import * as path from 'path'

import { transpile } from "../transpile"

const inFile = path.join(process.cwd(), process.argv[2])

const source = fs.readFileSync(inFile, 'utf-8')

const output = transpile(source)

if (process.argv[3]) {
  const outFile = path.join(process.cwd(), process.argv[3])
  fs.writeFileSync(outFile, output)
} else {
  console.log(output)
}
