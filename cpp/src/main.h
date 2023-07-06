#pragma once

#include <memory>

#include "scope.h"

int main();

void _run (std::shared_ptr<Scope> globalScope);
