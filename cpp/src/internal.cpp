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

shared_ptr<Value> _newThrowable (Reference constructor) {
  return static_pointer_cast<Value>(_new(constructor));
}
shared_ptr<Value> _newThrowable (Reference constructor, Reference firstParam) {
  return static_pointer_cast<Value>(_new(constructor, firstParam));
}
shared_ptr<Value> _newThrowable (Reference constructor, shared_ptr<Value> firstParam) {
  return static_pointer_cast<Value>(_new(constructor, firstParam));
}
shared_ptr<Value> _newThrowable (Reference constructor, vector<shared_ptr<Value> > params) {
  return static_pointer_cast<Value>(_new(constructor, params));
}
shared_ptr<Value> _newThrowable (shared_ptr<Value> constructor) {
  return static_pointer_cast<Value>(_new(constructor));
}
shared_ptr<Value> _newThrowable (shared_ptr<Value> constructor, Reference firstParam) {
  return static_pointer_cast<Value>(_new(constructor, firstParam));
}
shared_ptr<Value> _newThrowable (shared_ptr<Value> constructor, shared_ptr<Value> firstParam) {
  return static_pointer_cast<Value>(_new(constructor, firstParam));
}
shared_ptr<Value> _newThrowable (shared_ptr<Value> constructor, vector<shared_ptr<Value> > params) {
  return static_pointer_cast<Value>(_new(constructor, params));
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
  throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("unable to convert object to primitive using [[DefaultValue]]"));
}

shared_ptr<Boolean> _strictEquals (Reference a, Reference b) {
  return _strictEquals(GetValue(a), GetValue(b));
}
shared_ptr<Boolean> _strictEquals (Reference r, shared_ptr<Value> v) {
  return _strictEquals(GetValue(r), v);
}
shared_ptr<Boolean> _strictEquals (shared_ptr<Value> v, Reference r) {
  return _strictEquals(v, GetValue(r));
}
shared_ptr<Boolean> _strictEquals (shared_ptr<Value> a, shared_ptr<Value> b) {
  if (a->type != b->type) {
    return make_shared<Boolean>(false);
  } else {
    return a == b;
  }
}

shared_ptr<Boolean> _strictNotEquals (Reference a, Reference b) {
  return _strictNotEquals(GetValue(a), GetValue(b));
}
shared_ptr<Boolean> _strictNotEquals (Reference r, shared_ptr<Value> v) {
  return _strictNotEquals(GetValue(r), v);
}
shared_ptr<Boolean> _strictNotEquals (shared_ptr<Value> v, Reference r) {
  return _strictNotEquals(v, GetValue(r));
}
shared_ptr<Boolean> _strictNotEquals (shared_ptr<Value> a, shared_ptr<Value> b) {
  shared_ptr<Boolean> equal = _strictEquals(a, b);
  return make_shared<Boolean>(!equal->value);
}

bool _test (Reference ref) {
  return _test(GetValue(ref));
}
bool _test (shared_ptr<Value> value) {
  switch (value->type) {
    case UNDEFINED_VALUE_TYPE:
      return false;
    case NULL_VALUE_TYPE:
      return false;
    case BOOLEAN_VALUE_TYPE:
      return static_pointer_cast<Boolean>(value)->value;
    case NUMBER_VALUE_TYPE:
      return ToBoolean(static_pointer_cast<Number>(value))->value;
    case STRING_VALUE_TYPE:
      return ToBoolean(static_pointer_cast<String>(value))->value;
    case OBJECT_VALUE_TYPE:
      return true;
  }
}
bool _test (shared_ptr<Undefined>) {
  return false;
}
bool _test (shared_ptr<Null>) {
  return false;
}
bool _test (shared_ptr<Boolean> boolean) {
  return boolean->value;
}
bool _test (shared_ptr<Number> num) {
  return ToBoolean(num)->value;
}
bool _test (shared_ptr<String> str) {
  return ToBoolean(str)->value;
}
bool _test (shared_ptr<Object>) {
  return true;
}

shared_ptr<String> _typeof (Reference ref) {
  if (GetBase(ref)->type == NULL_VALUE_TYPE) {
    return make_shared<String>("undefined");
  } else {
    return _typeof(GetValue(ref));
  }
}
shared_ptr<String> _typeof (shared_ptr<Value> value) {
  switch (value->type) {
    case UNDEFINED_VALUE_TYPE:
      return make_shared<String>("undefined");
    case NULL_VALUE_TYPE:
      return make_shared<String>("null");
    case BOOLEAN_VALUE_TYPE:
      return make_shared<String>("boolean");
    case NUMBER_VALUE_TYPE:
      return make_shared<String>("number");
    case STRING_VALUE_TYPE:
      return make_shared<String>("string");
    case OBJECT_VALUE_TYPE: {
      shared_ptr<Object> obj = static_pointer_cast<Object>(value);
      if (obj->isFunction()) {
        return make_shared<String>("function");
      } else {
        return make_shared<String>("object");
      }
    }  
  }
}

shared_ptr<Undefined> _void (Reference ref) {
  GetValue(ref);
  return make_shared<Undefined>();
}
shared_ptr<Undefined> _void (shared_ptr<Value>) {
  return make_shared<Undefined>();
}

shared_ptr<Boolean> _instanceOf (Reference a, Reference b) {
  return _instanceOf(GetValue(a), GetValue(b));
}
shared_ptr<Boolean> _instanceOf (Reference ref, shared_ptr<Value> val) {
  return _instanceOf(GetValue(ref), val);
}
shared_ptr<Boolean> _instanceOf (shared_ptr<Value> val, Reference ref) {
  return _instanceOf(val, GetValue(ref));
}
shared_ptr<Boolean> _instanceOf (shared_ptr<Value> left, shared_ptr<Value> right) {
  if (right->type != OBJECT_VALUE_TYPE) {
    throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("Right-hand side of 'instanceof' is not an object"));
  }
  shared_ptr<Object> rightObj = static_pointer_cast<Object>(right);
  if (!rightObj->isFunction()) {
    throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("Right-hand side of 'instanceof' is not callable"));
  }
  return rightObj->__HasInstance__(left);
}
