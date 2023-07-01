
import type { NullLiteral } from '@babel/types'

import type { Generator } from './types.js'

export const NullLiteralGenerator: Generator<NullLiteral> = () => `make_shared<Null>()`
