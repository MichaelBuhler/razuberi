
import { VisitNodeObject } from '@babel/traverse'
import * as t from '@babel/types'

import { getProgramPath } from './utils'

export const FunctionDeclaration: VisitNodeObject<unknown, t.FunctionDeclaration> = {
  enter (path) {
    const { node, parentPath } = path

    if (!parentPath.isProgram()) {
      getProgramPath(path).pushContainer('body', node)
      path.remove()
    }
  }
}
