#include "main.h"

#include <iostream>
#include <memory>

#include "exception.h"
#include "global_scope.h"

using namespace std;

static const string red = "\033[31m";
static const string reset = "\033[0m";

int main () {
  shared_ptr<Scope> globalScope = nullptr;
  
  try {
    globalScope = init_global_scope();
  } catch (const RazuberiException& e) {
    cout << endl << red << e.toString() << reset << endl;
    return 2;
  }

  try {
    _run(globalScope);
  } catch (shared_ptr<Value> value) {
    cout << endl << red << "Uncaught ";
    (globalScope->*"console"->*"log").call(value);
    cout << reset;
    return 1;
  } catch (const RazuberiException& e) {
    cout << endl << red << e.toString() << reset << endl;
    return 2;
  } catch (const EcmaScriptRuntimeError& e) {
    cout << endl << red << "Uncaught " << e.toString() << reset << endl;
    return 3;
  }

  return 0;
}
