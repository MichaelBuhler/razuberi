
import { parse as parseJavascript } from '@babel/parser'
import { File } from '@babel/types'

export const parse = (javascript: string, sourceFilename?: string) : File => {
  return parseJavascript(javascript, {
    createParenthesizedExpressions: true,
    sourceFilename
  })
}

