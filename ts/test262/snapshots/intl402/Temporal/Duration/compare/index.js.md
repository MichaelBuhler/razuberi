# Snapshot report for `intl402/Temporal/Duration/compare/index.js`

The actual snapshot is saved in `index.js.snap`.

Generated by [AVA](https://avajs.dev).

## intl402/Temporal/Duration/compare/relativeto-hour.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:39:141: error: invalid operands to binary expression ('const char [11]' and 'const char [5]')␊
      (scope->*"assert"->*"sameValue").call(((scope->*"Temporal"->*"Duration"->*"compare").call((scope->*"oneDay", scope->*"hours24", "relativeTo"&"year"&make_shared<Number>(2019)|"month"&make_shared<Number>(11)|"day"&make_shared<Number>(3)|"timeZone"&make_shared<String>("America/Vancouver"))), make_shared<Number>(1), make_shared<String>("casts relativeTo to ZonedDateTime from object")));␊
                                                                                                                                      ~~~~~~~~~~~~^~~~~~~␊
      1 error generated.`,
    }

## intl402/Temporal/Duration/compare/relativeto-sub-minute-offset.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ❌ Fail | An error occurred while compiling the test with `g++`. |
> | Execute | ⬜ Skip | *This stage did not run.* |

    Error {
      message: `<stdin>:256:19: error: redefinition of '_anonymous_10'␊
      shared_ptr<Value> _anonymous_10 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      <stdin>:246:19: note: previous definition is here␊
      shared_ptr<Value> _anonymous_10 (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {␊
                        ^␊
      1 error generated.`,
    }
