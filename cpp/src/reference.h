#pragma once

#include <memory>

#include "value.h"

std::shared_ptr<Value> GetBase (std::shared_ptr<Value> reference);

std::shared_ptr<String> GetPropertyName (std::shared_ptr<Value> reference);

std::shared_ptr<Value> GetValue (std::shared_ptr<Value> value);

void PutValue (std::shared_ptr<Value> reference, std::shared_ptr<Value> value);
