#include "global_scope.h"

#include "builtin_objects.h"
#include "exception.h"
#include "host_objects.h"
#include "type_conversion.h"

using namespace std;

shared_ptr<Value> _eval__Call__ (shared_ptr<Value> _this, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  throw NotImplementedException("Cannot use global `eval()` to execute arbitrary code at runtime.");
}

shared_ptr<Value> _isNaN__Call__ (shared_ptr<Value> _this, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  // TODO: reimplement this after we have `arguments` and names/formal parameters
  shared_ptr<Number> num;
  if (arguments.size() == 0) {
    num = ToNumber(make_shared<Undefined>());
  } else {
    num = ToNumber(arguments[0]);
  }
  return make_shared<Boolean>(num->isNaN);
}

shared_ptr<Value> _isFinite__Call__ (shared_ptr<Value> _this, shared_ptr<Scope> scope, vector<shared_ptr<Value> > arguments) {
  // TODO: reimplement this after we have `arguments` and names/formal parameters
  shared_ptr<Number> num;
  if (arguments.size() == 0) {
    num = ToNumber(make_shared<Undefined>());
  } else {
    num = ToNumber(arguments[0]);
  }
  if (num->isNaN || num->isInfinity) {
    return make_shared<Boolean>(false);
  }
  return make_shared<Boolean>(true);
}

shared_ptr<Scope> init_global_scope () {
  shared_ptr<Scope> globalScope = make_shared<Scope>();

  globalScope->set("NaN", Number::makeNaN());
  globalScope->set("isNaN", make_shared<Object>(nullptr, _isNaN__Call__));
  globalScope->set("Infinity", Number::makeInfinity());
  globalScope->set("isFinite", make_shared<Object>(nullptr, _isFinite__Call__));

  init_builtin_objects(globalScope);
  init_host_objects(globalScope);
  return globalScope;
}
