# Snapshot report for `language/types/null/index.js`

The actual snapshot is saved in `index.js.snap`.

Generated by [AVA](https://avajs.dev).

## language/types/null/S8.2_A1_T1.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/types/null/S8.2_A1_T2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ✅ Pass |  |

    'No error'

## language/types/null/S8.2_A2.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ❌ Fail | An error occurred while loading the test from the `test262` folder. |
> | Transpile | ⬜ Skip | *This stage did not run.* |
> | Compile | ⬜ Skip | *This stage did not run.* |
> | Execute | ⬜ Skip | *This stage did not run.* |

    LoaderError {
      message: 'Negative tests, that is, test with the `negative` frontmatter attibute, are not supported at this time.',
    }

## language/types/null/S8.2_A3.js

> | Test Stage | Status | Details |
> | :-- | :-- | :-- |
> | Load | ✅ Pass |  |
> | Transpile | ✅ Pass |  |
> | Compile | ✅ Pass |  |
> | Execute | ❌ Fail | An error occurred while executing the test program. |

    Error {
      message: 'Uncaught Test262Error: #1: typeof null === "object". Actual: null',
    }
