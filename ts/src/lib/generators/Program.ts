
import type { Program } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const ProgramGenerator: Generator<Program> = ({ body }) => {
  return body.map(statement => generate(statement)).join('')
}
