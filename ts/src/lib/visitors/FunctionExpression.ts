
import type { VisitNodeObject } from '@babel/traverse'
import type { File, FunctionExpression } from '@babel/types'

const { returnStatement } = await import('@babel/types')

export const FunctionExpressionVisitor: VisitNodeObject<unknown, FunctionExpression> = {
  enter (path) {
    // Define `extra` on this FunctionDeclaration node.
    path.node.extra = {
      functionDeclarations: [],
    }

    // Give anonymous functions a name, for C++ purposes
    if (!path.node.id) {
      // TODO: #9: analyze the expression for a better name.
      // TODO: generateUidIdentifier() is only unique in this scope.
      //       For C++ ,it needs to be unique in the whole translation unit.
      path.node.id = path.scope.generateUidIdentifier('anonymous')
    }

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
  }
}
