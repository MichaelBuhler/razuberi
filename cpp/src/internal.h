#pragma once

#include <memory>
#include <vector>

#include "scope.h"
#include "value.h"

std::shared_ptr<Value> _assign(Reference, Reference);
std::shared_ptr<Value> _assign(Reference, std::shared_ptr<Value>);

std::shared_ptr<Value> _call (Reference callee);
std::shared_ptr<Value> _call (Reference callee, Reference firstParam);
std::shared_ptr<Value> _call (Reference callee, std::shared_ptr<Value> firstParam);
std::shared_ptr<Value> _call (Reference callee, std::vector<std::shared_ptr<Value> > params);
std::shared_ptr<Value> _call (std::shared_ptr<Value> callee);
std::shared_ptr<Value> _call (std::shared_ptr<Value> callee, Reference firstParam);
std::shared_ptr<Value> _call (std::shared_ptr<Value> callee, std::shared_ptr<Value> firstParam);
std::shared_ptr<Value> _call (std::shared_ptr<Value> callee, std::vector<std::shared_ptr<Value> > params);

bool _if (Reference);
bool _if (std::shared_ptr<Value>);

std::shared_ptr<Object> _new (Reference constructor);
std::shared_ptr<Object> _new (Reference constructor, Reference firstParam);
std::shared_ptr<Object> _new (Reference constructor, std::shared_ptr<Value> firstParam);
std::shared_ptr<Object> _new (Reference constructor, std::vector<std::shared_ptr<Value> > params);
std::shared_ptr<Object> _new (std::shared_ptr<Value> constructor);
std::shared_ptr<Object> _new (std::shared_ptr<Value> constructor, Reference firstParam);
std::shared_ptr<Object> _new (std::shared_ptr<Value> constructor, std::shared_ptr<Value> firstParam);
std::shared_ptr<Object> _new (std::shared_ptr<Value> constructor, std::vector<std::shared_ptr<Value> > params);

std::shared_ptr<Value> __DefaultValue__ (std::shared_ptr<Object> _this, HintValueType);
