#include "type_conversion.h"

#include "exception.h"

// TODO: ToPrimitive() should include a hint
shared_ptr<Primitive> ToPrimitive (shared_ptr<Value> value) {
  switch (value->type) {
    case UNDEFINED_VALUE_TYPE:
    case NULL_VALUE_TYPE:
    case BOOLEAN_VALUE_TYPE:
    case NUMBER_VALUE_TYPE:
    case STRING_VALUE_TYPE:
      return static_pointer_cast<Primitive>(value);
    case OBJECT_VALUE_TYPE:
      throw NotImplementedException("cannot convert an object to a primitive");
    default:
      throw NotImplementedException("don't know how to convert this value to a primitive");
  }
}

shared_ptr<Boolean> ToBoolean (shared_ptr<Value> value) {
  switch (value->type) {
    case UNDEFINED_VALUE_TYPE:
      return make_shared<Boolean>(false);
    case NULL_VALUE_TYPE:
      return make_shared<Boolean>(false);
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(value);
    case NUMBER_VALUE_TYPE:
      // TODO: should more carefully check +0, -0, and NaN
      return make_shared<Boolean>(static_pointer_cast<Number>(value)->value != 0);
    case STRING_VALUE_TYPE:
      return make_shared<Boolean>(static_pointer_cast<String>(value)->value != "");
    case OBJECT_VALUE_TYPE:
      return make_shared<Boolean>(true); 
    default:
      throw NotImplementedException("don't know how to convert this value to a boolean");
  }
}

shared_ptr<Number> ToNumber (shared_ptr<Value> value) {
  switch (value->type) {
    case UNDEFINED_VALUE_TYPE:
      // TODO: should be NaN
      return make_shared<Number>(0);
    case NULL_VALUE_TYPE:
      // TODO: should be +0
      return make_shared<Number>(0);
    case BOOLEAN_VALUE_TYPE:
      // TODO: false should be +0
      return static_pointer_cast<Boolean>(value)->value ? make_shared<Number>(1) : make_shared<Number>(0);
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(value);
    case STRING_VALUE_TYPE:
      throw NotImplementedException("cannot convert a string to a number");
    case OBJECT_VALUE_TYPE:
      // TODO: ToPrimitive() should include a hint
      return ToNumber(ToPrimitive(value));
    default:
      throw NotImplementedException("don't know how to convert this value to a number");
  }
}

shared_ptr<String> ToString (shared_ptr<Value> value) {
  switch (value->type) {
    case UNDEFINED_VALUE_TYPE:
      return make_shared<String>("undefined");
    case NULL_VALUE_TYPE:
      return make_shared<String>("null");
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(value)->value ? make_shared<String>("true") : make_shared<String>("false");
    case NUMBER_VALUE_TYPE:
      // TOOD: needs to be much more robust here
      return make_shared<String>(to_string(static_pointer_cast<Number>(value)->value));
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(value);
    case OBJECT_VALUE_TYPE:
      throw NotImplementedException("cannot convert an object to a string");
    default:
      throw NotImplementedException("don't know how to convert this value to a string");
  }
}

shared_ptr<Object> ToObject (shared_ptr<Value> value) {
  switch (value->type) {
    case UNDEFINED_VALUE_TYPE:
      throw TypeError("cannot convert undefined to object");
    case NULL_VALUE_TYPE:
      throw TypeError("cannot convert null to object");
    case BOOLEAN_VALUE_TYPE:
      throw NotImplementedException("cannot convert a boolean to an object");
    case NUMBER_VALUE_TYPE:
      throw NotImplementedException("cannot convert a number to an object");
    case STRING_VALUE_TYPE:
      throw NotImplementedException("cannot convert a value to an object");
    case OBJECT_VALUE_TYPE:
      return static_pointer_cast<Object>(value);
    default:
      throw NotImplementedException("don't know how to convert this value to an object");
  }
}
