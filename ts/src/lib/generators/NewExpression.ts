
import type { NewExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const NewExpressionGenerator: Generator<NewExpression> = ({ callee, arguments: args }) => {
  if (args.length === 0) {
    return `_new(${generate(callee)})`
  } else if (args.length === 1) {
    return `_new(${generate(callee)}, ${generate(args[0])})`
  } else {
    return `_new(${generate(callee)}, (${args.map(generate).join(', ')}))`
  }
}
