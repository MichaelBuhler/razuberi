#include "internal.h"

#include <memory>

#include "exception.h"
#include "global_scope.h"
#include "reference.h"
#include "scope.h"
#include "type_conversion.h"
#include "value.h"

using namespace std;

shared_ptr<Value> _call (Reference callee) {
  return _call(callee, vector<shared_ptr<Value> >());
}
shared_ptr<Value> _call (Reference callee, Reference firstParam) {
  vector<shared_ptr<Value> > params;
  params.push_back(GetValue(firstParam));
  return _call(callee, params);
}
shared_ptr<Value> _call (Reference callee, shared_ptr<Value> firstParam) {
  vector<shared_ptr<Value> > params;
  params.push_back(firstParam);
  return _call(callee, params);
}
shared_ptr<Value> _call (Reference callee, vector<shared_ptr<Value> > params) {
  shared_ptr<Value> val = GetValue(callee);
  if (val->type != OBJECT_VALUE_TYPE) {
    throw TypeError("callee is not an object");
  }
  shared_ptr<Object> obj = static_pointer_cast<Object>(val);
  if (obj->__Call__ == nullptr) {
    throw TypeError("object is not a function");
  }
  shared_ptr<Value> thisArg = GetBase(callee);
  return obj->__Call__(thisArg, params);
}
shared_ptr<Value> _call (shared_ptr<Value> callee) {
  return _call(callee, vector<shared_ptr<Value> >());
}
shared_ptr<Value> _call (shared_ptr<Value> callee, Reference firstParam) {
  vector<shared_ptr<Value> > params;
  params.push_back(GetValue(firstParam));
  return _call(callee, params);
}
shared_ptr<Value> _call (shared_ptr<Value> callee, shared_ptr<Value> firstParam) {
  vector<shared_ptr<Value> > params;
  params.push_back(firstParam);
  return _call(callee, params);
}
shared_ptr<Value> _call (shared_ptr<Value> callee, vector<shared_ptr<Value> > params) {
  if (callee->type != OBJECT_VALUE_TYPE) {
    throw TypeError("callee is not an object");
  }
  shared_ptr<Object> obj = static_pointer_cast<Object>(callee);
  if (obj->__Call__ == nullptr) {
    throw TypeError("object is not a function");
  }
  return obj->__Call__(make_shared<Null>(), params);
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
  shared_ptr<Value> result = obj->__Construct__(newObject, params);
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
