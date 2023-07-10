
import type { Expression } from '@babel/types'

import { generate } from '../generate.js'

export const GetValue = (expression: Expression) : string => {
  if (expression.type === 'Identifier' || expression.type == 'MemberExpression') {
    return `GetValue(${generate(expression)})`
  } else {
    return generate(expression)
  }
}
