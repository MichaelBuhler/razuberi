# Snapshot report for `language/expressions/logical-or/index.js`

The actual snapshot is saved in `index.js.snap`.

Generated by [AVA](https://avajs.dev).

## language/expressions/logical-or/S11.11.2_A1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:36:76: error: universal character name refers to a control character␊
      if (_test(_strictNotEquals((scope->*"eval").call(make_shared<String>("false\\u000b||\\u000btrue")), make_shared<Boolean>(true)))) {␊
                                                                                 ^~~~~~␊
      <stdin>:36:84: error: universal character name refers to a control character␊
      if (_test(_strictNotEquals((scope->*"eval").call(make_shared<String>("false\\u000b||\\u000btrue")), make_shared<Boolean>(true)))) {␊
                                                                                         ^~~~~~␊
      <stdin>:60:78: error: universal character name refers to a control character␊
      if (_test(_strictNotEquals((scope->*"eval").call(make_shared<String>("false\\t\\u000b\\f  \\n\\r      ||\\t\\u000b\\f  \\n\\r      true")), make_shared<Boolean>(true)))) {␊
                                                                                   ^~~~~~␊
      <stdin>:60:103: error: universal character name refers to a control character␊
      if (_test(_strictNotEquals((scope->*"eval").call(make_shared<String>("false\\t\\u000b\\f  \\n\\r      ||\\t\\u000b\\f  \\n\\r      true")), make_shared<Boolean>(true)))) {␊
                                                                                                       ^~~~~~␊
      4 errors generated.`,
    }

## language/expressions/logical-or/S11.11.2_A2.1_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/logical-or/S11.11.2_A2.1_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/logical-or/S11.11.2_A2.1_T3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/logical-or/S11.11.2_A2.1_T4.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/logical-or/S11.11.2_A2.4_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/logical-or/S11.11.2_A2.4_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:275:19: error: redefinition of '_anonymous_10'␊
      shared_ptr<Value> _anonymous_10 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:253:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_10 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:279:19: error: redefinition of '_anonymous_11'␊
      shared_ptr<Value> _anonymous_11 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:257:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_11 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      2 errors generated.`,
    }

## language/expressions/logical-or/S11.11.2_A2.4_T3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "y" is not defined',
    }

## language/expressions/logical-or/S11.11.2_A3_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/logical-or/S11.11.2_A3_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "Number" is not defined',
    }

## language/expressions/logical-or/S11.11.2_A3_T3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/logical-or/S11.11.2_A3_T4.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:238:85: error: no matching function for call to 'GetValue'␊
      return _test(scope->*"leftHandSideValue") ? GetValue(scope->*"leftHandSideValue") : GetValue(make_shared<Undefined>());␊
                                                                                          ^~~~~~~~␊
      /Users/michael/razuberi/cpp/out/include/reference.h:13:24: note: candidate function not viable: no known conversion from 'typename enable_if<!is_array<Undefined>::value, shared_ptr<Undefined> >::type' (aka 'std::__1::shared_ptr<Undefined>') to 'Reference' for 1st argument␊
      std::shared_ptr<Value> GetValue (Reference);␊
                             ^␊
      1 error generated.`,
    }

## language/expressions/logical-or/S11.11.2_A4_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/logical-or/S11.11.2_A4_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "Number" is not defined',
    }

## language/expressions/logical-or/S11.11.2_A4_T3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/logical-or/S11.11.2_A4_T4.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:238:85: error: no matching function for call to 'GetValue'␊
      return _test(scope->*"leftHandSideValue") ? GetValue(scope->*"leftHandSideValue") : GetValue(make_shared<Undefined>());␊
                                                                                          ^~~~~~~~␊
      /Users/michael/razuberi/cpp/out/include/reference.h:13:24: note: candidate function not viable: no known conversion from 'typename enable_if<!is_array<Undefined>::value, shared_ptr<Undefined> >::type' (aka 'std::__1::shared_ptr<Undefined>') to 'Reference' for 1st argument␊
      std::shared_ptr<Value> GetValue (Reference);␊
                             ^␊
      1 error generated.`,
    }

## language/expressions/logical-or/symbol-logical-or-evaluation.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:234:37: error: right hand operand to ->* has non-pointer-to-member type 'const char [4]'␊
      scope->*"leftHandSideValue" = !scope->*"sym";␊
                                          ^  ~~~~~␊
      1 error generated.`,
    }

## language/expressions/logical-or/tco-right.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'BinaryExpressions with operator `-` are not supported at this time',
    }
