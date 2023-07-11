
import type { UnaryExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const UnaryExpressionGenerator: Generator<UnaryExpression> = ({ operator, argument }) => {
  switch (operator) {
    case 'typeof':
      return `_typeof(${generate(argument)})`
    case 'void':
      return `_void(${generate(argument)})`
    case 'throw':
    case 'delete':
    case '!':
    case '+':
    case '-':
    case '~':
      throw new Error(`UnaryExpression operator '${operator}' is not supported at this time`)
  }
}
