#include "host_objects.h"

#include <iostream>
#include <memory>

#include "type_conversion.h"

using namespace std;

shared_ptr<Value> _log (shared_ptr<Value> thisArg, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  for ( int i = 0 ; i < arguments.size() ; i++ ) {
    if (i != 0) cout << " ";
    shared_ptr<Value> arg = arguments[i];
    cout << ToString(arguments[i])->value;
  }
  cout << endl;
  return make_shared<Undefined>();
}

void init_host_objects (shared_ptr<Scope> globalScope) {
  shared_ptr<Object> console = make_shared<Object>(nullptr, nullptr);
  globalScope->set("console", console);

  shared_ptr<Object> log = make_shared<Object>(nullptr, _log);
  console->__Put__("log", log);
}
