#include "internal.h"

#include <memory>

#include "exception.h"
#include "scope.h"
#include "value.h"

using namespace std;

shared_ptr<Value> _call (shared_ptr<Value> value, shared_ptr<Scope> scope, vector<shared_ptr<Value> > params) {
  if (value->type != OBJECT_VALUE_TYPE) {
    throw TypeError("callee is not an object");
  }
  shared_ptr<Object> obj = static_pointer_cast<Object>(value);
  if (obj->__Call__ == nullptr) {
    throw TypeError("object has no call signature");
  }
  shared_ptr<Scope> functionScope = make_shared<Scope>(scope);
  functionScope->set("this", value);
  return obj->__Call__(obj, functionScope, params);
}
