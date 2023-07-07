
import type { VisitNodeObject } from '@babel/traverse'
import type { Node } from '@babel/types'

import { FunctionDeclarationVisitor } from './FunctionDeclaration.js'
import { FunctionExpressionVisitor } from './FunctionExpression.js'
import { ProgramVisitor } from './Program.js'
import { VariableDeclarationVisitor } from './VariableDeclaration.js'
import { VariableDeclaratorVisitor } from './VariableDeclarator.js'

const visitors: Partial<{
  [nodeType in Node['type']]: VisitNodeObject<unknown,Node>
}> = {
  FunctionDeclaration: FunctionDeclarationVisitor,
  FunctionExpression: FunctionExpressionVisitor,
  Program: ProgramVisitor,
  VariableDeclaration: VariableDeclarationVisitor,
  VariableDeclarator: VariableDeclaratorVisitor,
}

export default visitors
