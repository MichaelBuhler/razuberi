#include "global_scope.h"

#include "builtin_objects.h"
#include "host_objects.h"

shared_ptr<Scope> init_global_scope () {
  shared_ptr<Scope> globalScope = make_shared<Scope>(nullptr);
  init_builtin_objects(globalScope);
  init_host_objects(globalScope);
  return globalScope;
}
