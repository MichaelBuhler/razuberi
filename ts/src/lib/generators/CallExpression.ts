
import type { CallExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const CallExpressionGenerator: Generator<CallExpression> = ({ callee, arguments: args }) => {
  if (args.length === 0) {
    return `_call(${generate(callee)}, scope)`
  } else if (args.length === 1) {
    return `_call(${generate(callee)}, scope, ${generate(args[0])})`
  } else {
    return `_call(${generate(callee)}, scope, (${args.map(generate).join(', ')}))`
  }
}
