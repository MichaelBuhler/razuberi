# Snapshot report for `language/expressions/strict-does-not-equals/index.js`

The actual snapshot is saved in `index.js.snap`.

Generated by [AVA](https://avajs.dev).

## language/expressions/strict-does-not-equals/S11.9.5_A1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:36:55: error: universal character name refers to a control character␊
      if (_test((scope->*"eval").call(make_shared<String>("1\\u000b!==\\u000b1")))) {␊
                                                            ^~~~~~␊
      <stdin>:36:64: error: universal character name refers to a control character␊
      if (_test((scope->*"eval").call(make_shared<String>("1\\u000b!==\\u000b1")))) {␊
                                                                     ^~~~~~␊
      <stdin>:60:57: error: universal character name refers to a control character␊
      if (_test((scope->*"eval").call(make_shared<String>("1\\t\\u000b\\f  \\n\\r      !==\\t\\u000b\\f  \\n\\r      1")))) {␊
                                                              ^~~~~~␊
      <stdin>:60:83: error: universal character name refers to a control character␊
      if (_test((scope->*"eval").call(make_shared<String>("1\\t\\u000b\\f  \\n\\r      !==\\t\\u000b\\f  \\n\\r      1")))) {␊
                                                                                   ^~~~~~␊
      4 errors generated.`,
    }

## language/expressions/strict-does-not-equals/S11.9.5_A2.1_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/strict-does-not-equals/S11.9.5_A2.1_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/strict-does-not-equals/S11.9.5_A2.1_T3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/strict-does-not-equals/S11.9.5_A2.4_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught Test262Error: #2: var x = 0; x !== (x = 1)',
    }

## language/expressions/strict-does-not-equals/S11.9.5_A2.4_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:259:19: error: redefinition of '_anonymous_10'␊
      shared_ptr<Value> _anonymous_10 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:251:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_10 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:263:19: error: redefinition of '_anonymous_11'␊
      shared_ptr<Value> _anonymous_11 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:255:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_11 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      2 errors generated.`,
    }

## language/expressions/strict-does-not-equals/S11.9.5_A2.4_T3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/strict-does-not-equals/S11.9.5_A2.4_T4.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "y" is not defined',
    }

## language/expressions/strict-does-not-equals/S11.9.5_A3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/strict-does-not-equals/S11.9.5_A4.1_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "Number" is not defined',
    }

## language/expressions/strict-does-not-equals/S11.9.5_A4.1_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "Number" is not defined',
    }

## language/expressions/strict-does-not-equals/S11.9.5_A4.2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'UnaryExpressions with operator `+` are not supported at this time',
    }

## language/expressions/strict-does-not-equals/S11.9.5_A4.3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "Number" is not defined',
    }

## language/expressions/strict-does-not-equals/S11.9.5_A5.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/strict-does-not-equals/S11.9.5_A6.1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## language/expressions/strict-does-not-equals/S11.9.5_A6.2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/strict-does-not-equals/S11.9.5_A7.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'UnaryExpressions with operator `+` are not supported at this time',
    }

## language/expressions/strict-does-not-equals/S11.9.5_A8_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "Number" is not defined',
    }

## language/expressions/strict-does-not-equals/S11.9.5_A8_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "Number" is not defined',
    }

## language/expressions/strict-does-not-equals/S11.9.5_A8_T3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "Number" is not defined',
    }

## language/expressions/strict-does-not-equals/S11.9.5_A8_T4.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/strict-does-not-equals/S11.9.5_A8_T5.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/strict-does-not-equals/bigint-and-bigint.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for BigIntLiteral nodes.',
    }

## language/expressions/strict-does-not-equals/bigint-and-boolean.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No handler for `BigIntLiteral` in `libRazuberiTypeof()` utility',
    }

## language/expressions/strict-does-not-equals/bigint-and-incomparable-primitive.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for BigIntLiteral nodes.',
    }

## language/expressions/strict-does-not-equals/bigint-and-non-finite.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for BigIntLiteral nodes.',
    }

## language/expressions/strict-does-not-equals/bigint-and-number-extremes.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for BigIntLiteral nodes.',
    }

## language/expressions/strict-does-not-equals/bigint-and-number.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for BigIntLiteral nodes.',
    }

## language/expressions/strict-does-not-equals/bigint-and-object.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No handler for `BigIntLiteral` in `libRazuberiTypeof()` utility',
    }

## language/expressions/strict-does-not-equals/bigint-and-string.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for BigIntLiteral nodes.',
    }
