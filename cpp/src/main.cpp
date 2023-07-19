#include "main.h"

#include <iostream>
#include <memory>

#if _WIN32
  #include <io.h>
  #define ISATTY _isatty
  #define FILENO _fileno
#else
  #include <unistd.h>
  #define ISATTY isatty
  #define FILENO fileno
#endif

#include "exception.h"
#include "global_scope.h"
#include "tty.h"
#include "type_conversion.h"

using namespace std;

static const string red = "\033[31m";
static const string reset = "\033[0m";

int main () {
  isTTY = ISATTY(FILENO(stderr));

  shared_ptr<Scope> globalScope = nullptr;
  
  try {
    globalScope = init_global_scope();
  } catch (const RazuberiException& e) {
    cerr << endl;
    if (isTTY) cerr << reset<<red;
    cerr << e.toString();
    if (isTTY) cerr << reset;
    cerr << endl;
    return 2;
  }

  try {
    _run(globalScope);
    return 0;
  } catch (shared_ptr<Value> value) {
    cerr << endl;
    if (isTTY) cerr << reset<<red;
    cerr << "Uncaught " << ToString(value)->value;
    if (isTTY) cerr << reset;
    cerr << endl;
    return 1;
  } catch (const RazuberiException& e) {
    cerr << endl;
    if (isTTY) cerr << reset<<red;
    cerr << e.toString();
    if (isTTY) cerr << reset;
    cerr << endl;
    return 2;
  } catch (const EcmaScriptRuntimeError& e) {
    cerr << endl;
    if (isTTY) cerr << reset<<red;
    cerr << "Uncaught " << e.toString();
    if (isTTY) cerr << reset;
    cerr << endl;
    return 3;
  }
}
