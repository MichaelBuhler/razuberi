#include "internal.h"

#include <memory>

#include "exception.h"
#include "reference.h"
#include "scope.h"
#include "value.h"

using namespace std;

shared_ptr<Value> _assign(shared_ptr<Reference> ref, shared_ptr<Reference> otherRef) {
  return _assign(ref, GetValue(otherRef));
}

shared_ptr<Value> _assign(shared_ptr<Reference> ref, shared_ptr<Value> value) {
  PutValue(ref, value);
  return value;
}

shared_ptr<Value> _call (shared_ptr<Value> maybeRef) {
  return _call(maybeRef, vector<shared_ptr<Value> >());
}

shared_ptr<Value> _call (shared_ptr<Value> maybeRef, shared_ptr<Value> value) {
  vector<shared_ptr<Value> > params;
  params.push_back(value);
  return _call(maybeRef, params);
}

shared_ptr<Value> _call (shared_ptr<Value> maybeRef, vector<shared_ptr<Value> > params) {
  shared_ptr<Value> callee = GetValue(maybeRef);
  if (callee->type != OBJECT_VALUE_TYPE) {
    throw TypeError("callee is not an object");
  }
  shared_ptr<Object> obj = static_pointer_cast<Object>(callee);
  if (obj->__Call__ == nullptr) {
    throw TypeError("object is not a function");
  }
  shared_ptr<Value> thisArg;
  if (maybeRef->type == REFERENCE_VALUE_TYPE) {
    thisArg = GetBase(maybeRef);
  } else {
    thisArg = make_shared<Null>();
  }
  return obj->__Call__(thisArg, params);
}

shared_ptr<Object> _new (shared_ptr<Value> maybeRef) {
  return _new(maybeRef, vector<shared_ptr<Value> >());
}

shared_ptr<Object> _new (shared_ptr<Value> maybeRef, shared_ptr<Value> value) {
  vector<shared_ptr<Value> > params;
  params.push_back(value);
  return _new(maybeRef, params);
}

shared_ptr<Object> _new (shared_ptr<Value> maybeRef, vector<shared_ptr<Value> > params) {
  shared_ptr<Value> constructor = GetValue(maybeRef);
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
      // TODO: should actually fall back to Object.prototype
      prototype = make_shared<Object>();
    }
  } else {
    throw ImplementationException("constructor has no prototype");
  }
  shared_ptr<Object> newObject = make_shared<Object>(prototype);
  shared_ptr<Value> result = obj->__Construct__(newObject, params);
  if (result->type != OBJECT_VALUE_TYPE) {
    throw TypeError("constructor returned a non-object");
  }
  return static_pointer_cast<Object>(result);
}

std::shared_ptr<Value> __DefaultValue__ (shared_ptr<Object> _this, HintValueType hint) {
  if (hint == NONE_HINT_VALUE_TYPE) {
    if (_this->__Class__ == "Date") { // TODO: enum this
      hint = STRING_HINT_VALUE_TYPE;
    } else {
      hint = NUMBER_HINT_VALUE_TYPE;
    }
  }
  vector<shared_ptr<Value> > emptyParams;
  switch (hint) {
    case STRING_HINT_VALUE_TYPE: {
      shared_ptr<Value> toString = _this->__Get__("toString");
      if (toString->type == OBJECT_VALUE_TYPE) {
        shared_ptr<Object> obj = static_pointer_cast<Object>(toString);
        // TODO: `toString` may not be callable. ES1 doesn't anticipate this problem.
        shared_ptr<Value> result = obj->__Call__(_this, emptyParams);
        if (result->type != OBJECT_VALUE_TYPE) {
          return result;
        }
      }
      shared_ptr<Value> valueOf = _this->__Get__("valueOf");
      if (valueOf->type == OBJECT_VALUE_TYPE) {
        shared_ptr<Object> obj = static_pointer_cast<Object>(valueOf);
        // TODO: `valueOf` may not be callable. ES1 doesn't anticipate this problem.
        shared_ptr<Value> result = obj->__Call__(_this, emptyParams);
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
        shared_ptr<Value> result = obj->__Call__(_this, emptyParams);
        if (result->type != OBJECT_VALUE_TYPE) {
          return result;
        }
      }
      shared_ptr<Value> toString = _this->__Get__("toString");
      if (toString->type == OBJECT_VALUE_TYPE) {
        shared_ptr<Object> obj = static_pointer_cast<Object>(toString);
        // TODO: `toString` may not be callable. ES1 doesn't anticipate this problem.
        shared_ptr<Value> result = obj->__Call__(_this, emptyParams);
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
