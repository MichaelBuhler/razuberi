
import * as fs from 'fs'
import * as path from 'path'

import babelGenerate from '@babel/generator'

import { transpile } from "../src/typescript"

import { parse } from '../src/babel'

import { generate } from '../src/generate'

const basename = path.join(__dirname, 'helloworld')

const typescript = fs.readFileSync(`${basename}.ts`, 'utf-8')

const javascript = transpile(typescript)

fs.writeFileSync(`${basename}.js`, javascript)

const babelFileNode = parse(javascript, 'helloworld')

fs.writeFileSync(`${basename}.babel.json`, JSON.stringify(babelFileNode, null, 2))

const razuberiFile = generate(babelFileNode)

console.log(razuberiFile.string)

console.log()

console.log(razuberiFile.code)

fs.writeFileSync(`${basename}.razuberi.json`, JSON.stringify(babelFileNode, null, 2))

fs.writeFileSync(`${basename}.razuberi.js`, babelGenerate(babelFileNode).code)

fs.writeFileSync(`${basename}.c`, razuberiFile.code)
