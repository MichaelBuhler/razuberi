#pragma once

#include <memory>

#include "value.h"

std::shared_ptr<Primitive> ToPrimitive (std::shared_ptr<Value> value, HintValueType hint = NONE_HINT_VALUE_TYPE);
std::shared_ptr<Primitive> ToPrimitive (std::shared_ptr<Object> obj, HintValueType hint = NONE_HINT_VALUE_TYPE);

std::shared_ptr<Boolean> ToBoolean (std::shared_ptr<Value> value);

std::shared_ptr<Number> ToNumber (std::shared_ptr<Value> value);
std::shared_ptr<Number> ToNumber (std::shared_ptr<Primitive> primitive);
std::shared_ptr<Number> ToNumber (std::shared_ptr<Boolean> boolean);

std::shared_ptr<Number> ToInteger (std::shared_ptr<Value> value);

std::shared_ptr<Number> ToInt32 (std::shared_ptr<Value> value);

std::shared_ptr<Number> ToUint32 (std::shared_ptr<Value> value);

std::shared_ptr<Number> ToUint16 (std::shared_ptr<Value> value);

std::shared_ptr<String> ToString (std::shared_ptr<Value> value);
std::shared_ptr<String> ToString (std::shared_ptr<Primitive> primitive);
std::shared_ptr<String> ToString (std::shared_ptr<Boolean> boolean);
std::shared_ptr<String> ToString (std::shared_ptr<Number> number);

std::shared_ptr<Object> ToObject (std::shared_ptr<Value> value);
