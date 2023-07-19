
import '@babel/types'

declare module '@babel/types' {
  interface File {
    extra?: {
      functions?: (FunctionDeclaration | FunctionExpression)[]
    }
  }
  interface Program {
    extra?: {
      declaredFunctions?: FunctionDeclaration[]
      declaredVariables?: Array<string>
    }
  }
  interface FunctionDeclaration {
    extra?: {
      cppFunctionName?: string
      declaredFunctions?: FunctionDeclaration[]
      declaredVariables?: Array<string>
    }
  }
  interface FunctionExpression {
    extra?: {
      cppFunctionName?: string
      desiredCppFunctionName?: string
      declaredFunctions?: FunctionDeclaration[]
      declaredVariables?: Array<string>
    }
  }
  interface NewExpression {
    extra?: {
      parentNodeIsThrowStatement: boolean
    }
  }
}
