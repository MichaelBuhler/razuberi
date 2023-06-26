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
  OBJECT_VALUE_TYPE
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

std::shared_ptr<Value> operator ->* (std::shared_ptr<Value> value, std::string name);

std::shared_ptr<Value> operator + (std::shared_ptr<Value> a, std::shared_ptr<Value> b);

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
};

class String : public Primitive {
  public: std::string value;
  public: String (std::string value);
};

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
