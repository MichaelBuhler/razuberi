#pragma once

#include <memory>

#include "value.h"

std::shared_ptr<Primitive> ToPrimitive (std::shared_ptr<Value>, HintValueType = NONE_HINT_VALUE_TYPE);
std::shared_ptr<Primitive> ToPrimitive (std::shared_ptr<Object>, HintValueType = NONE_HINT_VALUE_TYPE);

std::shared_ptr<Boolean> ToBoolean (std::shared_ptr<Value>);
std::shared_ptr<Boolean> ToBoolean (std::shared_ptr<Primitive>);
std::shared_ptr<Boolean> ToBoolean (std::shared_ptr<Undefined>);
std::shared_ptr<Boolean> ToBoolean (std::shared_ptr<Null>);
std::shared_ptr<Boolean> ToBoolean (std::shared_ptr<Number>);
std::shared_ptr<Boolean> ToBoolean (std::shared_ptr<String>);
std::shared_ptr<Boolean> ToBoolean (std::shared_ptr<Object>);

std::shared_ptr<Number> ToNumber (std::shared_ptr<Value>);
std::shared_ptr<Number> ToNumber (std::shared_ptr<Primitive>);
std::shared_ptr<Number> ToNumber (std::shared_ptr<Undefined>);
std::shared_ptr<Number> ToNumber (std::shared_ptr<Null>);
std::shared_ptr<Number> ToNumber (std::shared_ptr<Boolean>);
std::shared_ptr<Number> ToNumber (std::shared_ptr<String>);
std::shared_ptr<Number> ToNumber (std::shared_ptr<Object>);

std::shared_ptr<Number> ToInteger (std::shared_ptr<Value>);

std::shared_ptr<Number> ToInt32 (std::shared_ptr<Value>);

std::shared_ptr<Number> ToUint32 (std::shared_ptr<Value>);

std::shared_ptr<Number> ToUint16 (std::shared_ptr<Value>);

std::shared_ptr<String> ToString (std::shared_ptr<Value>);
std::shared_ptr<String> ToString (std::shared_ptr<Primitive>);
std::shared_ptr<String> ToString (std::shared_ptr<Undefined>);
std::shared_ptr<String> ToString (std::shared_ptr<Null>);
std::shared_ptr<String> ToString (std::shared_ptr<Boolean>);
std::shared_ptr<String> ToString (std::shared_ptr<Number>);
std::shared_ptr<String> ToString (std::shared_ptr<Object>);

std::shared_ptr<Object> ToObject (std::shared_ptr<Value>);
