#include "value.h"

#include "exception.h"
#include "reference.h"
#include "type_conversion.h"

using namespace std;

Value::Value () {}

shared_ptr<Object> Value::construct (vector<shared_ptr<Value> > params) {
    throw TypeError("constructor is not an object");
}

shared_ptr<Value> Value::call () {
  throw TypeError("callee is not an object");
}
shared_ptr<Value> Value::call (Reference firstParam) {
  throw TypeError("callee is not an object");
}
shared_ptr<Value> Value::call (shared_ptr<Value> firstParam) {
  throw TypeError("callee is not an object");
}
shared_ptr<Value> Value::call (vector<shared_ptr<Value> > params) {
  throw TypeError("callee is not an object");
}
shared_ptr<Value> Value::call (shared_ptr<Value> _this, vector<shared_ptr<Value> > params) {
  throw TypeError("callee is not an object");
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

Object::Object (shared_ptr<Object> __Prototype__) : Value() {
  this->type = OBJECT_VALUE_TYPE;
  this->__Prototype__ = __Prototype__;
  this->__Class__ = "Object"; // TODO: enum this
  this->__Construct__ = nullptr;
  this->__Call__ = nullptr;
}

std::shared_ptr<Object> Object::Object_prototype;
std::shared_ptr<Object> Object::Function_prototype;
std::shared_ptr<Object> Object::String_prototype;
std::shared_ptr<Object> Object::Boolean_prototype;

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

shared_ptr<Object> Object::construct (vector<shared_ptr<Value> > params) {
  if (this->__Construct__ == nullptr) {
    throw TypeError("object is not a constructor");
  }
  shared_ptr<Object> prototype;
  if (this->__HasProperty__("prototype")) {
    shared_ptr<Value> maybeObj = this->__Get__("prototype");
    if (maybeObj->type == OBJECT_VALUE_TYPE) {
      prototype = static_pointer_cast<Object>(maybeObj);
    } else {
      prototype = Object_prototype;
    }
  } else {
    throw ImplementationException("constructor has no prototype");
  }
  shared_ptr<Object> newObject = make_shared<Object>(prototype);
  shared_ptr<Value> result = this->__Construct__(this->closure, newObject, params);
  if (result->type != OBJECT_VALUE_TYPE) {
    // ES1: 11.2.2(6): If Type(result) is not Object, generate a runtime error.
    // But I have observed in the Chrome JavaScript console that this is not an error.
    throw TypeError("constructor returned a non-object");
  }
  return static_pointer_cast<Object>(result);
}

shared_ptr<Value> Object::call () {
  return this->call(vector<shared_ptr<Value> >());
}
shared_ptr<Value> Object::call (Reference firstParam) {
  vector<shared_ptr<Value> > params;
  params.push_back(GetValue(firstParam));
  return this->call(params);
}
shared_ptr<Value> Object::call (shared_ptr<Value> firstParam) {
  vector<shared_ptr<Value> > params;
  params.push_back(firstParam);
  return this->call(params);
}
shared_ptr<Value> Object::call (vector<shared_ptr<Value> > params) {
  shared_ptr<Value> _this = make_shared<Null>();
  return this->call(_this, params);
}
shared_ptr<Value> Object::call (shared_ptr<Value> _this, vector<shared_ptr<Value> > params) {
  if (this->__Call__ == nullptr) {
    throw TypeError("object is not a function");
  }
  shared_ptr<Scope> scope = this->closure;
  return this->__Call__(scope, _this, params);
}

Reference::Reference (shared_ptr<Value> baseObject, shared_ptr<String> propertyName) {
  this->baseObject = baseObject;
  this->propertyName = propertyName;
}

shared_ptr<Value> Reference::call () {
  return this->call(vector<shared_ptr<Value> >());
}
shared_ptr<Value> Reference::call (Reference firstParam) {
  vector<shared_ptr<Value> > params;
  params.push_back(GetValue(firstParam));
  return this->call(params);
}
shared_ptr<Value> Reference::call (shared_ptr<Value> firstParam) {
  vector<shared_ptr<Value> > params;
  params.push_back(firstParam);
  return this->call(params);
}
shared_ptr<Value> Reference::call (vector<shared_ptr<Value> > params) {
  shared_ptr<Value> value = GetValue(*this);
  shared_ptr<Value> base = GetBase(*this);
  return value->call(base, params);
}

Reference Reference::operator = (Reference rightHandSide) {
  PutValue(*this, GetValue(rightHandSide));
  return *this;
}

Reference Reference::operator = (shared_ptr<Value> rightHandSide) {
  PutValue(*this, rightHandSide);
  return *this;
}

Reference Reference::operator ->* (string identifier) {
  return Reference(ToObject(GetValue(*this)), make_shared<String>(identifier));
}

// TODO: fun for later
// shared_ptr<Value> Reference::operator () () {
//   return (*this)(vector<shared_ptr<Value> >());
// }
// shared_ptr<Value> Reference::operator () (Reference firstParam) {
//   vector<shared_ptr<Value> > params;
//   params.push_back(GetValue(firstParam));
//   return (*this)(params);
// }
// shared_ptr<Value> Reference::operator () (shared_ptr<Value> firstParam) {
//   vector<shared_ptr<Value> > params;
//   params.push_back(firstParam);
//   return (*this)(params);
// }
// shared_ptr<Value> Reference::operator () (vector<shared_ptr<Value> > params) {
//   shared_ptr<Value> value = GetValue(*this);
//   shared_ptr<Value> base = GetBase(*this);
//   return value->call(base, params);
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operator overloads

////////////////////////////////////////////////////////////////////////////////
// Pointer-to-member operator overloads for member expressions

// Accessing a property by `Identifier`
Reference operator ->* (shared_ptr<Value> val, string indentifier) {
  return ToObject(val)->*indentifier;
}
Reference operator ->* (shared_ptr<Object> obj, string indentifier) {
  return Reference(obj, make_shared<String>(indentifier));
}

// End pointer-to-member operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Comma operator overloads for arguments lists

// create a `vector`/`List` from two arguments
vector<shared_ptr<Value> > operator , (Reference a, Reference b) {
  vector<shared_ptr<Value> > vec;
  vec.push_back(GetValue(a));
  vec.push_back(GetValue(b));
  return vec;
}
vector<shared_ptr<Value> > operator , (Reference r, shared_ptr<Value> v) {
  vector<shared_ptr<Value> > vec;
  vec.push_back(GetValue(r));
  vec.push_back(v);
  return vec;
}
vector<shared_ptr<Value> > operator , (shared_ptr<Value> v, Reference r) {
  vector<shared_ptr<Value> > vec;
  vec.push_back(v);
  vec.push_back(GetValue(r));
  return vec;
}
vector<shared_ptr<Value> > operator , (shared_ptr<Value> a, shared_ptr<Value> b) {
  vector<shared_ptr<Value> > vec;
  vec.push_back(a);
  vec.push_back(b);
  return vec;
}

// append another argument onto a `vector`/`List`
vector<shared_ptr<Value> > operator , (vector<shared_ptr<Value> > v, Reference ref) {
  v.push_back(GetValue(ref));
  return v;
}
vector<shared_ptr<Value> > operator , (vector<shared_ptr<Value> > v, shared_ptr<Value> val) {
  v.push_back(val);
  return v;
}

// End comma operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Addition operator overloads for every combination of addition operands

////////////////////////////////////////
// Left operands of type `Reference`
shared_ptr<Value> operator + (Reference a, Reference b) {
  return ToPrimitive(GetValue(a)) + ToPrimitive(GetValue(b));
}
shared_ptr<Value> operator + (Reference r, shared_ptr<Value> v) {
  return ToPrimitive(GetValue(r)) + ToPrimitive(v);
}
shared_ptr<Value> operator + (Reference r, shared_ptr<Object> o) {
  return ToPrimitive(GetValue(r)) + ToPrimitive(o);
}
shared_ptr<Value> operator + (Reference r, shared_ptr<Primitive> p) {
  return ToPrimitive(GetValue(r)) + p;
}
shared_ptr<Value> operator + (Reference r, shared_ptr<Undefined> u) {
  return ToPrimitive(GetValue(r)) + u;
}
shared_ptr<Value> operator + (Reference r, shared_ptr<Null> n) {
  return ToPrimitive(GetValue(r)) + n;
}
shared_ptr<Value> operator + (Reference r, shared_ptr<Boolean> b) {
  return ToPrimitive(GetValue(r)) + b;
}
shared_ptr<Value> operator + (Reference r, shared_ptr<Number> n) {
  return ToPrimitive(GetValue(r)) + n;
}
shared_ptr<Value> operator + (Reference r, shared_ptr<String> s) {
  return ToPrimitive(GetValue(r)) + s;
}

////////////////////////////////////////
// Left operands of type `Value`
shared_ptr<Value> operator + (shared_ptr<Value> v, Reference r) {
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
shared_ptr<Value> operator + (shared_ptr<Object> o, Reference r) {
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
shared_ptr<Value> operator + (shared_ptr<Primitive> p, Reference r) {
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
shared_ptr<Value> operator + (shared_ptr<Undefined> u, Reference r) {
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
shared_ptr<Value> operator + (shared_ptr<Null> n, Reference r) {
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
shared_ptr<Value> operator + (shared_ptr<Boolean> b, Reference r) {
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
shared_ptr<Value> operator + (shared_ptr<Number> n, Reference r) {
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
shared_ptr<String> operator + (shared_ptr<String>s , Reference r) {
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
