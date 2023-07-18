#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "scope.fwd.h"

enum ValueType {
  UNDEFINED_VALUE_TYPE,
  NULL_VALUE_TYPE,
  BOOLEAN_VALUE_TYPE,
  STRING_VALUE_TYPE,
  NUMBER_VALUE_TYPE,
  OBJECT_VALUE_TYPE,
};

enum HintValueType {
  NONE_HINT_VALUE_TYPE,
  STRING_HINT_VALUE_TYPE,
  NUMBER_HINT_VALUE_TYPE,
};

// Forward declarations of class(es) in this file
class Value;
class String;
class Object;

// TODO: move this to "internal.h"?
class Reference {
  public: std::shared_ptr<Value> baseObject;
  public: std::shared_ptr<String> propertyName;
  public: Reference (std::shared_ptr<Value> baseObject, std::shared_ptr<String> propertyName);
  public: std::shared_ptr<Value> call ();
  public: std::shared_ptr<Value> call (Reference firstParam);
  public: std::shared_ptr<Value> call (std::shared_ptr<Value> firstParam);
  public: std::shared_ptr<Value> call (std::vector<std::shared_ptr<Value> > params);
  public: Reference operator = (Reference rightHandSide);
  public: Reference operator = (std::shared_ptr<Value> rightHandSide);
  public: Reference operator ->* (std::string identifier);
  // TODO: fun for later
  // public: std::shared_ptr<Value> operator () ();
  // public: std::shared_ptr<Value> operator () (Reference firstParam);
  // public: std::shared_ptr<Value> operator () (std::shared_ptr<Value> firstParam);
  // public: std::shared_ptr<Value> operator () (std::vector<std::shared_ptr<Value> > params);
};

class Value {
  public: ValueType type;
  public: Value ();

  // Entry point for constructing an instance of this Value
  public: virtual std::shared_ptr<Object> construct (std::vector<std::shared_ptr<Value> > params);

  // Entry points for the invocation of this Value as a function
  public: virtual std::shared_ptr<Value> call ();
  public: virtual std::shared_ptr<Value> call (Reference firstParam);
  public: virtual std::shared_ptr<Value> call (std::shared_ptr<Value> firstParam);
  public: virtual std::shared_ptr<Value> call (std::vector<std::shared_ptr<Value> > params);
  public: virtual std::shared_ptr<Value> call (std::shared_ptr<Value> _this, std::vector<std::shared_ptr<Value> > params);

  // Razuberi internal helpers
  public: virtual bool isFunction ();
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
  // Typedefs
  // Define the function interface for a call signature
  public: typedef std::shared_ptr<Value> (*CallSignature)(std::shared_ptr<Scope> scope, std::shared_ptr<Value> _this, std::vector<std::shared_ptr<Value> > params);

  // Friends
  // Allow the Razuberi internal `init_builtin_prototypes` to access the private members of this class
  friend void init_builtin_prototypes (std::shared_ptr<Scope> globalScope);

  // The original Object prototype object.
  public: static std::shared_ptr<Object> Object_prototype;
  // The original Function prototype object.
  public: static std::shared_ptr<Object> Function_prototype;
  // The original String prototype object.
  public: static std::shared_ptr<Object> String_prototype;
  // The original Boolean prototype object.
  public: static std::shared_ptr<Object> Boolean_prototype;

  // Inner class to hold property attributes
  // TODO: can be a simple struct?
  public: class Property {
    public: std::shared_ptr<Value> value;
    public: bool ReadOnly;
    public: bool DontEnum;
    public: bool DontDelete;
  };
  
  // TODO: map values can be Property instead of shared_ptr<Property>
  public: std::map<std::string, std::shared_ptr<Property> > properties;

  // Additional special members used only by function objects.
  private: std::shared_ptr<Scope> closure;

  // Constructor for instantiating an Object in-line
  public: Object (std::shared_ptr<Object> __Prototype__ = Object_prototype);

  // The "Internal" properties of objects.
  private: std::shared_ptr<Object> __Prototype__;
  public: std::string __Class__;
  public: std::shared_ptr<Value> __Value__;
  public: std::shared_ptr<Value> __Get__ (std::string key);
  public: void __Put__ (std::string key, std::shared_ptr<Value> value);
  public: bool __HasProperty__ (std::string key);
  private: CallSignature __Construct__;
  private: CallSignature __Call__;

  // Entry point for constructing an instance of this Object
  public: std::shared_ptr<Object> construct (std::vector<std::shared_ptr<Value> > params);

  // Entry points for the invocation of this Object as a function
  public: std::shared_ptr<Value> call ();
  public: std::shared_ptr<Value> call (Reference firstParam);
  public: std::shared_ptr<Value> call (std::shared_ptr<Value> firstParam);
  public: std::shared_ptr<Value> call (std::vector<std::shared_ptr<Value> > params);
  public: std::shared_ptr<Value> call (std::shared_ptr<Value> _this, std::vector<std::shared_ptr<Value> > params);

  // Static factory functions
  public: static std::shared_ptr<Object> makeFunction (CallSignature __Call__, CallSignature __Construct__ = nullptr, std::shared_ptr<Object> prototype = nullptr, std::shared_ptr<Scope> closure = nullptr);

  // Razuberi internal helpers
  public: bool isConstructor ();
  public: bool isFunction ();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operator overloads

////////////////////////////////////////////////////////////////////////////////
// Pointer-to-member operator overloads for member expressions

// Accessing a property by `Identifier`
Reference operator ->* (std::shared_ptr<Value> value, std::string name);
Reference operator ->* (std::shared_ptr<Object> obj, std::string name);

// End pointer-to-member operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Comma operator overloads for arguments lists

// create a `vector`/`List` from two arguments
std::vector<std::shared_ptr<Value> > operator , (Reference, Reference);
std::vector<std::shared_ptr<Value> > operator , (Reference, std::shared_ptr<Value>);
std::vector<std::shared_ptr<Value> > operator , (std::shared_ptr<Value>, Reference);
std::vector<std::shared_ptr<Value> > operator , (std::shared_ptr<Value>, std::shared_ptr<Value>);

// append another argument onto a `vector`/`List`
std::vector<std::shared_ptr<Value> > operator , (std::vector<std::shared_ptr<Value> >, Reference);
std::vector<std::shared_ptr<Value> > operator , (std::vector<std::shared_ptr<Value> >, std::shared_ptr<Value>);

// End comma operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Bitwise operator overloads for object literals/initializers/expressions

// create an object from a propery name and a value
std::shared_ptr<Object> operator & (std::string, Reference);
std::shared_ptr<Object> operator & (std::string, std::shared_ptr<Value>);

// merge right object into left one
std::shared_ptr<Object> operator | (std::shared_ptr<Object>, std::shared_ptr<Object>);

// End bitwise operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Addition operator overloads for every combination of addition operands

////////////////////////////////////////
// Left operands of type `Reference`
std::shared_ptr<Value>  operator + (Reference, Reference);
std::shared_ptr<Value>  operator + (Reference, std::shared_ptr<Value>);
std::shared_ptr<Value>  operator + (Reference, std::shared_ptr<Object>);
std::shared_ptr<Value>  operator + (Reference, std::shared_ptr<Primitive>);
std::shared_ptr<Value>  operator + (Reference, std::shared_ptr<Undefined>);
std::shared_ptr<Value>  operator + (Reference, std::shared_ptr<Null>);
std::shared_ptr<Value>  operator + (Reference, std::shared_ptr<Boolean>);
std::shared_ptr<Value>  operator + (Reference, std::shared_ptr<Number>);
std::shared_ptr<Value>  operator + (Reference, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Value`
std::shared_ptr<Value>  operator + (std::shared_ptr<Value>, Reference);
std::shared_ptr<Value>  operator + (std::shared_ptr<Value>, std::shared_ptr<Value>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Value>, std::shared_ptr<Object>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Value>, std::shared_ptr<Primitive>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Value>, std::shared_ptr<Undefined>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Value>, std::shared_ptr<Null>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Value>, std::shared_ptr<Boolean>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Value>, std::shared_ptr<Number>);
std::shared_ptr<String> operator + (std::shared_ptr<Value>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Object`
std::shared_ptr<Value>  operator + (std::shared_ptr<Object>, Reference);
std::shared_ptr<Value>  operator + (std::shared_ptr<Object>, std::shared_ptr<Value>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Object>, std::shared_ptr<Object>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Object>, std::shared_ptr<Primitive>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Object>, std::shared_ptr<Undefined>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Object>, std::shared_ptr<Null>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Object>, std::shared_ptr<Boolean>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Object>, std::shared_ptr<Number>);
std::shared_ptr<String> operator + (std::shared_ptr<Object>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Primitive`
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, Reference);
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, std::shared_ptr<Value>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, std::shared_ptr<Object>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, std::shared_ptr<Primitive>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, std::shared_ptr<Undefined>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, std::shared_ptr<Null>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, std::shared_ptr<Boolean>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Primitive>, std::shared_ptr<Number>);
std::shared_ptr<String> operator + (std::shared_ptr<Primitive>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Undefined`
std::shared_ptr<Value>  operator + (std::shared_ptr<Undefined>, Reference);
std::shared_ptr<Value>  operator + (std::shared_ptr<Undefined>, std::shared_ptr<Value>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Undefined>, std::shared_ptr<Object>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Undefined>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator + (std::shared_ptr<Undefined>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator + (std::shared_ptr<Undefined>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator + (std::shared_ptr<Undefined>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator + (std::shared_ptr<Undefined>, std::shared_ptr<Number>);
std::shared_ptr<String> operator + (std::shared_ptr<Undefined>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Null`
std::shared_ptr<Value>  operator + (std::shared_ptr<Null>, Reference);
std::shared_ptr<Value>  operator + (std::shared_ptr<Null>, std::shared_ptr<Value>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Null>, std::shared_ptr<Object>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Null>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator + (std::shared_ptr<Null>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator + (std::shared_ptr<Null>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator + (std::shared_ptr<Null>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator + (std::shared_ptr<Null>, std::shared_ptr<Number>);
std::shared_ptr<String> operator + (std::shared_ptr<Null>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Boolean`
std::shared_ptr<Value>  operator + (std::shared_ptr<Boolean>, Reference);
std::shared_ptr<Value>  operator + (std::shared_ptr<Boolean>, std::shared_ptr<Value>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Boolean>, std::shared_ptr<Object>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Boolean>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator + (std::shared_ptr<Boolean>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator + (std::shared_ptr<Boolean>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator + (std::shared_ptr<Boolean>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator + (std::shared_ptr<Boolean>, std::shared_ptr<Number>);
std::shared_ptr<String> operator + (std::shared_ptr<Boolean>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Number`
std::shared_ptr<Value>  operator + (std::shared_ptr<Number>, Reference);
std::shared_ptr<Value>  operator + (std::shared_ptr<Number>, std::shared_ptr<Value>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Number>, std::shared_ptr<Object>);
std::shared_ptr<Value>  operator + (std::shared_ptr<Number>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator + (std::shared_ptr<Number>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator + (std::shared_ptr<Number>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator + (std::shared_ptr<Number>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator + (std::shared_ptr<Number>, std::shared_ptr<Number>);
std::shared_ptr<String> operator + (std::shared_ptr<Number>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `String`
std::shared_ptr<String> operator + (std::shared_ptr<String>, Reference);
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<Value>);
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<Object>);
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<Primitive>);
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<Undefined>);
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<Null>);
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<Boolean>);
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<Number>);
std::shared_ptr<String> operator + (std::shared_ptr<String>, std::shared_ptr<String>);

// End addition operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Subtraction operator overloads for every combination of subtraction operands
// TODO: implement the rest of them

std::shared_ptr<Value> operator - (std::shared_ptr<Value>, std::shared_ptr<Value>);

// End subtraction operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Double equals operator overloads for every combination of operands

////////////////////////////////////////
// Left operands of type `Reference`
std::shared_ptr<Boolean> operator == (Reference, Reference);
std::shared_ptr<Boolean> operator == (Reference, std::shared_ptr<Value>);
std::shared_ptr<Boolean> operator == (Reference, std::shared_ptr<Object>);
std::shared_ptr<Boolean> operator == (Reference, std::shared_ptr<Primitive>);
std::shared_ptr<Boolean> operator == (Reference, std::shared_ptr<Undefined>);
std::shared_ptr<Boolean> operator == (Reference, std::shared_ptr<Null>);
std::shared_ptr<Boolean> operator == (Reference, std::shared_ptr<Boolean>);
std::shared_ptr<Boolean> operator == (Reference, std::shared_ptr<Number>);
std::shared_ptr<Boolean> operator == (Reference, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Value`
std::shared_ptr<Boolean> operator == (std::shared_ptr<Value>, Reference);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Value>, std::shared_ptr<Value>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Value>, std::shared_ptr<Object>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Value>, std::shared_ptr<Primitive>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Value>, std::shared_ptr<Undefined>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Value>, std::shared_ptr<Null>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Value>, std::shared_ptr<Boolean>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Value>, std::shared_ptr<Number>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Value>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Object`
std::shared_ptr<Boolean> operator == (std::shared_ptr<Object>, Reference);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Object>, std::shared_ptr<Value>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Object>, std::shared_ptr<Object>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Object>, std::shared_ptr<Primitive>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Object>, std::shared_ptr<Undefined>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Object>, std::shared_ptr<Null>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Object>, std::shared_ptr<Boolean>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Object>, std::shared_ptr<Number>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Object>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Primitive`
std::shared_ptr<Boolean> operator == (std::shared_ptr<Primitive>, Reference);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Primitive>, std::shared_ptr<Value>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Primitive>, std::shared_ptr<Object>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Primitive>, std::shared_ptr<Primitive>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Primitive>, std::shared_ptr<Undefined>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Primitive>, std::shared_ptr<Null>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Primitive>, std::shared_ptr<Boolean>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Primitive>, std::shared_ptr<Number>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Primitive>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Undefined`
std::shared_ptr<Boolean> operator == (std::shared_ptr<Undefined>, Reference);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Undefined>, std::shared_ptr<Value>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Undefined>, std::shared_ptr<Object>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Undefined>, std::shared_ptr<Primitive>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Undefined>, std::shared_ptr<Undefined>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Undefined>, std::shared_ptr<Null>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Undefined>, std::shared_ptr<Boolean>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Undefined>, std::shared_ptr<Number>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Undefined>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Null`
std::shared_ptr<Boolean> operator == (std::shared_ptr<Null>, Reference);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Null>, std::shared_ptr<Value>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Null>, std::shared_ptr<Object>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Null>, std::shared_ptr<Primitive>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Null>, std::shared_ptr<Undefined>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Null>, std::shared_ptr<Null>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Null>, std::shared_ptr<Boolean>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Null>, std::shared_ptr<Number>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Null>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Boolean`
std::shared_ptr<Boolean> operator == (std::shared_ptr<Boolean>, Reference);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Boolean>, std::shared_ptr<Value>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Boolean>, std::shared_ptr<Object>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Boolean>, std::shared_ptr<Primitive>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Boolean>, std::shared_ptr<Undefined>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Boolean>, std::shared_ptr<Null>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Boolean>, std::shared_ptr<Boolean>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Boolean>, std::shared_ptr<Number>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Boolean>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Number`
std::shared_ptr<Boolean> operator == (std::shared_ptr<Number>, Reference);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Number>, std::shared_ptr<Value>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Number>, std::shared_ptr<Object>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Number>, std::shared_ptr<Primitive>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Number>, std::shared_ptr<Undefined>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Number>, std::shared_ptr<Null>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Number>, std::shared_ptr<Boolean>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Number>, std::shared_ptr<Number>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<Number>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `String`
std::shared_ptr<Boolean> operator == (std::shared_ptr<String>, Reference);
std::shared_ptr<Boolean> operator == (std::shared_ptr<String>, std::shared_ptr<Value>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<String>, std::shared_ptr<Object>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<String>, std::shared_ptr<Primitive>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<String>, std::shared_ptr<Undefined>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<String>, std::shared_ptr<Null>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<String>, std::shared_ptr<Boolean>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<String>, std::shared_ptr<Number>);
std::shared_ptr<Boolean> operator == (std::shared_ptr<String>, std::shared_ptr<String>);

// End double equals operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Division operator overloads for every combination of operands

////////////////////////////////////////
// Left operands of type `Reference`
std::shared_ptr<Number> operator / (Reference, Reference);
std::shared_ptr<Number> operator / (Reference, std::shared_ptr<Value>);
std::shared_ptr<Number> operator / (Reference, std::shared_ptr<Object>);
std::shared_ptr<Number> operator / (Reference, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator / (Reference, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator / (Reference, std::shared_ptr<Null>);
std::shared_ptr<Number> operator / (Reference, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator / (Reference, std::shared_ptr<Number>);
std::shared_ptr<Number> operator / (Reference, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Value`
std::shared_ptr<Number> operator / (std::shared_ptr<Value>, Reference);
std::shared_ptr<Number> operator / (std::shared_ptr<Value>, std::shared_ptr<Value>);
std::shared_ptr<Number> operator / (std::shared_ptr<Value>, std::shared_ptr<Object>);
std::shared_ptr<Number> operator / (std::shared_ptr<Value>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator / (std::shared_ptr<Value>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator / (std::shared_ptr<Value>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator / (std::shared_ptr<Value>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator / (std::shared_ptr<Value>, std::shared_ptr<Number>);
std::shared_ptr<Number> operator / (std::shared_ptr<Value>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Object`
std::shared_ptr<Number> operator / (std::shared_ptr<Object>, Reference);
std::shared_ptr<Number> operator / (std::shared_ptr<Object>, std::shared_ptr<Value>);
std::shared_ptr<Number> operator / (std::shared_ptr<Object>, std::shared_ptr<Object>);
std::shared_ptr<Number> operator / (std::shared_ptr<Object>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator / (std::shared_ptr<Object>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator / (std::shared_ptr<Object>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator / (std::shared_ptr<Object>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator / (std::shared_ptr<Object>, std::shared_ptr<Number>);
std::shared_ptr<Number> operator / (std::shared_ptr<Object>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Primitive`
std::shared_ptr<Number> operator / (std::shared_ptr<Primitive>, Reference);
std::shared_ptr<Number> operator / (std::shared_ptr<Primitive>, std::shared_ptr<Value>);
std::shared_ptr<Number> operator / (std::shared_ptr<Primitive>, std::shared_ptr<Object>);
std::shared_ptr<Number> operator / (std::shared_ptr<Primitive>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator / (std::shared_ptr<Primitive>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator / (std::shared_ptr<Primitive>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator / (std::shared_ptr<Primitive>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator / (std::shared_ptr<Primitive>, std::shared_ptr<Number>);
std::shared_ptr<Number> operator / (std::shared_ptr<Primitive>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Undefined`
std::shared_ptr<Number> operator / (std::shared_ptr<Undefined>, Reference);
std::shared_ptr<Number> operator / (std::shared_ptr<Undefined>, std::shared_ptr<Value>);
std::shared_ptr<Number> operator / (std::shared_ptr<Undefined>, std::shared_ptr<Object>);
std::shared_ptr<Number> operator / (std::shared_ptr<Undefined>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator / (std::shared_ptr<Undefined>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator / (std::shared_ptr<Undefined>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator / (std::shared_ptr<Undefined>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator / (std::shared_ptr<Undefined>, std::shared_ptr<Number>);
std::shared_ptr<Number> operator / (std::shared_ptr<Undefined>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Null`
std::shared_ptr<Number> operator / (std::shared_ptr<Null>, Reference);
std::shared_ptr<Number> operator / (std::shared_ptr<Null>, std::shared_ptr<Value>);
std::shared_ptr<Number> operator / (std::shared_ptr<Null>, std::shared_ptr<Object>);
std::shared_ptr<Number> operator / (std::shared_ptr<Null>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator / (std::shared_ptr<Null>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator / (std::shared_ptr<Null>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator / (std::shared_ptr<Null>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator / (std::shared_ptr<Null>, std::shared_ptr<Number>);
std::shared_ptr<Number> operator / (std::shared_ptr<Null>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Boolean`
std::shared_ptr<Number> operator / (std::shared_ptr<Boolean>, Reference);
std::shared_ptr<Number> operator / (std::shared_ptr<Boolean>, std::shared_ptr<Value>);
std::shared_ptr<Number> operator / (std::shared_ptr<Boolean>, std::shared_ptr<Object>);
std::shared_ptr<Number> operator / (std::shared_ptr<Boolean>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator / (std::shared_ptr<Boolean>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator / (std::shared_ptr<Boolean>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator / (std::shared_ptr<Boolean>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator / (std::shared_ptr<Boolean>, std::shared_ptr<Number>);
std::shared_ptr<Number> operator / (std::shared_ptr<Boolean>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Number`
std::shared_ptr<Number> operator / (std::shared_ptr<Number>, Reference);
std::shared_ptr<Number> operator / (std::shared_ptr<Number>, std::shared_ptr<Value>);
std::shared_ptr<Number> operator / (std::shared_ptr<Number>, std::shared_ptr<Object>);
std::shared_ptr<Number> operator / (std::shared_ptr<Number>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator / (std::shared_ptr<Number>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator / (std::shared_ptr<Number>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator / (std::shared_ptr<Number>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator / (std::shared_ptr<Number>, std::shared_ptr<Number>);
std::shared_ptr<Number> operator / (std::shared_ptr<Number>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `String`
std::shared_ptr<Number> operator / (std::shared_ptr<String>, Reference);
std::shared_ptr<Number> operator / (std::shared_ptr<String>, std::shared_ptr<Value>);
std::shared_ptr<Number> operator / (std::shared_ptr<String>, std::shared_ptr<Object>);
std::shared_ptr<Number> operator / (std::shared_ptr<String>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator / (std::shared_ptr<String>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator / (std::shared_ptr<String>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator / (std::shared_ptr<String>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator / (std::shared_ptr<String>, std::shared_ptr<Number>);
std::shared_ptr<Number> operator / (std::shared_ptr<String>, std::shared_ptr<String>);

// End division operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Modulus operator overloads for every combination of operands

////////////////////////////////////////
// Left operands of type `Reference`
std::shared_ptr<Number> operator % (Reference, Reference);
std::shared_ptr<Number> operator % (Reference, std::shared_ptr<Value>);
std::shared_ptr<Number> operator % (Reference, std::shared_ptr<Object>);
std::shared_ptr<Number> operator % (Reference, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator % (Reference, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator % (Reference, std::shared_ptr<Null>);
std::shared_ptr<Number> operator % (Reference, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator % (Reference, std::shared_ptr<Number>);
std::shared_ptr<Number> operator % (Reference, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Value`
std::shared_ptr<Number> operator % (std::shared_ptr<Value>, Reference);
std::shared_ptr<Number> operator % (std::shared_ptr<Value>, std::shared_ptr<Value>);
std::shared_ptr<Number> operator % (std::shared_ptr<Value>, std::shared_ptr<Object>);
std::shared_ptr<Number> operator % (std::shared_ptr<Value>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator % (std::shared_ptr<Value>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator % (std::shared_ptr<Value>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator % (std::shared_ptr<Value>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator % (std::shared_ptr<Value>, std::shared_ptr<Number>);
std::shared_ptr<Number> operator % (std::shared_ptr<Value>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Object`
std::shared_ptr<Number> operator % (std::shared_ptr<Object>, Reference);
std::shared_ptr<Number> operator % (std::shared_ptr<Object>, std::shared_ptr<Value>);
std::shared_ptr<Number> operator % (std::shared_ptr<Object>, std::shared_ptr<Object>);
std::shared_ptr<Number> operator % (std::shared_ptr<Object>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator % (std::shared_ptr<Object>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator % (std::shared_ptr<Object>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator % (std::shared_ptr<Object>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator % (std::shared_ptr<Object>, std::shared_ptr<Number>);
std::shared_ptr<Number> operator % (std::shared_ptr<Object>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Primitive`
std::shared_ptr<Number> operator % (std::shared_ptr<Primitive>, Reference);
std::shared_ptr<Number> operator % (std::shared_ptr<Primitive>, std::shared_ptr<Value>);
std::shared_ptr<Number> operator % (std::shared_ptr<Primitive>, std::shared_ptr<Object>);
std::shared_ptr<Number> operator % (std::shared_ptr<Primitive>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator % (std::shared_ptr<Primitive>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator % (std::shared_ptr<Primitive>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator % (std::shared_ptr<Primitive>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator % (std::shared_ptr<Primitive>, std::shared_ptr<Number>);
std::shared_ptr<Number> operator % (std::shared_ptr<Primitive>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Undefined`
std::shared_ptr<Number> operator % (std::shared_ptr<Undefined>, Reference);
std::shared_ptr<Number> operator % (std::shared_ptr<Undefined>, std::shared_ptr<Value>);
std::shared_ptr<Number> operator % (std::shared_ptr<Undefined>, std::shared_ptr<Object>);
std::shared_ptr<Number> operator % (std::shared_ptr<Undefined>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator % (std::shared_ptr<Undefined>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator % (std::shared_ptr<Undefined>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator % (std::shared_ptr<Undefined>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator % (std::shared_ptr<Undefined>, std::shared_ptr<Number>);
std::shared_ptr<Number> operator % (std::shared_ptr<Undefined>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Null`
std::shared_ptr<Number> operator % (std::shared_ptr<Null>, Reference);
std::shared_ptr<Number> operator % (std::shared_ptr<Null>, std::shared_ptr<Value>);
std::shared_ptr<Number> operator % (std::shared_ptr<Null>, std::shared_ptr<Object>);
std::shared_ptr<Number> operator % (std::shared_ptr<Null>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator % (std::shared_ptr<Null>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator % (std::shared_ptr<Null>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator % (std::shared_ptr<Null>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator % (std::shared_ptr<Null>, std::shared_ptr<Number>);
std::shared_ptr<Number> operator % (std::shared_ptr<Null>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Boolean`
std::shared_ptr<Number> operator % (std::shared_ptr<Boolean>, Reference);
std::shared_ptr<Number> operator % (std::shared_ptr<Boolean>, std::shared_ptr<Value>);
std::shared_ptr<Number> operator % (std::shared_ptr<Boolean>, std::shared_ptr<Object>);
std::shared_ptr<Number> operator % (std::shared_ptr<Boolean>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator % (std::shared_ptr<Boolean>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator % (std::shared_ptr<Boolean>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator % (std::shared_ptr<Boolean>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator % (std::shared_ptr<Boolean>, std::shared_ptr<Number>);
std::shared_ptr<Number> operator % (std::shared_ptr<Boolean>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `Number`
std::shared_ptr<Number> operator % (std::shared_ptr<Number>, Reference);
std::shared_ptr<Number> operator % (std::shared_ptr<Number>, std::shared_ptr<Value>);
std::shared_ptr<Number> operator % (std::shared_ptr<Number>, std::shared_ptr<Object>);
std::shared_ptr<Number> operator % (std::shared_ptr<Number>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator % (std::shared_ptr<Number>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator % (std::shared_ptr<Number>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator % (std::shared_ptr<Number>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator % (std::shared_ptr<Number>, std::shared_ptr<Number>);
std::shared_ptr<Number> operator % (std::shared_ptr<Number>, std::shared_ptr<String>);

////////////////////////////////////////
// Left operands of type `String`
std::shared_ptr<Number> operator % (std::shared_ptr<String>, Reference);
std::shared_ptr<Number> operator % (std::shared_ptr<String>, std::shared_ptr<Value>);
std::shared_ptr<Number> operator % (std::shared_ptr<String>, std::shared_ptr<Object>);
std::shared_ptr<Number> operator % (std::shared_ptr<String>, std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator % (std::shared_ptr<String>, std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator % (std::shared_ptr<String>, std::shared_ptr<Null>);
std::shared_ptr<Number> operator % (std::shared_ptr<String>, std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator % (std::shared_ptr<String>, std::shared_ptr<Number>);
std::shared_ptr<Number> operator % (std::shared_ptr<String>, std::shared_ptr<String>);

// End modulus operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Unary `-` operator overloads for every possible operand

std::shared_ptr<Number> operator - (Reference);
std::shared_ptr<Number> operator - (std::shared_ptr<Value>);
std::shared_ptr<Number> operator - (std::shared_ptr<Object>);
std::shared_ptr<Number> operator - (std::shared_ptr<Primitive>);
std::shared_ptr<Number> operator - (std::shared_ptr<Undefined>);
std::shared_ptr<Number> operator - (std::shared_ptr<Null>);
std::shared_ptr<Number> operator - (std::shared_ptr<Boolean>);
std::shared_ptr<Number> operator - (std::shared_ptr<Number>);
std::shared_ptr<Number> operator - (std::shared_ptr<String>);

// End unary `-` operator overloads
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Logical NOT operator overloads for every possible operand

std::shared_ptr<Boolean> operator ! (Reference);
std::shared_ptr<Boolean> operator ! (std::shared_ptr<Value>);
std::shared_ptr<Boolean> operator ! (std::shared_ptr<Object>);
std::shared_ptr<Boolean> operator ! (std::shared_ptr<Primitive>);
std::shared_ptr<Boolean> operator ! (std::shared_ptr<Undefined>);
std::shared_ptr<Boolean> operator ! (std::shared_ptr<Null>);
std::shared_ptr<Boolean> operator ! (std::shared_ptr<Boolean>);
std::shared_ptr<Boolean> operator ! (std::shared_ptr<Number>);
std::shared_ptr<Boolean> operator ! (std::shared_ptr<String>);

// End logical NOT operator overloads
////////////////////////////////////////////////////////////////////////////////

// End operator overloads
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
