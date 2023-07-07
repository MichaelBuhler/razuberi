
import type { VisitNodeObject } from '@babel/traverse'
import type { VariableDeclarator, Program } from '@babel/types'

export const VariableDeclaratorVisitor: VisitNodeObject<unknown, VariableDeclarator> = {
  enter (path) {
    const idPath = path.get("id")
    if (!idPath.isIdentifier()) {
      throw new Error('Only Identifier l-values are supported in VariableDeclarators at this time')
    }

    // Tell the parent Function node about the declaration of this variable.
    const functionPath = path.getFunctionParent()
    if (functionPath) {
      if (
        !functionPath.isFunctionDeclaration() &&
        !functionPath.isFunctionExpression()
      ) {
        throw new Error(`VariableDeclaratorVisitor: Unsupported function parent type '${functionPath.node.type}'`) 
      }
      functionPath.node.extra.declaredVariables.push(idPath.node.name)
    } else {
      // If this variable was not declared inside of a Function,
      // then tell the Program node about the declaration of this variable.
      const programScope = path.scope.getProgramParent()
      const programNode = programScope.path.node as Program
      programNode.extra.declaredVariables.push(idPath.node.name)
    }
  }
}
