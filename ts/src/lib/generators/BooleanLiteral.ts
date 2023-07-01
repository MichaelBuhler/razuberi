
import type { BooleanLiteral } from '@babel/types'

import type { Generator } from './types.js'

export const BooleanLiteralGenerator: Generator<BooleanLiteral> = ({ value }) => {
  return `make_shared<Boolean>(${value})`
}
