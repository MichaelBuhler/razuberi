
import type { ConditionalExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'
import { GetValue } from './utils.js'

export const ConditionalExpressionGenerator: Generator<ConditionalExpression> = ({ test, consequent, alternate }) => {
  return `_test(${generate(test)}) ? ${GetValue(consequent)} : ${GetValue(alternate)}`
}
