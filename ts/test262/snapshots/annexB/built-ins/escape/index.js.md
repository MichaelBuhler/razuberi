# Snapshot report for `annexB/built-ins/escape/index.js`

The actual snapshot is saved in `index.js.snap`.

Generated by [AVA](https://avajs.dev).

## annexB/built-ins/escape/argument_bigint.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for BigIntLiteral nodes.',
    }

## annexB/built-ins/escape/argument_types.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "escape" is not defined',
    }

## annexB/built-ins/escape/empty-string.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "escape" is not defined',
    }

## annexB/built-ins/escape/escape-above-astral.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "escape" is not defined',
    }

## annexB/built-ins/escape/escape-above.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "escape" is not defined',
    }

## annexB/built-ins/escape/escape-below.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:33:85: error: universal character name refers to a control character␊
      (scope->*"assert"->*"sameValue").call(((scope->*"escape").call(make_shared<String>("\\u0000\\u0001\\u0002\\u0003")), make_shared<String>("%00%01%02%03"), make_shared<String>("characters: \\\\x00\\\\x01\\\\x02\\\\x03")));␊
                                                                                          ^~~~~~␊
      <stdin>:33:91: error: universal character name refers to a control character␊
      (scope->*"assert"->*"sameValue").call(((scope->*"escape").call(make_shared<String>("\\u0000\\u0001\\u0002\\u0003")), make_shared<String>("%00%01%02%03"), make_shared<String>("characters: \\\\x00\\\\x01\\\\x02\\\\x03")));␊
                                                                                                ^~~~~~␊
      <stdin>:33:97: error: universal character name refers to a control character␊
      (scope->*"assert"->*"sameValue").call(((scope->*"escape").call(make_shared<String>("\\u0000\\u0001\\u0002\\u0003")), make_shared<String>("%00%01%02%03"), make_shared<String>("characters: \\\\x00\\\\x01\\\\x02\\\\x03")));␊
                                                                                                      ^~~~~~␊
      <stdin>:33:103: error: universal character name refers to a control character␊
      (scope->*"assert"->*"sameValue").call(((scope->*"escape").call(make_shared<String>("\\u0000\\u0001\\u0002\\u0003")), make_shared<String>("%00%01%02%03"), make_shared<String>("characters: \\\\x00\\\\x01\\\\x02\\\\x03")));␊
                                                                                                            ^~~~~~␊
      4 errors generated.`,
    }

## annexB/built-ins/escape/length.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'We don\'t know what to do with this node type. We were previously a Statement but we can\'t fit in here?',
    }

## annexB/built-ins/escape/name.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'We don\'t know what to do with this node type. We were previously a Statement but we can\'t fit in here?',
    }

## annexB/built-ins/escape/not-a-constructor.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for ArrayExpression nodes.',
    }

## annexB/built-ins/escape/prop-desc.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'We don\'t know what to do with this node type. We were previously a Statement but we can\'t fit in here?',
    }

## annexB/built-ins/escape/to-primitive-err.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for SequenceExpression nodes.',
    }

## annexB/built-ins/escape/to-primitive-observe.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for SequenceExpression nodes.',
    }

## annexB/built-ins/escape/to-string-err-symbol.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "Symbol" is not defined',
    }

## annexB/built-ins/escape/to-string-err.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for ObjectExpression nodes.',
    }

## annexB/built-ins/escape/to-string-observe.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'No generator defined for ObjectExpression nodes.',
    }

## annexB/built-ins/escape/unmodified.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "escape" is not defined',
    }