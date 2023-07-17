
import type { MemberExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const MemberExpressionGenerator: Generator<MemberExpression> = ({ object, property }) => {
  if (property.type !== 'Identifier') {
    throw new Error(`MemberExpression properties of type \`${property.type}\` are not supported at this time`)
  }
  return generate(object) + `->*"${property.name}"`
}
