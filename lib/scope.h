#pragma once
#include "scope.fwd.h"

#include "value.fwd.h"
#include "value.h"

#include <map>
#include <memory>
#include <string>

class Scope {
  private: std::map<std::string, std::shared_ptr<Value> > locals;
  private: std::shared_ptr<Scope> parentScope;
  public: Scope (std::shared_ptr<Scope> parentScope = nullptr);
  public: std::shared_ptr<Value> get (std::string name);
  public: void set (std::string key, std::shared_ptr<Value> value);
};

std::shared_ptr<Value> inline operator ->* (std::shared_ptr<Scope> scope, std::string name) {
  return scope->get(name);
}


