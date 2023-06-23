#include "value.h"

#include "exception.h"
#include "type_conversion.h"

using namespace std;

Value::Value () {}

shared_ptr<Value> operator ->* (shared_ptr<Value> value, string name) {
  return ToObject(value)->__Get__(name);
}

shared_ptr<Value> operator + (shared_ptr<Value> valueA, shared_ptr<Value> valueB) {
  shared_ptr<Primitive> primitiveA = ToPrimitive(valueA);
  shared_ptr<Primitive> primitiveB = ToPrimitive(valueB);
  if ( primitiveA->type == STRING_VALUE_TYPE || primitiveB->type == STRING_VALUE_TYPE ) {
    shared_ptr<String> stringA = static_pointer_cast<String>(primitiveA);
    shared_ptr<String> stringB = static_pointer_cast<String>(primitiveB);
    return make_shared<String>(stringA->value + stringB->value);
  } else {
    shared_ptr<Number> numberA = ToNumber(primitiveA);
    shared_ptr<Number> numberB = ToNumber(primitiveB);
    return make_shared<Number>(numberA->value + numberB->value);
  }
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

Number::Number (double value) : Primitive() {
  this->type = NUMBER_VALUE_TYPE;
  this->value = value;
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
