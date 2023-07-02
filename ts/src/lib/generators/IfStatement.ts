
import type { IfStatement } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const IfStatementGenerator: Generator<IfStatement> = ({ test, consequent, alternate }) => {
  let code = `if (_if(${generate(test)})) ${generate(consequent)}`
  if (alternate) {
    code += `else ${generate(alternate)}`
  }
  return code
}
