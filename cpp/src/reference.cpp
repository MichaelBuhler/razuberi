#include "reference.h"

#include <memory>

#include "exception.h"
#include "value.h"

using namespace std;

shared_ptr<Value> GetBase (shared_ptr<Value> reference) {
  if (reference->type != REFERENCE_VALUE_TYPE) {
    throw ReferenceError("tried to GetBase on a non-Reference type");
  }
  shared_ptr<Reference> ref = static_pointer_cast<Reference>(reference);
  return ref->baseObject;
}

shared_ptr<String> GetPropertyName (shared_ptr<Value> reference) {
  if (reference->type != REFERENCE_VALUE_TYPE) {
    throw ReferenceError("tried to GetPropertyName on a non-Reference type");
  }
  shared_ptr<Reference> ref = static_pointer_cast<Reference>(reference);
  return ref->propertyName;
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

void PutValue (shared_ptr<Value> reference, shared_ptr<Value> value) {
  if (reference->type != REFERENCE_VALUE_TYPE) {
    throw ReferenceError("tried to GetPropertyName on a non-Reference type");
  }
  shared_ptr<Reference> ref = static_pointer_cast<Reference>(value);
  shared_ptr<Value> base = GetBase(ref);
  if (base->type != NULL_VALUE_TYPE) {
    if (base->type != OBJECT_VALUE_TYPE) {
      throw ImplementationException("baseObject of Reference is neither Null nor an Object");
    }
    shared_ptr<Object> obj = static_pointer_cast<Object>(base);
    return obj->__Put__(ref->propertyName->value, value);
  }
  // TODO: support setting values on the global object, according to ES1
  throw NotImplementedException("cannot set \"" + ref->propertyName->value + "\" on the global object yet");
}
