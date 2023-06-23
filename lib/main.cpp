#include "main.h"

#include <iostream>
#include <memory>

#include "exception.h"
#include "global_scope.h"

using namespace std;

int main () {
  try {
    shared_ptr<Scope> globalScope = init_global_scope();
    run(globalScope);
    return 0;
  } catch (NotImplementedException &e) {
    cout << e.toString() << endl;
  } catch (RuntimeException &e) {
    cout << "Uncaught " << e.toString() << endl;
  }
  return 1;
}
