
import type { VisitNodeObject } from '@babel/traverse'
import type { File, FunctionDeclaration, Program } from '@babel/types'

const { returnStatement } = await import('@babel/types')

export const FunctionDeclarationVisitor: VisitNodeObject<unknown, FunctionDeclaration> = {
  enter (path) {
    // Define `extra` on this FunctionDeclaration node.
    path.node.extra = {
      declaredFunctions: [],
      declaredVariables: [],
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

    // Tell the parent Function node about the declaration of this function.
    const functionScope = path.scope.parent.getFunctionParent()
    if (functionScope) {
      const functionPath = functionScope.path;
      if (
        !functionPath.isFunctionDeclaration() &&
        !functionPath.isFunctionExpression()
      ) {
        throw new Error(`FunctionDeclarationVisitor: Unsupported function parent type '${functionPath.node.type}'`)
      }
      functionPath.node.extra.declaredFunctions.push(path.node.id.name)
    } else {
      // If this function was not declared inside of a Function,
      // then tell the Program node about the declaration of this function.
      const programScope = path.scope.getProgramParent()
      const programNode = programScope.path.node as Program
      programNode.extra.declaredFunctions.push(path.node.id.name)
    }

    // Remove this FunctionDeclaration node from the AST.
    path.remove()
  }
}
