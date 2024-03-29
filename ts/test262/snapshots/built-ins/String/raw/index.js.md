# Snapshot report for `built-ins/String/raw/index.js`

The actual snapshot is saved in `index.js.snap`.

Generated by [AVA](https://avajs.dev).

## built-ins/String/raw/length.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'We don\'t know what to do with this node type. We were previously a Statement but we can\'t fit in here?',
    }

## built-ins/String/raw/name.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'We don\'t know what to do with this node type. We were previously a Statement but we can\'t fit in here?',
    }

## built-ins/String/raw/nextkey-is-symbol-throws.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:34:22: error: invalid operands to binary expression ('const char [4]' and 'const char [7]')␊
      scope->*"obj" = "raw"&"length"&make_shared<Number>(1)|"0"&(scope->*"Symbol").call(make_shared<String>(""));␊
                      ~~~~~^~~~~~~~~␊
      1 error generated.`,
    }

## built-ins/String/raw/not-a-constructor.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for ArrayExpression nodes.',
    }

## built-ins/String/raw/raw.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'We don\'t know what to do with this node type. We were previously a Statement but we can\'t fit in here?',
    }

## built-ins/String/raw/return-empty-string-from-empty-array-length.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for ArrayExpression nodes.',
    }

## built-ins/String/raw/return-empty-string-if-length-is-negative-infinity.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:33:57: error: invalid operands to binary expression ('const char [4]' and 'const char [7]')␊
      scope->*"result" = (scope->*"String"->*"raw").call("raw"&"length"&-(scope->*"Infinity"));␊
                                                         ~~~~~^~~~~~~~~␊
      1 error generated.`,
    }

## built-ins/String/raw/return-empty-string-if-length-is-not-defined.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught TypeError: raw is not a function',
    }

## built-ins/String/raw/return-empty-string-if-length-is-undefined.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:33:57: error: invalid operands to binary expression ('const char [4]' and 'const char [7]')␊
      scope->*"result" = (scope->*"String"->*"raw").call("raw"&"length"&make_shared<Undefined>());␊
                                                         ~~~~~^~~~~~~~~␊
      1 error generated.`,
    }

## built-ins/String/raw/return-empty-string-if-length-is-zero-NaN.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:33:57: error: invalid operands to binary expression ('const char [4]' and 'const char [7]')␊
      scope->*"result" = (scope->*"String"->*"raw").call("raw"&"length"&scope->*"NaN");␊
                                                         ~~~~~^~~~~~~~~␊
      1 error generated.`,
    }

## built-ins/String/raw/return-empty-string-if-length-is-zero-boolean.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:33:57: error: invalid operands to binary expression ('const char [4]' and 'const char [7]')␊
      scope->*"result" = (scope->*"String"->*"raw").call("raw"&"length"&make_shared<Boolean>(false));␊
                                                         ~~~~~^~~~~~~~~␊
      1 error generated.`,
    }

## built-ins/String/raw/return-empty-string-if-length-is-zero-null.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:33:57: error: invalid operands to binary expression ('const char [4]' and 'const char [7]')␊
      scope->*"result" = (scope->*"String"->*"raw").call("raw"&"length"&make_shared<Null>());␊
                                                         ~~~~~^~~~~~~~~␊
      1 error generated.`,
    }

## built-ins/String/raw/return-empty-string-if-length-is-zero-or-less-number.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:33:57: error: invalid operands to binary expression ('const char [4]' and 'const char [7]')␊
      scope->*"result" = (scope->*"String"->*"raw").call("raw"&"length"&make_shared<Number>(0));␊
                                                         ~~~~~^~~~~~~~~␊
      <stdin>:35:57: error: invalid operands to binary expression ('const char [4]' and 'const char [7]')␊
      scope->*"result" = (scope->*"String"->*"raw").call("raw"&"length"&-make_shared<Number>(1));␊
                                                         ~~~~~^~~~~~~~~␊
      <stdin>:37:57: error: invalid operands to binary expression ('const char [4]' and 'const char [7]')␊
      scope->*"result" = (scope->*"String"->*"raw").call("raw"&"length"&-make_shared<Number>(0));␊
                                                         ~~~~~^~~~~~~~~␊
      <stdin>:39:57: error: invalid operands to binary expression ('const char [4]' and 'const char [7]')␊
      scope->*"result" = (scope->*"String"->*"raw").call("raw"&"length"&make_shared<Number>(0.32));␊
                                                         ~~~~~^~~~~~~~~␊
      4 errors generated.`,
    }

## built-ins/String/raw/return-empty-string-if-length-is-zero-or-less-string.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:33:57: error: invalid operands to binary expression ('const char [4]' and 'const char [7]')␊
      scope->*"result" = (scope->*"String"->*"raw").call("raw"&"length"&make_shared<String>("0"));␊
                                                         ~~~~~^~~~~~~~~␊
      <stdin>:35:57: error: invalid operands to binary expression ('const char [4]' and 'const char [7]')␊
      scope->*"result" = (scope->*"String"->*"raw").call("raw"&"length"&make_shared<String>("-1"));␊
                                                         ~~~~~^~~~~~~~~␊
      <stdin>:37:57: error: invalid operands to binary expression ('const char [4]' and 'const char [7]')␊
      scope->*"result" = (scope->*"String"->*"raw").call("raw"&"length"&make_shared<String>(""));␊
                                                         ~~~~~^~~~~~~~~␊
      3 errors generated.`,
    }

## built-ins/String/raw/return-the-string-value-from-template.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for ArrayExpression nodes.',
    }

## built-ins/String/raw/return-the-string-value.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:33:22: error: invalid operands to binary expression ('const char [4]' and 'const char [7]')␊
      scope->*"obj" = "raw"&"length"&make_shared<Number>(5)|"0"&make_shared<String>("e")|"1"&make_shared<String>("")|"2"&make_shared<Null>()|"3"&make_shared<Undefined>()|"4"&make_shared<Number>(123)|"5"&make_shared<String>("overpass the length");␊
                      ~~~~~^~~~~~~~~␊
      1 error generated.`,
    }

## built-ins/String/raw/returns-abrupt-from-next-key-toString.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:36:22: error: invalid operands to binary expression ('const char [4]' and 'const char [7]')␊
      scope->*"obj" = "raw"&"length"&make_shared<Number>(1)|"0"&"toString"&_fn(scope, _anonymous_10);␊
                      ~~~~~^~~~~~~~~␊
      <stdin>:36:58: error: invalid operands to binary expression ('const char [2]' and 'const char [9]')␊
      scope->*"obj" = "raw"&"length"&make_shared<Number>(1)|"0"&"toString"&_fn(scope, _anonymous_10);␊
                                                            ~~~^~~~~~~~~~~␊
      <stdin>:240:19: error: redefinition of '_anonymous_10'␊
      shared_ptr<Value> _anonymous_10 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:231:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_10 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      3 errors generated.`,
    }

## built-ins/String/raw/returns-abrupt-from-next-key.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'UnaryExpressions with operator `delete` are not supported at this time',
    }

## built-ins/String/raw/returns-abrupt-from-substitution-symbol.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for ArrayExpression nodes.',
    }

## built-ins/String/raw/returns-abrupt-from-substitution.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for ArrayExpression nodes.',
    }

## built-ins/String/raw/special-characters.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for ArrayExpression nodes.',
    }

## built-ins/String/raw/substitutions-are-appended-on-same-index.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for ArrayExpression nodes.',
    }

## built-ins/String/raw/substitutions-are-limited-to-template-raw-length.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for ArrayExpression nodes.',
    }

## built-ins/String/raw/template-length-is-symbol-throws.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:229:38: error: invalid operands to binary expression ('const char [4]' and 'const char [7]')␊
      (scope->*"String"->*"raw").call("raw"&"length"&(scope->*"Symbol").call(make_shared<Number>(1)));␊
                                      ~~~~~^~~~~~~~~␊
      1 error generated.`,
    }

## built-ins/String/raw/template-length-throws.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught TypeError: defineProperty is not a function',
    }

## built-ins/String/raw/template-not-object-throws.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## built-ins/String/raw/template-raw-not-object-throws.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## built-ins/String/raw/template-raw-throws.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught TypeError: defineProperty is not a function',
    }

## built-ins/String/raw/template-substitutions-are-appended-on-same-index.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for ArrayExpression nodes.',
    }

## built-ins/String/raw/zero-literal-segments.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for ArrayExpression nodes.',
    }
