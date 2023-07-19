
import type { Expression } from '@babel/types'

import { generate } from '../generate.js'

export enum LibRazuberiType {
  Reference,
  Value,
  // 'Primitive' is defined in librazuberi for internal use as an intermediate value type and should only
  // be used within expression evaluation algorithms and not produced (returned) by any expression.
  // Primitive,
  Undefined,
  Null,
  Boolean,
  Number,
  String,
  Object
}

// What will be the librazuberi type of (the `shared_ptr` of) the result of evaluating the given Expression
export const libRazuberiTypeof = (expression: Expression) : LibRazuberiType => {
  switch (expression.type) {
    case 'AssignmentExpression':
      // TODO: #18: AssignmentExpressions should return the right hand `Value`, not the left hand `Reference`
      // return libRazuberiTypeof(expression.right)
      return LibRazuberiType.Reference;
    case 'BinaryExpression':
      // TODO: what the heck is a `PrivateName`, and why can `left` be of that type?
      // @ts-ignore
      const leftType = libRazuberiTypeof(expression.left)
      const rightType = libRazuberiTypeof(expression.right)
      switch (expression.operator) {
        case '+':
          if ( [leftType, rightType].includes(LibRazuberiType.String) ) {
            return LibRazuberiType.String
          }
          return LibRazuberiType.Number
        case '-':
          return LibRazuberiType.Number
        case '/':
          return LibRazuberiType.Number
        case '%':
          return LibRazuberiType.Number
        case '*':
          return LibRazuberiType.Number
        case '**':
          return LibRazuberiType.Number
        case '&':
          return LibRazuberiType.Number
        case '|':
          return LibRazuberiType.Number
        case '>>':
          return LibRazuberiType.Number
        case '>>>':
          return LibRazuberiType.Number
        case '<<':
          return LibRazuberiType.Number
        case '^':
          return LibRazuberiType.Number
        case '==':
          return LibRazuberiType.Boolean
        case '===':
          return LibRazuberiType.Boolean
        case '!=':
          return LibRazuberiType.Boolean
        case '!==':
          return LibRazuberiType.Boolean
        case 'in':
          return LibRazuberiType.Boolean
        case 'instanceof':
          return LibRazuberiType.Boolean
        case '>':
          return LibRazuberiType.Boolean
        case '<':
          return LibRazuberiType.Boolean
        case '>=':
          return LibRazuberiType.Boolean
        case '<=':
          return LibRazuberiType.Boolean
        case '|>':
          // TODO: what the heck is this operator?
          break;
      }
      break;
    case 'BooleanLiteral':
      return LibRazuberiType.Boolean
    case 'CallExpression':
      return LibRazuberiType.Value
    case 'ConditionalExpression':
      const consequentType = libRazuberiTypeof(expression.consequent)
      const alternateType = libRazuberiTypeof(expression.alternate)
      if ( consequentType === LibRazuberiType.Reference || alternateType === LibRazuberiType.Reference ) {
        return LibRazuberiType.Value
      }
      if ( consequentType === alternateType ) {
        return consequentType
      }
      return LibRazuberiType.Value
    case 'FunctionExpression':
      return LibRazuberiType.Object
    case 'Identifier':
      return LibRazuberiType.Reference
    case 'MemberExpression':
      return LibRazuberiType.Reference
    case 'NewExpression':
      return LibRazuberiType.Object
    case 'NullLiteral':
      return LibRazuberiType.Null
    case 'NumericLiteral':
      return LibRazuberiType.Number
    case 'ObjectExpression':
      return LibRazuberiType.Object
    case 'StringLiteral':
      return LibRazuberiType.String
    case 'ThisExpression':
      return LibRazuberiType.Value
    case 'UnaryExpression':
      switch (expression.operator) {
        case 'typeof':
          return LibRazuberiType.String
        case 'void':
          return LibRazuberiType.Undefined
        case 'throw':
          // `throw` expressions are not supported at this time
          break;
        case 'delete':
          return LibRazuberiType.Boolean
        case '!':
          return LibRazuberiType.Boolean
        case '+':
          return LibRazuberiType.Number
        case '-':
          return LibRazuberiType.Number
        case '~':
          return LibRazuberiType.Number
      }
      break
  }
  throw new Error(`No handler for \`${expression.type}\` in 'typeofExpression()' utility`)
}

export const producesReference = (expression: Expression) : boolean => {
  return libRazuberiTypeof(expression) === LibRazuberiType.Reference
}

export const strictlyProducesValue = (expression: Expression) => {
  return libRazuberiTypeof(expression) === LibRazuberiType.Value
}

export const GetValue = (expression: Expression) : string => {
  if (producesReference(expression)) {
    return `GetValue(${generate(expression)})`
  } else {
    return generate(expression)
  }
}
