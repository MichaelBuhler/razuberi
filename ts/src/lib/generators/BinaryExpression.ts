
import type { BinaryExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const BinaryExpressionGenerator: Generator<BinaryExpression> = ({ left, operator, right }) => {
  switch (operator) {
    case '+':
    case '==':
    case '/':
    case '%':
      return generate(left) + operator + generate(right)
    case '===':
      return `_strictEquals(${generate(left)}, ${generate(right)})`
    case '!==':
      return `_strictNotEquals(${generate(left)}, ${generate(right)})`
    case 'instanceof':
      return `_instanceOf(${generate(left)}, ${generate(right)})`
    case 'in':
      return `_in(${generate(left)}, ${generate(right)})`
    case '-':
    case '*':
    case '**':
    case '&':
    case '|':
    case '>>':
    case '>>>':
    case '<<':
    case '^':
    case '!=':
    case '>':
    case '<':
    case '>=':
    case '<=':
    // TODO: what the heck is this operator?
    case '|>':
      throw new Error(`BinaryExpressions with operator \`${operator}\` are not supported at this time`)
  }
}
