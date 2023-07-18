
import type { WhileStatement } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const WhileStatementGenerator: Generator<WhileStatement> = ({ test, body }) => {
  return `while (_test(${generate(test)})) ${generate(body)}`
}
