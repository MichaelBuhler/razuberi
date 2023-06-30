
import type { Identifier } from '@babel/types'

import type { Generator } from './types.js'

export const IdentifierGenerator: Generator<Identifier> = ({ name }) => {
  return `scope->*"${name}"`
}
