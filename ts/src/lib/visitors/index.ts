
import type { VisitNodeObject } from '@babel/traverse'
import type { Node } from '@babel/types'

import type { RazuberiTraversalState } from './state.js'

import { FunctionDeclarationVisitor } from './FunctionDeclaration.js'
import { FunctionExpressionVisitor } from './FunctionExpression.js'
import { LogicalExpressionVisitor } from './LogicalExpression.js'
import { ProgramVisitor } from './Program.js'
import { VariableDeclarationVisitor } from './VariableDeclaration.js'
import { VariableDeclaratorVisitor } from './VariableDeclarator.js'

export const visitors: Partial<{
  [nodeType in Node['type']]: VisitNodeObject<RazuberiTraversalState, Node>
}> = {
  FunctionDeclaration: FunctionDeclarationVisitor,
  FunctionExpression: FunctionExpressionVisitor,
  LogicalExpression: LogicalExpressionVisitor,
  Program: ProgramVisitor,
  VariableDeclaration: VariableDeclarationVisitor,
  VariableDeclarator: VariableDeclaratorVisitor,
}
