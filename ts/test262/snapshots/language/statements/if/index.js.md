# Snapshot report for `language/statements/if/index.js`

The actual snapshot is saved in `index.js.snap`.

Generated by [AVA](https://avajs.dev).

## language/statements/if/S12.5_A1.1_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/statements/if/S12.5_A1.1_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for UpdateExpression nodes.',
    }

## language/statements/if/S12.5_A1.2_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "Number" is not defined',
    }

## language/statements/if/S12.5_A1.2_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for UpdateExpression nodes.',
    }

## language/statements/if/S12.5_A10_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/statements/if/S12.5_A10_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/statements/if/S12.5_A11.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/S12.5_A12_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:33:231: error: expected expression␊
      if (_test(make_shared<Boolean>(true))) if (_test(make_shared<Boolean>(false))) throw _newThrowable(scope->*"Test262Error", make_shared<String>("#1.1: At embedded \\"if/else\\" constructions engine must select right branches"));else else if (_test(make_shared<Boolean>(true))) throw _newThrowable(scope->*"Test262Error", make_shared<String>("#1.2: At embedded \\"if/else\\" constructions engine must select right branches"));else throw _newThrowable(scope->*"Test262Error", make_shared<String>("#1.3: At embedded \\"if/else\\" constructions engine must select right branches"));␊
                                                                                                                                                                                                                                            ^␊
      <stdin>:34:79: error: expected expression␊
      if (_test(make_shared<Boolean>(true))) if (_test(make_shared<Boolean>(true))) else throw _newThrowable(scope->*"Test262Error", make_shared<String>("#2.1: At embedded \\"if/else\\" constructions engine must select right branches"));else if (_test(make_shared<Boolean>(true))) throw _newThrowable(scope->*"Test262Error", make_shared<String>("#2.2: At embedded \\"if/else\\" constructions engine must select right branches"));else throw _newThrowable(scope->*"Test262Error", make_shared<String>("#2.3: At embedded \\"if/else\\" constructions engine must select right branches"));␊
                                                                                    ^␊
      <stdin>:34:230: warning: add explicit braces to avoid dangling else [-Wdangling-else]␊
      if (_test(make_shared<Boolean>(true))) if (_test(make_shared<Boolean>(true))) else throw _newThrowable(scope->*"Test262Error", make_shared<String>("#2.1: At embedded \\"if/else\\" constructions engine must select right branches"));else if (_test(make_shared<Boolean>(true))) throw _newThrowable(scope->*"Test262Error", make_shared<String>("#2.2: At embedded \\"if/else\\" constructions engine must select right branches"));else throw _newThrowable(scope->*"Test262Error", make_shared<String>("#2.3: At embedded \\"if/else\\" constructions engine must select right branches"));␊
                                                                                                                                                                                                                                           ^␊
      <stdin>:35:421: error: expected expression␊
      if (_test(make_shared<Boolean>(false))) if (_test(make_shared<Boolean>(true))) throw _newThrowable(scope->*"Test262Error", make_shared<String>("#3.1: At embedded \\"if/else\\" constructions engine must select right branches"));else throw _newThrowable(scope->*"Test262Error", make_shared<String>("#3.2: At embedded \\"if/else\\" constructions engine must select right branches"));else if (_test(make_shared<Boolean>(true))) else throw _newThrowable(scope->*"Test262Error", make_shared<String>("#3.3: At embedded \\"if/else\\" constructions engine must select right branches"));␊
                                                                                                                                                                                                                                                                                                                                                                                                                                          ^␊
      <stdin>:37:5: error: expected statement␊
          }␊
          ^␊
      1 warning and 4 errors generated.`,
    }

## language/statements/if/S12.5_A12_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:40:3: error: expected statement␊
        }else {␊
        ^␊
      <stdin>:47:3: error: expected statement␊
        }␊
        ^␊
      2 errors generated.`,
    }

## language/statements/if/S12.5_A12_T3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:34:79: error: expected expression␊
      if (_test(make_shared<Boolean>(true))) if (_test(make_shared<Boolean>(true))) else throw _newThrowable(scope->*"Test262Error", make_shared<String>("#2.1: At embedded \\"if/else\\" constructions engine must select right branches"));␊
                                                                                    ^␊
      <stdin>:33:226: warning: add explicit braces to avoid dangling else [-Wdangling-else]␊
      if (_test(make_shared<Boolean>(true))) if (_test(make_shared<Boolean>(false))) throw _newThrowable(scope->*"Test262Error", make_shared<String>("#1.1: At embedded \\"if/else\\" constructions engine must select right branches"));else ␊
                                                                                                                                                                                                                                       ^␊
      <stdin>:35:226: warning: add explicit braces to avoid dangling else [-Wdangling-else]␊
      if (_test(make_shared<Boolean>(false))) if (_test(make_shared<Boolean>(true))) throw _newThrowable(scope->*"Test262Error", make_shared<String>("#3.1: At embedded \\"if/else\\" constructions engine must select right branches"));else throw _newThrowable(scope->*"Test262Error", make_shared<String>("#3.2: At embedded \\"if/else\\" constructions engine must select right branches"));␊
                                                                                                                                                                                                                                       ^␊
      <stdin>:36:226: warning: add explicit braces to avoid dangling else [-Wdangling-else]␊
      if (_test(make_shared<Boolean>(false))) if (_test(make_shared<Boolean>(true))) throw _newThrowable(scope->*"Test262Error", make_shared<String>("#4.1: At embedded \\"if/else\\" constructions engine must select right branches"));else throw _newThrowable(scope->*"Test262Error", make_shared<String>("#4.2: At embedded \\"if/else\\" constructions engine must select right branches"));␊
                                                                                                                                                                                                                                       ^␊
      3 warnings and 1 error generated.`,
    }

## language/statements/if/S12.5_A12_T4.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/statements/if/S12.5_A1_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/statements/if/S12.5_A1_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for UpdateExpression nodes.',
    }

## language/statements/if/S12.5_A2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## language/statements/if/S12.5_A3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/statements/if/S12.5_A4.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/statements/if/S12.5_A5.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/statements/if/S12.5_A6_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/S12.5_A6_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/S12.5_A8.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/cptn-else-false-abrupt-empty.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## language/statements/if/cptn-else-false-nrml.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## language/statements/if/cptn-else-true-abrupt-empty.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## language/statements/if/cptn-else-true-nrml.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## language/statements/if/cptn-empty-statement.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## language/statements/if/cptn-no-else-false.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## language/statements/if/cptn-no-else-true-abrupt-empty.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## language/statements/if/cptn-no-else-true-nrml.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## language/statements/if/empty-statement.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:34:5: error: expected statement␊
          }␊
          ^␊
      1 error generated.`,
    }

## language/statements/if/if-async-fun-else-async-fun.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-async-fun-else-stmt.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-async-fun-no-else.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-async-gen-else-async-gen.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-async-gen-else-stmt.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-async-gen-no-else.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-cls-else-cls.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-cls-else-stmt.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-cls-no-else.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-const-else-const.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-const-else-stmt.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-const-no-else.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-decl-else-decl-strict.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-decl-else-stmt-strict.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-decl-no-else-strict.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-fun-else-fun-strict.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-fun-else-stmt-strict.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-fun-no-else-strict.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-gen-else-gen.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-gen-else-stmt.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-gen-no-else.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-let-else-let.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-let-else-stmt.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-let-no-else.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-stmt-else-async-fun.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-stmt-else-async-gen.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-stmt-else-cls.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-stmt-else-const.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-stmt-else-decl-strict.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-stmt-else-fun-strict.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-stmt-else-gen.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/if-stmt-else-let.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/labelled-fn-stmt-first.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/labelled-fn-stmt-lone.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/labelled-fn-stmt-second.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/let-array-with-newline.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/statements/if/let-block-with-newline.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/statements/if/let-identifier-with-newline.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/statements/if/tco-else-body.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'BinaryExpressions with operator `-` are not supported at this time',
    }

## language/statements/if/tco-if-body.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'BinaryExpressions with operator `-` are not supported at this time',
    }
