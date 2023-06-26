#include "builtin_objects.h"

#include "exception.h"
#include "value.h"
#include "type_conversion.h"

using namespace std;

shared_ptr<Value> _Object__Call__ (shared_ptr<Value> _this, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  if (arguments.size() == 0) {
    shared_ptr<Object> obj = make_shared<Object>();
    obj->__Class__ = "Object";
    return obj;
  }
  shared_ptr<Value> arg = arguments[0];
  switch (arg->type) {
    case UNDEFINED_VALUE_TYPE:
    case NULL_VALUE_TYPE: {
      shared_ptr<Object> obj = make_shared<Object>();
      obj->__Class__ = "Object";
      return obj;
    }
    case BOOLEAN_VALUE_TYPE:
    case NUMBER_VALUE_TYPE:
    case STRING_VALUE_TYPE:
    case OBJECT_VALUE_TYPE:
      return ToObject(arg);
  }
}

shared_ptr<Object> _Object__Construct__ (shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  shared_ptr<Object> _this = static_pointer_cast<Object>(scope->*"this");
  _this->__Class__ = "Object"; // TODO: enum this
  if (arguments.size() == 0) return _this;
  shared_ptr<Value> arg = arguments[0];
  switch (arg->type) {
    case UNDEFINED_VALUE_TYPE:
    case NULL_VALUE_TYPE:
      return _this;
    case BOOLEAN_VALUE_TYPE:
    case NUMBER_VALUE_TYPE:
    case STRING_VALUE_TYPE:
      return ToObject(arg);
    case OBJECT_VALUE_TYPE:
      return static_pointer_cast<Object>(arg);
  }
}

shared_ptr<Value> _Object_prototype_toString (shared_ptr<Value> _this, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  switch (_this->type) {
    case UNDEFINED_VALUE_TYPE:
      return make_shared<String>("[object Undefined]");
    case NULL_VALUE_TYPE:
      return make_shared<String>("[object Null]");
    case BOOLEAN_VALUE_TYPE:
      return make_shared<String>("[object Boolean]");
    case NUMBER_VALUE_TYPE:
      return make_shared<String>("[object Number]");
    case STRING_VALUE_TYPE:
      return make_shared<String>("[object String]");
    case OBJECT_VALUE_TYPE: {
      shared_ptr<Object> obj = static_pointer_cast<Object>(_this);
      return make_shared<String>("[object "+obj->__Class__+"]");
    }
  }
}

shared_ptr<Value> _Object_prototype_valueOf (shared_ptr<Value> _this, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  return ToObject(_this);
}

shared_ptr<Value> _Function__Call__ (shared_ptr<Value> _this, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  throw NotImplementedException("Cannot call `Function` to create new functions at runtime.");
}

shared_ptr<Object> _Function__Construct__ (shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
   throw NotImplementedException("Cannot use `Function` as a constructor to create new functions at runtime.");
}

shared_ptr<Value> _Function_prototype_toString (shared_ptr<Value> _this, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  throw NotImplementedException("Function.prototype.toString()");
}

shared_ptr<Value> _Boolean__Call__ (shared_ptr<Value> _this, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  if (arguments.size() == 0) return make_shared<Boolean>(false);
  return ToBoolean(arguments[0]);
}

shared_ptr<Object> _Boolean__Construct__ (shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  shared_ptr<Object> _this = static_pointer_cast<Object>(scope->*"this");
  _this->__Class__ = "Boolean"; // TODO: enum this
  if (arguments.size() == 0) _this->__Value__ = make_shared<Boolean>(false);
  else _this->__Value__ = ToBoolean(arguments[0]);
  return _this;
}

shared_ptr<Value> _Boolean_prototype_toString (shared_ptr<Value> _this, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  if (_this->type == OBJECT_VALUE_TYPE) {
    shared_ptr<Object> obj = static_pointer_cast<Object>(_this);
    if (obj->__Class__ == "Boolean") { // TODO: enum this
      shared_ptr<Boolean> val = static_pointer_cast<Boolean>(obj->__Value__);
      if (val->value) {
        return make_shared<String>("true");
      } else {
        return make_shared<String>("false");
      }
    }
  }
  throw TypeError("Boolean.prototype.toString requires that 'this' be a Boolean");
}

shared_ptr<Value> _Boolean_prototype_valueOf (shared_ptr<Value> _this, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  if (_this->type == OBJECT_VALUE_TYPE) {
    shared_ptr<Object> obj = static_pointer_cast<Object>(_this);
    if (obj->__Class__ == "Boolean") { // TODO: enum this
      return obj->__Value__;
    }
  }
  throw TypeError("Boolean.prototype.toString requires that 'this' be a Boolean");
}

void init_builtin_objects (shared_ptr<Scope> globalScope) {
  shared_ptr<Object> ObjectPrototype = make_shared<Object>();
  shared_ptr<Object> ObjectObject = make_shared<Object>(ObjectPrototype, _Object__Call__, _Object__Construct__);
  ObjectObject->__Put__("prototype", ObjectPrototype);
  ObjectObject->__Put__("length", make_shared<Number>(1));
  ObjectPrototype->__Put__("constructor", ObjectObject);
  ObjectPrototype->__Put__("toString", make_shared<Object>(nullptr, _Object_prototype_toString));
  ObjectPrototype->__Put__("valueOf", make_shared<Object>(nullptr, _Object_prototype_valueOf));
  globalScope->set("Object", ObjectObject);

  shared_ptr<Object> FunctionPrototype = make_shared<Object>();
  shared_ptr<Object> Function = make_shared<Object>(FunctionPrototype, _Function__Call__, _Function__Construct__);
  Function->__Put__("prototype", FunctionPrototype);
  Function->__Put__("length", make_shared<Number>(1));
  FunctionPrototype->__Put__("constructor", Function);
  FunctionPrototype->__Put__("toString", make_shared<Object>(nullptr, _Function_prototype_toString));
  globalScope->set("Function", Function);

  // TODO: Boolean.prototype should be 'a Boolean object whose value is false'.
  shared_ptr<Object> BooleanPrototype = make_shared<Object>();
  shared_ptr<Object> Boolean = make_shared<Object>(BooleanPrototype, _Boolean__Call__, _Boolean__Construct__);
  Boolean->__Put__("prototype", BooleanPrototype);
  Boolean->__Put__("length", make_shared<Number>(1));
  BooleanPrototype->__Put__("constructor", Boolean);
  BooleanPrototype->__Put__("toString", make_shared<Object>(nullptr, _Boolean_prototype_toString));
  BooleanPrototype->__Put__("valueOf", make_shared<Object>(nullptr, _Boolean_prototype_valueOf));
  globalScope->set("Boolean", Boolean);
}