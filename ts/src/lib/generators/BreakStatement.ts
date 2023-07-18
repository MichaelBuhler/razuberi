
import type { BreakStatement } from '@babel/types'

import type { Generator } from './types.js'

export const BreakStatementGenerator: Generator<BreakStatement> = () => 'break;'
