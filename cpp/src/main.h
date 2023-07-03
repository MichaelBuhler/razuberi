#pragma once

#include <memory>

#include "scope.h"

int main();

void run (std::shared_ptr<Scope> globalScope);
