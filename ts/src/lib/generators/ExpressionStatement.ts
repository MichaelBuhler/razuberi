
import type { ExpressionStatement } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const ExpressionStatementGenerator: Generator<ExpressionStatement> = ({ expression }) => {
  // TODO: ES1: 12.4.2: do we need to `GetValue` of the expression?
  return generate(expression) + ';'
}
