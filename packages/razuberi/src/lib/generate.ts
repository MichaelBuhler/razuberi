
import babelTraverse from '@babel/traverse'
import { File, Node } from '@babel/types'

import { RazuberiMetadata } from './types'

import { renamers, hoisters, generators } from './visitors'

class UnsupportedNodeTypeError extends Error {
  public name = 'UnsupportedNodeTypeError'

  public constructor (nodeType: Node['type']) {
    super(`unsupported node type: ${nodeType}`);
  }
}

export const generate = (fileNode: File) : RazuberiMetadata => {
  babelTraverse(fileNode, {
    ...renamers
  })

  babelTraverse(fileNode, {
    ...hoisters
  })

  babelTraverse(fileNode, {
    enter (path) {
      const { node } = path
      const { type } = node

      if (!generators[type]) {
        throw new UnsupportedNodeTypeError(type)
      }
    },
    ...generators
  })

  fileNode.razuberi = fileNode.program.razuberi

  return fileNode.razuberi
}
