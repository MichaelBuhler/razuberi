#include "reference.h"

#include <memory>

#include "global_scope.h"
#include "exception.h"
#include "value.h"

using namespace std;

shared_ptr<Value> GetBase (Reference ref) {
  return ref.baseObject;
}

shared_ptr<String> GetPropertyName (Reference ref) {
  return ref.propertyName;
}

shared_ptr<Value> GetValue (Reference ref) {
  shared_ptr<Value> base = GetBase(ref);
  if (base->type == NULL_VALUE_TYPE) {
    throw ReferenceError("\"" + ref.propertyName->value + "\" is not defined");
  }
  if (base->type != OBJECT_VALUE_TYPE) {
    throw ImplementationException("baseObject of Reference is neither Null nor an Object");
  }
  shared_ptr<Object> obj = static_pointer_cast<Object>(base);
  return obj->__Get__(ref.propertyName->value);
}
// TODO: can we ensure that this will never be needed, and remove this?
shared_ptr<Value> GetValue (shared_ptr<Value> value) {
    return value;
}

void PutValue (Reference ref, shared_ptr<Value> value) {
  shared_ptr<Value> base = GetBase(ref);
  if (base->type == NULL_VALUE_TYPE) {
    globalScope.object.__Put__(ref.propertyName->value, value);
    return;
  }
  if (base->type == OBJECT_VALUE_TYPE) {
    static_pointer_cast<Object>(base)->__Put__(ref.propertyName->value, value);
    return;
  }
  throw ImplementationException("baseObject of Reference is neither Null nor an Object");
}
