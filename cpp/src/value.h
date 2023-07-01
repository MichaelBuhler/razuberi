#pragma once
#include "value.fwd.h"

#include "scope.fwd.h"
#include "scope.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

enum ValueType {
  UNDEFINED_VALUE_TYPE,
  NULL_VALUE_TYPE,
  BOOLEAN_VALUE_TYPE,
  STRING_VALUE_TYPE,
  NUMBER_VALUE_TYPE,
  OBJECT_VALUE_TYPE,
  REFERENCE_VALUE_TYPE
};

enum HintValueType {
  NONE_HINT_VALUE_TYPE,
  STRING_HINT_VALUE_TYPE,
  NUMBER_HINT_VALUE_TYPE
};

class Value {
  public: ValueType type;
  public: Value ();
};

class Primitive : public Value {
  public: Primitive ();
};

class Undefined : public Primitive {
  public: Undefined ();
};

class Null : public Primitive {
  public: Null ();
};

class Boolean : public Primitive {
  public: bool value;
  public: Boolean (bool value);
  // TODO: #3: can we overload the bool() operator to cast this?
  // public: operator bool ();
};

class Number : public Primitive {
  public: double value;
  public: bool isNaN;
  public: bool isInfinity;
  public: bool isNegative;
  public: Number (double value = 0, bool isNegative = false);
  public: static std::shared_ptr<Number> makeNaN();
  public: static std::shared_ptr<Number> makeInfinity(bool isNegative = false);
  public: std::shared_ptr<Number> plus (std::shared_ptr<Number> b);
  public: std::shared_ptr<Number> minus (std::shared_ptr<Number> b);
};

class String : public Primitive {
  public: std::string value;
  public: String (std::string value);
};

// TODO: #4: can we cast a `string` where a `shared_ptr<String>` is expected??? big if true.
// template <class _CharT,
//           class _Traits = std::char_traits<_CharT>,
//           class _Allocator = std::allocator<_CharT> >
//     class _LIBCPP_TEMPLATE_VIS basic_string {
//   public: operator std::shared_ptr<String> ();
// };

class Object : public Value {
  private: typedef std::shared_ptr<Value> (*Call)(std::shared_ptr<Value> _this, std::shared_ptr<Scope> scope, std::vector<std::shared_ptr<Value> > params);
  private: typedef std::shared_ptr<Object> (*Construct)(std::shared_ptr<Object> _this, std::shared_ptr<Scope> scope, std::vector<std::shared_ptr<Value> > params);
  private: class Property {
    public: std::shared_ptr<Value> value;
    public: bool ReadOnly;
    public: bool DontEnum;
    public: bool DontDelete;
    // public: bool Internal; // TODO: not sure how this is used
  };
  private: std::map<std::string, std::shared_ptr<Property> > properties;
  public: Object (std::shared_ptr<Object> prototype = nullptr, Call call = nullptr, Construct construct = nullptr);

  private: std::shared_ptr<Object> __Prototype__;
  public: std::string __Class__;
  public: std::shared_ptr<Value> __Value__;
  public: std::shared_ptr<Value> __Get__ (std::string key);
  public: void __Put__ (std::string key, std::shared_ptr<Value> value);
  public: bool __HasProperty__ (std::string key);
  public: Construct __Construct__;
  public: Call __Call__;
};

class Internal : public Value {
  public: Internal ();
};

class Reference : public Internal {
  public: std::shared_ptr<Value> baseObject;
  public: std::shared_ptr<String> propertyName;
  public: Reference (std::shared_ptr<Value> baseObject, std::shared_ptr<String> propertyName);
};

std::shared_ptr<Reference> operator ->* (std::shared_ptr<Value> value, std::string name);

////////////////////////////////////////////////////////////////////////////////
// Additive operater overloads for every combination of additive operands

////////////////////////////////////////
// `Reference` type left operands
std::shared_ptr<Value>  operator + (std::shared_ptr<Reference>, std::shared_ptr<Reference>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Reference>, std::shared_ptr<Value>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Reference>, std::shared_ptr<Object>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Reference>, std::shared_ptr<Primitive>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Reference>, std::shared_ptr<Undefined>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Reference>, std::shared_ptr<Null>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Reference>, std::shared_ptr<Boolean>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Reference>, std::shared_ptr<Number>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Reference>, std::shared_ptr<String>);

////////////////////////////////////////
// `Value` type left operands
std::shared_ptr<Value>  operator + (std::shared_ptr<Value>, std::shared_ptr<Reference>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Value>, std::shared_ptr<Value>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Value>, std::shared_ptr<Object>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Value>, std::shared_ptr<Primitive>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Value>, std::shared_ptr<Undefined>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Value>, std::shared_ptr<Null>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Value>, std::shared_ptr<Boolean>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Value>, std::shared_ptr<Number>);
std::shared_ptr<String> operator + (std::shared_ptr<Value>, std::shared_ptr<String>);

////////////////////////////////////////
// `Object` type left operands
std::shared_ptr<Value>  operator + (std::shared_ptr<Object>, std::shared_ptr<Reference>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Object>, std::shared_ptr<Value>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Object>, std::shared_ptr<Object>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Object>, std::shared_ptr<Primitive>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Object>, std::shared_ptr<Undefined>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Object>, std::shared_ptr<Null>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Object>, std::shared_ptr<Boolean>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Object>, std::shared_ptr<Number>);
std::shared_ptr<String> operator + (std::shared_ptr<Object>, std::shared_ptr<String>);

////////////////////////////////////////
// `Primitive` type left operands
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, std::shared_ptr<Reference>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, std::shared_ptr<Value>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, std::shared_ptr<Object>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, std::shared_ptr<Primitive>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, std::shared_ptr<Undefined>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, std::shared_ptr<Null>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, std::shared_ptr<Boolean>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, std::shared_ptr<Number>);
std::shared_ptr<String> operator + (std::shared_ptr<Primitive>, std::shared_ptr<String>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, std::shared_ptr<Object>);

////////////////////////////////////////
// `Undefined` type left operands
std::shared_ptr<Value>  operator + (std::shared_ptr<Undefined>, std::shared_ptr<Reference>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Undefined>, std::shared_ptr<Value>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Undefined>, std::shared_ptr<Object>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Undefined>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator + (std::shared_ptr<Undefined>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator + (std::shared_ptr<Undefined>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator + (std::shared_ptr<Undefined>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator + (std::shared_ptr<Undefined>, std::shared_ptr<Number>);
std::shared_ptr<String> operator + (std::shared_ptr<Undefined>, std::shared_ptr<String>);

////////////////////////////////////////
// `Null` type left operands
std::shared_ptr<Value>  operator + (std::shared_ptr<Null>, std::shared_ptr<Reference>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Null>, std::shared_ptr<Value>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Null>, std::shared_ptr<Object>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Null>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator + (std::shared_ptr<Null>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator + (std::shared_ptr<Null>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator + (std::shared_ptr<Null>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator + (std::shared_ptr<Null>, std::shared_ptr<Number>);
std::shared_ptr<String> operator + (std::shared_ptr<Null>, std::shared_ptr<String>);

////////////////////////////////////////
// `Boolean` type left operands
std::shared_ptr<Value>  operator + (std::shared_ptr<Boolean>, std::shared_ptr<Reference>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Boolean>, std::shared_ptr<Value>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Boolean>, std::shared_ptr<Object>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Boolean>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator + (std::shared_ptr<Boolean>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator + (std::shared_ptr<Boolean>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator + (std::shared_ptr<Boolean>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator + (std::shared_ptr<Boolean>, std::shared_ptr<Number>);
std::shared_ptr<String> operator + (std::shared_ptr<Boolean>, std::shared_ptr<String>);

////////////////////////////////////////
// `Number` type left operands
std::shared_ptr<Value>  operator + (std::shared_ptr<Number>, std::shared_ptr<Reference>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Number>, std::shared_ptr<Value>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Number>, std::shared_ptr<Object>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Number>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator + (std::shared_ptr<Number>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator + (std::shared_ptr<Number>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator + (std::shared_ptr<Number>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator + (std::shared_ptr<Number>, std::shared_ptr<Number>);
std::shared_ptr<String> operator + (std::shared_ptr<Number>, std::shared_ptr<String>);

////////////////////////////////////////
// `String` type left operands
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<Reference>);
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<Value>);
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<Object>);
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<Primitive>);
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<Undefined>);
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<Null>);
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<Boolean>);
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<Number>);
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<String>);

// End additive operator overloads
////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<Value> operator - (std::shared_ptr<Value>, std::shared_ptr<Value>);
