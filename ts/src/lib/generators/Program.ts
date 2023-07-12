
import type { Program } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const ProgramGenerator: Generator<Program> = ({ body, extra }) => {
  const { declaredFunctions, declaredVariables } = extra

  // TODO: #11: move the function body generator to a util
  const functionDeclarations = declaredFunctions.map(fn => {
    const { id: { name }, extra: { cppFunctionName } } = fn
    return `scope->declare("${name}", _fn(scope, ${cppFunctionName}));`
  }).join('\n')

  const variableDeclarations = declaredVariables.map(variableName => {
    return `scope->declare("${variableName}");`
  }).join('\n')

  const statements = body.map(statement => generate(statement)).join('\n')

  let cppFunctionBody = ''
  if (functionDeclarations) cppFunctionBody += functionDeclarations
  if (variableDeclarations) cppFunctionBody += variableDeclarations
  if (cppFunctionBody && statements) cppFunctionBody += '\n\n'
  if (statements) cppFunctionBody += statements
  return cppFunctionBody
}
