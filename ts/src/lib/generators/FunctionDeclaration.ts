
import type { FunctionDeclaration } from '@babel/types'

import type { Generator } from './types.js'

export const FunctionDeclarationGenerator: Generator<FunctionDeclaration> = ({ async, generator, id }) => {
  if (generator) {
    throw new Error("generator FunctionDeclarations are not supported at this time")
  }
  if (async) {
    throw new Error("async FunctionDeclarations are not supported at this time")
  }
  const { name } = id;
  return `scope->declare("${name}", _fn(scope, ${name}));`
}
