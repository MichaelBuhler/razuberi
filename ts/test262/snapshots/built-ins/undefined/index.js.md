# Snapshot report for `built-ins/undefined/index.js`

The actual snapshot is saved in `index.js.snap`.

Generated by [AVA](https://avajs.dev).

## built-ins/undefined/15.1.1.3-0.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:33:72: error: use of undeclared identifier '_this'␊
      scope->*"desc" = (scope->*"Object"->*"getOwnPropertyDescriptor").call((_this, make_shared<String>("undefined")));␊
                                                                             ^␊
      1 error generated.`,
    }

## built-ins/undefined/15.1.1.3-1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:33:26: error: no viable overloaded '='␊
      make_shared<Undefined>() = make_shared<Number>(5);␊
      ~~~~~~~~~~~~~~~~~~~~~~~~ ^ ~~~~~~~~~~~~~~~~~~~~~~␊
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

## built-ins/undefined/15.1.1.3-2.js

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

## built-ins/undefined/15.1.1.3-3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:33:50: error: no viable overloaded '='␊
      scope->*"newProperty" = make_shared<Undefined>() = make_shared<Number>(42);␊
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

## built-ins/undefined/S15.1.1.3_A1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'NotImplementedException: Cannot use global `eval()` to execute arbitrary code at runtime.',
    }

## built-ins/undefined/S15.1.1.3_A3_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'UnaryExpressions with operator `delete` are not supported at this time',
    }

## built-ins/undefined/S15.1.1.3_A4.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'We don\'t know what to do with this node type. We were previously a Statement but we can\'t fit in here?',
    }

## built-ins/undefined/prop-desc.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ❌ Fail | An error occurred while transpiling the test with `@razuberi/transpiler`. |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: 'We don\'t know what to do with this node type. We were previously a Statement but we can\'t fit in here?',
    }
