
import type { UnaryExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'
import { producesReference } from './utils.js'

export const UnaryExpressionGenerator: Generator<UnaryExpression> = ({ operator, argument }) => {
  switch (operator) {
    case 'typeof':
      return `_typeof(${generate(argument)})`
    case 'void':
      return `_void(${generate(argument)})`
    case '!':
      return '!' + generate(argument)
    case '-':
      if (producesReference(argument)) {
        return `-(${generate(argument)})`
      } else {
        return '-' + generate(argument)
      }
    case 'throw':
      throw new Error('`throw` expressions are not supported at this time')
    case 'delete':
    case '+':
    case '~':
      throw new Error(`UnaryExpressions with operator \`${operator}\` are not supported at this time`)
  }
}
