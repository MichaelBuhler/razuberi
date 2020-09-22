
import * as ts from 'typescript'

export const transpile = (source: string) => {
  return ts.transpile(source, {
      target: ts.ScriptTarget.ES3,
      module: ts.ModuleKind.CommonJS
  })
}
