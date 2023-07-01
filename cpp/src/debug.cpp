#include "debug.h"

#include <iostream>
#include <string>

#include "type_conversion.h"
#include "value.h"

using namespace std;

static const string yellow = "\033[33m";
static const string bold = "\033[1m";
static const string reset = "\033[0m";

string stringify (shared_ptr<Value> value) {
  if (value == nullptr) {
    return "nullptr";
  }
  switch (value->type) {
    case UNDEFINED_VALUE_TYPE:
      return "shared_ptr<Undefined>";
    case NULL_VALUE_TYPE:
      return "shared_ptr<Null>";
    case BOOLEAN_VALUE_TYPE:
      return "shared_ptr<Boolean> { value: " + ToString(value)->value + " }";
    case NUMBER_VALUE_TYPE:
      return "shared_ptr<Number> { value: " + ToString(value)->value + " }";
    case STRING_VALUE_TYPE:
      return "shared_ptr<String> { value: \"" + static_pointer_cast<String>(value)->value + "\" }";
    case OBJECT_VALUE_TYPE: {
      shared_ptr<Object> obj = static_pointer_cast<Object>(value);
      return "shared_ptr<Object> [" + obj->__Class__ + "] { properties: ... }";
    }
    case REFERENCE_VALUE_TYPE: {
      shared_ptr<Reference> ref = static_pointer_cast<Reference>(value);
      return "shared_ptr<Reference> {\n  baseObject:" + stringify(ref->baseObject) + "\n  propertyName: " + stringify(ref->propertyName) + "\n}";
    }
  }
}

void debug (string str) {
  cout << reset<<yellow<<bold << "[debug] " << reset<<yellow << str << reset << endl;
}

void debug (shared_ptr<Value> value) {
  cout << reset<<yellow<<bold << "[debug] " << reset<<yellow << stringify(value) << reset << endl;
}

void debug (string str, shared_ptr<Value> value) {
  cout << reset<<yellow<<bold << "[debug] " << reset<<yellow << str << ": " << stringify(value) << reset << endl;
}
