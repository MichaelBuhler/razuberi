
import '@babel/types'

declare module '@babel/types' {
  interface File {
    extra: {
      functions: Array<FunctionDeclaration | FunctionExpression>
    }
  }
  interface Program {
    extra: {
      declaredFunctions: Array<string>
      declaredVariables: Array<string>
    }
  }
  interface FunctionDeclaration {
    extra: {
      declaredFunctions: Array<string>
      declaredVariables: Array<string>
    }
  }
  interface FunctionExpression {
    extra: {
      declaredFunctions: Array<string>
      declaredVariables: Array<string>
    }
  }
}
