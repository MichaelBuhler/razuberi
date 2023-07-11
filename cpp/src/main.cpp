#include "main.h"

#include <iostream>
#include <memory>

#include "exception.h"
#include "global_scope.h"

using namespace std;

static const string red = "\033[31m";
static const string reset = "\033[0m";

int main () {
  try {
    shared_ptr<Scope> globalScope = init_global_scope();
    _run(globalScope);
    return 0;
  } catch (const RazuberiException& e) {
    cout << endl << red << e.toString() << reset << endl;
  } catch (const EcmaScriptRuntimeError& e) {
    cout << endl << red << "Uncaught " << e.toString() << reset << endl;
  }
  return 1;
}
