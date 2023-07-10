
import type { VisitNodeObject } from '@babel/traverse'
import type { ConditionalExpression, Identifier, LogicalExpression } from '@babel/types'

import {
  blockStatement,
  callExpression,
  conditionalExpression,
  identifier,
  functionExpression,
  returnStatement,
  variableDeclaration,
  variableDeclarator,
} from '@babel/types'

// TODO: if either the `left` hand side or `right` hand side expressions
//       make use of a variable with this name, the behavior is undefined.
const intermediateVariable = identifier('leftHandSideValue')

/*
 * As the rules for && and || are different in C++, we will transpile this LogicalExpression into an
 * immediately invoked function expression (IIFE) which internally makes use of a conditional operator.
 */
export const LogicalExpressionVisitor: VisitNodeObject<unknown, LogicalExpression> = {
  enter (path) {
    const { left, operator, right } = path.node

    let functionIdentifier: Identifier
    let _conditionalExpression: ConditionalExpression
    switch (operator) {
      case '&&':
        functionIdentifier = identifier('andExpression')
        _conditionalExpression = conditionalExpression(intermediateVariable, right, intermediateVariable)
        break
      case '||':
        functionIdentifier = identifier('orExpression')
        _conditionalExpression = conditionalExpression(intermediateVariable, intermediateVariable, right)
        break
      case '??':
        throw new Error("The nullish coalescing operator `??` is not supported at this time")
    }

    path.replaceWith(
      callExpression(
        functionExpression(
          functionIdentifier,
          [],
          blockStatement([
            variableDeclaration('var', [
              variableDeclarator(intermediateVariable, left),
            ]),
            returnStatement(_conditionalExpression),
          ]),
        ),
        [],
      ),
    )
  }
}