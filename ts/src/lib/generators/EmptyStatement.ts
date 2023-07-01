
import type { EmptyStatement } from '@babel/types'

import type { Generator } from './types.js'

// TODO: #5: maybe remove the `EmptyStatement`s so they don't have to be generated
export const EmptyStatementGenerator: Generator<EmptyStatement> = () => ''
