
import * as fs from 'fs'
import * as path from 'path'

import { transpile } from "../transpile"

const filename = path.join(process.cwd(), process.argv[2])

const source = fs.readFileSync(filename, 'utf-8')

const output = transpile(source)

console.log(output)
