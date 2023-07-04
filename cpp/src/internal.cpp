#include "internal.h"

#include <memory>

#include "exception.h"
#include "global_scope.h"
#include "reference.h"
#include "scope.h"
#include "type_conversion.h"
#include "value.h"

using namespace std;

shared_ptr<Object> _fn(Object::CallSignature __Call__, Object::CallSignature __Construct__) {
  return _fn(make_shared<Object>(), __Call__, __Construct__);
}

shared_ptr<Object> _fn(shared_ptr<Object> prototype, Object::CallSignature __Call__, Object::CallSignature __Construct__) {
  // ES1: 15(5): Every built-in function and every built-in constructor has the Function prototype object,
  //             which is the value of the expression `Function.prototype` (15.3.3.1), as the value of its
  //             internal [[Prototype]] property, except the Function prototype object itself.
  shared_ptr<Object> fn = make_shared<Object>(Object::Function_prototype);
  fn->__Class__ = "Function"; // TODO: enum this
  fn->__Construct__ = __Construct__;
  fn->__Call__ = __Call__;
  // TODO: #6: each function should have formal params and a `length` property.
  // TODO: ES1: 15.2.3.1(2): This property shall have the attributes { DontEnum, DontDelete, ReadOnly }.
  // TODO: ES1: 15.3.3.1(2): This property shall have the attributes { DontEnum, DontDelete, ReadOnly }.
  // TODO: ES1: 15.4.3.1(2): This property shall have the attributes { DontEnum, DontDelete, ReadOnly }.
  // TODO: ES1: 15.5.3.1(2): This property shall have the attributes { DontEnum, DontDelete, ReadOnly }.
  // TODO: ES1: 15.6.3.1(2): This property shall have the attributes { DontEnum, DontDelete, ReadOnly }.
  // TODO: ES1: 15.7.3.1(2): This property shall have the attributes { DontEnum, DontDelete, ReadOnly }.
  // TODO: ES1: 15.9.4.1(2): This property shall have the attributes { DontEnum, DontDelete, ReadOnly }.
  fn->*"prototype" = prototype;
  return fn;
}

shared_ptr<Object> _fn(shared_ptr<Scope> closure, Object::CallSignature __Construct_and_Call__) {
  // ES1: 15.3.2.1.16: The [[Prototype]] property of F is set to the original Function prototype
  //                   object, the one that is the initial value of `Function.prototype` (15.3.3.1)
  shared_ptr<Object> fn = make_shared<Object>(Object::Function_prototype);
  fn->__Class__ = "Function"; // TODO: enum this
  fn->closure = closure;
  fn->__Construct__ = __Construct_and_Call__;
  fn->__Call__ = __Construct_and_Call__;
  // TODO: #6: each function should have formal params and a `length` property.
  // TODO: ES1: 15.3.2.1.23: This property is given attributes { DontEnum }.
  fn->*"prototype" = make_shared<Object>();
  return fn;
}

bool _if (Reference ref) {
  return ToBoolean(GetValue(ref))->value;
}

bool _if (shared_ptr<Value> val) {
  return ToBoolean(val)->value;
}

std::shared_ptr<Object> _new (Reference constructor) {
  return _new(constructor, vector<shared_ptr<Value> >());
}
std::shared_ptr<Object> _new (Reference constructor, Reference firstParam) {
  vector<shared_ptr<Value> > params;
  params.push_back(GetValue(firstParam));
  return _new(constructor, params);
}
std::shared_ptr<Object> _new (Reference constructor, std::shared_ptr<Value> firstParam) {
  vector<shared_ptr<Value> > params;
  params.push_back(firstParam);
  return _new(constructor, params);
}
std::shared_ptr<Object> _new (Reference constructor, std::vector<std::shared_ptr<Value> > params) {
  shared_ptr<Value> val = GetValue(constructor);
  return _new(val, params);
}
shared_ptr<Object> _new (shared_ptr<Value> constructor) {
  return _new(constructor, vector<shared_ptr<Value> >());
}
shared_ptr<Object> _new (shared_ptr<Value> constructor, Reference firstParam) {
  vector<shared_ptr<Value> > params;
  params.push_back(GetValue(firstParam));
  return _new(constructor, params);
}
shared_ptr<Object> _new (shared_ptr<Value> constructor, shared_ptr<Value> firstParam) {
  vector<shared_ptr<Value> > params;
  params.push_back(firstParam);
  return _new(constructor, params);
}
shared_ptr<Object> _new (shared_ptr<Value> constructor, vector<shared_ptr<Value> > params) {
  if (constructor->type != OBJECT_VALUE_TYPE) {
    throw TypeError("constructor is not an object");
  }
  shared_ptr<Object> obj = static_pointer_cast<Object>(constructor);
  if (obj->__Construct__ == nullptr) {
    throw TypeError("object is not a constructor");
  }
  shared_ptr<Object> prototype = nullptr;
  if (obj->__HasProperty__("prototype")) {
    shared_ptr<Value> maybeObj = obj->__Get__("prototype");
    if (maybeObj->type == OBJECT_VALUE_TYPE) {
      prototype = static_pointer_cast<Object>(maybeObj);
    } else {
      // TODO: should actually fall back to the _original_ Object prototype object?
      prototype = static_pointer_cast<Object>(GetValue(globalScope->*"Object"->*"prototype"));
    }
  } else {
    throw ImplementationException("constructor has no prototype");
  }
  shared_ptr<Object> newObject = make_shared<Object>(prototype);
  shared_ptr<Value> result = obj->__Construct__(obj->closure, newObject, params);
  if (result->type != OBJECT_VALUE_TYPE) {
    throw TypeError("constructor returned a non-object");
  }
  return static_pointer_cast<Object>(result);
}

shared_ptr<Value> __DefaultValue__ (shared_ptr<Object> _this, HintValueType hint) {
  if (hint == NONE_HINT_VALUE_TYPE) {
    if (_this->__Class__ == "Date") { // TODO: enum this
      hint = STRING_HINT_VALUE_TYPE;
    } else {
      hint = NUMBER_HINT_VALUE_TYPE;
    }
  }
  switch (hint) {
    case STRING_HINT_VALUE_TYPE: {
      shared_ptr<Value> toString = _this->__Get__("toString");
      if (toString->type == OBJECT_VALUE_TYPE) {
        shared_ptr<Object> obj = static_pointer_cast<Object>(toString);
        // TODO: `toString` may not be callable. ES1 doesn't anticipate this problem.
        shared_ptr<Value> result = obj->__Call__(obj->closure, _this, vector<shared_ptr<Value> >());
        if (result->type != OBJECT_VALUE_TYPE) {
          return result;
        }
      }
      shared_ptr<Value> valueOf = _this->__Get__("valueOf");
      if (valueOf->type == OBJECT_VALUE_TYPE) {
        shared_ptr<Object> obj = static_pointer_cast<Object>(valueOf);
        // TODO: `valueOf` may not be callable. ES1 doesn't anticipate this problem.
        shared_ptr<Value> result = obj->__Call__(obj->closure, _this, vector<shared_ptr<Value> >());
        if (result->type != OBJECT_VALUE_TYPE) {
          return result;
        }
      }
      break;
    }
    case NUMBER_HINT_VALUE_TYPE:{
      shared_ptr<Value> valueOf = _this->__Get__("valueOf");
      if (valueOf->type == OBJECT_VALUE_TYPE) {
        shared_ptr<Object> obj = static_pointer_cast<Object>(valueOf);
        // TODO: `valueOf` may not be callable. ES1 doesn't anticipate this problem.
        shared_ptr<Value> result = obj->__Call__(obj->closure, _this, vector<shared_ptr<Value> >());
        if (result->type != OBJECT_VALUE_TYPE) {
          return result;
        }
      }
      shared_ptr<Value> toString = _this->__Get__("toString");
      if (toString->type == OBJECT_VALUE_TYPE) {
        shared_ptr<Object> obj = static_pointer_cast<Object>(toString);
        // TODO: `toString` may not be callable. ES1 doesn't anticipate this problem.
        shared_ptr<Value> result = obj->__Call__(obj->closure, _this, vector<shared_ptr<Value> >());
        if (result->type != OBJECT_VALUE_TYPE) {
          return result;
        }
      }
      break;
    }
    case NONE_HINT_VALUE_TYPE:
      throw ImplementationException("hint should never be None here");
  }
  throw TypeError("unable to convert object to primitive using [[DefaultValue]]");
}
