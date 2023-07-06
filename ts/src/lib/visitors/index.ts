
import type { VisitNodeObject } from '@babel/traverse'
import type { Node } from '@babel/types'

import { FunctionDeclarationVisitor } from './FunctionDeclaration.js'
import { FunctionExpressionVisitor } from './FunctionExpression.js'
import { ProgramVisitor } from './Program.js'

const visitors: Partial<{
  [nodeType in Node['type']]: VisitNodeObject<unknown,Node>
}> = {
  FunctionDeclaration: FunctionDeclarationVisitor,
  FunctionExpression: FunctionExpressionVisitor,
  Program: ProgramVisitor,
}

export default visitors
