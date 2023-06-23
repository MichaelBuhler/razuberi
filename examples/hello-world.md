# razuberi/examples/hello-world.md

## Hello, world!

The simplest and most important of all programs.

Below are input and output examples of the transpilation process. C++ output is likely to change in the future.

*Note: As of 2023-06-21 this is transpilation is not possible*

### JavaScript/TypeScript Input

```javascript
console.log("Hello, world!")
```

### C++ Output

```c++
#include <string>
#include <vector>

#include "razuberi.h"

using namespace std;

void run (shared_ptr<Scope> scope) {
  vector<shared_ptr<Value> > params;
  params.push_back(make_shared<String>("Hello, world!"));
  _invoke(scope->*"console"->*"log", scope, params);
}
```
