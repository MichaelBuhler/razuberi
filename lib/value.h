#pragma once
#include "value.fwd.h"

#include "scope.fwd.h"
#include "scope.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

enum ValueType {
  UNDEFINED_VALUE_TYPE,
  NULL_VALUE_TYPE,
  BOOLEAN_VALUE_TYPE,
  STRING_VALUE_TYPE,
  NUMBER_VALUE_TYPE,
  OBJECT_VALUE_TYPE
};

class Value {
  public: ValueType type;
  public: Value ();
};

shared_ptr<Value> operator ->* (shared_ptr<Value> value, string name);

shared_ptr<Value> operator + (shared_ptr<Value> a, shared_ptr<Value> b);

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
  public: Number (double value);
};

class String : public Primitive {
  public: string value;
  public: String (string value);
};

class Object : public Value {
  private: class Property {
    public: shared_ptr<Value> value;
    public: bool ReadOnly;
    public: bool DontEnum;
    public: bool DontDelete;
    // public: bool Internal; // not sure how this is used
  };
  private: map<string, shared_ptr<Property> > properties;
  private: shared_ptr<Value> (*fn)(shared_ptr<Scope>, vector<shared_ptr<Value> >);
  public: Object ();
  public: Object (shared_ptr<Value> (*fn)(shared_ptr<Scope>, vector<shared_ptr<Value> >));
  public: shared_ptr<Value> __Get__ (string name);
  public: void __Put__ (string key, shared_ptr<Value> value);
  public: shared_ptr<Value> __Call__ (shared_ptr<Scope> callingScope, vector<shared_ptr<Value> > params);
};
