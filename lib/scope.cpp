#include "scope.h"

Scope::Scope () {}

shared_ptr<Value> Scope::get (string name) {
  return this->locals.at(name);
}

void Scope::set (string key, shared_ptr<Value> value) {
  this->locals[key] = value;
}
