
import { VisitNodeObject } from '@babel/traverse'
import * as t from '@babel/types'

import { getProgramPath } from './utils'

export const FunctionExpression: VisitNodeObject<unknown, t.FunctionExpression> = {
  enter (path) {
    const { node } = path
    const { params, body } = node
    const { id } = node
    const { name } = id

    const functionDeclaration = t.functionDeclaration(id, params, body)
    getProgramPath(path).pushContainer('body', functionDeclaration)
    path.replaceWith(t.identifier(name))
  }
}
