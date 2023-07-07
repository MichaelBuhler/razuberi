
import type { Program } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const ProgramGenerator: Generator<Program> = ({ body, extra }) => {
  // TODO: #11: move the function body generator to a util
  const functionDeclarations = extra.declaredFunctions.map(fnName => {
    return `scope->declare("${fnName}", _fn(scope, ${fnName}));`
  }).join('\n')

  const variableDeclarations = extra.declaredVariables.map(varName => {
    return `scope->declare("${varName}");`
  }).join('\n')

  const statements = body.map(statement => generate(statement)).join('\n')

  let cppFunctionBody = ''
  if (functionDeclarations) cppFunctionBody += functionDeclarations
  if (variableDeclarations) cppFunctionBody += variableDeclarations
  if (cppFunctionBody && statements) cppFunctionBody += '\n\n'
  if (statements) cppFunctionBody += statements
  return cppFunctionBody
}
