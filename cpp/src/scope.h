#pragma once

#include "value.h"

#include <memory>
#include <string>

class Scope {
  public: Object object;
  public: std::shared_ptr<Scope> parentScope;
  public: Scope (std::shared_ptr<Scope> parentScope = nullptr);
  public: Reference operator ->* (std::string name);
};

Reference operator ->* (std::shared_ptr<Scope> scope, std::string name);
