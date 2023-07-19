
import type { VisitNodeObject } from '@babel/traverse'
import type { NewExpression } from '@babel/types'

import type { RazuberiTraversalState } from './state.js'

export const NewExpressionVisitor: VisitNodeObject<RazuberiTraversalState, NewExpression> = {
  enter (path) {
    if (path.parent.type == 'ThrowStatement') {
      // add a flag on this node, so that the NewExpressionGenerator will know that this new object will be thrown
      path.node.extra = { parentNodeIsThrowStatement: true }
    }
  }
}
