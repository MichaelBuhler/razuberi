
import '@babel/types'

import type { FunctionDeclaration, FunctionExpression } from '@babel/types'

declare module '@babel/types' {
  interface File {
    extra: {
      functions: Array<FunctionDeclaration | FunctionExpression>
    }
  }
}
