
import type { NewExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const NewExpressionGenerator: Generator<NewExpression> = ({ callee, arguments: args, extra }) => {
  const fn = extra?.parentNodeIsThrowStatement ? '_newThrowable' : '_new'
  if (args.length === 0) {
    return `${fn}(${generate(callee)})`
  } else if (args.length === 1) {
    return `${fn}(${generate(callee)}, ${generate(args[0])})`
  } else {
    return `${fn}(${generate(callee)}, (${args.map(generate).join(', ')}))`
  }
}
