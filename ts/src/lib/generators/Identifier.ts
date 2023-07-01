
import type { Identifier } from '@babel/types'

import type { Generator } from './types.js'

export const IdentifierGenerator: Generator<Identifier> = ({ name }) => {
  if (name === 'undefined') {
    return 'make_shared<Undefined>()'
  } else {
    return `scope->*"${name}"`
  }
}
