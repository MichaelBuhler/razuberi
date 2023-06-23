#pragma once

#include <memory>

#include "scope.h"
#include "value.h"

std::shared_ptr<Value> _invoke (std::shared_ptr<Value> value, std::shared_ptr<Scope> scope, std::vector<std::shared_ptr<Value> > params);
