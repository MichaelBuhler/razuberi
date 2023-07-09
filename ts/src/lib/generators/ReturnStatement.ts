
import type { ReturnStatement } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const ReturnStatementGenerator: Generator<ReturnStatement> = ({ argument }) => {
  if (argument) {
    if ( argument.type === 'Identifier' || argument.type === 'MemberExpression' ) {
      return `return GetValue(${generate(argument)});`
    } else {
      return `return ${generate(argument)};`
    }
  } else {
    return 'return nullptr;'
  }
}
