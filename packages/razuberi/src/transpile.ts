
import { transpile as ts2js } from './typescript'

export const transpile = (typescriptSource: string) : string => {
  return ts2js(typescriptSource)
}
