
import type { Node } from '@babel/types'

import type { Generator } from './types.js'

import { CallExpressionGenerator } from './CallExpression.js'
import { EmptyStatementGenerator } from './EmptyStatement.js'
import { ExpressionStatementGenerator } from './ExpressionStatement.js'
import { FileGenerator } from './File.js'
import { IdentifierGenerator } from './Identifier.js'
import { MemberExpressionGenerator } from './MemberExpression.js'
import { ProgramGenerator } from './Program.js'
import { StringLiteralGenerator } from './StringLiteral.js'

const generators: Partial<{
  [nodeType in Node['type']]: Generator<Node>
}> = {
  CallExpression: CallExpressionGenerator,
  EmptyStatement: EmptyStatementGenerator,
  ExpressionStatement: ExpressionStatementGenerator,
  File: FileGenerator,
  Identifier: IdentifierGenerator,
  MemberExpression: MemberExpressionGenerator,
  Program: ProgramGenerator,
  StringLiteral: StringLiteralGenerator,
}

export default generators
