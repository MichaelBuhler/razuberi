
import { VisitNodeObject } from '@babel/traverse'
import * as t from '@babel/types'

import { indent } from './utils'

export const CallExpression: VisitNodeObject<unknown, t.CallExpression> = {
  exit (path) {
    const { node } = path
    const { callee, arguments: args } = node

    const code = `${callee.razuberi.code}(${args.map(x => x.razuberi.code).join(', ')})`

    let string = 'CallExpression\n'
    string += indent('Callee') +'\n'
    string += indent(indent(callee.razuberi.string)) +'\n'
    string += indent(`Arguments (length: ${args.length})`)
    if (args.length) {
      string += '\n' + indent(indent(args.map(x => x.razuberi.string).join('\n')))
    }

    node.razuberi = { code, string }
  }
}
