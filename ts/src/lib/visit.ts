
import type { Node } from '@babel/types'

const { default: babel_traverse } = await import('@babel/traverse')
const { default: traverse } = babel_traverse

import { RazuberiTraversalState } from './visitors/state.js'
import { visitors } from './visitors/index.js'

export const visit = (node: Node) => {
  traverse<RazuberiTraversalState>(
    node,
    {
      ...visitors,
    },
    undefined,
    new RazuberiTraversalState(),
  )
}
