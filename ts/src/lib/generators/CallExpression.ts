
import type { CallExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const CallExpressionGenerator: Generator<CallExpression> = ({ callee, arguments: args }) => {
  return `_call(${generate(callee)}, scope, (0, ${args.map(generate).join()}))`
}
