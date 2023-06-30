#include "debug.h"

#include <iostream>

#include "type_conversion.h"
#include "value.h"

using namespace std;

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

void debug (std::string str) {
  cout << endl << "debug: " << str << endl << endl;
}

void debug (shared_ptr<Value> value) {
  cout << endl << "debug: " << stringify(value) << endl << endl;
}

void debug (std::string str, std::shared_ptr<Value> value) {
  cout << endl << "debug: " << str << ": " << stringify(value) << endl << endl;
}
