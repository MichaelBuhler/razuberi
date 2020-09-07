
import { VisitNodeObject } from '@babel/traverse'
import * as t from '@babel/types'

export const FunctionExpression: VisitNodeObject<unknown, t.FunctionExpression> = {
  enter (path) {
    const { node, scope } = path

    if (node.id) {
      scope.rename(node.id.name)
    } else {
      node.id = scope.generateUidIdentifier('anonymous')
    }
  }
}
