#include "scope.h"

#include "value.h"

using namespace std;

Scope::Scope (shared_ptr<Scope> parentScope) {
  this->object = make_shared<Object>();
  this->parentScope = parentScope;
}

Reference operator ->* (shared_ptr<Scope> scope, string identifier) {
  if (scope->object->__HasProperty__(identifier)) {
    return Reference(scope->object, make_shared<String>(identifier));
  }
  if (scope->parentScope) {
    return scope->parentScope->*identifier;
  }
  return Reference(make_shared<Null>(), make_shared<String>(identifier));
}
