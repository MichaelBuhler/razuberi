
import type { VisitNodeObject } from '@babel/traverse'
import type { File, FunctionExpression } from '@babel/types'

import { returnStatement } from '@babel/types'

import type { RazuberiTraversalState } from './state.js'

export const FunctionExpressionVisitor: VisitNodeObject<RazuberiTraversalState, FunctionExpression> = {
  enter (path) {
    // ensure we have a unique function name, for C++ purposes
    const desiredCppFunctionName = path.node.extra?.desiredCppFunctionName
    // TODO: #9: analyze the parent expression for a better name?
    const cppFunctionName =  this.generateUniqueCppFunctionName(desiredCppFunctionName ?? '_anonymous')

    // Define `extra` on this FunctionDeclaration node.
    path.node.extra = {
      cppFunctionName,
      desiredCppFunctionName,
      declaredFunctions: [],
      declaredVariables: [],
    }

    // Tell the root File node about the existence of this function.
    const file = path.scope.getProgramParent().path.parent as File
    file.extra!.functions!.push(path.node);
  },
  exit (path) {
    // Ensure that the generated C++ code has a return statement.
    const statements = path.node.body.body
    const lastStatement = statements[statements.length - 1]
    if (
      lastStatement === undefined || (
        lastStatement.type !== 'ReturnStatement' &&
        lastStatement.type !== 'ThrowStatement'
      )
    ) {
      path.get('body').pushContainer('body', returnStatement())
    }
  }
}
