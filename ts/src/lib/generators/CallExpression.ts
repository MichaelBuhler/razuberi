
import type { CallExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const CallExpressionGenerator: Generator<CallExpression> = ({ callee, arguments: _arguments }) => {
  if (callee.type != 'MemberExpression') {
    throw new Error(`CallExpressions only support MemberExpression callees at this time (got ${callee.type})`)
  }

  const args = _arguments.map(arg => generate(arg))

  return `
    vector<shared_ptr<Value> > args;
    ${args.map(arg => `args.push_back(${arg});`).join('')}
    _call(${generate(callee)}, scope, args)
  `
}