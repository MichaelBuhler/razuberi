#include "debug.h"

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "type_conversion.h"
#include "value.h"

using namespace std;

static const string yellow = "\033[33m";
static const string bold = "\033[1m";
static const string reset = "\033[0m";

string indent (string str, int spaces = 2);
string stringify (Scope& scope);
string stringify (Reference ref);
string stringify (shared_ptr<Value> value);

void debug (string str) {
  cout << reset<<yellow<<bold << "[debug] " << reset<<yellow << str << reset << endl;
}

void debug (Scope scope) {
  debug(stringify(scope));
}
void debug (std::string str, Scope scope) {
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

string stringify (Scope& scope) {
  string str = "Scope {";
  map<string, shared_ptr<Object::Property> > properties = scope.object.properties;
  if (properties.size() > 0) {
    for ( map<string, shared_ptr<Object::Property> >::iterator it = properties.begin() ; it != properties.end() ; it++ ) {
      str += "\n  " + it->first + ": " + indent(stringify(it->second->value));
    }
    str += "\n";
  }
  str += "}";
  if (scope.parentScope) {
    str += " parent " + stringify(*scope.parentScope);
  }
  return str;
}

string stringify (Reference ref) {
  return "Reference {\n  baseObject:" + stringify(ref.baseObject) + "\n  propertyName: " + stringify(ref.propertyName) + "\n}";
}

string stringify (shared_ptr<Value> val) {
  if (val == nullptr) {
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
      if (properties.size() > 0) {
        for ( map<string, shared_ptr<Object::Property> >::iterator it = properties.begin() ; it != properties.end() ; it++ ) {
          str += " " + it->first + ",";
        }
        str = str.substr(0, str.length()-1);
        str += " ";
      }
      str += "}";
      str += "\n}";
      return str;
    }
    case REFERENCE_VALUE_TYPE: {
      shared_ptr<Reference> ref = static_pointer_cast<Reference>(val);
      return "shared_ptr<Reference> {\n  baseObject:" + stringify(ref->baseObject) + "\n  propertyName: " + stringify(ref->propertyName) + "\n}";
    }
  }
}
