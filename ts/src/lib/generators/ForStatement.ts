
import type { Expression, ForStatement } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'
import { GetValue } from './utils.js'

export const ForStatementGenerator: Generator<ForStatement> = ({ init, test, update, body }) => {
  return `for ( ${GetValue(init as Expression)} ; _if(${generate(test)}) ; ${generate(update)} ) ${generate(body)}`
}
