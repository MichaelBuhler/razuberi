
import type { NumericLiteral } from '@babel/types'

import type { Generator } from './types.js'

export const NumericLiteralGenerator: Generator<NumericLiteral> = ({ value }) => {
  return `make_shared<Number>(${value})`
}
