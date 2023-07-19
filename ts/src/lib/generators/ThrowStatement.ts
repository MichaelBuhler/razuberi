
import type { ThrowStatement } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'
import { producesReference, strictlyProducesValue } from './utils.js'

export const ThrowStatementGenerator: Generator<ThrowStatement> = ({ argument }) => {
  if (producesReference(argument)) {
    return `throw GetValue(${generate(argument)});`
  }
  if (strictlyProducesValue(argument)) {
    return `throw ${generate(argument)};`
  }
  return `throw static_pointer_cast<Value>(${generate(argument)});`
}
