#include "builtin_objects.h"

#include "exception.h"
#include "value.h"
#include "type_conversion.h"

using namespace std;

shared_ptr<Value> _Function__Call__ (shared_ptr<Value> thisArg, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  throw new NotImplementedException("Cannot use the Function function to create new functions at runtime.");
}

shared_ptr<Value> _Function_prototype_toString (shared_ptr<Value> thisArg, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  // TODO: needs the context of a `this` arg
  throw new NotImplementedException("Function.prototype.toString()");
}

shared_ptr<Value> _Boolean__Call__ (shared_ptr<Value> thisArg, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  if (arguments.size() == 0) return make_shared<Boolean>(false);
  return ToBoolean(arguments[0]);
}

shared_ptr<Value> _Boolean_prototype_toString (shared_ptr<Value> thisArg, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  // TODO: needs the context of a `this` arg
  throw new NotImplementedException("Boolean.prototype.toString()");
}

shared_ptr<Value> _Boolean_prototype_valueOf (shared_ptr<Value> thisArg, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  // TODO: needs the context of a `this` arg
  throw new NotImplementedException("Boolean.prototype.valueOf()");
}

void init_builtin_objects (shared_ptr<Scope> globalScope) {
  shared_ptr<Object> FunctionPrototype = make_shared<Object>();
  shared_ptr<Object> Function = make_shared<Object>(FunctionPrototype, _Function__Call__);
  Function->__Put__("prototype", FunctionPrototype);
  Function->__Put__("length", make_shared<Number>(1));
  FunctionPrototype->__Put__("constructor", Function);
  FunctionPrototype->__Put__("toString", make_shared<Object>(nullptr, _Function_prototype_toString));
  globalScope->set("Function", Function);

  shared_ptr<Object> BooleanPrototype = make_shared<Object>();
  shared_ptr<Object> Boolean = make_shared<Object>(BooleanPrototype, _Boolean__Call__);
  Boolean->__Put__("prototype", BooleanPrototype);
  Boolean->__Put__("length", make_shared<Number>(1));
  BooleanPrototype->__Put__("constructor", Boolean);
  BooleanPrototype->__Put__("toString", make_shared<Object>(nullptr, _Boolean_prototype_toString));
  BooleanPrototype->__Put__("valueOf", make_shared<Object>(nullptr, _Boolean_prototype_valueOf));
  globalScope->set("Boolean", Boolean);
}
