#pragma once

#include <memory>

#include "scope.h"
#include "value.h"

std::shared_ptr<Value> _call (std::shared_ptr<Value> maybeRef, std::shared_ptr<Scope> scope, std::vector<std::shared_ptr<Value> > params);

std::shared_ptr<Object> _new (std::shared_ptr<Value> maybeRef, std::vector<std::shared_ptr<Value> > params);

std::shared_ptr<Value> __DefaultValue__ (std::shared_ptr<Object> _this, HintValueType hint);
