#pragma once

#include <memory>
#include <vector>

#include "scope.h"
#include "value.h"

// Used for constructing user-defined script functions, at runtime.
std::shared_ptr<Object> _fn (std::shared_ptr<Scope> closure, Object::CallSignature __Call_and_Construct__);

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

// TODO: could be implemented with 81 overloads
std::shared_ptr<Boolean> _strictEquals (Reference, Reference);
std::shared_ptr<Boolean> _strictEquals (Reference, std::shared_ptr<Value>);
std::shared_ptr<Boolean> _strictEquals (std::shared_ptr<Value>, Reference);
std::shared_ptr<Boolean> _strictEquals (std::shared_ptr<Value>, std::shared_ptr<Value>);
