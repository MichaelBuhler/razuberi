#pragma once

#include <memory>

#include "value.h"

std::shared_ptr<Value> GetBase (Reference);
std::shared_ptr<Value> GetBase (std::shared_ptr<Value>);

std::shared_ptr<String> GetPropertyName (Reference);
std::shared_ptr<String> GetPropertyName (std::shared_ptr<Value>);

std::shared_ptr<Value> GetValue (Reference);

void PutValue (Reference, std::shared_ptr<Value>);
