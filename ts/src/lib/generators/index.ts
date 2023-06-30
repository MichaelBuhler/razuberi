
import type { Node } from '@babel/types'

import type { Generator } from './types.js'

import { CallExpressionGenerator } from './CallExpression.js'
import { ExpressionStatementGenerator } from './ExpressionStatement.js'
import { FileGenerator } from './File.js'
import { ProgramGenerator } from './Program.js'
import { StringLiteralGenerator } from './StringLiteral.js'

const generators: Partial<{
  [nodeType in Node['type']]: Generator<Node>
}> = {
  CallExpression: CallExpressionGenerator,
  ExpressionStatement: ExpressionStatementGenerator,
  File: FileGenerator,
  Program: ProgramGenerator,
  StringLiteral: StringLiteralGenerator,
}

export default generators
