#include "value.h"

#include "exception.h"
#include "type_conversion.h"

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

Object::Object (shared_ptr<Object> prototype) : Value() {
  this->type = OBJECT_VALUE_TYPE;
  this->__Prototype__ = prototype;
  this->fn = nullptr;
};

Object::Object (shared_ptr<Object> prototype, shared_ptr<Value> (*fn)(shared_ptr<Scope>, vector<shared_ptr<Value> >)) : Value() {
  this->type = OBJECT_VALUE_TYPE;
  this->__Prototype__ = prototype;
  this->fn = fn;
};

shared_ptr<Value> Object::__Get__ (string name) {
  try {
    return this->properties.at(name)->value;
  } catch (out_of_range e) {
    if (this->__Prototype__ == nullptr) {
      return make_shared<Undefined>();
    } else {
      return this->__Prototype__->__Get__(name);
    }
  }
}

void Object::__Put__ (string key, shared_ptr<Value> value) {
  shared_ptr<Property> property = make_shared<Property>();
  property->value = value;
  this->properties[key] = property;
}

shared_ptr<Value> Object::__Call__ (shared_ptr<Object> thisArg, shared_ptr<Scope> callingScope, vector<shared_ptr<Value> > params) {
  if (this->fn == nullptr) {
    throw TypeError("not a function");
  }
  shared_ptr<Scope> scope = make_shared<Scope>(callingScope);
  scope->set("this", thisArg);
  return this->fn(scope, params);
}
