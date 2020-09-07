
import { VisitNodeObject } from '@babel/traverse'
import * as t from '@babel/types'

import { indent } from './utils'

export const BlockStatement: VisitNodeObject<unknown, t.BlockStatement> = {
  exit (path) {
    const { node } = path
    const { body } = node

    let code = '{\n'
    code += indent(body.map(x => x.razuberi.code).join('\n')) + '\n'
    code += '}'

    let string = `BlockStatement\n`
    string += indent(body.map(x => x.razuberi.string).join('\n'))

    node.razuberi = { code, string }
  }
}
