
import { VisitNodeObject } from '@babel/traverse'
import * as t from '@babel/types'

import { indent } from './utils'

export const FunctionDeclaration: VisitNodeObject<unknown, t.FunctionDeclaration> = {
  exit (path) {
    const { node } = path
    const { id, params, body } = node

    let code = 'static Return '
    code += id ? id.razuberi.code : 'anonymous'
    code += ' (Scope* callingScope, Object* arguments) {\n'
    let block = 'Return ret;\n'
    block += 'Scope* scope = new_Scope(callingScope);\n'
    params.forEach(param => {
      block += `scope_setValue(scope, "${param.razuberi.code}", arguments_getValue(arguments, "${param.razuberi.code}"))\n`
    })
    block += body.razuberi.code
    block += '\nret.value = new_undefined();\nreturn ret;'
    code += indent(block)
    code += '\n}'

    let string = 'FunctionDeclaration\n'
    string += indent(`Name (${id ? id.razuberi.string : 'anonymous'})`) + '\n'
    string += indent(`Parameters (${params.map(x => x.razuberi.string).join(', ')})`) + '\n'
    string += indent('Body\n' + indent(body.razuberi.string))

    node.razuberi = { code, string }
  }
}
