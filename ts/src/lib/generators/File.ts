
import type { File } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const FileGenerator: Generator<File> = ({ program, extra }) => {
  const cppFunctionDeclarations = extra.functions.map(fn => {
    const { id: { name } } = fn
    return `shared_ptr<Value> ${name} (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> >);`
  }).join('\n')

  const cppFunctionDefinitions = extra.functions.map(fn => {
    const { id: { name }, params, body: { body }, extra } = fn

    // TODO: #11: move the function body generator to a util
    const functionDeclarations = extra.declaredFunctions.map(fnName => {
      return `scope->declare("${fnName}", _fn(scope, ${fnName}));`
    }).join('\n')

    const formalParameters = params.map((param, i) => {
      if (param.type !== 'Identifier') {
        throw new Error('Only Indentifier formal parameters are supported at this time')
      }
      return `scope->declare("${param.name}", arguments.size() > ${i} ? arguments[${i}] : make_shared<Undefined>());`
    }).reverse().join('\n')

    const variableDeclarations = extra.declaredVariables.map(varName => {
      return `scope->declare("${varName}");`
    }).join('\n')

    const statements = body.map(statement => generate(statement)).join('\n')

    let cppFunctionDefinition = `shared_ptr<Value> ${name} (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {`
    if (functionDeclarations) cppFunctionDefinition += '\n' + functionDeclarations
    if (formalParameters)     cppFunctionDefinition += '\n' + formalParameters
    if (variableDeclarations) cppFunctionDefinition += '\n' + variableDeclarations
    if (functionDeclarations || formalParameters || variableDeclarations) cppFunctionDefinition += '\n'
    cppFunctionDefinition += '\n' + statements + '\n}'
    return cppFunctionDefinition
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
