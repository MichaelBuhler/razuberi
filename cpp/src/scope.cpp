#include "scope.h"

#include "value.h"

using namespace std;

Scope::Scope (shared_ptr<Scope> parentScope) {
  this->object = make_shared<Object>();
  this->parentScope = parentScope;
}

void Scope::declare (string identifier, shared_ptr<Value> value) {
  if (!this->object->__HasProperty__(identifier)) {
    this->object->__Put__(identifier, value);
  }
}

Reference operator ->* (shared_ptr<Scope> scope, string identifier) {
  if (scope->object->__HasProperty__(identifier)) {
    return Reference(scope->object, make_shared<String>(identifier));
  }
  if (scope->parentScope) {
    // TODO: this access should not be recursive.
    return scope->parentScope->*identifier;
  }
  return Reference(make_shared<Null>(), make_shared<String>(identifier));
}
