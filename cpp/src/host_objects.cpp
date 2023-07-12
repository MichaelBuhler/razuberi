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
    switch (arg->type) {
      case UNDEFINED_VALUE_TYPE:
        cout << "undefined";
        break;
      case NULL_VALUE_TYPE:
        cout << "null";
        break;
      case BOOLEAN_VALUE_TYPE:
        cout << ToString(static_pointer_cast<Boolean>(arg))->value;
        break;
      case NUMBER_VALUE_TYPE: {
        shared_ptr<Number> num = static_pointer_cast<Number>(arg);
        if (!num->isNaN && !num->isInfinity && num->value == 0 && num->isNegative) {
          cout << "-0";
        } else {
          cout << ToString(static_pointer_cast<Number>(arg))->value;
        }
      } break;
      case STRING_VALUE_TYPE:
        cout << static_pointer_cast<String>(arg)->value;
        break;
      case OBJECT_VALUE_TYPE: {
        shared_ptr<Object> obj = static_pointer_cast<Object>(arg);
        if (obj->__HasProperty__("toString")) {
          cout << ToString((obj->*"toString").call())->value;
        } else {
          cout << ToString(obj)->value;
        }
      } break;
    }
  }
  cout << endl;
  return make_shared<Undefined>();
}

void init_host_objects (shared_ptr<Scope> globalScope) {
  shared_ptr<Object> console = make_shared<Object>();
  console->__Class__ = "Console";
  globalScope->*"console" = console;
  globalScope->*"console"->*"log" = Object::makeFunction(Console_log);
}
