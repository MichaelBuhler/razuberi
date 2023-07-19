#include "debug.h"

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "reference.h"
#include "tty.h"
#include "type_conversion.h"
#include "value.h"

using namespace std;

static bool enabled = false;

static const string yellow = "\033[33m";
static const string bold = "\033[1m";
static const string reset = "\033[0m";

void debug (string str);
string indent (string str, int spaces = 2);
string stringify (shared_ptr<Scope> scope);
string stringify (Reference ref);
string stringify (shared_ptr<Value> value);

void debugEnable () {
  enabled = true;
  debug("logging enabled");
}
void debugDisable () {
  enabled = false;
  debug("logging disabled");
}

void debug (string str) {
  if (enabled) {
    if (isTTY) cout << reset<<yellow<<bold;
    cout << "[debug] ";
    if (isTTY) cout << reset<<yellow;
    cout << str;
    if (isTTY) cout << reset;
    cout << endl;
  }
}

void debug (std::shared_ptr<Scope> scope) {
  debug(stringify(scope));
}
void debug (std::string str, std::shared_ptr<Scope> scope) {
  debug(str + ": " +stringify(scope));
}

void debug (Reference ref) {
  debug(stringify(ref));
}

void debug (string str, Reference ref) {
  debug(str + ": " +stringify(ref));
}

void debug (shared_ptr<Value> value) {
  debug(stringify(value));
}

void debug (string str, shared_ptr<Value> value) {
  debug(str + ": " +stringify(value));
}

string indent (string str, int spaces) {
  string res = "";
  for ( int i = 0 ; i < str.length() ; i++ ) {
    res += str[i];
    if (str[i] == '\n') {
      for ( int i = 0 ; i < spaces ; i++ ) {
        res += " ";
      }
    }
  }
  return res;
}

string stringify (std::shared_ptr<Scope> scope) {
  string str = "Scope {";
  if (scope->object->properties.size() > 0) {
    for ( map<string, shared_ptr<Object::Property> >::iterator it = scope->object->properties.begin() ; it != scope->object->properties.end() ; it++ ) {
      str += "\n  " + it->first + ": " + indent(stringify(it->second->value));
    }
    str += "\n";
  }
  str += "}";
  if (scope->parentScope) {
    str += " parent " + stringify(scope->parentScope);
  }
  return str;
}

string stringify (Reference ref) {
  string str = "Reference {\n  baseObject: " + indent(stringify(ref.baseObject));
  str += "\n  propertyName: " + stringify(ref.propertyName);
  str += "\n  currentValue: ";
  try {
    str += indent(stringify(GetValue(ref)));
  } catch (shared_ptr<Value> referenceError) {
    str += ToString(referenceError)->value;
  }
  str += "\n}";
  return str;
}

string stringify (shared_ptr<Value> val) {
  if (val.get() == nullptr) {
    return "nullptr";
  }
  switch (val->type) {
    case UNDEFINED_VALUE_TYPE:
      return "shared_ptr<Undefined>";
    case NULL_VALUE_TYPE:
      return "shared_ptr<Null>";
    case BOOLEAN_VALUE_TYPE:
      return "shared_ptr<Boolean>(" + ToString(val)->value + ")";
    case NUMBER_VALUE_TYPE:
      return "shared_ptr<Number>(" + ToString(val)->value + ")";
    case STRING_VALUE_TYPE:
      return "shared_ptr<String>(\"" + static_pointer_cast<String>(val)->value + "\")";
    case OBJECT_VALUE_TYPE: {
      shared_ptr<Object> obj = static_pointer_cast<Object>(val);
      string str = "shared_ptr<Object> [";
      if (obj->__Class__.length()) {
        str += obj->__Class__;
      } else {
        str += "__Class__ not defined";
      }
      str += "] {\n  properties: {";
      map<string, shared_ptr<Object::Property> > properties = obj->properties;
      if (obj->properties.size() > 0) {
        // TODO: this version is seg faulting?
        // for ( map<string, shared_ptr<Object::Property> >::iterator it = obj->properties.begin() ; it != obj->properties.end() ; it++ ) {
        //   debug(it->second.get());
        //   str += "\n  " + it->first + ": " + stringify(it->second->value);
        // }
        // str += "\n";
        for ( map<string, shared_ptr<Object::Property> >::iterator it = obj->properties.begin() ; it != obj->properties.end() ; it++ ) {
          str += " " + it->first + ",";
        }
        str = str.substr(0, str.length()-1);
        str += " ";
      }
      str += "}";
      str += "\n}";
      return str;
    }
  }
}
