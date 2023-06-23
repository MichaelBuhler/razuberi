#include "scope.h"

using namespace std;

Scope::Scope (shared_ptr<Scope> parentScope) {
  this->parentScope = parentScope;
}

shared_ptr<Value> Scope::get (string name) {
  try {
    return this->locals.at(name);
  } catch (out_of_range e) {
    if (this->parentScope == nullptr) {
      return make_shared<Undefined>();
    } else {
      return this->parentScope->get(name);
    }
  }
}

void Scope::set (string key, shared_ptr<Value> value) {
  this->locals[key] = value;
}
