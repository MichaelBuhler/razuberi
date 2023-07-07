#include "internal.h"

#include <memory>

#include "exception.h"
#include "global_scope.h"
#include "reference.h"
#include "scope.h"
#include "type_conversion.h"
#include "value.h"

using namespace std;

shared_ptr<Object> _fn (shared_ptr<Scope> closure, Object::CallSignature __Call_and_Construct__) {
  return Object::makeFunction(
    // User-defined script functions use the same function body whether called as functions or constructors.
    __Call_and_Construct__,
    // User-defined script functions use the same function body whether called as functions or constructors.
    __Call_and_Construct__,
    // ES1: 15.3.2.1.22: Create a new object as if by the expression `new Object()`.
    // ES1: 15.3.2.1.23: The prototype property of _F_ is set to Result(22)
    make_shared<Object>(),
    closure
  );
}

bool _if (Reference ref) {
  return ToBoolean(GetValue(ref))->value;
}

bool _if (shared_ptr<Value> val) {
  return ToBoolean(val)->value;
}

shared_ptr<Object> _new (Reference constructor) {
  return _new(constructor, vector<shared_ptr<Value> >());
}
shared_ptr<Object> _new (Reference constructor, Reference firstParam) {
  vector<shared_ptr<Value> > params;
  params.push_back(GetValue(firstParam));
  return _new(constructor, params);
}
shared_ptr<Object> _new (Reference constructor, shared_ptr<Value> firstParam) {
  vector<shared_ptr<Value> > params;
  params.push_back(firstParam);
  return _new(constructor, params);
}
shared_ptr<Object> _new (Reference constructor, vector<shared_ptr<Value> > params) {
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
  return constructor->construct(params);
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
        shared_ptr<Value> result = obj->call(_this, vector<shared_ptr<Value> >());
        if (result->type != OBJECT_VALUE_TYPE) {
          return result;
        }
      }
      shared_ptr<Value> valueOf = _this->__Get__("valueOf");
      if (valueOf->type == OBJECT_VALUE_TYPE) {
        shared_ptr<Object> obj = static_pointer_cast<Object>(valueOf);
        // TODO: `valueOf` may not be callable. ES1 doesn't anticipate this problem.
        shared_ptr<Value> result = obj->call(_this, vector<shared_ptr<Value> >());
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
        shared_ptr<Value> result = obj->call(_this, vector<shared_ptr<Value> >());
        if (result->type != OBJECT_VALUE_TYPE) {
          return result;
        }
      }
      shared_ptr<Value> toString = _this->__Get__("toString");
      if (toString->type == OBJECT_VALUE_TYPE) {
        shared_ptr<Object> obj = static_pointer_cast<Object>(toString);
        // TODO: `toString` may not be callable. ES1 doesn't anticipate this problem.
        shared_ptr<Value> result = obj->call(_this, vector<shared_ptr<Value> >());
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
