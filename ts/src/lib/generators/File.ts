
import type { File } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const FileGenerator: Generator<File> = ({ program, extra: { functions } }) => {
  const functionDeclarations = functions.map(fn => {
    const { id: { name } } = fn
    return `shared_ptr<Value> ${name} (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> >);`
  }).join('\n')

  const functionDefinitions = functions.map(fn => {
    const { id: { name }, body } = fn
    return `shared_ptr<Value> ${name} (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) ${generate(body)}`
  }).join('\n\n')

  return `#include "razuberi.h"
    using namespace std;
    
    ${functionDeclarations}

    void _run (shared_ptr<Scope> scope) {
      ${generate(program)}
    }

    ${functionDefinitions}
  `
}
