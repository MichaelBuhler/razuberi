#include "razuberi.h"

#include <iostream>

#include "global_scope.h"
#include "exception.h"
#include "type_conversion.h"

using namespace std;

shared_ptr<Value> _invoke (shared_ptr<Value> value, shared_ptr<Scope> scope, vector<shared_ptr<Value> > params) {
  shared_ptr<Object> obj = ToObject(value);
  return obj->__Call__(obj, scope, params);
}

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
