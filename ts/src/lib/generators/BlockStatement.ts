
import type { BlockStatement } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const BlockStatementGenerator: Generator<BlockStatement> = ({ body }) => {
  return `{
    ${body.map(statement => generate(statement)).join('\n')}
  }`
}
