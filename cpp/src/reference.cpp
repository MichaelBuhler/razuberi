#include "reference.h"

#include <memory>

#include "global_scope.h"
#include "exception.h"
#include "value.h"

using namespace std;

shared_ptr<Value> GetBase (Reference ref) {
  return ref.baseObject;
}
shared_ptr<Value> GetBase (shared_ptr<Value> ref) {
  if (ref->type != REFERENCE_VALUE_TYPE) {
    throw ReferenceError("tried to GetBase on a non-Reference type");
  }
  return static_pointer_cast<Reference>(ref)->baseObject;
}

shared_ptr<String> GetPropertyName (Reference ref) {
  return ref.propertyName;
}
shared_ptr<String> GetPropertyName (shared_ptr<Value> ref) {
  if (ref->type != REFERENCE_VALUE_TYPE) {
    throw ReferenceError("tried to GetPropertyName on a non-Reference type");
  }
  return static_pointer_cast<Reference>(ref)->propertyName;
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
shared_ptr<Value> GetValue (shared_ptr<Value> value) {
  if (value->type != REFERENCE_VALUE_TYPE) {
    return value;
  }
  shared_ptr<Reference> ref = static_pointer_cast<Reference>(value);
  shared_ptr<Value> base = GetBase(ref);
  if (base->type == NULL_VALUE_TYPE) {
    throw ReferenceError("\"" + ref->propertyName->value + "\" is not defined");
  }
  if (base->type != OBJECT_VALUE_TYPE) {
    throw ImplementationException("baseObject of Reference is neither Null nor an Object");
  }
  shared_ptr<Object> obj = static_pointer_cast<Object>(base);
  return obj->__Get__(ref->propertyName->value);
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
void PutValue (shared_ptr<Value> ref, shared_ptr<Value> value) {
  if (ref->type != REFERENCE_VALUE_TYPE) {
    throw ReferenceError("tried to PutValue on a non-Reference type");
  }
  shared_ptr<Reference> p_ref = static_pointer_cast<Reference>(ref);
  shared_ptr<Value> base = GetBase(ref);
  if (base->type != NULL_VALUE_TYPE) {
    if (base->type != OBJECT_VALUE_TYPE) {
      throw ImplementationException("baseObject of Reference is neither Null nor an Object");
    }
    shared_ptr<Object> obj = static_pointer_cast<Object>(base);
    return obj->__Put__(static_pointer_cast<Reference>(ref)->propertyName->value, value);
  }
  // TODO: support setting values on the global object, according to ES1
  throw NotImplementedException("cannot set \"" + static_pointer_cast<Reference>(ref)->propertyName->value + "\" on the global object yet");
}
