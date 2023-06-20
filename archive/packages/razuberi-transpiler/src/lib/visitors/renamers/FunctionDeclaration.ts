
import { VisitNodeObject } from '@babel/traverse'
import * as t from '@babel/types'

export const FunctionDeclaration: VisitNodeObject<unknown, t.FunctionDeclaration> = {
  enter (path) {
    const { node, scope } = path
    const { id } = node
    const { name } = id

    scope.rename(name)
  }
}
