#include "host_objects.h"

#include <iostream>
#include <memory>

#include "internal.h"
#include "reference.h"
#include "type_conversion.h"
#include "value.h"

using namespace std;

shared_ptr<Value> _log (shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {
  for ( int i = 0 ; i < arguments.size() ; i++ ) {
    if (i != 0) cout << " ";
    shared_ptr<Value> arg = arguments[i];
    shared_ptr<String> str = nullptr;
    if (arg->type == OBJECT_VALUE_TYPE) {
      shared_ptr<Object> obj = static_pointer_cast<Object>(arg);
      if (obj->__HasProperty__("toString")) {
        vector<shared_ptr<Value> > params;
        str = ToString(_call(Reference(obj, make_shared<String>("toString")), params));
      }
    }
    if (str == nullptr) {
      str = ToString(arg);
    }
    cout << str->value;
  }
  cout << endl;
  return make_shared<Undefined>();
}

void init_host_objects (shared_ptr<Scope> globalScope) {
  shared_ptr<Object> console = make_shared<Object>();
  console->__Class__ = "Console";
  globalScope->*"console" = console;

  console->*"log" = make_shared<Object>(static_pointer_cast<Object>(GetValue(globalScope->*"Function"->*"prototype")), _log);
}
