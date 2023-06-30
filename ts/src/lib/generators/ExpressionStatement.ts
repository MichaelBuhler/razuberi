
import type { ExpressionStatement } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const ExpressionStatementGenerator: Generator<ExpressionStatement> = ({ expression }) => {
  return generate(expression) + ';'
}
