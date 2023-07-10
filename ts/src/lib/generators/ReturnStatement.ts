
import type { ReturnStatement } from '@babel/types'

import type { Generator } from './types.js'

import { GetValue } from './utils.js'

export const ReturnStatementGenerator: Generator<ReturnStatement> = ({ argument }) => {
  if (argument) {
    return `return ${GetValue(argument)};`
  } else {
    return 'return nullptr;'
  }
}
