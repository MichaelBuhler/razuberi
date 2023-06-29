
const { default: typescript } = await import('typescript')
const { transpile: ts2js, ScriptTarget } = typescript

export const transpile = (typescriptSource: string) : string => {
  const javascriptSource = ts2js(typescriptSource, {
    target: ScriptTarget.ES3,
  })

  return javascriptSource
}
