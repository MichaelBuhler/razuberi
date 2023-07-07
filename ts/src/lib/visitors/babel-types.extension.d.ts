
import '@babel/types'

import type { FunctionDeclaration, FunctionExpression } from '@babel/types'

declare module '@babel/types' {
  interface File {
    extra: {
      functions: Array<FunctionDeclaration | FunctionExpression>
    }
  }
  interface Program {
    extra: {
      functionDeclarations: Array<FunctionDeclaration>
    }
  }
  interface FunctionDeclaration {
    extra: {
      functionDeclarations: Array<FunctionDeclaration>
    }
  }
  interface FunctionExpression {
    extra: {
      functionDeclarations: Array<FunctionDeclaration>
    }
  }
}
