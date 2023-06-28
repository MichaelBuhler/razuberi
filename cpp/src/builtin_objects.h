#pragma once

#include <memory>

#include "scope.h"

void init_builtin_objects (std::shared_ptr<Scope> globalScope);
