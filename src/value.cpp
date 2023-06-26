#include "value.h"

#include "exception.h"
#include "type_conversion.h"

using namespace std;

Value::Value () {}

shared_ptr<Value> operator ->* (shared_ptr<Value> value, string name) {
  return ToObject(value)->__Get__(name);
}

shared_ptr<Value> operator + (shared_ptr<Value> valueA, shared_ptr<Value> valueB) {
  shared_ptr<Primitive> primitiveA = ToPrimitive(valueA, NONE_HINT_VALUE_TYPE);
  shared_ptr<Primitive> primitiveB = ToPrimitive(valueB, NONE_HINT_VALUE_TYPE);
  if ( primitiveA->type == STRING_VALUE_TYPE || primitiveB->type == STRING_VALUE_TYPE ) {
    shared_ptr<String> stringA = static_pointer_cast<String>(primitiveA);
    shared_ptr<String> stringB = static_pointer_cast<String>(primitiveB);
    return make_shared<String>(stringA->value + stringB->value);
  } else {
    shared_ptr<Number> numberA = ToNumber(primitiveA);
    shared_ptr<Number> numberB = ToNumber(primitiveB);
    return numberA->plus(numberB);
  }
}

shared_ptr<Value> operator - (shared_ptr<Value> valueA, shared_ptr<Value> valueB) {
  shared_ptr<Number> a = ToNumber(valueA);
  shared_ptr<Number> b = ToNumber(valueB);
  return a->minus(b);
}

Primitive::Primitive () : Value() {}

Undefined::Undefined () : Primitive() {
  this->type = UNDEFINED_VALUE_TYPE;
}

Null::Null () : Primitive() {
  this->type = NULL_VALUE_TYPE;
}

Boolean::Boolean (bool value) : Primitive() {
  this->type = BOOLEAN_VALUE_TYPE;
  this->value = value;
}

Number::Number (double value, bool isNegative) : Primitive() {
  this->type = NUMBER_VALUE_TYPE;
  this->value = value;
  this->isNaN = false;
  this->isInfinity = false;
  this->isNegative = isNegative;
}

shared_ptr<Number> Number::makeNaN () {
  shared_ptr<Number> num = make_shared<Number>();
  num->isNaN = true;
  return num;
}

shared_ptr<Number> Number::makeInfinity (bool isNegative) {
  shared_ptr<Number> num = make_shared<Number>(0, isNegative);
  num->isInfinity = true;
  return num;
}

shared_ptr<Number> Number::plus (shared_ptr<Number> b) {
  Number* a = this;
  if (a->isNaN || b->isNaN) {
    return Number::makeNaN();
  }
  if (a->isInfinity) {
    if (b->isInfinity) {
      if (a->isNegative == b->isNegative) {
        return Number::makeInfinity(a->isNegative);
      }
      return Number::makeNaN();
    }
    return Number::makeInfinity(a->isNegative);
  }
  if (b->isInfinity) {
    return Number::makeInfinity(b->isNegative);
  }
  if (a->value == 0) {
    if (b->value == 0) {
      if (a->isNegative && b->isNegative) {
        return make_shared<Number>(0, true);
      }
      return make_shared<Number>(0, false);
    }
  }
  return make_shared<Number>(a->value + b->value);
}

shared_ptr<Number> Number::minus (shared_ptr<Number> b) {
  Number* a = this;
  shared_ptr<Number> negativeB;
  if (b->isNaN) {
    negativeB = Number::makeNaN();
  }
  else if (b->isInfinity) {
    negativeB = Number::makeInfinity(!b->isNegative);
  }
  else if (b->value == 0) {
    negativeB = make_shared<Number>(b->value, !b->isNegative);
  }
  else {
    negativeB = make_shared<Number>(-b->value);
  }
  return a->plus(negativeB);
}

String::String (string value) : Primitive() {
  this->type = STRING_VALUE_TYPE;
  this->value = value;
}

Object::Object (shared_ptr<Object> prototype, Call call, Construct construct) : Value() {
  this->type = OBJECT_VALUE_TYPE;
  this->__Prototype__ = prototype;
  this->__Call__ = call;
  this->__Construct__ = construct;
};

shared_ptr<Value> Object::__Get__ (string key) {
  try {
    return this->properties.at(key)->value;
  } catch (out_of_range e) {
    if (this->__Prototype__ == nullptr) {
      return make_shared<Undefined>();
    } else {
      return this->__Prototype__->__Get__(key);
    }
  }
}

void Object::__Put__ (string key, shared_ptr<Value> value) {
  shared_ptr<Property> property = make_shared<Property>();
  property->value = value;
  this->properties[key] = property;
}

bool Object::__HasProperty__ (string key) {
  try {
    shared_ptr<Property> p = this->properties.at(key);
    return true;
  } catch (out_of_range e) {
    if (this->__Prototype__ == nullptr) {
      return false;
    } else {
      return this->__Prototype__->__HasProperty__(key);
    }
  }
}
