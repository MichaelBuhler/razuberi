
import type { Node } from '@babel/types'

import type { Generator } from './types.js'

import { AssignmentExpressionGenerator } from './AssignmentExpression.js'
import { BinaryExpressionGenerator } from './BinaryExpression.js'
import { BlockStatementGenerator } from './BlockStatement.js'
import { BooleanLiteralGenerator } from './BooleanLiteral.js'
import { CallExpressionGenerator } from './CallExpression.js'
import { ConditionalExpressionGenerator } from './ConditionalExpression.js'
import { EmptyStatementGenerator } from './EmptyStatement.js'
import { ExpressionStatementGenerator } from './ExpressionStatement.js'
import { FileGenerator } from './File.js'
import { FunctionDeclarationGenerator } from './FunctionDeclaration.js'
import { FunctionExpressionGenerator } from './FunctionExpression.js'
import { IdentifierGenerator } from './Identifier.js'
import { IfStatementGenerator } from './IfStatement.js'
import { MemberExpressionGenerator } from './MemberExpression.js'
import { NewExpressionGenerator } from './NewExpression.js'
import { NullLiteralGenerator } from './NullLiteral.js'
import { NumericLiteralGenerator } from './NumericLiteral.js'
import { ProgramGenerator } from './Program.js'
import { ReturnStatementGenerator } from './ReturnStatement.js'
import { StringLiteralGenerator } from './StringLiteral.js'
import { ThisExpressionGenerator } from './ThisExpression.js'

const generators: Partial<{
  [nodeType in Node['type']]: Generator<Node>
}> = {
  AssignmentExpression: AssignmentExpressionGenerator,
  BinaryExpression: BinaryExpressionGenerator,
  BlockStatement: BlockStatementGenerator,
  BooleanLiteral:BooleanLiteralGenerator,
  CallExpression: CallExpressionGenerator,
  ConditionalExpression: ConditionalExpressionGenerator,
  EmptyStatement: EmptyStatementGenerator,
  ExpressionStatement: ExpressionStatementGenerator,
  File: FileGenerator,
  FunctionDeclaration: FunctionDeclarationGenerator,
  FunctionExpression: FunctionExpressionGenerator,
  Identifier: IdentifierGenerator,
  IfStatement: IfStatementGenerator,
  MemberExpression: MemberExpressionGenerator,
  NewExpression: NewExpressionGenerator,
  NullLiteral: NullLiteralGenerator,
  NumericLiteral: NumericLiteralGenerator,
  Program: ProgramGenerator,
  ReturnStatement: ReturnStatementGenerator,
  StringLiteral: StringLiteralGenerator,
  ThisExpression: ThisExpressionGenerator,
}

export default generators
