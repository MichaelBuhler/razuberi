
import type { CallExpression } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const CallExpressionGenerator: Generator<CallExpression> = ({ callee, arguments: args }) => {
  let code = '';
  if (callee.type === 'MemberExpression' || callee.type === 'Identifier') {
    code = '(' + generate(callee) + ').call'
  } else {
    code = generate(callee) + '->call'
  }
  if (args.length === 0) {
    code += '()'
  } else if (args.length === 1) {
    code += '(' + generate(args[0]) + ')'
  } else {
    code += '((' + args.map(generate).join(', ') + '))'
  }
  return code;
}
