
import type { ThrowStatement } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const ThrowStatementGenerator: Generator<ThrowStatement> = ({ argument }) => {
  const expression = generate(argument)
  let message = 'Throwing is not supported at this time\n'
  message += 'Was supposed to throw the result of this C++ expression:\n'
  message += expression;
  // TODO: need a string sanitizing utility function
  message = message.replace(/\n/g, '\\n').replace(/"/g, '\\"')
  return `${expression};\nthrow NotImplementedException("${message}");`
}
