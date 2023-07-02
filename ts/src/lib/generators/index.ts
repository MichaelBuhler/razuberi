
import type { Node } from '@babel/types'

import type { Generator } from './types.js'

import { AssignmentExpressionGenerator } from './AssignmentExpression.js'
import { BinaryExpressionGenerator } from './BinaryExpression.js'
import { BooleanLiteralGenerator } from './BooleanLiteral.js'
import { CallExpressionGenerator } from './CallExpression.js'
import { EmptyStatementGenerator } from './EmptyStatement.js'
import { ExpressionStatementGenerator } from './ExpressionStatement.js'
import { FileGenerator } from './File.js'
import { IdentifierGenerator } from './Identifier.js'
import { MemberExpressionGenerator } from './MemberExpression.js'
import { NewExpressionGenerator } from './NewExpression.js'
import { NullLiteralGenerator } from './NullLiteral.js'
import { NumericLiteralGenerator } from './NumericLiteral.js'
import { ProgramGenerator } from './Program.js'
import { StringLiteralGenerator } from './StringLiteral.js'

const generators: Partial<{
  [nodeType in Node['type']]: Generator<Node>
}> = {
  AssignmentExpression: AssignmentExpressionGenerator,
  BinaryExpression: BinaryExpressionGenerator,
  BooleanLiteral:BooleanLiteralGenerator,
  CallExpression: CallExpressionGenerator,
  EmptyStatement: EmptyStatementGenerator,
  ExpressionStatement: ExpressionStatementGenerator,
  File: FileGenerator,
  Identifier: IdentifierGenerator,
  MemberExpression: MemberExpressionGenerator,
  NewExpression: NewExpressionGenerator,
  NullLiteral: NullLiteralGenerator,
  NumericLiteral: NumericLiteralGenerator,
  Program: ProgramGenerator,
  StringLiteral: StringLiteralGenerator,
}

export default generators
