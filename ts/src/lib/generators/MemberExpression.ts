
import type { MemberExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const MemberExpressionGenerator: Generator<MemberExpression> = ({ object, property }) => {
  switch (property.type) {
    case 'Identifier':
      return generate(object) + `->*"${property.name}"`
    case 'NumericLiteral':
      return generate(object) + `->*"${property.value}"`
    case 'StringLiteral':
      return generate(object) + `->*${JSON.stringify(property.value)}`
    default:
      throw new Error(`MemberExpression properties of type \`${property.type}\` are not supported at this time`)
  }
}
