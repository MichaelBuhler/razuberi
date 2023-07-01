#include "value.h"

#include "exception.h"
#include "reference.h"
#include "type_conversion.h"

using namespace std;

Value::Value () {}

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
}

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

Internal::Internal () : Value() {}

Reference::Reference (shared_ptr<Value> baseObject, shared_ptr<String> propertyName) : Internal() {
  this->type = REFERENCE_VALUE_TYPE;
  this->baseObject = baseObject;
  this->propertyName = propertyName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operator overloads

////////////////////////////////////////////////////////////////////////////////
// Pointer-to-member operator overloads for member expressions

// Accessing a property by `Identifier`
shared_ptr<Reference> operator ->* (shared_ptr<Reference> ref, string name) {
  return GetValue(ref)->*name;
}
shared_ptr<Reference> operator ->* (shared_ptr<Value> value, string name) {
  return make_shared<Reference>(ToObject(value), make_shared<String>(name));
}
shared_ptr<Reference> operator ->* (shared_ptr<Object> obj, string name) {
  return make_shared<Reference>(obj, make_shared<String>(name));
}

// End pointer-to-member operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Addition operator overloads for every combination of addition operands

////////////////////////////////////////
// Left operands of type `Reference`
shared_ptr<Value> operator + (shared_ptr<Reference> a, shared_ptr<Reference> b) {
  return ToPrimitive(GetValue(a)) + ToPrimitive(GetValue(b));
}
shared_ptr<Value> operator + (shared_ptr<Reference> r, shared_ptr<Value> v) {
  return ToPrimitive(GetValue(r)) + ToPrimitive(v);
}
shared_ptr<Value> operator + (shared_ptr<Reference> r, shared_ptr<Object> o) {
  return ToPrimitive(GetValue(r)) + ToPrimitive(o);
}
shared_ptr<Value> operator + (shared_ptr<Reference> r, shared_ptr<Primitive> p) {
  return ToPrimitive(GetValue(r)) + p;
}
shared_ptr<Value> operator + (shared_ptr<Reference> r, shared_ptr<Undefined> u) {
  return ToPrimitive(GetValue(r)) + u;
}
shared_ptr<Value> operator + (shared_ptr<Reference> r, shared_ptr<Null> n) {
  return ToPrimitive(GetValue(r)) + n;
}
shared_ptr<Value> operator + (shared_ptr<Reference> r, shared_ptr<Boolean> b) {
  return ToPrimitive(GetValue(r)) + b;
}
shared_ptr<Value> operator + (shared_ptr<Reference> r, shared_ptr<Number> n) {
  return ToPrimitive(GetValue(r)) + n;
}
shared_ptr<Value> operator + (shared_ptr<Reference> r, shared_ptr<String> s) {
  return ToPrimitive(GetValue(r)) + s;
}

////////////////////////////////////////
// Left operands of type `Value`
shared_ptr<Value> operator + (shared_ptr<Value> v, shared_ptr<Reference> r) {
  return ToPrimitive(v) + ToPrimitive(GetValue(r));
}
shared_ptr<Value> operator + (shared_ptr<Value> a, shared_ptr<Value> b) {
  return ToPrimitive(a) + ToPrimitive(b);
}
shared_ptr<Value> operator + (shared_ptr<Value> v, shared_ptr<Object> o) {
  return ToPrimitive(v) + ToPrimitive(o);
}
shared_ptr<Value> operator + (shared_ptr<Value> v, shared_ptr<Primitive> p) {
  return ToPrimitive(v) + p;
}
shared_ptr<Value> operator + (shared_ptr<Value> v, shared_ptr<Undefined> u) {
  return ToPrimitive(v) + u;
}
shared_ptr<Value> operator + (shared_ptr<Value> v, shared_ptr<Null> n) {
  return ToPrimitive(v) + n;
}
shared_ptr<Value> operator + (shared_ptr<Value> v, shared_ptr<Boolean> b) {
  return ToPrimitive(v) + b;
}
shared_ptr<Value> operator + (shared_ptr<Value> v, shared_ptr<Number> n) {
  return ToPrimitive(v) + n;
}
shared_ptr<String> operator + (shared_ptr<Value> v, shared_ptr<String> s) {
  return ToPrimitive(v) + s;
}

////////////////////////////////////////
// Left operands of type `Object`
shared_ptr<Value> operator + (shared_ptr<Object> o, shared_ptr<Reference> r) {
  return ToPrimitive(o) + ToPrimitive(GetValue(r));
}
shared_ptr<Value> operator + (shared_ptr<Object> o, shared_ptr<Value> v) {
  return ToPrimitive(o) + ToPrimitive(v);
}
shared_ptr<Value> operator + (shared_ptr<Object> a, shared_ptr<Object> b) {
  return ToPrimitive(a) + ToPrimitive(b);
}
shared_ptr<Value> operator + (shared_ptr<Object> o, shared_ptr<Primitive> p) {
  return ToPrimitive(o) + p;
}
shared_ptr<Value> operator + (shared_ptr<Object> o, shared_ptr<Undefined> u) {
  return ToPrimitive(o) + u;
}
shared_ptr<Value> operator + (shared_ptr<Object> o, shared_ptr<Null> n) {
  return ToPrimitive(o) + n;
}
shared_ptr<Value> operator + (shared_ptr<Object> o, shared_ptr<Boolean> b) {
  return ToPrimitive(o) + b;
}
shared_ptr<Value> operator + (shared_ptr<Object> o, shared_ptr<Number> n) {
  return ToPrimitive(o) + n;
}
shared_ptr<String> operator + (shared_ptr<Object> o, shared_ptr<String> s) {
  return ToPrimitive(o) + s;
}

////////////////////////////////////////
// Left operands of type `Primitive`
shared_ptr<Value> operator + (shared_ptr<Primitive> p, shared_ptr<Reference> r) {
  return p + ToPrimitive(GetValue(r));
}
shared_ptr<Value> operator + (shared_ptr<Primitive> p, shared_ptr<Value> v) {
  return p + ToPrimitive(v);
}
shared_ptr<Value> operator + (shared_ptr<Primitive> p, shared_ptr<Object> o) {
  return p + ToPrimitive(o);
}
shared_ptr<Value> operator + (shared_ptr<Primitive> a, shared_ptr<Primitive> b) {
  if (a->type == STRING_VALUE_TYPE) {
    if (b->type == STRING_VALUE_TYPE) {
      return static_pointer_cast<String>(a) + static_pointer_cast<String>(b);
    } else {
      return static_pointer_cast<String>(a) + ToString(b);
    }
  } else if (b->type == STRING_VALUE_TYPE) {
    return ToString(a) + static_pointer_cast<String>(b);
  } else {
    return ToNumber(a) + ToNumber(b);
  }
}
shared_ptr<Value> operator + (shared_ptr<Primitive> p, shared_ptr<Undefined> u) {
  if (p->type == STRING_VALUE_TYPE) {
    return static_pointer_cast<String>(p) + make_shared<String>("undefined");
  } else {
    return Number::makeNaN();
  }
}
shared_ptr<Value> operator + (shared_ptr<Primitive> p, shared_ptr<Null> n) {
  if (p->type == STRING_VALUE_TYPE) {
    return static_pointer_cast<String>(p) + make_shared<String>("null");
  } else {
    return ToNumber(p);
  }
}
shared_ptr<Value> operator + (shared_ptr<Primitive> p, shared_ptr<Boolean> b) {
  if (p->type == STRING_VALUE_TYPE) {
    return static_pointer_cast<String>(p) + ToString(b);
  } else {
    return ToNumber(p) + ToNumber(b);
  }
}
shared_ptr<Value> operator + (shared_ptr<Primitive> p, shared_ptr<Number> n) {
  if (p->type == STRING_VALUE_TYPE) {
    return static_pointer_cast<String>(p) + ToString(n);
  } else {
    return ToNumber(p) + n;
  }
}
shared_ptr<String> operator + (shared_ptr<Primitive> p, shared_ptr<String> s) {
  if (p->type == STRING_VALUE_TYPE) {
    return static_pointer_cast<String>(p) + s;
  } else {
    return ToString(p) + s;
  }
}

////////////////////////////////////////
// Left operands of type `Undefined`
shared_ptr<Value> operator + (shared_ptr<Undefined> u, shared_ptr<Reference> r) {
  return u + ToPrimitive(GetValue(r));
}
shared_ptr<Value> operator + (shared_ptr<Undefined> u, shared_ptr<Value> v) {
  return u + ToPrimitive(v);
}
shared_ptr<Value> operator + (shared_ptr<Undefined> u, shared_ptr<Object> o) {
  return u + ToPrimitive(o);
}
shared_ptr<Value> operator + (shared_ptr<Undefined> u, shared_ptr<Primitive> p) {
  if (p->type == STRING_VALUE_TYPE) {
    return make_shared<String>("undefined") + static_pointer_cast<String>(p);
  } else {
    return Number::makeNaN();
  }
}
shared_ptr<Number> operator + (shared_ptr<Undefined> a, shared_ptr<Undefined> b) {
  return Number::makeNaN();
}
shared_ptr<Number> operator + (shared_ptr<Undefined> u, shared_ptr<Null> n) {
  return Number::makeNaN();
}
shared_ptr<Number> operator + (shared_ptr<Undefined> u, shared_ptr<Boolean> b) {
  return Number::makeNaN();
}
shared_ptr<Number> operator + (shared_ptr<Undefined> u, shared_ptr<Number> n)  {
  return Number::makeNaN();
}
shared_ptr<String> operator + (shared_ptr<Undefined> u, shared_ptr<String> s)  {
  return make_shared<String>("undefined") + s;
}

////////////////////////////////////////
// Left operands of type `Null`
shared_ptr<Value> operator + (shared_ptr<Null> n, shared_ptr<Reference> r) {
  return n + ToPrimitive(GetValue(r));
}
shared_ptr<Value> operator + (shared_ptr<Null> n, shared_ptr<Value> v) {
  return n + ToPrimitive(v);
}
shared_ptr<Value> operator + (shared_ptr<Null> n, shared_ptr<Object> o) {
  return n + ToPrimitive(o);
}
shared_ptr<Value> operator + (shared_ptr<Null> n, shared_ptr<Primitive> p) {
  if (p->type == STRING_VALUE_TYPE) {
    return make_shared<String>("null") + static_pointer_cast<String>(p);
  } else {
    return ToNumber(p);
  }
}
shared_ptr<Number> operator + (shared_ptr<Null> n, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator + (shared_ptr<Null> a, shared_ptr<Null> b) {
  return make_shared<Number>(0, false);
}
shared_ptr<Number> operator + (shared_ptr<Null> n, shared_ptr<Boolean> b) {
  return ToNumber(b);
}
shared_ptr<Number> operator + (shared_ptr<Null> n, shared_ptr<Number> x) {
  return x;
}
shared_ptr<String> operator + (shared_ptr<Null> n, shared_ptr<String> s) {
  return make_shared<String>("null") + s;
}

////////////////////////////////////////
// Left operands of type `Boolean`
shared_ptr<Value> operator + (shared_ptr<Boolean> b, shared_ptr<Reference> r) {
  return b + ToPrimitive(GetValue(r));
}
shared_ptr<Value> operator + (shared_ptr<Boolean> b, shared_ptr<Value> v) {
  return b + ToPrimitive(v);
}
shared_ptr<Value> operator + (shared_ptr<Boolean> b, shared_ptr<Object> o) {
  return b + ToPrimitive(o);
}
shared_ptr<Value> operator + (shared_ptr<Boolean> b, shared_ptr<Primitive> p) {
  if (p->type == STRING_VALUE_TYPE) {
    return ToString(b) + static_pointer_cast<String>(p);
  } else {
    return ToNumber(p) + ToNumber(b);
  }
}
shared_ptr<Number> operator + (shared_ptr<Boolean> b, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator + (shared_ptr<Boolean> b, shared_ptr<Null> n) {
  return ToNumber(b);
}
shared_ptr<Number> operator + (shared_ptr<Boolean> a, shared_ptr<Boolean> b) {
  return ToNumber(a) + ToNumber(b);
}
shared_ptr<Number> operator + (shared_ptr<Boolean> b, shared_ptr<Number> n) {
  return ToNumber(b) + n;
}
shared_ptr<String> operator + (shared_ptr<Boolean> b, shared_ptr<String> s) {
  return ToString(b) + s;
}

////////////////////////////////////////
// Left operands of type `Number`
shared_ptr<Value> operator + (shared_ptr<Number> n, shared_ptr<Reference> r) {
  return n + ToPrimitive(GetValue(r));
}
shared_ptr<Value> operator + (shared_ptr<Number> n, shared_ptr<Value> v) {
  return n + ToPrimitive(v);
}
shared_ptr<Value> operator + (shared_ptr<Number> n, shared_ptr<Object> o) {
  return n + ToPrimitive(o);
}
shared_ptr<Value> operator + (shared_ptr<Number> n, shared_ptr<Primitive> p) {
  if (p->type == STRING_VALUE_TYPE) {
    return ToString(n) + static_pointer_cast<String>(p);
  } else {
    return n + ToNumber(p);
  }
}
shared_ptr<Number> operator + (shared_ptr<Number> n, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator + (shared_ptr<Number> n, shared_ptr<Null> x) {
  return n;
}
shared_ptr<Number> operator + (shared_ptr<Number> n, shared_ptr<Boolean> b) {
  return n + ToNumber(b);
}
shared_ptr<Number> operator + (shared_ptr<Number> a, shared_ptr<Number> b) {
  // TODO: inline Number::plus here?
  return a->plus(b);
};
shared_ptr<String> operator + (shared_ptr<Number> n, shared_ptr<String> s) {
  return ToString(n) + s;
}

////////////////////////////////////////
// Left operands of type `String`
shared_ptr<String> operator + (shared_ptr<String>s , shared_ptr<Reference> r) {
  return s + ToString(ToPrimitive(GetValue(r)));
}
shared_ptr<String> operator + (shared_ptr<String>s , shared_ptr<Value> v) {
  return s + ToString(ToPrimitive(v));
}
shared_ptr<String> operator + (shared_ptr<String>s , shared_ptr<Object> o) {
  return s + ToString(ToPrimitive(o));
}
shared_ptr<String> operator + (shared_ptr<String>s , shared_ptr<Primitive> p) {
  return s + ToString(p);
}
shared_ptr<String> operator + (shared_ptr<String>s , shared_ptr<Undefined> u) {
  return s + make_shared<String>("undefined");
}
shared_ptr<String> operator + (shared_ptr<String>s , shared_ptr<Null> n) {
  return s + make_shared<String>("null");
}
shared_ptr<String> operator + (shared_ptr<String>s , shared_ptr<Boolean> b) {
  return s + ToString(b);
}
shared_ptr<String> operator + (shared_ptr<String>s , shared_ptr<Number> n) {
  return s + ToString(n);
}
shared_ptr<String> operator + (shared_ptr<String> a, shared_ptr<String> b) {
  return make_shared<String>(a->value + b->value);
}

// End addition operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Subtraction operator overloads for every combination of subtraction operands

shared_ptr<Value> operator - (shared_ptr<Value> valueA, shared_ptr<Value> valueB) {
  shared_ptr<Number> a = ToNumber(valueA);
  shared_ptr<Number> b = ToNumber(valueB);
  return a->minus(b);
}

// End subtraction operator overloads
////////////////////////////////////////////////////////////////////////////////

// End operator overloads
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
