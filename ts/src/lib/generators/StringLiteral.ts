
import type { StringLiteral } from '@babel/types'

import type { Generator } from './types.js'

export const StringLiteralGenerator: Generator<StringLiteral> = ({ value }) => {
  return `make_shared<String>("${value}")`
}
