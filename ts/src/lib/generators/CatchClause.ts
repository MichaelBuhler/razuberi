
import type { CatchClause } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const CatchClauseGenerator: Generator<CatchClause> = ({ param, body}) => {
  if (param) {
    if (param.type !== 'Identifier') {
      throw new Error(`Catch parameters of type \`${param.type}'\` are not supported at this time`)
    }

    return `catch (shared_ptr<Value> value) {
      shared_ptr<Scope> outerScope = scope;
      shared_ptr<Scope> scope = make_shared<Scope>(outerScope);
      scope->declare("${param.name}", value);
      
      ${generate(body)}
    }`
  } else {
    return `catch (shared_ptr<Value> value) ${generate(body)}`
  }
}
