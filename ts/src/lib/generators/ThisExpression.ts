
import type { ThisExpression } from '@babel/types'

import type { Generator } from './types.js'

export const ThisExpressionGenerator: Generator<ThisExpression> = () => `_this`
