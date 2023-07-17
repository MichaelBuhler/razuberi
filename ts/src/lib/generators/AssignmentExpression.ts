
import type { AssignmentExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const AssignmentExpressionGenerator: Generator<AssignmentExpression> = ({ left, right }) => {
  if (left.type !== 'Identifier' && left.type !== 'MemberExpression') {
    throw new Error(`AssignmentExpressions with left hand sides of type \`${left.type}\` are not supported at this time`)
  }
  return generate(left) + ' = ' + generate(right);
}
