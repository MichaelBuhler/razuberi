
import type { File } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const FileGenerator: Generator<File> = ({ program, extra }) => {
  const cppFunctionDeclarations = []
  const cppFunctionDefinitions = [];

  extra.functions.forEach(fn => {
    const { params, body: { body }, extra } = fn
    const { cppFunctionName, declaredFunctions, declaredVariables } = extra;

    cppFunctionDeclarations.push(`shared_ptr<Value> ${cppFunctionName} (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> >);`)

    // TODO: #11: move the function body generator to a util
    const functionDeclarations = declaredFunctions.map(fn => {
      const { id: { name }, extra: { cppFunctionName } } = fn
      return `scope->declare("${name}", _fn(scope, ${cppFunctionName}));`
    }).join('\n')

    const formalParameters = params.map((param, i) => {
      if (param.type !== 'Identifier') {
        throw new Error('Only Identifier formal parameters are supported at this time')
      }
      return `scope->declare("${param.name}", arguments.size() > ${i} ? arguments[${i}] : make_shared<Undefined>());`
    }).reverse().join('\n')

    const variableDeclarations = declaredVariables.map(variableName => {
      return `scope->declare("${variableName}");`
    }).join('\n')

    const statements = body.map(statement => generate(statement)).join('\n')

    let cppFunctionDefinition = `shared_ptr<Value> ${cppFunctionName} (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {`
    if (functionDeclarations) cppFunctionDefinition += '\n' + functionDeclarations
    if (formalParameters)     cppFunctionDefinition += '\n' + formalParameters
    if (variableDeclarations) cppFunctionDefinition += '\n' + variableDeclarations
    if (functionDeclarations || formalParameters || variableDeclarations) cppFunctionDefinition += '\n'
    cppFunctionDefinition += '\n' + statements + '\n}'
    cppFunctionDefinitions.push(cppFunctionDefinition)
  })

  return `#include "razuberi.h"
    #undef assert
    using namespace std;
    
    ${cppFunctionDeclarations.join('\n')}

    void _run (shared_ptr<Scope> scope) {
      ${generate(program)}
    }

    ${cppFunctionDefinitions.join('\n\n')}
  `
}
