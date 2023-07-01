
import type { BinaryExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const BinaryExpressionGenerator: Generator<BinaryExpression> = ({ left, operator, right }) => {
  switch (operator) {
    case '+':
      return generate(left) + operator + generate(right)
    case '-':
    case '/':
    case '%':
    case '*':
    case '**':
    case '&':
    case '|':
    case '>>':
    case '>>>':
    case '<<':
    case '^':
    case '==':
    case '===':
    case '!=':
    case '!==':
    case 'in':
    case 'instanceof':
    case '>':
    case '<':
    case '>=':
    case '<=':
    case '|>':
      throw new Error(`BinaryExpression operator '${operator}' is not supported at this time`)
  }
}
