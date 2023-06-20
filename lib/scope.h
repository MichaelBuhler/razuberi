#pragma once
#include "scope.fwd.h"

#include "value.fwd.h"
#include "value.h"

#include <map>
#include <memory>
#include <string>

using namespace std;

class Scope {
  private: map<string, shared_ptr<Value> > locals;
  public: Scope ();
  public: shared_ptr<Value> get (string name);
  public: void set (string key, shared_ptr<Value> value);
};

shared_ptr<Value> inline operator ->* (shared_ptr<Scope> scope, string name) {
  return scope->get(name);
}
