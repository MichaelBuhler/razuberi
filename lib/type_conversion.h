#pragma once

#include <memory>

#include "value.h"

// TODO: ToPrimitive() should include a hint
shared_ptr<Primitive> ToPrimitive (shared_ptr<Value> value);

shared_ptr<Boolean> ToBoolean (shared_ptr<Value> value);

shared_ptr<Number> ToNumber (shared_ptr<Value> value);

shared_ptr<String> ToString (shared_ptr<Value> value);

shared_ptr<Object> ToObject (shared_ptr<Value> value);
