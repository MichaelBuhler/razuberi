
const { default: typescript } = await import('typescript')
const { transpile: ts2js, ScriptTarget } = typescript

const { parse: js2ast } = await import('@babel/parser')

const { visit } = await import('./visit.js')

const { generate: ast2cpp } = await import('./generate.js')

export const transpile = (typescriptSource: string) : string => {
  const javascriptCode = ts2js(typescriptSource, {
    target: ScriptTarget.ES3,
  })

  const ast = js2ast(javascriptCode, {
    annexB: false,
    errorRecovery: true,
    sourceType: 'script',
  })

  visit(ast)

  const cppCode = ast2cpp(ast)

  return cppCode
}
