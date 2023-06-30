#pragma once

#include <string>

#include "value.h"

void debug (std::string str);

void debug (std::shared_ptr<Value> value);

void debug (std::string str, std::shared_ptr<Value> value);
