
import { VisitNodeObject } from '@babel/traverse'
import * as t from '@babel/types'

export const Identifier: VisitNodeObject<unknown, t.Identifier> = {
  exit (path) {
    const { node } = path
    const { name } = node

    const code = name

    const string = `Identifier (${name})`

    node.razuberi = { code, string }
  }
}
