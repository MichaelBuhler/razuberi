#include "scope.h"

using namespace std;

Scope::Scope (shared_ptr<Scope> parentScope) {
  this->object = Object();
  this->parentScope = parentScope;
}

Reference Scope::operator ->* (string identifier) {
  if (this->object.__HasProperty__(identifier)) {
    return Reference(make_shared<Object>(this->object), make_shared<String>(identifier));
  }
  if (this->parentScope) {
    return this->parentScope->*identifier;
  }
  return Reference(make_shared<Null>(), make_shared<String>(identifier));
}

Reference operator ->* (shared_ptr<Scope> scope, string identifier) {
  if (scope->object.__HasProperty__(identifier)) {
    return Reference(make_shared<Object>(scope->object), make_shared<String>(identifier));
  }
  if (scope->parentScope) {
    return scope->parentScope->*identifier;
  }
  return Reference(make_shared<Null>(), make_shared<String>(identifier));
}
