
import { parse as parseJs } from './babel'
import { transpile as ts2js } from './typescript'
import { generate } from './generate'

export const transpile = (typescriptSource: string) : string => {
  const javascript = ts2js(typescriptSource)
  const parseTree = parseJs(javascript)
  const program = generate(parseTree)
  return program.code
}
