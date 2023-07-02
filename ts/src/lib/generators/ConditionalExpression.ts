
import type { ConditionalExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const ConditionalExpressionGenerator: Generator<ConditionalExpression> = ({ test, consequent, alternate }) => {
  return `_if(${generate(test)}) ? ${generate(consequent)} : ${generate(alternate)}`
}
