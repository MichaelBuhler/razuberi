#include "host_objects.h"

#include <iostream>
#include <memory>

#include "internal.h"
#include "reference.h"
#include "type_conversion.h"
#include "value.h"

using namespace std;

shared_ptr<Value> Console_log (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> > arguments) {
  for ( int i = 0 ; i < arguments.size() ; i++ ) {
    if (i != 0) cout << " ";
    shared_ptr<Value> arg = arguments[i];
    shared_ptr<String> str = nullptr;
    if (arg->type == OBJECT_VALUE_TYPE) {
      shared_ptr<Object> obj = static_pointer_cast<Object>(arg);
      if (obj->__HasProperty__("toString")) {
        str = ToString((obj->*"toString").call());
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
  globalScope->*"console"->*"log" = _fn(Console_log);
}
