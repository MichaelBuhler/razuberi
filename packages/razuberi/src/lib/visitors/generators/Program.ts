
import { VisitNodeObject } from '@babel/traverse'
import * as t from '@babel/types'

import { indent } from './utils'

export const Program: VisitNodeObject<unknown, t.Program> = {
  exit (path) {
    const { node } = path
    const { body } = node

    const functions: string[] = []
    const statements: string[] = []
    body.forEach(statement => {
      (t.isFunctionDeclaration(statement) ? functions : statements).push(statement.razuberi?.code)
    })

    let code = functions.join('\n\n')
    code += '\n\nint main () {\n'
    code += indent(statements.join('\n')) + '\n'
    code += '}'

    let string = 'Program\n'
    string += indent(node.body.map(x => x.razuberi?.string).join('\n'))

    node.razuberi = { code, string }
  }
}
