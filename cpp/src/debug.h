#pragma once

#include <string>

#include "scope.h"
#include "value.h"

void debug (std::string str = "");

void debug (Scope scope);
void debug (std::string str, Scope scope);

void debug (Reference ref);
void debug (std::string str, Reference ref);

void debug (std::shared_ptr<Value> value);
void debug (std::string str, std::shared_ptr<Value> value);
