# Snapshot report for `built-ins/global/index.js`

The actual snapshot is saved in `index.js.snap`.

Generated by [AVA](https://avajs.dev).

## built-ins/global/10.2.1.1.3-4-16-s.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught Test262Error: Expected a undefined to be thrown but no exception was thrown at all',
    }

## built-ins/global/10.2.1.1.3-4-18-s.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:229:26: error: no viable overloaded '='␊
      make_shared<Undefined>() = make_shared<Number>(12);␊
      ~~~~~~~~~~~~~~~~~~~~~~~~ ^ ~~~~~~~~~~~~~~~~~~~~~~~␊
      /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1/memory:3435:17: note: candidate function not viable: no known conversion from 'shared_ptr<Number>' to 'const shared_ptr<Undefined>' for 1st argument␊
          shared_ptr& operator=(const shared_ptr& __r) _NOEXCEPT;␊
                      ^␊
      /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1/memory:3443:9: note: candidate template ignored: requirement '__compatible_with<Number, Undefined>::value' was not satisfied [with _Yp = Number]␊
              operator=(const shared_ptr<_Yp>& __r) _NOEXCEPT;␊
              ^␊
      /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1/memory:3445:17: note: candidate function not viable: no known conversion from 'shared_ptr<Number>' to 'shared_ptr<Undefined>' for 1st argument␊
          shared_ptr& operator=(shared_ptr&& __r) _NOEXCEPT;␊
                      ^␊
      /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1/memory:3453:9: note: candidate template ignored: requirement '__compatible_with<Number, Undefined>::value' was not satisfied [with _Yp = Number]␊
              operator=(shared_ptr<_Yp>&& __r);␊
              ^␊
      /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1/memory:3463:9: note: candidate template ignored: could not match 'auto_ptr' against 'shared_ptr'␊
              operator=(auto_ptr<_Yp>&& __r);␊
              ^␊
      /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1/memory:3473:9: note: candidate template ignored: could not match 'unique_ptr' against 'shared_ptr'␊
              operator=(unique_ptr<_Yp, _Dp>&& __r);␊
              ^␊
      1 error generated.`,
    }

## built-ins/global/10.2.1.1.3-4-22.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: '`finally` blocks are not supported at this time',
    }

## built-ins/global/10.2.1.1.3-4-27.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: '`finally` blocks are not supported at this time',
    }

## built-ins/global/S10.2.3_A1.1_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## built-ins/global/S10.2.3_A1.1_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "parseInt" is not defined',
    }

## built-ins/global/S10.2.3_A1.1_T3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "Number" is not defined',
    }

## built-ins/global/S10.2.3_A1.1_T4.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "Math" is not defined',
    }

## built-ins/global/S10.2.3_A1.2_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## built-ins/global/S10.2.3_A1.2_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "parseInt" is not defined',
    }

## built-ins/global/S10.2.3_A1.2_T3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "Number" is not defined',
    }

## built-ins/global/S10.2.3_A1.2_T4.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught ReferenceError: "Math" is not defined',
    }

## built-ins/global/S10.2.3_A1.3_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## built-ins/global/S10.2.3_A1.3_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## built-ins/global/S10.2.3_A1.3_T3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## built-ins/global/S10.2.3_A1.3_T4.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## built-ins/global/S10.2.3_A2.1_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'We don\'t know what to do with this node type. We were previously a Statement but we can\'t fit in here?',
    }

## built-ins/global/S10.2.3_A2.1_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'We don\'t know what to do with this node type. We were previously a Statement but we can\'t fit in here?',
    }

## built-ins/global/S10.2.3_A2.1_T3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'We don\'t know what to do with this node type. We were previously a Statement but we can\'t fit in here?',
    }

## built-ins/global/S10.2.3_A2.1_T4.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'We don\'t know what to do with this node type. We were previously a Statement but we can\'t fit in here?',
    }

## built-ins/global/S10.2.3_A2.3_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## built-ins/global/S10.2.3_A2.3_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## built-ins/global/S10.2.3_A2.3_T3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## built-ins/global/S10.2.3_A2.3_T4.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## built-ins/global/S15.1_A1_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:34:20: error: use of undeclared identifier '_this'␊
      scope->*"global" = _this;␊
                         ^␊
      1 error generated.`,
    }

## built-ins/global/S15.1_A1_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:34:20: error: use of undeclared identifier '_this'␊
      scope->*"global" = _this;␊
                         ^␊
      1 error generated.`,
    }

## built-ins/global/S15.1_A2_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:34:20: error: use of undeclared identifier '_this'␊
      scope->*"global" = _this;␊
                         ^␊
      1 error generated.`,
    }

## built-ins/global/global-object.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:33:40: error: use of undeclared identifier '_this'␊
      (scope->*"assert"->*"sameValue").call((_this, scope->*"globalThis"));␊
                                             ^␊
      1 error generated.`,
    }

## built-ins/global/property-descriptor.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'We don\'t know what to do with this node type. We were previously a Statement but we can\'t fit in here?',
    }
