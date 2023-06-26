#include "type_conversion.h"

#include <math.h>

#include "exception.h"
#include "internal.h"

using namespace std;

shared_ptr<Primitive> ToPrimitive (shared_ptr<Value> value, HintValueType hint) {
  switch (value->type) {
    case UNDEFINED_VALUE_TYPE:
    case NULL_VALUE_TYPE:
    case BOOLEAN_VALUE_TYPE:
    case NUMBER_VALUE_TYPE:
    case STRING_VALUE_TYPE:
      return static_pointer_cast<Primitive>(value);
    case OBJECT_VALUE_TYPE:
      shared_ptr<Object> obj = static_pointer_cast<Object>(value);
      shared_ptr<Value> result = __DefaultValue__(obj, hint);
      // TODO: result may be a Reference value type?
      if (result->type == OBJECT_VALUE_TYPE) {
        throw TypeError("[[DefaultValue]] returned an object");
      }
      return static_pointer_cast<Primitive>(result);
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
    case NUMBER_VALUE_TYPE: {
      shared_ptr<Number> num = static_pointer_cast<Number>(value);
      if (num->isNaN) return make_shared<Boolean>(false);
      if (num->isInfinity) return make_shared<Boolean>(true);
      if (num->value == 0) return make_shared<Boolean>(false);
      return make_shared<Boolean>(true);
    }
    case STRING_VALUE_TYPE:
      if (static_pointer_cast<String>(value)->value == "") {
        return make_shared<Boolean>(false);
      } else {
        return make_shared<Boolean>(true);
      }
    case OBJECT_VALUE_TYPE:
      return make_shared<Boolean>(true); 
  }
}

shared_ptr<Number> ToNumber (shared_ptr<Value> value) {
  switch (value->type) {
    case UNDEFINED_VALUE_TYPE:
      return Number::makeNaN();
    case NULL_VALUE_TYPE:
      return make_shared<Number>(0, false);
    case BOOLEAN_VALUE_TYPE:
      if (static_pointer_cast<Boolean>(value)->value) {
        return make_shared<Number>(1);
      } else {
        return make_shared<Number>(0, false);
      }
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(value);
    case STRING_VALUE_TYPE:
      // TODO: need to parse a floating point number from this string
      throw NotImplementedException("cannot convert a string to a number");
    case OBJECT_VALUE_TYPE:
      return ToNumber(ToPrimitive(value, NUMBER_HINT_VALUE_TYPE));
  }
}

shared_ptr<Number> ToInteger (shared_ptr<Value> value) {
  shared_ptr<Number> num = ToNumber(value);
  if (num->isNaN) {
    return make_shared<Number>(0, false);
  }
  if (num->isInfinity || num->value == 0) {
    return num;
  }
  double sign = num->value > 0 ? 1 : -1;
  double magnitude = floor(abs(num->value));
  return make_shared<Number>(sign * magnitude);
}

std::shared_ptr<Number> ToInt32 (std::shared_ptr<Value> value) {
  shared_ptr<Number> num = ToNumber(value);
  if (num->isNaN || num->isInfinity || num->value == 0) {
    return make_shared<Number>(0, false);
  }
  double sign = num->value > 0 ? 1 : -1;
  double magnitude = floor(abs(num->value));
  int32_t x = (uint64_t)(sign * magnitude) % (1<<31); // 1<<31 == 2^32
  if (x >= (1<<30)) { // 1<<30 == 2^31
    return make_shared<Number>(x - (1<<31)); // 1<<31 == 2^32
  }
  return make_shared<Number>(x);
}

std::shared_ptr<Number> ToUint32 (std::shared_ptr<Value> value) {
  shared_ptr<Number> num = ToNumber(value);
  if (num->isNaN || num->isInfinity || num->value == 0) {
    return make_shared<Number>(0, false);
  }
  double sign = num->value > 0 ? 1 : -1;
  double magnitude = floor(abs(num->value));
  uint32_t x = (uint64_t)(sign * magnitude) % (1<<31); // 1<<31 == 2^32
  return make_shared<Number>(x);
}

std::shared_ptr<Number> ToUint16 (std::shared_ptr<Value> value) {
  shared_ptr<Number> num = ToNumber(value);
  if (num->isNaN || num->isInfinity || num->value == 0) {
    return make_shared<Number>(0, false);
  }
  double sign = num->value > 0 ? 1 : -1;
  double magnitude = floor(abs(num->value));
  uint16_t x = (uint64_t)(sign * magnitude) % (1<<15); // 1<<15 == 2^16
  return make_shared<Number>(x);
}

shared_ptr<String> ToString (shared_ptr<Value> value) {
  switch (value->type) {
    case UNDEFINED_VALUE_TYPE:
      return make_shared<String>("undefined");
    case NULL_VALUE_TYPE:
      return make_shared<String>("null");
    case BOOLEAN_VALUE_TYPE:
      if (static_pointer_cast<Boolean>(value)->value) {
        return make_shared<String>("true");
      } else {
        return make_shared<String>("false");
      }
    case NUMBER_VALUE_TYPE: {
      shared_ptr<Number> num = static_pointer_cast<Number>(value);
      if (num->isNaN) {
        return make_shared<String>("NaN");
      }
      if (num->isInfinity) {
        if (num->isNegative) {
          return make_shared<String>("-Infinity");
        } else {
          return make_shared<String>("Infinity");
        }
      }
      if (num->value == 0) {
        return make_shared<String>("0");
      }
      // TODO: needs to be much more robust here, including scientific notation
      return make_shared<String>(to_string(num->value));
    }
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(value);
    case OBJECT_VALUE_TYPE:
      return ToString(ToPrimitive(value, STRING_HINT_VALUE_TYPE));
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
      // TODO: implement this after the `Number` type
      throw NotImplementedException("cannot convert a number to an object");
    case STRING_VALUE_TYPE:
      throw NotImplementedException("cannot convert a string to an object");
    case OBJECT_VALUE_TYPE:
      return static_pointer_cast<Object>(value);
  }
}
