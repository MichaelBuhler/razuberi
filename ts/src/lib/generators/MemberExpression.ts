
import type { MemberExpression } from '@babel/types'

import type { Generator } from './types.js'
import { generate } from '../generate.js'

export const MemberExpressionGenerator: Generator<MemberExpression> = ({ object, property }) => {
  if (property.type === 'Identifier') {
    return generate(object) + `->*"${property.name}"`
  } else {
    throw new Error(`MemberExpressions only support Identifier properties at this time (got ${property.type})`)
  }
}
