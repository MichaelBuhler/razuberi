#pragma once

#include <memory>
#include <vector>

#include "scope.h"
#include "value.h"

std::shared_ptr<Value> _assign(Reference ref, Reference otherRef);
std::shared_ptr<Value> _assign(Reference ref, std::shared_ptr<Reference> otherRef);
std::shared_ptr<Value> _assign(Reference ref, std::shared_ptr<Value> val);
std::shared_ptr<Value> _assign(std::shared_ptr<Reference> ref, std::shared_ptr<Reference> otherRef);
std::shared_ptr<Value> _assign(std::shared_ptr<Reference> ref, Reference otherRef);
std::shared_ptr<Value> _assign(std::shared_ptr<Reference> ref, std::shared_ptr<Value> val);

std::shared_ptr<Value> _call (Reference ref);
std::shared_ptr<Value> _call (Reference ref, Reference val);
std::shared_ptr<Value> _call (Reference ref, std::shared_ptr<Value> val);
std::shared_ptr<Value> _call (Reference ref, std::vector<std::shared_ptr<Value> > params);
std::shared_ptr<Value> _call (std::shared_ptr<Value> maybeRef);
std::shared_ptr<Value> _call (std::shared_ptr<Value> maybeRef, Reference val);
std::shared_ptr<Value> _call (std::shared_ptr<Value> maybeRef, std::shared_ptr<Value> val);
std::shared_ptr<Value> _call (std::shared_ptr<Value> maybeRef, std::vector<std::shared_ptr<Value> > params);

bool _if (std::shared_ptr<Value> maybeRef);

std::shared_ptr<Object> _new (Reference ref);
std::shared_ptr<Object> _new (Reference ref, std::shared_ptr<Value> val);
std::shared_ptr<Object> _new (Reference ref, std::vector<std::shared_ptr<Value> > params);
std::shared_ptr<Object> _new (std::shared_ptr<Value> maybeRef);
std::shared_ptr<Object> _new (std::shared_ptr<Value> maybeRef, std::shared_ptr<Value> val);
std::shared_ptr<Object> _new (std::shared_ptr<Value> maybeRef, std::vector<std::shared_ptr<Value> > params);

std::shared_ptr<Value> __DefaultValue__ (std::shared_ptr<Object> _this, HintValueType hint);
