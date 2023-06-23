#include "razuberi.h"

#include <memory>

#include "type_conversion.h"

using namespace std;

shared_ptr<Value> _invoke (shared_ptr<Value> value, shared_ptr<Scope> scope, vector<shared_ptr<Value> > params) {
  shared_ptr<Object> obj = ToObject(value);
  return obj->__Call__(obj, scope, params);
}
