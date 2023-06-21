#include <iostream>
#include <string>
#include <vector>

#include "lib/exception.h"
#include "lib/global_scope.h"
#include "lib/scope.h"
#include "lib/type_conversion.h"
#include "lib/value.h"

using namespace std;

shared_ptr<Value> inline _invoke (shared_ptr<Value> value, shared_ptr<Scope> scope, vector<shared_ptr<Value> > params) {
  shared_ptr<Object> obj = ToObject(value);
  return obj->__Call__(obj, scope, params);
}

void run (shared_ptr<Scope> scope) {
  {
    vector<shared_ptr<Value> > params;
    params.push_back(make_shared<Undefined>());
    params.push_back(make_shared<Null>());
    params.push_back(make_shared<Boolean>(true));
    params.push_back(make_shared<Boolean>(false));
    params.push_back(make_shared<Number>(123.45));
    params.push_back(make_shared<String>("Hello, world!"));
    _invoke(scope->*"console"->*"log", scope, params);
  }
  {
    shared_ptr<Object> A = make_shared<Object>(nullptr);
    A->__Put__("hello", make_shared<String>("world"));
    shared_ptr<Object> B = make_shared<Object>(A);
    shared_ptr<Object> C = make_shared<Object>(B);
    vector<shared_ptr<Value> > params;
    params.push_back(C->__Get__("hello"));
    _invoke(scope->*"console"->*"log", scope, params);
  }
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
