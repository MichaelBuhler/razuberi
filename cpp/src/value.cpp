#include "value.h"

#include <math.h>

#include "exception.h"
#include "global_scope.h"
#include "internal.h"
#include "reference.h"
#include "scope.h"
#include "type_conversion.h"

using namespace std;

Value::Value () {}

shared_ptr<Object> Value::construct (vector<shared_ptr<Value> > params) {
  throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("constructor is not an object"));
}

shared_ptr<Value> Value::call () {
  throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("callee is not an object"));
}
shared_ptr<Value> Value::call (Reference firstParam) {
  throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("callee is not an object"));
}
shared_ptr<Value> Value::call (shared_ptr<Value> firstParam) {
  throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("callee is not an object"));
}
shared_ptr<Value> Value::call (vector<shared_ptr<Value> > params) {
  throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("callee is not an object"));
}
shared_ptr<Value> Value::call (shared_ptr<Value> _this, vector<shared_ptr<Value> > params) {
  throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("callee is not an object"));
}

bool Value::isFunction () {
  return false;
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
  this->closure = nullptr;
}

shared_ptr<Object> Object::Object_prototype;
shared_ptr<Object> Object::Function_prototype;
shared_ptr<Object> Object::String_prototype;
shared_ptr<Object> Object::Boolean_prototype;
shared_ptr<Object> Object::Error_prototype;

shared_ptr<Value> Object::__Get__ (string key) {
  try {
    return this->properties.at(key)->value;
  } catch (out_of_range e) {
    if (this->__Prototype__.get() == nullptr) {
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
    if (this->__Prototype__.get() == nullptr) {
      return false;
    } else {
      return this->__Prototype__->__HasProperty__(key);
    }
  }
}

shared_ptr<Boolean> Object::__HasInstance__ (shared_ptr<Value> value) {
  if (!this->isFunction()) {
    throw ImplementationException("attempted to invoke [[HasInstance]] on a non-object");
  }
  if (value->type != OBJECT_VALUE_TYPE) {
    return make_shared<Boolean>(false);
  }
  shared_ptr<Value> prototype = this->__Get__("prototype");
  if (prototype->type != OBJECT_VALUE_TYPE) {
    throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("Function has non-object prototype '" + ToString(prototype)->value + "' in instanceof check"));
  }
  shared_ptr<Object> obj = static_pointer_cast<Object>(value);
  while (true) {
    obj = obj->__Prototype__;
    if (obj.get() == nullptr) {
      return make_shared<Boolean>(false);
    }
    if ((obj == prototype)->value) {
      return make_shared<Boolean>(true);
    }
  }
}

shared_ptr<Object> Object::construct (vector<shared_ptr<Value> > params) {
  if (!this->isConstructor()) {
    throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("object is not a constructor"));
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
  shared_ptr<Scope> scope = make_shared<Scope>(this->closure);
  shared_ptr<Object> _this = make_shared<Object>(prototype);
  shared_ptr<Value> result = this->__Construct__(scope, _this, params);
  if (result.get() == nullptr) {
    return _this;
  }
  if (result->type == OBJECT_VALUE_TYPE) {
    return static_pointer_cast<Object>(result);
  }
  // ES1: 11.2.2(6): If Type(result) is not Object, generate a runtime error.
  // But I have observed in the Chrome JavaScript console that this is not an error.
  throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("constructor returned a non-object"));
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
  if (!this->isFunction()) {
    throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("object is not a function"));
  }
  shared_ptr<Scope> scope = make_shared<Scope>(this->closure);
  shared_ptr<Value> result = this->__Call__(scope, _this, params);
  if (result.get() == nullptr) {
    return make_shared<Undefined>();
  }
  return result;
}

// TODO: #6: each function should have formal params and a `length` property.
// TODO: each function should have a name.
shared_ptr<Object> Object::makeFunction (CallSignature __Call__, CallSignature __Construct__, shared_ptr<Object> prototype, shared_ptr<Scope> closure) {
  // ES1: 15(5): Every built-in function and every built-in constructor has the Function prototype object,
  //             which is the value of the expression `Function.prototype` (15.3.3.1), as the value of its
  //             internal [[Prototype]] property, except the Function prototype object itself.
  // ES1: 15.3.2.1.16: The [[Prototype]] property of _F_ is set to the original Function prototype
  //                   object, the one that is the initial value of `Function.prototype` (15.3.3.1)
  shared_ptr<Object> fn = make_shared<Object>(Function_prototype);
  // ES1: 15.3.2.1.15: The [[Class]] property of _F_ is set to "Function".
  fn->__Class__ = "Function"; // TODO: enum this
  fn->__Construct__ = __Construct__;
  fn->__Call__ = __Call__;
  
  if (__Construct__ != nullptr) {
    if (prototype.get() == nullptr) {
      throw ImplementationException("attempted to instantiate a Constructor without providing a prototype");
    }
    // TODO: For user-defined script functions, at runtime:
    // TODO: ES1: 15.3.2.1.23: This property is given attributes { DontEnum }.
    // TODO: For built-in and host function objects:
    // TODO: ES1: 15.2.3.1(2): This property shall have the attributes { DontEnum, DontDelete, ReadOnly }.
    // TODO: ES1: 15.3.3.1(2): This property shall have the attributes { DontEnum, DontDelete, ReadOnly }.
    // TODO: ES1: 15.4.3.1(2): This property shall have the attributes { DontEnum, DontDelete, ReadOnly }.
    // TODO: ES1: 15.5.3.1(2): This property shall have the attributes { DontEnum, DontDelete, ReadOnly }.
    // TODO: ES1: 15.6.3.1(2): This property shall have the attributes { DontEnum, DontDelete, ReadOnly }.
    // TODO: ES1: 15.7.3.1(2): This property shall have the attributes { DontEnum, DontDelete, ReadOnly }.
    // TODO: ES1: 15.9.4.1(2): This property shall have the attributes { DontEnum, DontDelete, ReadOnly }.
    fn->*"prototype" = prototype;
    // ES1: 15.3.2.1.24: The constructor property ... is set to _F_.
    // TODO: ES1: 15.3.2.1.24: This property is given attributes { DontEnum }.
    fn->*"prototype"->*"constructor" = fn;
  }

  // Additional special members used only by function objects.
  fn->closure = closure;
  return fn;
}

bool Object::isConstructor () {
  if (this->__Construct__ == nullptr) {
    return false;
  } else {
    return true;
  }
}
bool Object::isFunction () {
  if (this->__Call__ == nullptr) {
    return false;
  } else {
    return true;
  }
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
  if (!value->isFunction()) {
    throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>(this->propertyName->value + " is not a function"));
  }
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
Reference operator ->* (shared_ptr<Value> val, string identifier) {
  return ToObject(val)->*identifier;
}
Reference operator ->* (shared_ptr<Object> obj, string identifier) {
  return Reference(obj, make_shared<String>(identifier));
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
vector<shared_ptr<Value> > operator , (vector<shared_ptr<Value> > v, Reference r) {
  v.push_back(GetValue(r));
  return v;
}
vector<shared_ptr<Value> > operator , (vector<shared_ptr<Value> > v, shared_ptr<Value> x) {
  v.push_back(x);
  return v;
}

// End comma operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Bitwise operator overloads for object literals/initializers/expressions

// create an object from a propery name and a value
shared_ptr<Object> operator & (string propertyName, Reference ref) {
  return propertyName&GetValue(ref);
}
shared_ptr<Object> operator & (string propertyName, shared_ptr<Value> val) {
  shared_ptr<Object> obj = make_shared<Object>();
  obj->__Put__(propertyName, val);
  return obj;
}

// merge right object into left one
shared_ptr<Object> operator | (shared_ptr<Object> a, shared_ptr<Object> b) {
  for ( map<string, shared_ptr<Object::Property> >::iterator it = b->properties.begin() ; it != b->properties.end() ; it++ ) {
    a->__Put__(it->first, it->second->value);
  }
  return a;
}

// End bitwise operator overloads
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
shared_ptr<Number> operator + (shared_ptr<Undefined> u, shared_ptr<Number> n) {
  return Number::makeNaN();
}
shared_ptr<String> operator + (shared_ptr<Undefined> u, shared_ptr<String> s) {
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
    return ToNumber(b) + ToNumber(p);
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

////////////////////////////////////////////////////////////////////////////////
// Double equals operator overloads for every combination of operands

////////////////////////////////////////
// Left operands of type `Reference`
shared_ptr<Boolean> operator == (Reference a, Reference b) {
  return GetValue(a) == b;
}
shared_ptr<Boolean> operator == (Reference r, shared_ptr<Value> v) {
  return GetValue(r) == v;
}
shared_ptr<Boolean> operator == (Reference r, shared_ptr<Object> o) {
  return GetValue(r) == o;
}
shared_ptr<Boolean> operator == (Reference r, shared_ptr<Primitive> p) {
  return GetValue(r) == p;
}
shared_ptr<Boolean> operator == (Reference r, shared_ptr<Undefined> u) {
  return GetValue(r) == u;
}
shared_ptr<Boolean> operator == (Reference r, shared_ptr<Null> n) {
  return GetValue(r) == n;
}
shared_ptr<Boolean> operator == (Reference r, shared_ptr<Boolean> b) {
  return GetValue(r) == b;
}
shared_ptr<Boolean> operator == (Reference r, shared_ptr<Number> n) {
  return GetValue(r) == n;
}
shared_ptr<Boolean> operator == (Reference r, shared_ptr<String> s) {
  return GetValue(r) == s;
}

////////////////////////////////////////
// Left operands of type `Value`
shared_ptr<Boolean> operator == (shared_ptr<Value> v, Reference r) {
  return v == GetValue(r);
}
shared_ptr<Boolean> operator == (shared_ptr<Value> a, shared_ptr<Value> b) {
  switch (a->type) {
    case UNDEFINED_VALUE_TYPE:
      return static_pointer_cast<Undefined>(a) == b;
    case NULL_VALUE_TYPE:
      return static_pointer_cast<Null>(a) == b;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(a) == b;
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(a) == b;
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(a) == b;
    case OBJECT_VALUE_TYPE:
      return static_pointer_cast<Object>(a) == b;
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Value> v, shared_ptr<Object> o) {
  switch (v->type) {
    case UNDEFINED_VALUE_TYPE:
      return static_pointer_cast<Undefined>(v) == o;
    case NULL_VALUE_TYPE:
      return static_pointer_cast<Null>(v) == o;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(v) == o;
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(v) == o;
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(v) == o;
    case OBJECT_VALUE_TYPE:
      return static_pointer_cast<Object>(v) == o;
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Value> v, shared_ptr<Primitive> p) {
  switch (v->type) {
    case UNDEFINED_VALUE_TYPE:
      return static_pointer_cast<Undefined>(v) == p;
    case NULL_VALUE_TYPE:
      return static_pointer_cast<Null>(v) == p;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(v) == p;
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(v) == p;
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(v) == p;
    case OBJECT_VALUE_TYPE:
      return static_pointer_cast<Object>(v) == p;
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Value> v, shared_ptr<Undefined> u) {
  switch (v->type) {
    case UNDEFINED_VALUE_TYPE:
      return static_pointer_cast<Undefined>(v) == u;
    case NULL_VALUE_TYPE:
      return static_pointer_cast<Null>(v) == u;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(v) == u;
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(v) == u;
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(v) == u;
    case OBJECT_VALUE_TYPE:
      return static_pointer_cast<Object>(v) == u;
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Value> v, shared_ptr<Null> n) {
  switch (v->type) {
    case UNDEFINED_VALUE_TYPE:
      return static_pointer_cast<Undefined>(v) == n;
    case NULL_VALUE_TYPE:
      return static_pointer_cast<Null>(v) == n;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(v) == n;
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(v) == n;
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(v) == n;
    case OBJECT_VALUE_TYPE:
      return static_pointer_cast<Object>(v) == n;
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Value> v, shared_ptr<Boolean> b) {
  switch (v->type) {
    case UNDEFINED_VALUE_TYPE:
      return static_pointer_cast<Undefined>(v) == b;
    case NULL_VALUE_TYPE:
      return static_pointer_cast<Null>(v) == b;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(v) == b;
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(v) == b;
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(v) == b;
    case OBJECT_VALUE_TYPE:
      return static_pointer_cast<Object>(v) == b;
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Value> v, shared_ptr<Number> n) {
  switch (v->type) {
    case UNDEFINED_VALUE_TYPE:
      return static_pointer_cast<Undefined>(v) == n;
    case NULL_VALUE_TYPE:
      return static_pointer_cast<Null>(v) == n;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(v) == n;
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(v) == n;
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(v) == n;
    case OBJECT_VALUE_TYPE:
      return static_pointer_cast<Object>(v) == n;
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Value> v, shared_ptr<String> s) {
  switch (v->type) {
    case UNDEFINED_VALUE_TYPE:
      return static_pointer_cast<Undefined>(v) == s;
    case NULL_VALUE_TYPE:
      return static_pointer_cast<Null>(v) == s;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(v) == s;
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(v) == s;
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(v) == s;
    case OBJECT_VALUE_TYPE:
      return static_pointer_cast<Object>(v) == s;
  }
}

////////////////////////////////////////
// Left operands of type `Object`
shared_ptr<Boolean> operator == (shared_ptr<Object> o, Reference r) {
  return o == GetValue(r);
}
shared_ptr<Boolean> operator == (shared_ptr<Object> o, shared_ptr<Value> v) {
  switch (v->type) {
    case UNDEFINED_VALUE_TYPE:
      return o == static_pointer_cast<Undefined>(v);
    case NULL_VALUE_TYPE:
      return o == static_pointer_cast<Null>(v);
    case BOOLEAN_VALUE_TYPE:
      return o == static_pointer_cast<Boolean>(v);
    case NUMBER_VALUE_TYPE:
      return o == static_pointer_cast<Number>(v);
    case STRING_VALUE_TYPE:
      return o == static_pointer_cast<String>(v);
    case OBJECT_VALUE_TYPE:
      return o == static_pointer_cast<Object>(v);
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Object> a, shared_ptr<Object> b) {
  return make_shared<Boolean>(a.get() == b.get());
}
shared_ptr<Boolean> operator == (shared_ptr<Object> o, shared_ptr<Primitive> p) {
  switch (p->type) {
    case UNDEFINED_VALUE_TYPE:
      return o == static_pointer_cast<Undefined>(p);
    case NULL_VALUE_TYPE:
      return o == static_pointer_cast<Null>(p);
    case BOOLEAN_VALUE_TYPE:
      return o == static_pointer_cast<Boolean>(p);
    case NUMBER_VALUE_TYPE:
      return o == static_pointer_cast<Number>(p);
    case STRING_VALUE_TYPE:
      return o == static_pointer_cast<String>(p);
    case OBJECT_VALUE_TYPE:
      throw ImplementationException("an object was passed to operator==(Object, Primitive)");
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Object> o, shared_ptr<Undefined> u) {
  return make_shared<Boolean>(false);
}
shared_ptr<Boolean> operator == (shared_ptr<Object> o, shared_ptr<Null> n) {
  return make_shared<Boolean>(false);
}
shared_ptr<Boolean> operator == (shared_ptr<Object> o, shared_ptr<Boolean> b) {
  return o == ToNumber(b);
}
shared_ptr<Boolean> operator == (shared_ptr<Object> o, shared_ptr<Number> n) {
  return ToPrimitive(o) == n;
}
shared_ptr<Boolean> operator == (shared_ptr<Object> o, shared_ptr<String> s) {
  return ToPrimitive(o) == s;
}

////////////////////////////////////////
// Left operands of type `Primitive`
shared_ptr<Boolean> operator == (shared_ptr<Primitive> p, Reference r) {
  return p == GetValue(r);
}
shared_ptr<Boolean> operator == (shared_ptr<Primitive> p, shared_ptr<Value> v) {
  switch (p->type) {
    case UNDEFINED_VALUE_TYPE:
      return static_pointer_cast<Undefined>(p) == v;
    case NULL_VALUE_TYPE:
      return static_pointer_cast<Null>(p) == v;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(p) == v;
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(p) == v;
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(p) == v;
    case OBJECT_VALUE_TYPE:
      throw ImplementationException("an object was passed to operator==(Primitive, Value)");
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Primitive> p, shared_ptr<Object> o) {
  switch (p->type) {
    case UNDEFINED_VALUE_TYPE:
      return static_pointer_cast<Undefined>(p) == o;
    case NULL_VALUE_TYPE:
      return static_pointer_cast<Null>(p) == o;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(p) == o;
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(p) == o;
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(p) == o;
    case OBJECT_VALUE_TYPE:
      throw ImplementationException("an object was passed to operator==(Primitive, Object)");
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Primitive> a, shared_ptr<Primitive> b) {
  switch (a->type) {
    case UNDEFINED_VALUE_TYPE:
      return static_pointer_cast<Undefined>(a) == b;
    case NULL_VALUE_TYPE:
      return static_pointer_cast<Null>(a) == b;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(a) == b;
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(a) == b;
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(a) == b;
    case OBJECT_VALUE_TYPE:
      throw ImplementationException("an object was passed to operator==(Primitive, Primitive)");
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Primitive> p, shared_ptr<Undefined> u) {
  switch (p->type) {
    case UNDEFINED_VALUE_TYPE:
      return static_pointer_cast<Undefined>(p) == u;
    case NULL_VALUE_TYPE:
      return static_pointer_cast<Null>(p) == u;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(p) == u;
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(p) == u;
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(p) == u;
    case OBJECT_VALUE_TYPE:
      throw ImplementationException("an object was passed to operator==(Primitive, Undefined)");
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Primitive> p, shared_ptr<Null> n) {
  switch (p->type) {
    case UNDEFINED_VALUE_TYPE:
      return static_pointer_cast<Undefined>(p) == n;
    case NULL_VALUE_TYPE:
      return static_pointer_cast<Null>(p) == n;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(p) == n;
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(p) == n;
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(p) == n;
    case OBJECT_VALUE_TYPE:
      throw ImplementationException("an object was passed to operator==(Primitive, Null)");
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Primitive> p, shared_ptr<Boolean> b) {
  switch (p->type) {
    case UNDEFINED_VALUE_TYPE:
      return static_pointer_cast<Undefined>(p) == b;
    case NULL_VALUE_TYPE:
      return static_pointer_cast<Null>(p) == b;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(p) == b;
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(p) == b;
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(p) == b;
    case OBJECT_VALUE_TYPE:
      throw ImplementationException("an object was passed to operator==(Primitive, Boolean)");
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Primitive> p, shared_ptr<Number> n) {
  switch (p->type) {
    case UNDEFINED_VALUE_TYPE:
      return static_pointer_cast<Undefined>(p) == n;
    case NULL_VALUE_TYPE:
      return static_pointer_cast<Null>(p) == n;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(p) == n;
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(p) == n;
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(p) == n;
    case OBJECT_VALUE_TYPE:
      throw ImplementationException("an object was passed to operator==(Primitive, Number)");
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Primitive> p, shared_ptr<String> s) {
  switch (p->type) {
    case UNDEFINED_VALUE_TYPE:
      return static_pointer_cast<Undefined>(p) == s;
    case NULL_VALUE_TYPE:
      return static_pointer_cast<Null>(p) == s;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(p) == s;
    case NUMBER_VALUE_TYPE:
      return static_pointer_cast<Number>(p) == s;
    case STRING_VALUE_TYPE:
      return static_pointer_cast<String>(p) == s;
    case OBJECT_VALUE_TYPE:
      throw ImplementationException("an object was passed to operator==(Primitive, String)");
  }
}

////////////////////////////////////////
// Left operands of type `Undefined`
shared_ptr<Boolean> operator == (shared_ptr<Undefined> u, Reference r) {
  return u == GetValue(r);
}
shared_ptr<Boolean> operator == (shared_ptr<Undefined> u, shared_ptr<Value> v) {
  switch (v->type) {
    case UNDEFINED_VALUE_TYPE:
      return u == static_pointer_cast<Undefined>(v);
    case NULL_VALUE_TYPE:
      return u == static_pointer_cast<Null>(v);
    case BOOLEAN_VALUE_TYPE:
      return u == static_pointer_cast<Boolean>(v);
    case NUMBER_VALUE_TYPE:
      return u == static_pointer_cast<Number>(v);
    case STRING_VALUE_TYPE:
      return u == static_pointer_cast<String>(v);
    case OBJECT_VALUE_TYPE:
      return u == static_pointer_cast<Object>(v);
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Undefined> u, shared_ptr<Object> o) {
  return make_shared<Boolean>(false);
}
shared_ptr<Boolean> operator == (shared_ptr<Undefined> u, shared_ptr<Primitive> p) {
  switch (p->type) {
    case UNDEFINED_VALUE_TYPE:
      return u == static_pointer_cast<Undefined>(p);
    case NULL_VALUE_TYPE:
      return u == static_pointer_cast<Null>(p);
    case BOOLEAN_VALUE_TYPE:
      return u == static_pointer_cast<Boolean>(p);
    case NUMBER_VALUE_TYPE:
      return u == static_pointer_cast<Number>(p);
    case STRING_VALUE_TYPE:
      return u == static_pointer_cast<String>(p);
    case OBJECT_VALUE_TYPE:
      throw ImplementationException("an object was passed to operator==(Undefined, Primitive)");
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Undefined> a, shared_ptr<Undefined> b) {
  return make_shared<Boolean>(true);
}
shared_ptr<Boolean> operator == (shared_ptr<Undefined> u, shared_ptr<Null> n) {
  return make_shared<Boolean>(true);
}
shared_ptr<Boolean> operator == (shared_ptr<Undefined> u, shared_ptr<Boolean> b) {
  return make_shared<Boolean>(false);
}
shared_ptr<Boolean> operator == (shared_ptr<Undefined> u, shared_ptr<Number> n) {
  return make_shared<Boolean>(false);
}
shared_ptr<Boolean> operator == (shared_ptr<Undefined> u, shared_ptr<String> s) {
  return make_shared<Boolean>(false);
}

////////////////////////////////////////
// Left operands of type `Null`
shared_ptr<Boolean> operator == (shared_ptr<Null> n, Reference r) {
  return n == GetValue(r);
}
shared_ptr<Boolean> operator == (shared_ptr<Null> n, shared_ptr<Value> v) {
  switch (v->type) {
    case UNDEFINED_VALUE_TYPE:
      return n == static_pointer_cast<Undefined>(v);
    case NULL_VALUE_TYPE:
      return n == static_pointer_cast<Null>(v);
    case BOOLEAN_VALUE_TYPE:
      return n == static_pointer_cast<Boolean>(v);
    case NUMBER_VALUE_TYPE:
      return n == static_pointer_cast<Number>(v);
    case STRING_VALUE_TYPE:
      return n == static_pointer_cast<String>(v);
    case OBJECT_VALUE_TYPE:
      return n == static_pointer_cast<Object>(v);
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Null> n, shared_ptr<Object> o) {
  return make_shared<Boolean>(false);
}
shared_ptr<Boolean> operator == (shared_ptr<Null> n, shared_ptr<Primitive> p) {
  switch (p->type) {
    case UNDEFINED_VALUE_TYPE:
      return n == static_pointer_cast<Undefined>(p);
    case NULL_VALUE_TYPE:
      return n == static_pointer_cast<Null>(p);
    case BOOLEAN_VALUE_TYPE:
      return n == static_pointer_cast<Boolean>(p);
    case NUMBER_VALUE_TYPE:
      return n == static_pointer_cast<Number>(p);
    case STRING_VALUE_TYPE:
      return n == static_pointer_cast<String>(p);
    case OBJECT_VALUE_TYPE:
      throw ImplementationException("an object was passed to operator==(Null, Primitive)");
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Null> n, shared_ptr<Undefined> u) {
  return make_shared<Boolean>(true);
}
shared_ptr<Boolean> operator == (shared_ptr<Null> a, shared_ptr<Null> b) {
  return make_shared<Boolean>(true);
}
shared_ptr<Boolean> operator == (shared_ptr<Null> n, shared_ptr<Boolean> b) {
  return make_shared<Boolean>(false);
}
shared_ptr<Boolean> operator == (shared_ptr<Null> n, shared_ptr<Number> x) {
  return make_shared<Boolean>(false);
}
shared_ptr<Boolean> operator == (shared_ptr<Null> n, shared_ptr<String> s) {
  return make_shared<Boolean>(false);
}

////////////////////////////////////////
// Left operands of type `Boolean`
shared_ptr<Boolean> operator == (shared_ptr<Boolean> b, Reference r) {
  return b == GetValue(r);
}
shared_ptr<Boolean> operator == (shared_ptr<Boolean> b, shared_ptr<Value> v) {
  switch (v->type) {
    case UNDEFINED_VALUE_TYPE:
      return b == static_pointer_cast<Undefined>(v);
    case NULL_VALUE_TYPE:
      return b == static_pointer_cast<Null>(v);
    case BOOLEAN_VALUE_TYPE:
      return b == static_pointer_cast<Boolean>(v);
    case NUMBER_VALUE_TYPE:
      return b == static_pointer_cast<Number>(v);
    case STRING_VALUE_TYPE:
      return b == static_pointer_cast<String>(v);
    case OBJECT_VALUE_TYPE:
      return b == static_pointer_cast<Object>(v);
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Boolean> b, shared_ptr<Object> o) {
  return ToNumber(b) == o;
}
shared_ptr<Boolean> operator == (shared_ptr<Boolean> b, shared_ptr<Primitive> p) {
  switch (p->type) {
    case UNDEFINED_VALUE_TYPE:
      return b == static_pointer_cast<Undefined>(p);
    case NULL_VALUE_TYPE:
      return b == static_pointer_cast<Null>(p);
    case BOOLEAN_VALUE_TYPE:
      return b == static_pointer_cast<Boolean>(p);
    case NUMBER_VALUE_TYPE:
      return b == static_pointer_cast<Number>(p);
    case STRING_VALUE_TYPE:
      return b == static_pointer_cast<String>(p);
    case OBJECT_VALUE_TYPE:
      throw ImplementationException("an object was passed to operator==(Boolean, Primitive)");
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Boolean> b, shared_ptr<Undefined> u) {
  return make_shared<Boolean>(false);
}
shared_ptr<Boolean> operator == (shared_ptr<Boolean> b, shared_ptr<Null> n) {
  return make_shared<Boolean>(false);
}
shared_ptr<Boolean> operator == (shared_ptr<Boolean> a, shared_ptr<Boolean> b) {
  return make_shared<Boolean>(a->value == b->value);
}
shared_ptr<Boolean> operator == (shared_ptr<Boolean> b, shared_ptr<Number> n) {
  return ToNumber(b) == n;
}
shared_ptr<Boolean> operator == (shared_ptr<Boolean> b, shared_ptr<String> s) {
  return ToNumber(b) == s;
}

////////////////////////////////////////
// Left operands of type `Number`
shared_ptr<Boolean> operator == (shared_ptr<Number> n, Reference r) {
  return n == GetValue(r);
}
shared_ptr<Boolean> operator == (shared_ptr<Number> n, shared_ptr<Value> v) {
  switch (v->type) {
    case UNDEFINED_VALUE_TYPE:
      return n == static_pointer_cast<Undefined>(v);
    case NULL_VALUE_TYPE:
      return n == static_pointer_cast<Null>(v);
    case BOOLEAN_VALUE_TYPE:
      return n == static_pointer_cast<Boolean>(v);
    case NUMBER_VALUE_TYPE:
      return n == static_pointer_cast<Number>(v);
    case STRING_VALUE_TYPE:
      return n == static_pointer_cast<String>(v);
    case OBJECT_VALUE_TYPE:
      return n == static_pointer_cast<Object>(v);
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Number> n, shared_ptr<Object> o) {
  return n == ToPrimitive(o);
}
shared_ptr<Boolean> operator == (shared_ptr<Number> n, shared_ptr<Primitive> p) {
  switch (p->type) {
    case UNDEFINED_VALUE_TYPE:
      return n == static_pointer_cast<Undefined>(p);
    case NULL_VALUE_TYPE:
      return n == static_pointer_cast<Null>(p);
    case BOOLEAN_VALUE_TYPE:
      return n == static_pointer_cast<Boolean>(p);
    case NUMBER_VALUE_TYPE:
      return n == static_pointer_cast<Number>(p);
    case STRING_VALUE_TYPE:
      return n == static_pointer_cast<String>(p);
    case OBJECT_VALUE_TYPE:
      throw ImplementationException("an object was passed to operator==(Number, Primitive)");
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Number> n, shared_ptr<Undefined> u) {
  return make_shared<Boolean>(false);
}
shared_ptr<Boolean> operator == (shared_ptr<Number> n, shared_ptr<Null> x) {
  return make_shared<Boolean>(false);
}
shared_ptr<Boolean> operator == (shared_ptr<Number> n, shared_ptr<Boolean> b) {
  return n == ToNumber(b);
}
shared_ptr<Boolean> operator == (shared_ptr<Number> a, shared_ptr<Number> b) {
  if (a->isNaN) {
    return make_shared<Boolean>(false);
  }
  if (b->isNaN) {
    return make_shared<Boolean>(false);
  }
  if (a->isInfinity && b->isInfinity) {
    if (a->isNegative == b->isNegative) {
      return make_shared<Boolean>(true);
    } else {
      return make_shared<Boolean>(false);
    }
  }
  if (a->value == b->value) {
    return make_shared<Boolean>(true);
  } else {
    return make_shared<Boolean>(false);
  }
}
shared_ptr<Boolean> operator == (shared_ptr<Number> n, shared_ptr<String> s) {
  return n == ToNumber(s);
};

////////////////////////////////////////
// Left operands of type `String`
shared_ptr<Boolean> operator == (shared_ptr<String> s, Reference r) {
  return s == GetValue(r);
}
shared_ptr<Boolean> operator == (shared_ptr<String> s, shared_ptr<Value> v) {
  switch (v->type) {
    case UNDEFINED_VALUE_TYPE:
      return s == static_pointer_cast<Undefined>(v);
    case NULL_VALUE_TYPE:
      return s == static_pointer_cast<Null>(v);
    case BOOLEAN_VALUE_TYPE:
      return s == static_pointer_cast<Boolean>(v);
    case NUMBER_VALUE_TYPE:
      return s == static_pointer_cast<Number>(v);
    case STRING_VALUE_TYPE:
      return s == static_pointer_cast<String>(v);
    case OBJECT_VALUE_TYPE:
      return s == static_pointer_cast<Object>(v);
  }
}
shared_ptr<Boolean> operator == (shared_ptr<String> s, shared_ptr<Object> o) {
  return s == ToPrimitive(o);
}
shared_ptr<Boolean> operator == (shared_ptr<String> s, shared_ptr<Primitive> p) {
  switch (p->type) {
    case UNDEFINED_VALUE_TYPE:
      return s == static_pointer_cast<Undefined>(p);
    case NULL_VALUE_TYPE:
      return s == static_pointer_cast<Null>(p);
    case BOOLEAN_VALUE_TYPE:
      return s == static_pointer_cast<Boolean>(p);
    case NUMBER_VALUE_TYPE:
      return s == static_pointer_cast<Number>(p);
    case STRING_VALUE_TYPE:
      return s == static_pointer_cast<String>(p);
    case OBJECT_VALUE_TYPE:
      throw ImplementationException("an object was passed to operator==(String, Primitive)");
  }
}
shared_ptr<Boolean> operator == (shared_ptr<String> s, shared_ptr<Undefined> u) {
  return make_shared<Boolean>(false);
}
shared_ptr<Boolean> operator == (shared_ptr<String> s, shared_ptr<Null> n) {
  return make_shared<Boolean>(false);
}
shared_ptr<Boolean> operator == (shared_ptr<String> s, shared_ptr<Boolean> b) {
  return s == ToNumber(b);
}
shared_ptr<Boolean> operator == (shared_ptr<String> s, shared_ptr<Number> n) {
  return ToNumber(s) == n;
}
shared_ptr<Boolean> operator == (shared_ptr<String> a, shared_ptr<String> b) {
  return make_shared<Boolean>(a->value == b->value);
}

// End double equals operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Division operator overloads for every combination of operands

////////////////////////////////////////
// Left operands of type `Reference`
shared_ptr<Number> operator / (Reference a, Reference b) {
  return ToNumber(GetValue(a)) / ToNumber(GetValue(b));
}
shared_ptr<Number> operator / (Reference r, shared_ptr<Value> v) {
  return ToNumber(GetValue(r)) / ToNumber(v);
}
shared_ptr<Number> operator / (Reference r, shared_ptr<Object> o) {
  return ToNumber(GetValue(r)) / ToNumber(o);
}
shared_ptr<Number> operator / (Reference r, shared_ptr<Primitive> p) {
  return ToNumber(GetValue(r)) / ToNumber(p);
}
shared_ptr<Number> operator / (Reference r, shared_ptr<Undefined> u) {
  GetValue(r);
  return Number::makeNaN();
}
shared_ptr<Number> operator / (Reference r, shared_ptr<Null> n) {
  GetValue(r);
  return Number::makeNaN();
}
shared_ptr<Number> operator / (Reference r, shared_ptr<Boolean> b) {
  return ToNumber(GetValue(r)) / ToNumber(b);
}
shared_ptr<Number> operator / (Reference r, shared_ptr<Number> n) {
  return ToNumber(GetValue(r)) / n;
}
shared_ptr<Number> operator / (Reference r, shared_ptr<String> s) {
  return ToNumber(GetValue(r)) / ToNumber(s);
}

////////////////////////////////////////
// Left operands of type `Value`
shared_ptr<Number> operator / (shared_ptr<Value> v, Reference r) {
  return ToNumber(v) / ToNumber(GetValue(r));
}
shared_ptr<Number> operator / (shared_ptr<Value> a, shared_ptr<Value> b) {
  return ToNumber(a) / ToNumber(b);
}
shared_ptr<Number> operator / (shared_ptr<Value> v, shared_ptr<Object> o) {
  return ToNumber(v) / ToNumber(o);
}
shared_ptr<Number> operator / (shared_ptr<Value> v, shared_ptr<Primitive> p) {
  return ToNumber(v) / ToNumber(p);
}
shared_ptr<Number> operator / (shared_ptr<Value> v, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Value> v, shared_ptr<Null> n) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Value> v, shared_ptr<Boolean> b) {
  return ToNumber(v) / ToNumber(b);
}
shared_ptr<Number> operator / (shared_ptr<Value> v, shared_ptr<Number> n) {
  return ToNumber(v) / n;
}
shared_ptr<Number> operator / (shared_ptr<Value> v, shared_ptr<String> s) {
  return ToNumber(v) / ToNumber(s);
}

////////////////////////////////////////
// Left operands of type `Object`
shared_ptr<Number> operator / (shared_ptr<Object> o, Reference r) {
  return ToNumber(o) / ToNumber(GetValue(r));
}
shared_ptr<Number> operator / (shared_ptr<Object> o, shared_ptr<Value> v) {
  return ToNumber(o) / ToNumber(v);
}
shared_ptr<Number> operator / (shared_ptr<Object> a, shared_ptr<Object> b) {
  return ToNumber(a) / ToNumber(b);
}
shared_ptr<Number> operator / (shared_ptr<Object> o, shared_ptr<Primitive> p) {
  return ToNumber(o) / ToNumber(p);
}
shared_ptr<Number> operator / (shared_ptr<Object> o, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Object> o, shared_ptr<Null> n) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Object> o, shared_ptr<Boolean> b) {
  return ToNumber(o) / ToNumber(b);
}
shared_ptr<Number> operator / (shared_ptr<Object> o, shared_ptr<Number> n) {
  return ToNumber(o) / n;
}
shared_ptr<Number> operator / (shared_ptr<Object> o, shared_ptr<String> s) {
  return ToNumber(o) / ToNumber(s);
}

////////////////////////////////////////
// Left operands of type `Primitive`
shared_ptr<Number> operator / (shared_ptr<Primitive> p, Reference r) {
  return ToNumber(p) / ToNumber(GetValue(r));
}
shared_ptr<Number> operator / (shared_ptr<Primitive> p, shared_ptr<Value> v) {
  return ToNumber(p) / ToNumber(v);
}
shared_ptr<Number> operator / (shared_ptr<Primitive> p, shared_ptr<Object> o) {
  return ToNumber(p) / ToNumber(o);
}
shared_ptr<Number> operator / (shared_ptr<Primitive> a, shared_ptr<Primitive> b) {
  return ToNumber(a) / ToNumber(b);
}
shared_ptr<Number> operator / (shared_ptr<Primitive> p, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Primitive> p, shared_ptr<Null> n) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Primitive> p, shared_ptr<Boolean> b) {
  return ToNumber(p) / ToNumber(b);
}
shared_ptr<Number> operator / (shared_ptr<Primitive> p, shared_ptr<Number> n) {
  return ToNumber(p) / n;
}
shared_ptr<Number> operator / (shared_ptr<Primitive> p, shared_ptr<String> s) {
  return ToNumber(p) / ToNumber(s);
}

////////////////////////////////////////
// Left operands of type `Undefined`
shared_ptr<Number> operator / (shared_ptr<Undefined> u, Reference r) {
  GetValue(r);
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Undefined> u, shared_ptr<Value> v) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Undefined> u, shared_ptr<Object> o) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Undefined> u, shared_ptr<Primitive> p) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Undefined> a, shared_ptr<Undefined> b) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Undefined> u, shared_ptr<Null> n) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Undefined> u, shared_ptr<Boolean> b) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Undefined> u, shared_ptr<Number> n) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Undefined> u, shared_ptr<String> s) {
  return Number::makeNaN();
}

////////////////////////////////////////
// Left operands of type `Null`
shared_ptr<Number> operator / (shared_ptr<Null> n, Reference r) {
  return make_shared<Number>(0, false) / ToNumber(GetValue(r));
}
shared_ptr<Number> operator / (shared_ptr<Null> n, shared_ptr<Value> v) {
  return make_shared<Number>(0, false) / ToNumber(v);
}
shared_ptr<Number> operator / (shared_ptr<Null> n, shared_ptr<Object> o) {
  return make_shared<Number>(0, false) / ToNumber(o);
}
shared_ptr<Number> operator / (shared_ptr<Null> n, shared_ptr<Primitive> p) {
  return make_shared<Number>(0, false) / ToNumber(p);
}
shared_ptr<Number> operator / (shared_ptr<Null> n, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Null> a, shared_ptr<Null> b) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Null> n, shared_ptr<Boolean> b) {
  return make_shared<Number>(0, false) / ToNumber(b);
}
shared_ptr<Number> operator / (shared_ptr<Null> n, shared_ptr<Number> x) {
  return make_shared<Number>(0, false) / x;
}
shared_ptr<Number> operator / (shared_ptr<Null> n, shared_ptr<String> s) {
  return make_shared<Number>(0, false) / ToNumber(s);
}

////////////////////////////////////////
// Left operands of type `Boolean`
shared_ptr<Number> operator / (shared_ptr<Boolean> b, Reference r) {
  return ToNumber(b) / ToNumber(GetValue(r));
}
shared_ptr<Number> operator / (shared_ptr<Boolean> b, shared_ptr<Value> v) {
  return ToNumber(b) / ToNumber(v);
}
shared_ptr<Number> operator / (shared_ptr<Boolean> b, shared_ptr<Object> o) {
  return ToNumber(b) / ToNumber(o);
}
shared_ptr<Number> operator / (shared_ptr<Boolean> b, shared_ptr<Primitive> p) {
  return ToNumber(b) / ToNumber(p);
}
shared_ptr<Number> operator / (shared_ptr<Boolean> b, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Boolean> b, shared_ptr<Null> n) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Boolean> a, shared_ptr<Boolean> b) {
  return b->value ? make_shared<Number>(0, false) : Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Boolean> b, shared_ptr<Number> n) {
  return ToNumber(b) / n;
}
shared_ptr<Number> operator / (shared_ptr<Boolean> b, shared_ptr<String> s) {
  return ToNumber(b) / ToNumber(s);
}

////////////////////////////////////////
// Left operands of type `Number`
shared_ptr<Number> operator / (shared_ptr<Number> n, Reference r) {
  return n / ToNumber(GetValue(r));
}
shared_ptr<Number> operator / (shared_ptr<Number> n, shared_ptr<Value> v) {
  return n / ToNumber(v);
}
shared_ptr<Number> operator / (shared_ptr<Number> n, shared_ptr<Object> o) {
  return n / ToNumber(o);
}
shared_ptr<Number> operator / (shared_ptr<Number> n, shared_ptr<Primitive> p) {
  return n / ToNumber(p);
}
shared_ptr<Number> operator / (shared_ptr<Number> n, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Number> n, shared_ptr<Null> x) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<Number> n, shared_ptr<Boolean> b) {
  return n / ToNumber(b);
}
shared_ptr<Number> operator / (shared_ptr<Number> dividend, shared_ptr<Number> divisor) {
  if (dividend->isNaN || divisor->isNaN) {
    return Number::makeNaN();
  }
  if (dividend->isInfinity) {
    if (divisor->isInfinity) {
      return Number::makeNaN();
    }
    if (divisor->value == 0) {
      if (dividend->isNegative == divisor->isNegative) {
        return Number::makeInfinity(false);
      } else {
        return Number::makeInfinity(true);
      }
    }
    if (dividend->isNegative == (divisor->value < 0)) {
      return Number::makeInfinity(false);
    } else {
      return Number::makeInfinity(true);
    }
  }
  if (divisor->isInfinity) {
    if ((dividend->value < 0) == divisor->isNegative) {
      return make_shared<Number>(0, false);
    } else {
      return make_shared<Number>(0, true);
    }
  }
  if (dividend->value == 0) {
    if (divisor->value == 0) {
      return Number::makeNaN();
    }
    if (dividend->isNegative == (divisor->value < 0)) {
      return make_shared<Number>(0, false);
    } else {
      return make_shared<Number>(0, true);
    }
  }
  if (divisor->value == 0) {
    if ((dividend->value < 0) == divisor->isNegative) {
      return Number::makeInfinity(false);
    } else {
      return Number::makeInfinity(true);
    }
  }
  return make_shared<Number>(dividend->value / divisor->value);
}
shared_ptr<Number> operator / (shared_ptr<Number> n, shared_ptr<String> s) {
  return n / ToNumber(s);
}

////////////////////////////////////////
// Left operands of type `String`
shared_ptr<Number> operator / (shared_ptr<String> s, Reference r) {
  return ToNumber(s) / ToNumber(GetValue(r));
}
shared_ptr<Number> operator / (shared_ptr<String> s, shared_ptr<Value> v) {
  return ToNumber(s) / ToNumber(v);
}
shared_ptr<Number> operator / (shared_ptr<String> s, shared_ptr<Object> o) {
  return ToNumber(s) / ToNumber(o);
}
shared_ptr<Number> operator / (shared_ptr<String> s, shared_ptr<Primitive> p) {
  return ToNumber(s) / ToNumber(p);
}
shared_ptr<Number> operator / (shared_ptr<String> s, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<String> s, shared_ptr<Null> n) {
  return Number::makeNaN();
}
shared_ptr<Number> operator / (shared_ptr<String> s, shared_ptr<Boolean> b) {
  return ToNumber(s) / ToNumber(b);
}
shared_ptr<Number> operator / (shared_ptr<String> s, shared_ptr<Number> n) {
  return ToNumber(s) / n;
}
shared_ptr<Number> operator / (shared_ptr<String> a, shared_ptr<String> b) {
  return ToNumber(a) / ToNumber(b);
}

// End modulus operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Modulus operator overloads for every combination of operands

////////////////////////////////////////
// Left operands of type `Reference`
shared_ptr<Number> operator % (Reference a, Reference b) {
  return ToNumber(GetValue(a)) % ToNumber(GetValue(b));
}
shared_ptr<Number> operator % (Reference r, shared_ptr<Value> v) {
  return ToNumber(GetValue(r)) % ToNumber(v);
}
shared_ptr<Number> operator % (Reference r, shared_ptr<Object> o) {
  return ToNumber(GetValue(r)) % ToNumber(o);
}
shared_ptr<Number> operator % (Reference r, shared_ptr<Primitive> p) {
  return ToNumber(GetValue(r)) % ToNumber(p);
}
shared_ptr<Number> operator % (Reference r, shared_ptr<Undefined> u) {
  GetValue(r);
  return Number::makeNaN();
}
shared_ptr<Number> operator % (Reference r, shared_ptr<Null> n) {
  GetValue(r);
  return Number::makeNaN();
}
shared_ptr<Number> operator % (Reference r, shared_ptr<Boolean> b) {
  return ToNumber(GetValue(r)) % ToNumber(b);
}
shared_ptr<Number> operator % (Reference r, shared_ptr<Number> n) {
  return ToNumber(GetValue(r)) % n;
}
shared_ptr<Number> operator % (Reference r, shared_ptr<String> s) {
  return ToNumber(GetValue(r)) % ToNumber(s);
}

////////////////////////////////////////
// Left operands of type `Value`
shared_ptr<Number> operator % (shared_ptr<Value> v, Reference r) {
  return ToNumber(v) % ToNumber(GetValue(r));
}
shared_ptr<Number> operator % (shared_ptr<Value> a, shared_ptr<Value> b) {
  return ToNumber(a) % ToNumber(b);
}
shared_ptr<Number> operator % (shared_ptr<Value> v, shared_ptr<Object> o) {
  return ToNumber(v) % ToNumber(o);
}
shared_ptr<Number> operator % (shared_ptr<Value> v, shared_ptr<Primitive> p) {
  return ToNumber(v) % ToNumber(p);
}
shared_ptr<Number> operator % (shared_ptr<Value> v, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Value> v, shared_ptr<Null> n) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Value> v, shared_ptr<Boolean> b) {
  return ToNumber(v) % ToNumber(b);
}
shared_ptr<Number> operator % (shared_ptr<Value> v, shared_ptr<Number> n) {
  return ToNumber(v) % n;
}
shared_ptr<Number> operator % (shared_ptr<Value> v, shared_ptr<String> s) {
  return ToNumber(v) % ToNumber(s);
}

////////////////////////////////////////
// Left operands of type `Object`
shared_ptr<Number> operator % (shared_ptr<Object> o, Reference r) {
  return ToNumber(o) % ToNumber(GetValue(r));
}
shared_ptr<Number> operator % (shared_ptr<Object> o, shared_ptr<Value> v) {
  return ToNumber(o) % ToNumber(v);
}
shared_ptr<Number> operator % (shared_ptr<Object> a, shared_ptr<Object> b) {
  return ToNumber(a) % ToNumber(b);
}
shared_ptr<Number> operator % (shared_ptr<Object> o, shared_ptr<Primitive> p) {
  return ToNumber(o) % ToNumber(p);
}
shared_ptr<Number> operator % (shared_ptr<Object> o, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Object> o, shared_ptr<Null> n) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Object> o, shared_ptr<Boolean> b) {
  return ToNumber(o) % ToNumber(b);
}
shared_ptr<Number> operator % (shared_ptr<Object> o, shared_ptr<Number> n) {
  return ToNumber(o) % n;
}
shared_ptr<Number> operator % (shared_ptr<Object> o, shared_ptr<String> s) {
  return ToNumber(o) % ToNumber(s);
}

////////////////////////////////////////
// Left operands of type `Primitive`
shared_ptr<Number> operator % (shared_ptr<Primitive> p, Reference r) {
  return ToNumber(p) % ToNumber(GetValue(r));
}
shared_ptr<Number> operator % (shared_ptr<Primitive> p, shared_ptr<Value> v) {
  return ToNumber(p) % ToNumber(v);
}
shared_ptr<Number> operator % (shared_ptr<Primitive> p, shared_ptr<Object> o) {
  return ToNumber(p) % ToNumber(o);
}
shared_ptr<Number> operator % (shared_ptr<Primitive> a, shared_ptr<Primitive> b) {
  return ToNumber(a) % ToNumber(b);
}
shared_ptr<Number> operator % (shared_ptr<Primitive> p, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Primitive> p, shared_ptr<Null> n) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Primitive> p, shared_ptr<Boolean> b) {
  return ToNumber(p) % ToNumber(b);
}
shared_ptr<Number> operator % (shared_ptr<Primitive> p, shared_ptr<Number> n) {
  return ToNumber(p) % n;
}
shared_ptr<Number> operator % (shared_ptr<Primitive> p, shared_ptr<String> s) {
  return ToNumber(p) % ToNumber(s);
}

////////////////////////////////////////
// Left operands of type `Undefined`
shared_ptr<Number> operator % (shared_ptr<Undefined> u, Reference r) {
  GetValue(r);
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Undefined> u, shared_ptr<Value> v) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Undefined> u, shared_ptr<Object> o) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Undefined> u, shared_ptr<Primitive> p) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Undefined> a, shared_ptr<Undefined> b) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Undefined> u, shared_ptr<Null> n) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Undefined> u, shared_ptr<Boolean> b) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Undefined> u, shared_ptr<Number> n) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Undefined> u, shared_ptr<String> s) {
  return Number::makeNaN();
}

////////////////////////////////////////
// Left operands of type `Null`
shared_ptr<Number> operator % (shared_ptr<Null> n, Reference r) {
  return make_shared<Number>(0, false) % ToNumber(GetValue(r));
}
shared_ptr<Number> operator % (shared_ptr<Null> n, shared_ptr<Value> v) {
  return make_shared<Number>(0, false) % ToNumber(v);
}
shared_ptr<Number> operator % (shared_ptr<Null> n, shared_ptr<Object> o) {
  return make_shared<Number>(0, false) % ToNumber(o);
}
shared_ptr<Number> operator % (shared_ptr<Null> n, shared_ptr<Primitive> p) {
  return make_shared<Number>(0, false) % ToNumber(p);
}
shared_ptr<Number> operator % (shared_ptr<Null> n, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Null> a, shared_ptr<Null> b) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Null> n, shared_ptr<Boolean> b) {
  return make_shared<Number>(0, false) % ToNumber(b);
}
shared_ptr<Number> operator % (shared_ptr<Null> n, shared_ptr<Number> x) {
  return make_shared<Number>(0, false) % x;
}
shared_ptr<Number> operator % (shared_ptr<Null> n, shared_ptr<String> s) {
  return make_shared<Number>(0, false) % ToNumber(s);
}

////////////////////////////////////////
// Left operands of type `Boolean`
shared_ptr<Number> operator % (shared_ptr<Boolean> b, Reference r) {
  return ToNumber(b) % ToNumber(GetValue(r));
}
shared_ptr<Number> operator % (shared_ptr<Boolean> b, shared_ptr<Value> v) {
  return ToNumber(b) % ToNumber(v);
}
shared_ptr<Number> operator % (shared_ptr<Boolean> b, shared_ptr<Object> o) {
  return ToNumber(b) % ToNumber(o);
}
shared_ptr<Number> operator % (shared_ptr<Boolean> b, shared_ptr<Primitive> p) {
  return ToNumber(b) % ToNumber(p);
}
shared_ptr<Number> operator % (shared_ptr<Boolean> b, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Boolean> b, shared_ptr<Null> n) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Boolean> a, shared_ptr<Boolean> b) {
  return b->value ? make_shared<Number>(0, false) : Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Boolean> b, shared_ptr<Number> n) {
  return ToNumber(b) % n;
}
shared_ptr<Number> operator % (shared_ptr<Boolean> b, shared_ptr<String> s) {
  return ToNumber(b) % ToNumber(s);
}

////////////////////////////////////////
// Left operands of type `Number`
shared_ptr<Number> operator % (shared_ptr<Number> n, Reference r) {
  return n % ToNumber(GetValue(r));
}
shared_ptr<Number> operator % (shared_ptr<Number> n, shared_ptr<Value> v) {
  return n % ToNumber(v);
}
shared_ptr<Number> operator % (shared_ptr<Number> n, shared_ptr<Object> o) {
  return n % ToNumber(o);
}
shared_ptr<Number> operator % (shared_ptr<Number> n, shared_ptr<Primitive> p) {
  return n % ToNumber(p);
}
shared_ptr<Number> operator % (shared_ptr<Number> n, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Number> n, shared_ptr<Null> x) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<Number> n, shared_ptr<Boolean> b) {
  return n % ToNumber(b);
}
shared_ptr<Number> operator % (shared_ptr<Number> dividend, shared_ptr<Number> divisor) {
  if (dividend->isNaN || divisor->isNaN) {
    return Number::makeNaN();
  }
  if (dividend->isInfinity) {
    return Number::makeNaN();
  }
  if (divisor->isInfinity) {
    return dividend;
  }
  if (dividend->value == 0) {
    return dividend;
  }
  if (divisor->value == 0) {
    Number::makeNaN();
  }
  return make_shared<Number>(fmod(dividend->value, divisor->value));
}
shared_ptr<Number> operator % (shared_ptr<Number> n, shared_ptr<String> s) {
  return n % ToNumber(s);
}

////////////////////////////////////////
// Left operands of type `String`
shared_ptr<Number> operator % (shared_ptr<String> s, Reference r) {
  return ToNumber(s) % ToNumber(GetValue(r));
}
shared_ptr<Number> operator % (shared_ptr<String> s, shared_ptr<Value> v) {
  return ToNumber(s) % ToNumber(v);
}
shared_ptr<Number> operator % (shared_ptr<String> s, shared_ptr<Object> o) {
  return ToNumber(s) % ToNumber(o);
}
shared_ptr<Number> operator % (shared_ptr<String> s, shared_ptr<Primitive> p) {
  return ToNumber(s) % ToNumber(p);
}
shared_ptr<Number> operator % (shared_ptr<String> s, shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<String> s, shared_ptr<Null> n) {
  return Number::makeNaN();
}
shared_ptr<Number> operator % (shared_ptr<String> s, shared_ptr<Boolean> b) {
  return ToNumber(s) % ToNumber(b);
}
shared_ptr<Number> operator % (shared_ptr<String> s, shared_ptr<Number> n) {
  return ToNumber(s) % n;
}
shared_ptr<Number> operator % (shared_ptr<String> a, shared_ptr<String> b) {
  return ToNumber(a) % ToNumber(b);
}

// End modulus operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Unary `-` operator overloads for every possible operand

shared_ptr<Number> operator - (Reference r) {
  return -GetValue(r);
}
shared_ptr<Number> operator - (shared_ptr<Value> v) {
  switch (v->type) {
    case UNDEFINED_VALUE_TYPE:
      return Number::makeNaN();
    case NULL_VALUE_TYPE:
      return make_shared<Number>(0, true);
    case BOOLEAN_VALUE_TYPE:
      return -static_pointer_cast<Boolean>(v);
    case NUMBER_VALUE_TYPE:
      return -static_pointer_cast<Number>(v);
    case STRING_VALUE_TYPE:
      return -ToNumber(static_pointer_cast<String>(v));
    case OBJECT_VALUE_TYPE:
      return -ToNumber(static_pointer_cast<Object>(v));
  }
}
shared_ptr<Number> operator - (shared_ptr<Object> o) {
  return -ToNumber(o);
}
shared_ptr<Number> operator - (shared_ptr<Primitive> p) {
  switch (p->type) {
    case UNDEFINED_VALUE_TYPE:
      return Number::makeNaN();
    case NULL_VALUE_TYPE:
      return make_shared<Number>(0, true);
    case BOOLEAN_VALUE_TYPE:
      return -static_pointer_cast<Boolean>(p);
    case NUMBER_VALUE_TYPE:
      return -static_pointer_cast<Number>(p);
    case STRING_VALUE_TYPE:
      return -ToNumber(static_pointer_cast<String>(p));
    case OBJECT_VALUE_TYPE:
      throw ImplementationException("an object was passed to operator-(Primitive)");
  }
}
shared_ptr<Number> operator - (shared_ptr<Undefined> u) {
  return Number::makeNaN();
}
shared_ptr<Number> operator - (shared_ptr<Null> n) {
  return make_shared<Number>(0, true);
}
shared_ptr<Number> operator - (shared_ptr<Boolean> b) {
  if (b->value) {
    return make_shared<Number>(1, true);
  } else {
    return make_shared<Number>(0, true);
  }
}
shared_ptr<Number> operator - (shared_ptr<Number> n) {
  if (n->isNaN) {
    return Number::makeNaN();
  }
  if (n->isInfinity) {
    return Number::makeInfinity(!n->isNegative);
  }
  if (n->value == 0) {
    return make_shared<Number>(0, !n->isNegative);
  }
  return make_shared<Number>(-n->value);
}
shared_ptr<Number> operator - (shared_ptr<String> s) {
  return -ToNumber(s);
}

// End unary `-` operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Logical NOT operator overloads for every possible operand

shared_ptr<Boolean> operator ! (Reference r) {
  return !GetValue(r);
}
shared_ptr<Boolean> operator ! (shared_ptr<Value> v) {
  switch (v->type) {
    case UNDEFINED_VALUE_TYPE:
      return make_shared<Boolean>(true);
    case NULL_VALUE_TYPE:
      return make_shared<Boolean>(true);
    case BOOLEAN_VALUE_TYPE:
      return make_shared<Boolean>(!static_pointer_cast<Boolean>(v)->value);
    case NUMBER_VALUE_TYPE:
      return !static_pointer_cast<Number>(v);
    case STRING_VALUE_TYPE:
      return !static_pointer_cast<String>(v);
    case OBJECT_VALUE_TYPE:
      return make_shared<Boolean>(false);
  }
}
shared_ptr<Boolean> operator ! (shared_ptr<Object> o) {
   return make_shared<Boolean>(false);
}
shared_ptr<Boolean> operator ! (shared_ptr<Primitive> p) {
  switch (p->type) {
    case UNDEFINED_VALUE_TYPE:
      return make_shared<Boolean>(true);
    case NULL_VALUE_TYPE:
      return make_shared<Boolean>(true);
    case BOOLEAN_VALUE_TYPE:
      return make_shared<Boolean>(!static_pointer_cast<Boolean>(p)->value);
    case NUMBER_VALUE_TYPE:
      return !static_pointer_cast<Number>(p);
    case STRING_VALUE_TYPE:
      return !static_pointer_cast<String>(p);
    case OBJECT_VALUE_TYPE:
      throw ImplementationException("an object was passed to operator!(Primitive)");
  }
}
shared_ptr<Boolean> operator ! (shared_ptr<Undefined> u) {
  return make_shared<Boolean>(true);
}
shared_ptr<Boolean> operator ! (shared_ptr<Null> n) {
  return make_shared<Boolean>(true);
}
shared_ptr<Boolean> operator ! (shared_ptr<Boolean> b) {
  return make_shared<Boolean>(!b->value);
}
shared_ptr<Boolean> operator ! (shared_ptr<Number> n) {
  if (n->isNaN)      return make_shared<Boolean>(true);
  if (n->isInfinity) return make_shared<Boolean>(false);
  if (n->value == 0) return make_shared<Boolean>(true);
  return make_shared<Boolean>(false);
}
shared_ptr<Boolean> operator ! (shared_ptr<String> s) {
  if (s->value == "") {
    return make_shared<Boolean>(true);
  } else {
    return make_shared<Boolean>(false);
  }
}

// End logical NOT operator overloads
////////////////////////////////////////////////////////////////////////////////

// End operator overloads
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
