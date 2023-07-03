#pragma once

#include <memory>

#include "value.h"

std::shared_ptr<Value> GetBase (Reference);
std::shared_ptr<Value> GetBase (std::shared_ptr<Value>);

std::shared_ptr<String> GetPropertyName (Reference);
std::shared_ptr<String> GetPropertyName (std::shared_ptr<Value>);

std::shared_ptr<Value> GetValue (Reference);
std::shared_ptr<Value> GetValue (std::shared_ptr<Value>);

void PutValue (Reference, std::shared_ptr<Value>);
