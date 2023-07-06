
import type { FunctionExpression } from '@babel/types'

import type { Generator } from './types.js'

export const FunctionExpressionGenerator: Generator<FunctionExpression> = ({ async, generator, id }) => {
  if (generator) {
    throw new Error("generator FunctionExpressions are not supported at this time")
  }
  if (async) {
    throw new Error("async FunctionExpressions are not supported at this time")
  }
  const { name } = id;
  return `_fn(scope, ${name})`
}
