
import type { VisitNodeObject } from '@babel/traverse'
import type { File, Program } from '@babel/types'

export const ProgramVisitor: VisitNodeObject<unknown, Program> = {
  enter (path) {
    // Define `extra` on the root File node.
    const file = path.parent as File
    file.extra = {
      functions: []
    }
    // Define `extra` on this Program node.
    path.node.extra = {
      functionDeclarations: [],
    }
  }
}
