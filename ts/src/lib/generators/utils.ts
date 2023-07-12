
import type { Expression } from '@babel/types'

import { generate } from '../generate.js'

export const producesReference = (expression: Expression) : boolean => {
  return [
    'Identifier',
    'MemberExpression',
  ].includes(expression.type)
}

export const GetValue = (expression: Expression) : string => {
  if (producesReference(expression)) {
    return `GetValue(${generate(expression)})`
  } else {
    return generate(expression)
  }
}
