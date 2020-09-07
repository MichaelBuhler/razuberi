
import { NodePath } from '@babel/traverse'
import * as t from '@babel/types'

export const getProgramPath = <T extends t.Node>(path: NodePath<T>) : NodePath<t.Program> => {
  return path.find(t.isProgram) as NodePath<t.Program>
}
