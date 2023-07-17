
import type { ObjectExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const ObjectExpressionGenerator: Generator<ObjectExpression> = ({ properties }) => {
  if (properties.length === 0) {
    return 'make_shared<Object>()'
  }

  return properties.map(property => {
    if (property.type !== 'ObjectProperty') {
      throw new Error(`ObjectExpression properties of type \`${property.type}\` are not supported at this time`)
    }
    if (property.computed) {
      throw new Error('`computed` ObjectProperties are not supported at this time')
    }
    if (property.shorthand) {
      throw new Error('`shorthand` ObjectProperties are not supported at this time')
    }
    const { key, value } = property;
    switch (key.type) {
      case 'Identifier':
        return `"${key.name}"&${generate(value)}`
      case 'NumericLiteral':
        return `"${key.value}"&${generate(value)}`
      case 'StringLiteral':
        return `${JSON.stringify(key.value)}&${generate(value)}`
      default:
        throw new Error(`ObjectProperty keys of type \`${key.type}\` are not supported at this time`)
    }
  }).join('|')
}
