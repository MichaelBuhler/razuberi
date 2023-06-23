#include "internal.h"

#include <memory>

#include "exception.h"
#include "scope.h"
#include "value.h"

using namespace std;

shared_ptr<Value> _call (shared_ptr<Value> callee, shared_ptr<Scope> scope, vector<shared_ptr<Value> > params) {
  if (callee->type != OBJECT_VALUE_TYPE) {
    throw TypeError("callee is not an object");
  }
  shared_ptr<Object> obj = static_pointer_cast<Object>(callee);
  if (obj->__Call__ == nullptr) {
    throw TypeError("object is not a function");
  }
  shared_ptr<Scope> functionScope = make_shared<Scope>(scope);
  functionScope->set("this", callee);
  return obj->__Call__(obj, functionScope, params);
}
