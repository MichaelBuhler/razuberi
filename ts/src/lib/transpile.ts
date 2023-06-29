
const { default: typescript } = await import('typescript')
const { transpile: ts2js, ScriptTarget } = typescript

const { parse: js2ast } = await import('@babel/parser')

export const transpile = (typescriptSource: string) : string => {
  const javascriptSource = ts2js(typescriptSource, {
    target: ScriptTarget.ES3,
  })

  const ast = js2ast(javascriptSource, {
    annexB: false,
    errorRecovery: true,
    sourceType: 'script',
  })

  return JSON.stringify(ast, null, 2)
}
