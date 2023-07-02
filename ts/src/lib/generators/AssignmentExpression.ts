
import type { AssignmentExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const AssignmentExpressionGenerator: Generator<AssignmentExpression> = ({ left, right }) => {
  return `_assign(${generate(left)}, ${generate(right)})`
}
