
import * as ts from 'typescript'

export const transpile = (source: string) => {
  const { outputText } = ts.transpileModule(source, {
    compilerOptions: {
      target: ts.ScriptTarget.ES3,
      module: ts.ModuleKind.AMD
    }
  })
  return outputText
}
