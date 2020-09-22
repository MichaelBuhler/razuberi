
import { VisitNodeObject } from '@babel/traverse'
import * as t from '@babel/types'

export const StringLiteral: VisitNodeObject<unknown, t.StringLiteral> = {
  exit (path) {
    const { node } = path
    const { value } = node

    const code = JSON.stringify(value)

    const string = `StringLiteral (${JSON.stringify(value)})`

    node.razuberi = { code, string }
  }
}
