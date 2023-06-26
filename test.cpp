#include <string>
#include <vector>

#include "razuberi.h"

using namespace std;

void run (shared_ptr<Scope> scope) {
  {
    vector<shared_ptr<Value> > params;
    params.push_back(make_shared<Undefined>());
    params.push_back(make_shared<Null>());
    params.push_back(make_shared<Boolean>(true));
    params.push_back(make_shared<Boolean>(false));
    params.push_back(make_shared<Number>(123.45));
    params.push_back(scope->*"NaN");
    params.push_back(Number::makeInfinity(true));
    params.push_back(make_shared<String>("Hello, world!"));
    _call(scope->*"console", "log", scope, params);
  }
  {
    shared_ptr<Object> A = make_shared<Object>(static_pointer_cast<Object>(scope->*"console"), nullptr);
    A->__Put__("hello", make_shared<String>("world"));
    shared_ptr<Object> B = make_shared<Object>(A, nullptr);
    shared_ptr<Object> C = make_shared<Object>(B, nullptr);
    vector<shared_ptr<Value> > params;
    params.push_back(C->__Get__("hello"));
    _call(scope->*"console", "log", scope, params);
  }
  {
    vector<shared_ptr<Value> > params;
    params.push_back(make_shared<Boolean>(true));
    shared_ptr<Object> tmp = _new(scope->*"Boolean", params);
    {
      vector<shared_ptr<Value> > params;
      params.push_back(tmp);
      _call(scope->*"console", "log", scope, params);
    }
  }
  {
    vector<shared_ptr<Value> > params;
    params.push_back(make_shared<String>("Hello, world!"));
    shared_ptr<Object> str = _new(scope->*"String", params);
    {
      vector<shared_ptr<Value> > params;
      params.push_back(make_shared<Number>(1));
      shared_ptr<Value> c = _call(str, "charAt", scope, params);
      {
        vector<shared_ptr<Value> > params;
        params.push_back(str);
        params.push_back(str->*"length");
        params.push_back(c);
        _call(scope->*"console", "log", scope, params);
      }
    }
  }
}
