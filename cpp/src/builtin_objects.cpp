#include "builtin_objects.h"

#include "exception.h"
#include "global_scope.h"
#include "internal.h"
#include "value.h"
#include "type_conversion.h"

using namespace std;

// ES1: 15.2.1
shared_ptr<Value> Object__Call__ (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> > arguments) {
  if (arguments.size() == 0) {
    return make_shared<Object>();
  }
  shared_ptr<Value> arg = arguments[0];
  switch (arg->type) {
    case UNDEFINED_VALUE_TYPE:
    case NULL_VALUE_TYPE:
      return make_shared<Object>();
    case BOOLEAN_VALUE_TYPE:
    case NUMBER_VALUE_TYPE:
    case STRING_VALUE_TYPE:
    case OBJECT_VALUE_TYPE:
      return ToObject(arg);
  }
}

// ES1: 15.2.2
shared_ptr<Value> Object__Construct__ (shared_ptr<Scope>,  shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {
  if (arguments.size() == 0) {
    return _this; // _this was already a newly constructed object
  }
  shared_ptr<Value> arg = arguments[0];
  switch (arg->type) {
    case UNDEFINED_VALUE_TYPE:
    case NULL_VALUE_TYPE:
      return _this; // _this was already a newly constructed object
    case BOOLEAN_VALUE_TYPE:
    case NUMBER_VALUE_TYPE:
    case STRING_VALUE_TYPE:
      return ToObject(arg);
    case OBJECT_VALUE_TYPE:
      // All built-in objects, host objects, and native objects
      // ES1 does for host objects to do something implementation dependent.
      return arg;
  }
}

// ES1: 15.2.4.2
shared_ptr<Value> Object_prototype_toString (shared_ptr<Scope>, shared_ptr<Value> _this, vector<shared_ptr<Value> >) {
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
      return make_shared<String>("[object " + obj->__Class__ + "]");
    }
  }
}

// ES1: 15.2.4.3: As a rule, the valueOf method for an object simply returns the object...
shared_ptr<Value> Object_prototype_valueOf (shared_ptr<Scope>, shared_ptr<Value> _this, vector<shared_ptr<Value> >) {
  // ES1 didn't anticipate that the `this` arg could be a non object.
  // As of 2023-07-05, Chrome/V8 seems to convert the `this` arg to an object.
  return ToObject(_this);
}

// ES1: 15.3.4: The Function prototype object is itself a Function object (its [[Class]] is "Function") that,
//              when invoked, accepts any arguments and returns undefined
shared_ptr<Value> Function_prototype__Call__ (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> >) {
  return make_shared<Undefined>();
}

// ES1: 15.3.1
shared_ptr<Value> Function__Call__ (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> >) {
  throw NotImplementedException("Cannot call `Function` to create new functions at runtime.");
}

// ES1: 15.3.2
shared_ptr<Value> Function__Construct__ (shared_ptr<Scope>,  shared_ptr<Value>, vector<shared_ptr<Value> >) {
   throw NotImplementedException("Cannot use `Function` as a constructor to create new functions at runtime.");
}

// ES1: 15.3.4.2
shared_ptr<Value> Function_prototype_toString (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> >) {
  return make_shared<String>("function () { /* Function.prototype.toString() is not fully implemented yet */ }");
}

// ES1: 15.5.1
shared_ptr<Value> String__Call__ (shared_ptr<Scope>, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {
  if (arguments.size() == 0) return make_shared<String>("");
  return ToString(arguments[0]);
}

// ES1: 15.5.2
shared_ptr<Value> String__Construct__ (shared_ptr<Scope>, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {
  shared_ptr<Object> obj = static_pointer_cast<Object>(_this);
  obj->__Class__ = "String"; // TODO: enum this
  if (arguments.size() == 0) {
    obj->__Value__ = make_shared<String>("");
    obj->*"length" = make_shared<Number>(0);
  } else {
    shared_ptr<String> str = ToString(arguments[0]);
    obj->__Value__ = str;
    obj->*"length" = make_shared<Number>(str->value.length());
  }
  return _this;
}

// TODO: ES1: 15.5.3.2: String.fromCharCode(char0, char1, ...)
shared_ptr<Value> String_fromCharCode (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> >) {
  throw NotImplementedException("String.fromCharCode(char0, char1, ...)");
}

// ES1: 15.5.4.2
shared_ptr<Value> String_prototype_toString (shared_ptr<Scope>, shared_ptr<Value> _this, vector<shared_ptr<Value> >) {
  if (_this->type == OBJECT_VALUE_TYPE) {
    shared_ptr<Object> obj = static_pointer_cast<Object>(_this);
    if (obj->__Class__ == "String") { // TODO: enum this
      return obj->__Value__;
    }
  }
  throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("String.prototype.toString requires that 'this' be a String"));
}

// ES1: 15.5.4.3
shared_ptr<Value> String_prototype_valueOf (shared_ptr<Scope>, shared_ptr<Value> _this, vector<shared_ptr<Value> >) {
  if (_this->type == OBJECT_VALUE_TYPE) {
    shared_ptr<Object> obj = static_pointer_cast<Object>(_this);
    if (obj->__Class__ == "String") { // TODO: enum this
      return obj->__Value__;
    }
  }
  throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("String.prototype.valueOf requires that 'this' be a String"));
}

// ES1: 15.5.4.4
shared_ptr<Value> String_prototype_charAt (shared_ptr<Scope>, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {
  shared_ptr<String> str = ToString(_this);
  shared_ptr<Value> arg;
  if (arguments.size() == 0) arg = make_shared<Undefined>();
  else arg = arguments[0];
  unsigned long index = ToInteger(arguments[0])->value;
  if (index < 0 || index >= str->value.length()) {
    return make_shared<String>("");
  }
  return make_shared<String>(str->value.substr(index, 1));
}

// ES1: 15.5.4.6
shared_ptr<Value> String_prototype_indexOf (shared_ptr<Scope>, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {
  shared_ptr<String> __this = ToString(_this);
  shared_ptr<String> searchString = arguments.size() > 0 ? ToString(arguments[0]) : make_shared<String>("undefined");
  size_t position;
  if (arguments.size() > 1 && arguments[1]->type != UNDEFINED_VALUE_TYPE) {
    position = ToNumber(arguments[1])->value;
    if (position < 0) {
      position = 0;
    }
  } else {
    position = 0;
  }
  size_t thisLength = __this->value.length();
  size_t searchLength = searchString->value.length();
  if (searchLength > thisLength) {
    return make_shared<Number>(-1);
  }
  size_t maxPosition = thisLength - searchLength;
  for ( size_t k = position ; k < maxPosition ; k++ ) {
    bool match = true;
    for ( size_t j = 0 ; j < searchLength ; j++ ) {
      if ( __this->value[k+j] != searchString->value[j] ) {
        match = false;
        break;
      }
    }
    if (match) {
      return make_shared<Number>(k);
    }
  }
  return make_shared<Number>(-1);
}

// ES1: 15.6.1
shared_ptr<Value> Boolean__Call__ (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> > arguments) {
  if (arguments.size() == 0) return make_shared<Boolean>(false);
  return ToBoolean(arguments[0]);
}

// ES1: 15.6.2
shared_ptr<Value> Boolean__Construct__ (shared_ptr<Scope>,  shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {
  shared_ptr<Object> obj = static_pointer_cast<Object>(_this);
  obj->__Class__ = "Boolean"; // TODO: enum this
  if (arguments.size() == 0) {
    obj->__Value__ = make_shared<Boolean>(false);
  } else {
    obj->__Value__ = ToBoolean(arguments[0]);
  }
  return _this;
}

// ES1: 15.6.4.2
shared_ptr<Value> Boolean_prototype_toString (shared_ptr<Scope>, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {
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
  throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("Boolean.prototype.toString requires that 'this' be a Boolean"));
}

// ES1: 15.6.4.3
shared_ptr<Value> Boolean_prototype_valueOf (shared_ptr<Scope>, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {
  if (_this->type == OBJECT_VALUE_TYPE) {
    shared_ptr<Object> obj = static_pointer_cast<Object>(_this);
    if (obj->__Class__ == "Boolean") { // TODO: enum this
      return obj->__Value__;
    }
  }
  throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("Boolean.prototype.valueOf requires that 'this' be a Boolean"));
}

// ES3: 15.11.1
shared_ptr<Value> Error__Call__ (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> > arguments) {
  // ES3: 15.11.1: When Error is called as a function rather than as a constructor, it creates and initialises a new
  //               Error object. Thus the function call Error(...) is equivalent to the object creation expression new
  //               Error(...) with the same arguments.
  return _new(get_global_scope()->*"Error", arguments);
}

// ES3: 15.11.2
shared_ptr<Value> Error__Construct__ (shared_ptr<Scope>, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {
  shared_ptr<Object> obj = static_pointer_cast<Object>(_this);
  obj->__Class__ = "Error"; // TODO: enum this
  shared_ptr<Value> message = arguments.size() > 0 ? arguments[0] : make_shared<Undefined>() ;
  if (message->type != UNDEFINED_VALUE_TYPE) {
    // ES3: 15.11.2.1(3): If the argument `message` is not undefined, the `message` property of the newly constructed
    //                    object is set to `ToString(message)`.
    obj->__Put__("message", ToString(message));
  }
  return _this;
}

// ES3: 15.11.4.4
shared_ptr<Value> Error_prototype_toString (shared_ptr<Scope>, shared_ptr<Value> _this, vector<shared_ptr<Value> >) {
  if (_this->type != OBJECT_VALUE_TYPE) {
    throw _newThrowable(get_global_scope()->*"TypeError", make_shared<String>("Error.prototype.toString requires that 'this' be an object"));
  }
  shared_ptr<Object> obj = static_pointer_cast<Object>(_this);
  shared_ptr<Value> name = obj->__Get__("name");
  if (name->type == UNDEFINED_VALUE_TYPE) {
    name = make_shared<String>("Error");
  }
  shared_ptr<String> stringName = ToString(name);
  shared_ptr<Value> message = obj->__Get__("message");
  if (message->type == UNDEFINED_VALUE_TYPE) {
    return make_shared<String>(stringName->value);
  }
  shared_ptr<String> stringMessage;
  if (message->type == STRING_VALUE_TYPE) {
    stringMessage = static_pointer_cast<String>(message);
  } else {
    stringMessage = ToString(message);
  }
  if (stringMessage->value.length() == 0) {
    return make_shared<String>(stringName->value);
  } else {
    return make_shared<String>(stringName->value + ": " + stringMessage->value);
  }
}

// ES3: 15.11.6.3
shared_ptr<Value> ReferenceError__Call__ (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> > arguments) {
  // ES3: 15.11.7.1: When a NativeError constructor is called as a function rather than as a constructor, it
  //                 creates and initialises a new object. A call of the object as a function is equivalent to
  //                 calling it as a constructor with the same arguments.
  return _new(get_global_scope()->*"ReferenceError", arguments);
}

// ES3: 15.11.6.5
shared_ptr<Value> TypeError__Call__ (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> > arguments) {
  // ES3: 15.11.7.1: When a NativeError constructor is called as a function rather than as a constructor, it
  //                 creates and initialises a new object. A call of the object as a function is equivalent to
  //                 calling it as a constructor with the same arguments.
  return _new(get_global_scope()->*"TypeError", arguments);
}

void init_builtin_prototypes (shared_ptr<Scope> globalScope) {
  // ES1: 15.2.4: The value of the internal [[Prototype]] property of the Object prototype object is null.
  Object::Object_prototype = make_shared<Object>(nullptr);

  // ES1: 15.3.4(2): The value of the internal [[Prototype]] property of the Function prototype object is
  //                 the Object prototype object (15.2.3.1).
  Object::Function_prototype = make_shared<Object>(Object::Object_prototype);
  // ES1: 15.3.4(1): The Function prototype object is itself a Function object (its [[Class]]
  //                 is "Function") that, when invoked, accepts any arguments and returns undefined.
  Object::Function_prototype->__Class__ = "Function"; // TODO: enum this
  Object::Function_prototype->__Call__ = Function_prototype__Call__;

  // ES1: 15.5.4(2): The value of the internal [[Prototype]] property of the String prototype object is
  //                 the Object prototype object (15.2.3.1).
  Object::String_prototype = make_shared<Object>(Object::Object_prototype);
  // ES1: 15.5.4(1): The String prototype object is itself a String object (its [[Class]]
  //                 is "String") whose value is an empty string.
  Object::String_prototype->__Class__ = "String"; // TODO: enum this
  Object::String_prototype->__Value__ = make_shared<String>("");

  // ES1: 15.6.4(2): The value of the internal [[Prototype]] property of the Boolean prototype object is
  //                 the Object prototype object (15.2.3.1).
  Object::Boolean_prototype = make_shared<Object>(Object::Object_prototype);
  // ES1: 15.6.4(1): The Boolean prototype object is itself a Boolean object (its [[Class]]
  //                 is "Boolean") whose value is false.
  Object::Boolean_prototype->__Class__ = "Boolean"; // TODO: enum this
  Object::Boolean_prototype->__Value__ = make_shared<Boolean>(false);

  // ES3: 15.11.4(2): The value of the internal [[Prototype]] property of the Error prototype object is
  //                  the Object prototype object (15.2.3.1).
  Object::Error_prototype = make_shared<Object>(Object::Object_prototype);
  // ES3: 15.11.4(1): The Error prototype object is itself an Error object (its [[Class]] is "Error").
  Object::Error_prototype->__Class__ = "Error"; // TODO: enum this
}

void init_builtin_objects (shared_ptr<Scope> globalScope) {
  init_builtin_prototypes(globalScope);

  // ES1: 15.2.2: The Object Constructor
  globalScope->*"Object" = Object::makeFunction(Object__Call__, Object__Construct__, Object::Object_prototype);
  // ES1: 15.2.4.2
  globalScope->*"Object"->*"prototype"->*"toString" = Object::makeFunction(Object_prototype_toString);
  // ES1: 15.2.4.3
  globalScope->*"Object"->*"prototype"->*"valueOf" = Object::makeFunction(Object_prototype_valueOf);

  // ES1: 15.3.2: The Function Constructor
  globalScope->*"Function" = Object::makeFunction(Function__Call__, Function__Construct__, Object::Function_prototype);
  // ES1: 15.3.3.2: The `length` property is `1`.
  globalScope->*"Function"->*"length" = make_shared<Number>(1);
  // ES1: 15.3.4.2
  globalScope->*"Function"->*"prototype"->*"toString" = Object::makeFunction(Function_prototype_toString);

  // TODO: ES1: 15.4.2: The Array Constructor

  // ES1: 15.3.2: The String Constructor
  globalScope->*"String" = Object::makeFunction(String__Call__, String__Construct__, Object::String_prototype);
  // ES1: 15.5.3.2:
  globalScope->*"String"->*"fromCharCode" = Object::makeFunction(String_fromCharCode);
  // ES1: 15.5.4.2
  globalScope->*"String"->*"prototype"->*"toString" = Object::makeFunction(String_prototype_toString);
  // ES1: 15.5.4.3
  globalScope->*"String"->*"prototype"->*"valueOf" = Object::makeFunction(String_prototype_valueOf);
  // ES1: 15.5.4.4
  globalScope->*"String"->*"prototype"->*"charAt" = Object::makeFunction(String_prototype_charAt);
  // TODO: ES1: 15.5.4.5: String.prototype.charCodeAt(pos)
  // ES1: 15.5.4.6
  globalScope->*"String"->*"prototype"->*"indexOf" = Object::makeFunction(String_prototype_indexOf);
  // TODO: ES1: 15.5.4.7: String.prototype.lastIndexOf(searchString, position)
  // TODO: ES1: 15.5.4.8: String.prototype.split(separator)
  // TODO: ES1: 15.5.4.9: String.prototype.substring(start)
  // TODO: ES1: 15.5.4.10: String.prototype.substring(start, end)
  // TODO: ES1: 15.5.4.11: String.prototype.toLowerCase
  // TODO: ES1: 15.5.4.12: String.prototype.toUpperCase

  // ES1: 15.6.4: The Boolean Constructor
  globalScope->*"Boolean" = Object::makeFunction(Boolean__Call__, Boolean__Construct__, Object::Boolean_prototype);
  // ES1: 15.6.4.2
  globalScope->*"Boolean"->*"prototype"->*"toString" = Object::makeFunction(Boolean_prototype_toString);
  // ES1: 15.6.4.3
  globalScope->*"Boolean"->*"prototype"->*"valueOf" = Object::makeFunction(Boolean_prototype_valueOf);

  // ES3: 15.11.2: The Error Constructor
  globalScope->*"Error" = Object::makeFunction(Error__Call__, Error__Construct__, Object::Error_prototype);
  // ES3: 15.11.4.2
  globalScope->*"Error"->*"prototype"->*"name" = make_shared<String>("Error");
  // ES3: 15.11.4.3
  globalScope->*"Error"->*"prototype"->*"message" = make_shared<String>("");
  // ES3: 15.11.4.4
  globalScope->*"Error"->*"prototype"->*"toString" = Object::makeFunction(Error_prototype_toString);

  // TODO: ES3: 15.11.6.2: RangeError
  
  // ES3: 15.11.6.3: ReferenceError
  // `Error__Construct__` is generic enough to be reused
  globalScope->*"ReferenceError" = Object::makeFunction(ReferenceError__Call__, Error__Construct__, _new(globalScope->*"Error"));
  // ES3: 15.11.7.9
  globalScope->*"ReferenceError"->*"prototype"->*"name" = make_shared<String>("ReferenceError");

  // TODO: ES3: 15.11.6.5: TypeError
  // `Error__Construct__` is generic enough to be reused
  globalScope->*"TypeError" = Object::makeFunction(TypeError__Call__, Error__Construct__, _new(globalScope->*"Error"));
  // ES3: 15.11.7.9
  globalScope->*"TypeError"->*"prototype"->*"name" = make_shared<String>("TypeError");
}
