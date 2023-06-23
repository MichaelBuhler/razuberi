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

shared_ptr<Object> _new (shared_ptr<Value> constructor, vector<shared_ptr<Value> > params) {
  if (constructor->type != OBJECT_VALUE_TYPE) {
    throw TypeError("constructor is not an object");
  }
  shared_ptr<Object> obj = static_pointer_cast<Object>(constructor);
  if (obj->__Construct__ == nullptr) {
    throw TypeError("object is not a constructor");
  }
  shared_ptr<Scope> constructorScope = make_shared<Scope>();
  constructorScope->set("this", make_shared<Object>());
  shared_ptr<Value> result = obj->__Construct__(constructorScope, params);
  if (result->type != OBJECT_VALUE_TYPE) {
    throw TypeError("constructor returned a non-object");
  }
  return static_pointer_cast<Object>(result);
}
