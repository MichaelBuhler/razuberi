
import type { VisitNodeObject } from '@babel/traverse'
import type { VariableDeclaration } from '@babel/types'

import { assignmentExpression, expressionStatement } from '@babel/types'

import type { RazuberiTraversalState } from './state.js'

export const VariableDeclarationVisitor: VisitNodeObject<RazuberiTraversalState, VariableDeclaration> = {
  enter (path) {
    if (path.node.kind !== 'var') {
      throw new Error('Only VariableDeclarations of the kind \'var\' are supported at this time')
    }
  },
  exit (path) {
    const initializingDeclarations = path.node.declarations.filter(({ init }) => !!init)
    const assignmentExpressions = initializingDeclarations.map(({ id, init }) => assignmentExpression('=', id, init))
    const expressionStatements = assignmentExpressions.map(x => expressionStatement(x))
    path.replaceWithMultiple(expressionStatements)
  }
}
