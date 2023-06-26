#pragma once

#include <memory>

#include "value.h"

// TODO: ToPrimitive() should include a hint
std::shared_ptr<Primitive> ToPrimitive (std::shared_ptr<Value> value);

std::shared_ptr<Boolean> ToBoolean (std::shared_ptr<Value> value);

std::shared_ptr<Number> ToNumber (std::shared_ptr<Value> value);

std::shared_ptr<String> ToString (std::shared_ptr<Value> value);

std::shared_ptr<Object> ToObject (std::shared_ptr<Value> value);
