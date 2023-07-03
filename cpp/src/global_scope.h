#pragma once

#include <memory>

#include "scope.h"

extern std::shared_ptr<Scope> globalScope;

std::shared_ptr<Scope> init_global_scope ();
