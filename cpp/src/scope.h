#pragma once

#include <memory>
#include <string>

#include "value.fwd.h"
#include "reference.h"

class Scope {
  public: std::shared_ptr<Object> object;
  public: std::shared_ptr<Scope> parentScope;
  public: Scope (std::shared_ptr<Scope> parentScope = nullptr);
};

Reference operator ->* (std::shared_ptr<Scope> scope, std::string name);
