
import type { File } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const FileGenerator: Generator<File> = ({ program, extra }) => {
  const cppFunctionDeclarations = extra.functions.map(fn => {
    const { id: { name } } = fn
    return `shared_ptr<Value> ${name} (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> >);`
  }).join('\n')

  const cppFunctionDefinitions = extra.functions.map(fn => {
    const { id: { name }, body: { body }, extra } = fn

    const functionDeclarations = extra.functionDeclarations.map(functionDeclaration => {
      const { id: { name } } = functionDeclaration
      return `scope->declare("${name}", _fn(scope, ${name}));`
    }).join('\n')

    const statements = body.map(statement => generate(statement)).join('\n')

    return `shared_ptr<Value> ${name} (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {
      ${functionDeclarations}

      ${statements}
    }`
  }).join('\n\n')

  return `#include "razuberi.h"
    using namespace std;
    
    ${cppFunctionDeclarations}

    void _run (shared_ptr<Scope> scope) {
      ${generate(program)}
    }

    ${cppFunctionDefinitions}
  `
}
