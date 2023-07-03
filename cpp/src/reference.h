#pragma once

#include <memory>

#include "value.h"

std::shared_ptr<Value> GetBase (Reference ref);
std::shared_ptr<Value> GetBase (std::shared_ptr<Value> ref);

std::shared_ptr<String> GetPropertyName (Reference ref);
std::shared_ptr<String> GetPropertyName (std::shared_ptr<Value> ref);

std::shared_ptr<Value> GetValue (Reference ref);
std::shared_ptr<Value> GetValue (std::shared_ptr<Value> val);

void PutValue (Reference ref, std::shared_ptr<Value> val);
void PutValue (std::shared_ptr<Value> ref, std::shared_ptr<Value> val);
