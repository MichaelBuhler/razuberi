#include "global_scope.h"

#include "builtin_objects.h"
#include "exception.h"
#include "internal.h"
#include "host_objects.h"
#include "type_conversion.h"

using namespace std;

static shared_ptr<Scope> globalScope;

// ES1: 15.1.2.1
shared_ptr<Value> eval (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> >) {
  throw NotImplementedException("Cannot use global `eval()` to execute arbitrary code at runtime.");
}

// ES1: 15.1.2.6
shared_ptr<Value> isNaN (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> > arguments) {
  // TODO: reimplement this after we have `arguments` and names/formal parameters
  shared_ptr<Number> num;
  if (arguments.size() == 0) {
    shared_ptr<Primitive> undefined = make_shared<Undefined>();
    num = ToNumber(undefined);
  } else {
    num = ToNumber(arguments[0]);
  }
  return make_shared<Boolean>(num->isNaN);
}

// ES1: 15.1.2.7
shared_ptr<Value> isFinite (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> > arguments) {
  // TODO: reimplement this after we have `arguments` and names/formal parameters
  shared_ptr<Number> num;
  if (arguments.size() == 0) {
    shared_ptr<Primitive> undefined = make_shared<Undefined>();
    num = ToNumber(undefined);
  } else {
    num = ToNumber(arguments[0]);
  }
  if (num->isNaN || num->isInfinity) {
    return make_shared<Boolean>(false);
  }
  return make_shared<Boolean>(true);
}

shared_ptr<Scope> init_global_scope () {
  // ES1: 10.1.5: There is a unique global object which is created before control enters any execution context.
  // The global scope is the last object in the scope chain; it has no parent scope.
  globalScope = make_shared<Scope>(nullptr);

  init_builtin_objects(globalScope);

  // ES1: 15.1.1.1
  globalScope->*"NaN" = Number::makeNaN();
  // ES1: 15.1.1.2
  globalScope->*"Infinity" = Number::makeInfinity();
  // ES1: 15.1.2.1
  globalScope->*"eval" = Object::makeFunction(eval);
  // TODO: ES1: 15.1.2.2: parseInt(string, radix)
  // TODO: ES1: 15.1.2.3: parseFloat(string)
  // TODO: ES1: 15.1.2.4: escape(string)
  // TODO: ES1: 15.1.2.5: unescape(string)
  // ES1: 15.1.2.6
  globalScope->*"isNaN" = Object::makeFunction(isNaN);
  // ES1: 15.1.2.7
  globalScope->*"isFinite" = Object::makeFunction(isFinite);

  init_host_objects(globalScope);
  
  return globalScope;
}

shared_ptr<Scope> get_global_scope () {
  return globalScope;
}
