#pragma once

#include <memory>

#include "scope.h"

std::shared_ptr<Scope> init_global_scope ();

std::shared_ptr<Scope> get_global_scope ();
