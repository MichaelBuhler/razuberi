
import type { Node } from '@babel/types'

import type { Generator } from './generators/types.js'

import { generators } from  './generators/index.js'

export const generate: Generator<Node> = (node) : string => {
  const generator = generators[node.type]

  if (!generator) {
    throw new Error(`No generator defined for ${node.type} nodes.`)
  }

  return generator(node)
}

