
import { VisitNodeObject } from '@babel/traverse'
import * as t from '@babel/types'

import { indent } from './utils'

export const MemberExpression: VisitNodeObject<unknown, t.MemberExpression> = {
  exit (path) {
    const { node } = path
    const { object, property } = node

    const code = `object_getProperty(${object.razuberi.code}, ${property.razuberi.code})`

    let string = 'MemberExpression\n'
    string += indent('Object') +'\n'
    string += indent(indent(object.razuberi.string)) +'\n'
    string += indent(`Property`) +'\n'
    string += indent(indent(property.razuberi.string))

    node.razuberi = { code, string }
  }
}
