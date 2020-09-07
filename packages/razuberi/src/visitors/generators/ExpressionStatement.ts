
import { VisitNodeObject } from '@babel/traverse'
import * as t from '@babel/types'

import { indent } from './utils'

export const ExpressionStatement: VisitNodeObject<unknown, t.ExpressionStatement> = {
  exit (path) {
    const { node } = path
    const { expression } = node

    const code = `${expression.razuberi.code};`

    let string = 'ExpressionStatement\n'
    string += indent(expression.razuberi.string)

    node.razuberi = { code, string }
  }
}
