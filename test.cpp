#include <iostream>
#include <string>
#include <vector>

#include "lib/exception.h"
#include "lib/host_objects.h"
#include "lib/scope.h"
#include "lib/type_conversion.h"
#include "lib/value.h"

using namespace std;

shared_ptr<Value> inline _invoke (shared_ptr<Value> value, shared_ptr<Scope> scope, vector<shared_ptr<Value> > params) {
  return ToObject(value)->__Call__(scope, params);
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

  scope->set("a", make_shared<Boolean>(true));
  scope->set("b", make_shared<Number>(999.999));
  {
    vector<shared_ptr<Value> > params;
    params.push_back(scope->get("a") + scope->get("b"));
    _invoke(scope->*"console"->*"log", scope, params);
  }
}

int main () {
  try {
    shared_ptr<Scope> globalScope = make_shared<Scope>();
    init_host_objects(globalScope);
    run(globalScope);
    return 0;
  } catch (NotImplementedException &e) {
    cout << e.toString() << endl;
  } catch (RuntimeException &e) {
    cout << "Uncaught " << e.toString() << endl;
  }
  return 1;
}
