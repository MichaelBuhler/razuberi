
import type { AssignmentExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const AssignmentExpressionGenerator: Generator<AssignmentExpression> = ({ left, right }) => {
  if (left.type !== 'Identifier' && left.type !== 'MemberExpression') {
    throw new Error(`Dangerous left hand side expression: ${left.type}`)
  }
  return generate(left) + ' = ' + generate(right);
}
