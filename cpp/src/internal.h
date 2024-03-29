#pragma once

#include <memory>
#include <vector>

#include "scope.h"
#include "value.h"

// Used for constructing user-defined script functions, at runtime.
std::shared_ptr<Object> _fn (std::shared_ptr<Scope> closure, Object::CallSignature __Call_and_Construct__);

// Used for constructing other, regular, sorts of Objects.
std::shared_ptr<Object> _new (Reference constructor);
std::shared_ptr<Object> _new (Reference constructor, Reference firstParam);
std::shared_ptr<Object> _new (Reference constructor, std::shared_ptr<Value> firstParam);
std::shared_ptr<Object> _new (Reference constructor, std::vector<std::shared_ptr<Value> > params);
std::shared_ptr<Object> _new (std::shared_ptr<Value> constructor);
std::shared_ptr<Object> _new (std::shared_ptr<Value> constructor, Reference firstParam);
std::shared_ptr<Object> _new (std::shared_ptr<Value> constructor, std::shared_ptr<Value> firstParam);
std::shared_ptr<Object> _new (std::shared_ptr<Value> constructor, std::vector<std::shared_ptr<Value> > params);

// Same as above, but static cast it to a `Value` so you can throw it
std::shared_ptr<Value> _newThrowable (Reference constructor);
std::shared_ptr<Value> _newThrowable (Reference constructor, Reference firstParam);
std::shared_ptr<Value> _newThrowable (Reference constructor, std::shared_ptr<Value> firstParam);
std::shared_ptr<Value> _newThrowable (Reference constructor, std::vector<std::shared_ptr<Value> > params);
std::shared_ptr<Value> _newThrowable (std::shared_ptr<Value> constructor);
std::shared_ptr<Value> _newThrowable (std::shared_ptr<Value> constructor, Reference firstParam);
std::shared_ptr<Value> _newThrowable (std::shared_ptr<Value> constructor, std::shared_ptr<Value> firstParam);
std::shared_ptr<Value> _newThrowable (std::shared_ptr<Value> constructor, std::vector<std::shared_ptr<Value> > params);

// TODO: due to limitations workgin with `std::shared_ptr` this Object method has been implemented functionally
std::shared_ptr<Value> __DefaultValue__ (std::shared_ptr<Object> _this, HintValueType);

// C++ does not have a `===` operator to overload, so this is implemented functionally
// TODO: could be implemented with 81 overloads
std::shared_ptr<Boolean> _strictEquals (Reference, Reference);
std::shared_ptr<Boolean> _strictEquals (Reference, std::shared_ptr<Value>);
std::shared_ptr<Boolean> _strictEquals (std::shared_ptr<Value>, Reference);
std::shared_ptr<Boolean> _strictEquals (std::shared_ptr<Value>, std::shared_ptr<Value>);

// C++ does not have a `!==` operator to overload, so this is implemented functionally
// TODO: could be implemented with 81 overloads
std::shared_ptr<Boolean> _strictNotEquals (Reference, Reference);
std::shared_ptr<Boolean> _strictNotEquals (Reference, std::shared_ptr<Value>);
std::shared_ptr<Boolean> _strictNotEquals (std::shared_ptr<Value>, Reference);
std::shared_ptr<Boolean> _strictNotEquals (std::shared_ptr<Value>, std::shared_ptr<Value>);

// a common sub-algorithm of control statement evaluation is coersion to a boolean
// by further converting the value to a C++ bool, we can re-use C++ control statements
bool _test (Reference);
bool _test (std::shared_ptr<Value>);
bool _test (std::shared_ptr<Undefined>);
bool _test (std::shared_ptr<Null>);
bool _test (std::shared_ptr<Boolean>);
bool _test (std::shared_ptr<Number>);
bool _test (std::shared_ptr<String>);
bool _test (std::shared_ptr<Object>);

// C++ does not have a `typeof` operator to overload, so this is implemented functionally
std::shared_ptr<String> _typeof (Reference);
std::shared_ptr<String> _typeof (std::shared_ptr<Value>);

// C++ does not have a `void` operator to overload, and `void` is a keyword, so this is implemented functionally
std::shared_ptr<Undefined> _void (Reference);
std::shared_ptr<Undefined> _void (std::shared_ptr<Value>);

// C++ does not have an `instanceof` operator to overload, so this is implemented functionally
std::shared_ptr<Boolean> _instanceOf (Reference, Reference);
std::shared_ptr<Boolean> _instanceOf (Reference, std::shared_ptr<Value>);
std::shared_ptr<Boolean> _instanceOf (std::shared_ptr<Value>, Reference);
std::shared_ptr<Boolean> _instanceOf (std::shared_ptr<Value>, std::shared_ptr<Value>);

// C++ does not have an `in` operator to overload, so this is implemented functionally
std::shared_ptr<Boolean> _in (Reference, Reference);
std::shared_ptr<Boolean> _in (Reference, std::shared_ptr<Value>);
std::shared_ptr<Boolean> _in (std::shared_ptr<Value>, Reference);
std::shared_ptr<Boolean> _in (std::shared_ptr<Value>, std::shared_ptr<Value>);
