
import type { Node } from '@babel/types'

import type { Generator } from './types.js'

import { AssignmentExpressionGenerator } from './AssignmentExpression.js'
import { BinaryExpressionGenerator } from './BinaryExpression.js'
import { BlockStatementGenerator } from './BlockStatement.js'
import { BooleanLiteralGenerator } from './BooleanLiteral.js'
import { BreakStatementGenerator } from './BreakStatement.js'
import { CallExpressionGenerator } from './CallExpression.js'
import { CatchClauseGenerator } from './CatchClause.js'
import { ConditionalExpressionGenerator } from './ConditionalExpression.js'
import { EmptyStatementGenerator } from './EmptyStatement.js'
import { ExpressionStatementGenerator } from './ExpressionStatement.js'
import { FileGenerator } from './File.js'
import { ForStatementGenerator } from './ForStatement.js'
import { FunctionExpressionGenerator } from './FunctionExpression.js'
import { IdentifierGenerator } from './Identifier.js'
import { IfStatementGenerator } from './IfStatement.js'
import { MemberExpressionGenerator } from './MemberExpression.js'
import { NewExpressionGenerator } from './NewExpression.js'
import { NullLiteralGenerator } from './NullLiteral.js'
import { NumericLiteralGenerator } from './NumericLiteral.js'
import { ObjectExpressionGenerator } from './ObjectExpression.js'
import { ProgramGenerator } from './Program.js'
import { ReturnStatementGenerator } from './ReturnStatement.js'
import { StringLiteralGenerator } from './StringLiteral.js'
import { ThisExpressionGenerator } from './ThisExpression.js'
import { ThrowStatementGenerator } from './ThrowStatement.js'
import { TryStatementGenerator } from './TryStatement.js'
import { UnaryExpressionGenerator } from './UnaryExpression.js'
import { WhileStatementGenerator } from './WhileStatement.js'

export const generators: Partial<{
  [nodeType in Node['type']]: Generator<Node>
}> = {
  AssignmentExpression: AssignmentExpressionGenerator,
  BinaryExpression: BinaryExpressionGenerator,
  BlockStatement: BlockStatementGenerator,
  BooleanLiteral:BooleanLiteralGenerator,
  BreakStatement: BreakStatementGenerator,
  CallExpression: CallExpressionGenerator,
  CatchClause: CatchClauseGenerator,
  ConditionalExpression: ConditionalExpressionGenerator,
  EmptyStatement: EmptyStatementGenerator,
  ExpressionStatement: ExpressionStatementGenerator,
  File: FileGenerator,
  ForStatement: ForStatementGenerator,
  FunctionExpression: FunctionExpressionGenerator,
  Identifier: IdentifierGenerator,
  IfStatement: IfStatementGenerator,
  MemberExpression: MemberExpressionGenerator,
  NewExpression: NewExpressionGenerator,
  NullLiteral: NullLiteralGenerator,
  NumericLiteral: NumericLiteralGenerator,
  ObjectExpression: ObjectExpressionGenerator,
  Program: ProgramGenerator,
  ReturnStatement: ReturnStatementGenerator,
  StringLiteral: StringLiteralGenerator,
  ThisExpression: ThisExpressionGenerator,
  ThrowStatement: ThrowStatementGenerator,
  TryStatement: TryStatementGenerator,
  UnaryExpression: UnaryExpressionGenerator,
  WhileStatement: WhileStatementGenerator,
}
