#include "builtin_objects.h"

#include "value.h"
#include "type_conversion.h"

shared_ptr<Value> _Boolean (shared_ptr<Scope> callingScope, vector<shared_ptr<Value> > arguments) {
  if (arguments.size() == 0 ) return make_shared<Boolean>(false);
  return ToBoolean(arguments[0]);
}

void init_builtin_objects (shared_ptr<Scope> globalScope) {
  shared_ptr<Object> BooleanPrototype = make_shared<Object>(nullptr);
  shared_ptr<Object> Boolean = make_shared<Object>(BooleanPrototype, _Boolean);
  globalScope->set("Boolean", Boolean);
}
