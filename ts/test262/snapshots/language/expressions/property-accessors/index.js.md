# Snapshot report for `language/expressions/property-accessors/index.js`

The actual snapshot is saved in `index.js.snap`.

Generated by [AVA](https://avajs.dev).

## language/expressions/property-accessors/S11.2.1_A1.1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:36:75: error: universal character name refers to a control character␊
      if (_if(_strictNotEquals((scope->*"eval").call(make_shared<String>("Number\\u000b.\\u000bPOSITIVE_INFINITY")), scope->*"Number"->*"POSITIVE_INFINITY"))) {␊
                                                                                ^~~~~~␊
      <stdin>:36:82: error: universal character name refers to a control character␊
      if (_if(_strictNotEquals((scope->*"eval").call(make_shared<String>("Number\\u000b.\\u000bPOSITIVE_INFINITY")), scope->*"Number"->*"POSITIVE_INFINITY"))) {␊
                                                                                       ^~~~~~␊
      <stdin>:60:77: error: universal character name refers to a control character␊
      if (_if(_strictNotEquals((scope->*"eval").call(make_shared<String>("Number\\t\\u000b\\f  \\n\\r      .\\t\\u000b\\f  \\n\\r      POSITIVE_INFINITY")), scope->*"Number"->*"POSITIVE_INFINITY"))) {␊
                                                                                  ^~~~~~␊
      <stdin>:60:101: error: universal character name refers to a control character␊
      if (_if(_strictNotEquals((scope->*"eval").call(make_shared<String>("Number\\t\\u000b\\f  \\n\\r      .\\t\\u000b\\f  \\n\\r      POSITIVE_INFINITY")), scope->*"Number"->*"POSITIVE_INFINITY"))) {␊
                                                                                                     ^~~~~~␊
      4 errors generated.`,
    }

## language/expressions/property-accessors/S11.2.1_A1.2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:36:76: error: universal character name refers to a control character␊
      if (_if(_strictNotEquals((scope->*"eval").call(make_shared<String>("Number[\\u000b\\"POSITIVE_INFINITY\\"\\u000b]")), scope->*"Number"->*"POSITIVE_INFINITY"))) {␊
                                                                                 ^~~~~~␊
      <stdin>:36:103: error: universal character name refers to a control character␊
      if (_if(_strictNotEquals((scope->*"eval").call(make_shared<String>("Number[\\u000b\\"POSITIVE_INFINITY\\"\\u000b]")), scope->*"Number"->*"POSITIVE_INFINITY"))) {␊
                                                                                                            ^~~~~~␊
      <stdin>:60:78: error: universal character name refers to a control character␊
      if (_if(_strictNotEquals((scope->*"eval").call(make_shared<String>("Number[\\t\\u000b\\f  \\n\\r      \\"POSITIVE_INFINITY\\"\\t\\u000b\\f  \\n\\r      ]")), scope->*"Number"->*"POSITIVE_INFINITY"))) {␊
                                                                                   ^~~~~~␊
      <stdin>:60:122: error: universal character name refers to a control character␊
      if (_if(_strictNotEquals((scope->*"eval").call(make_shared<String>("Number[\\t\\u000b\\f  \\n\\r      \\"POSITIVE_INFINITY\\"\\t\\u000b\\f  \\n\\r      ]")), scope->*"Number"->*"POSITIVE_INFINITY"))) {␊
                                                                                                                          ^~~~~~␊
      4 errors generated.`,
    }

## language/expressions/property-accessors/S11.2.1_A2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'MemberExpressions only support Identifier properties at this time (got NumericLiteral)',
    }

## language/expressions/property-accessors/S11.2.1_A3_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'MemberExpressions only support Identifier properties at this time (got StringLiteral)',
    }

## language/expressions/property-accessors/S11.2.1_A3_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'MemberExpressions only support Identifier properties at this time (got StringLiteral)',
    }

## language/expressions/property-accessors/S11.2.1_A3_T3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'MemberExpressions only support Identifier properties at this time (got StringLiteral)',
    }

## language/expressions/property-accessors/S11.2.1_A3_T4.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'BinaryExpression operator \'instanceof\' is not supported at this time',
    }

## language/expressions/property-accessors/S11.2.1_A3_T5.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'BinaryExpression operator \'instanceof\' is not supported at this time',
    }

## language/expressions/property-accessors/S11.2.1_A4_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'MemberExpressions only support Identifier properties at this time (got StringLiteral)',
    }

## language/expressions/property-accessors/S11.2.1_A4_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'MemberExpressions only support Identifier properties at this time (got StringLiteral)',
    }

## language/expressions/property-accessors/S11.2.1_A4_T3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'MemberExpressions only support Identifier properties at this time (got StringLiteral)',
    }

## language/expressions/property-accessors/S11.2.1_A4_T4.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'MemberExpressions only support Identifier properties at this time (got StringLiteral)',
    }

## language/expressions/property-accessors/S11.2.1_A4_T5.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'MemberExpressions only support Identifier properties at this time (got StringLiteral)',
    }

## language/expressions/property-accessors/S11.2.1_A4_T6.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'MemberExpressions only support Identifier properties at this time (got StringLiteral)',
    }

## language/expressions/property-accessors/S11.2.1_A4_T7.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'MemberExpressions only support Identifier properties at this time (got StringLiteral)',
    }

## language/expressions/property-accessors/S11.2.1_A4_T8.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'MemberExpressions only support Identifier properties at this time (got StringLiteral)',
    }

## language/expressions/property-accessors/S11.2.1_A4_T9.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'MemberExpressions only support Identifier properties at this time (got StringLiteral)',
    }

## language/expressions/property-accessors/S8.12.3_A1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'MemberExpressions only support Identifier properties at this time (got StringLiteral)',
    }

## language/expressions/property-accessors/S8.12.3_A2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for ObjectExpression nodes.',
    }

## language/expressions/property-accessors/S8.12.3_A3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for ObjectExpression nodes.',
    }

## language/expressions/property-accessors/non-identifier-name.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }