# Snapshot report for `language/expressions/unary-minus/index.js`

The actual snapshot is saved in `index.js.snap`.

Generated by [AVA](https://avajs.dev).

## language/expressions/unary-minus/11.4.7-4-1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: cannot convert a string to a number',
    }

## language/expressions/unary-minus/S11.4.7_A1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:36:72: error: universal character name refers to a control character␊
      if (_test(_strictNotEquals((scope->*"eval").call(make_shared<String>("-\\u000b1")), -make_shared<Number>(1)))) {␊
                                                                             ^~~~~~␊
      <stdin>:60:74: error: universal character name refers to a control character␊
      if (_test(_strictNotEquals((scope->*"eval").call(make_shared<String>("-\\t\\u000b\\f  \\n\\r      1")), -make_shared<Number>(1)))) {␊
                                                                               ^~~~~~␊
      2 errors generated.`,
    }

## language/expressions/unary-minus/S11.4.7_A2.1_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:38:28: error: cannot decrement value of type 'typename enable_if<!is_array<Number>::value, shared_ptr<Number> >::type' (aka 'std::__1::shared_ptr<Number>')␊
      if (_test(_strictNotEquals(--make_shared<Number>(1), make_shared<Number>(1)))) {␊
                                 ^ ~~~~~~~~~~~~~~~~~~~~~~␊
      <stdin>:39:99: error: cannot decrement value of type 'typename enable_if<!is_array<Number>::value, shared_ptr<Number> >::type' (aka 'std::__1::shared_ptr<Number>')␊
          throw _newThrowable(scope->*"Test262Error", make_shared<String>("#2: -(-1) === -1. Actual: ")+--make_shared<Number>(1));␊
                                                                                                        ^ ~~~~~~~~~~~~~~~~~~~~~~␊
      <stdin>:46:28: error: cannot decrement value of type 'Reference'␊
      if (_test(_strictNotEquals(--(scope->*"x"), -make_shared<Number>(1)))) {␊
                                 ^ ~~~~~~~~~~~~~␊
      <stdin>:47:111: error: cannot decrement value of type 'Reference'␊
          throw _newThrowable(scope->*"Test262Error", make_shared<String>("#4: var x = -1; -(-x) === -1. Actual: ")+--(scope->*"x"));␊
                                                                                                                    ^ ~~~~~~~~~~~~~␊
      4 errors generated.`,
    }

## language/expressions/unary-minus/S11.4.7_A2.1_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/unary-minus/S11.4.7_A2.2_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:357:19: error: redefinition of '_anonymous_15'␊
      shared_ptr<Value> _anonymous_15 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:349:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_15 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:361:19: error: redefinition of '_anonymous_16'␊
      shared_ptr<Value> _anonymous_16 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:353:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_16 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:385:19: error: redefinition of '_anonymous_22'␊
      shared_ptr<Value> _anonymous_22 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:377:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_22 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:389:19: error: redefinition of '_anonymous_23'␊
      shared_ptr<Value> _anonymous_23 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:381:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_23 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:401:19: error: redefinition of '_anonymous_26'␊
      shared_ptr<Value> _anonymous_26 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:393:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_26 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:405:19: error: redefinition of '_anonymous_27'␊
      shared_ptr<Value> _anonymous_27 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:397:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_27 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:409:19: error: redefinition of '_anonymous_28'␊
      shared_ptr<Value> _anonymous_28 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:329:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_28 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:413:19: error: redefinition of '_anonymous_29'␊
      shared_ptr<Value> _anonymous_29 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:333:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_29 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:417:19: error: redefinition of '_anonymous_30'␊
      shared_ptr<Value> _anonymous_30 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:337:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_30 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:421:19: error: redefinition of '_anonymous_31'␊
      shared_ptr<Value> _anonymous_31 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:341:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_31 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:425:19: error: redefinition of '_anonymous_32'␊
      shared_ptr<Value> _anonymous_32 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:345:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_32 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:429:19: error: redefinition of '_anonymous_33'␊
      shared_ptr<Value> _anonymous_33 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:365:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_33 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:433:19: error: redefinition of '_anonymous_34'␊
      shared_ptr<Value> _anonymous_34 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:369:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_34 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:437:19: error: redefinition of '_anonymous_35'␊
      shared_ptr<Value> _anonymous_35 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:373:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_35 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      14 errors generated.`,
    }

## language/expressions/unary-minus/S11.4.7_A3_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/expressions/unary-minus/S11.4.7_A3_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "Number" is not defined',
    }

## language/expressions/unary-minus/S11.4.7_A3_T3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: cannot convert a string to a number',
    }

## language/expressions/unary-minus/S11.4.7_A3_T4.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'UnaryExpressions with operator `+` are not supported at this time',
    }

## language/expressions/unary-minus/S11.4.7_A3_T5.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: cannot convert a string to a number',
    }

## language/expressions/unary-minus/S11.4.7_A4.1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'BinaryExpressions with operator `!=` are not supported at this time',
    }

## language/expressions/unary-minus/S11.4.7_A4.2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "Number" is not defined',
    }

## language/expressions/unary-minus/bigint-non-primitive.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No handler for `BigIntLiteral` in `libRazuberiTypeof()` utility',
    }

## language/expressions/unary-minus/bigint.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No handler for `BigIntLiteral` in `libRazuberiTypeof()` utility',
    }
