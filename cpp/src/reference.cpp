#include "reference.h"

#include <memory>

#include "global_scope.h"
#include "internal.h"
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
    throw _newThrowable(get_global_scope()->*"ReferenceError", make_shared<String>("\"" + ref.propertyName->value + "\" is not defined"));
  }
  if (base->type != OBJECT_VALUE_TYPE) {
    throw ImplementationException("baseObject of Reference is neither Null nor an Object");
  }
  shared_ptr<Object> obj = static_pointer_cast<Object>(base);
  return obj->__Get__(ref.propertyName->value);
}

void PutValue (Reference ref, shared_ptr<Value> value) {
  shared_ptr<Value> base = GetBase(ref);
  if (base->type == NULL_VALUE_TYPE) {
    get_global_scope()->object->__Put__(ref.propertyName->value, value);
    return;
  }
  if (base->type == OBJECT_VALUE_TYPE) {
    static_pointer_cast<Object>(base)->__Put__(ref.propertyName->value, value);
    return;
  }
  throw ImplementationException("baseObject of Reference is neither Null nor an Object");
}
