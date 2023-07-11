
import type { ThrowStatement } from '@babel/types'

import type { Generator } from './types.js'

import { GetValue } from './utils.js'

export const ThrowStatementGenerator: Generator<ThrowStatement> = ({ argument }) => {
  return `throw static_pointer_cast<Value>(${GetValue(argument)});`
}
