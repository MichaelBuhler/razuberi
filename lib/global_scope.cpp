#include "global_scope.h"

#include "builtin_objects.h"
#include "host_objects.h"

using namespace std;

shared_ptr<Scope> init_global_scope () {
  shared_ptr<Scope> globalScope = make_shared<Scope>();

  globalScope->set("NaN", Number::makeNaN());
  globalScope->set("Infinity", Number::makeInfinity());

  init_builtin_objects(globalScope);
  init_host_objects(globalScope);
  return globalScope;
}
