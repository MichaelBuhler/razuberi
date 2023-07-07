
import type { Program } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const ProgramGenerator: Generator<Program> = ({ body, extra }) => {
  const functionDeclarations = extra.functionDeclarations.map(functionDeclaration => {
    const { id: { name } } = functionDeclaration
    return `scope->declare("${name}", _fn(scope, ${name}));`
  }).join('\n')

  const statements = body.map(statement => generate(statement)).join('\n')

  return functionDeclarations + '\n\n' + statements
}
