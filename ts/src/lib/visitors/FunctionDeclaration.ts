
import type { VisitNodeObject } from '@babel/traverse'
import type { File, FunctionDeclaration, Node } from '@babel/types'

const { isFunctionDeclaration, returnStatement } = await import('@babel/types')

export const FunctionDeclarationVisitor: VisitNodeObject<unknown, FunctionDeclaration> = {
  enter (path) {
    // Tell the root File node about the existence of this function.
    const file = path.scope.getProgramParent().path.parent as File
    file.extra.functions.push(path.node);
  },
  exit (path) {
    // Ensure that the generated C++ code has a return statement.
    const statements = path.node.body.body
    const lastStatement = statements[statements.length - 1]
    if (
      statements.length === 0 ||
      lastStatement.type !== 'ReturnStatement'
    ) {
      path.get('body').pushContainer('body', returnStatement())
    }

    // Hoist this FunctionDeclaration to the top of the block is it declared inside of.
    const blockParentPath = path.scope.parent.getBlockParent().path
    if (blockParentPath.isBlockParent()) {
      const container = path.container as Node[]
      const oldIndex = container.indexOf(path.node)
      const [functionDeclaration] = container.splice(oldIndex, 1)
      const newIndex = container.findIndex(n => !isFunctionDeclaration(n))
      container.splice(newIndex, 0, functionDeclaration);
    } else {
      throw new Error(`Unexpected block parent type '${blockParentPath.node.type}' in FunctionDeclarationVisitor`)
    }
  }
}
