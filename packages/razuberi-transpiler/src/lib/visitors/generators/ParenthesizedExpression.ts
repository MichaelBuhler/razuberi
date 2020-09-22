
import { VisitNodeObject } from '@babel/traverse'
import * as t from '@babel/types'

import { indent } from './utils'

export const ParenthesizedExpression: VisitNodeObject<unknown, t.ParenthesizedExpression> = {
  exit (path) {
    const { node } = path
    const { expression } = node

    const code = `(${expression.razuberi.code})`

    let string = 'ParenthesizedExpression\n'
    string += indent(expression.razuberi.string)

    node.razuberi = { code, string }
  }
}
