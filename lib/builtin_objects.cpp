#include "builtin_objects.h"

#include "exception.h"
#include "value.h"
#include "type_conversion.h"

shared_ptr<Value> _Function (shared_ptr<Scope> callingScope, vector<shared_ptr<Value> > arguments) {
  throw new NotImplementedException("Cannot use the Function function to create new functions at runtime.");
}

shared_ptr<Value> _Function_toString (shared_ptr<Scope> callingScope, vector<shared_ptr<Value> > arguments) {
  // TODO: needs the context of a `this` arg
  throw new NotImplementedException("Function.prototype.toString()");
}

shared_ptr<Value> _Boolean (shared_ptr<Scope> callingScope, vector<shared_ptr<Value> > arguments) {
  if (arguments.size() == 0 ) return make_shared<Boolean>(false);
  return ToBoolean(arguments[0]);
}

void init_builtin_objects (shared_ptr<Scope> globalScope) {
  shared_ptr<Object> FunctionPrototype = make_shared<Object>(nullptr);
  shared_ptr<Object> Function = make_shared<Object>(FunctionPrototype, _Boolean);
  Function->__Put__("prototype", FunctionPrototype);
  Function->__Put__("length", make_shared<Number>(1));
  FunctionPrototype->__Put__("constructor", Function);
  FunctionPrototype->__Put__("toString", make_shared<Object>(nullptr, _Function_toString));
  globalScope->set("Function", Function);

  shared_ptr<Object> BooleanPrototype = make_shared<Object>(nullptr);
  shared_ptr<Object> Boolean = make_shared<Object>(BooleanPrototype, _Boolean);
  globalScope->set("Boolean", Boolean);
}
