#include "internal.h"

#include <memory>

#include "exception.h"
#include "scope.h"
#include "value.h"

using namespace std;

// TODO: base+propertyName are mocking the Refernce type
shared_ptr<Value> _call (shared_ptr<Value> base, string propertyName, shared_ptr<Scope> scope, vector<shared_ptr<Value> > params) {
  // TODO: dangerous to cast `base` to Object here
  shared_ptr<Value> callee = static_pointer_cast<Object>(base)->__Get__(propertyName);
  if (callee->type != OBJECT_VALUE_TYPE) {
    throw TypeError("callee is not an object");
  }
  shared_ptr<Object> obj = static_pointer_cast<Object>(callee);
  if (obj->__Call__ == nullptr) {
    throw TypeError("object is not a function");
  }
  shared_ptr<Scope> functionScope = make_shared<Scope>(scope);
  functionScope->set("this", callee);
  return obj->__Call__(base, functionScope, params);
}

shared_ptr<Object> _new (shared_ptr<Value> constructor, vector<shared_ptr<Value> > params) {
  if (constructor->type != OBJECT_VALUE_TYPE) {
    throw TypeError("constructor is not an object");
  }
  shared_ptr<Object> obj = static_pointer_cast<Object>(constructor);
  if (obj->__Construct__ == nullptr) {
    throw TypeError("object is not a constructor");
  }
  shared_ptr<Object> prototype = nullptr;
  if (obj->__HasProperty__("prototype")) {
    shared_ptr<Value> maybeObj = obj->__Get__("prototype");
    if (maybeObj->type == OBJECT_VALUE_TYPE) {
      prototype = static_pointer_cast<Object>(maybeObj);
    } else {
      // TODO: should actually fall back to Object.prototype
      prototype = make_shared<Object>();
    }
  } else {
    // TODO: not really a TypeError, but rather an implmentation error
    throw TypeError("constructor has no prototype");
  }
  shared_ptr<Object> newObject = make_shared<Object>(prototype);
  shared_ptr<Scope> constructorScope = make_shared<Scope>();
  shared_ptr<Value> result = obj->__Construct__(newObject, constructorScope, params);
  if (result->type != OBJECT_VALUE_TYPE) {
    throw TypeError("constructor returned a non-object");
  }
  return static_pointer_cast<Object>(result);
}
