
import type { File } from '@babel/types'

import type { Generator } from './types.js'

import { generate } from '../generate.js'

export const FileGenerator: Generator<File> = ({ program }) => `
  #include <memory>

  #include "razuberi.h"

  using namespace std;
  
  void _run (shared_ptr<Scope> scope) {
    ${generate(program)}
  }
`