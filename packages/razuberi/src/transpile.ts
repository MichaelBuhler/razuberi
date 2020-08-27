
import { ModuleKind, ScriptTarget, transpileModule } from 'typescript'

export const transpile = (source: string) : string => {
  const { outputText: output } = transpileModule(source, {
    compilerOptions: {
      target: ScriptTarget.ES3,
      module: ModuleKind.AMD
    }
  })
  return output
}
