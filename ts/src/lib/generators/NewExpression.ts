
import type { NewExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const NewExpressionGenerator: Generator<NewExpression> = ({ callee, arguments: args }) => {
  return `_new(${generate(callee)}, (0, ${args.map(generate).join(', ')}))`
}
