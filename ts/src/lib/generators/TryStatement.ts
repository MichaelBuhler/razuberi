
import type { TryStatement } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const TryStatementGenerator: Generator<TryStatement> = ({ block, handler, finalizer }) => {
  let code = 'try ' + generate(block)
  if (handler) code += ' ' + generate(handler)
  if (finalizer) {
    throw new Error("'finally' blocks are not supported at this time")
  }
  return code
}
