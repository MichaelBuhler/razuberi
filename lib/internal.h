#pragma once

#include <memory>

#include "scope.h"
#include "value.h"

std::shared_ptr<Value> _call (std::shared_ptr<Value> value, std::shared_ptr<Scope> scope, std::vector<std::shared_ptr<Value> > params);

std::shared_ptr<Object> _new (std::shared_ptr<Value> value, std::vector<std::shared_ptr<Value> > params);
