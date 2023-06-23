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
    params.push_back(make_shared<String>("Hello, world!"));
    _invoke(scope->*"console"->*"log", scope, params);
  }
  {
    shared_ptr<Object> A = make_shared<Object>(static_pointer_cast<Object>(scope->*"console"));
    A->__Put__("hello", make_shared<String>("world"));
    shared_ptr<Object> B = make_shared<Object>(A);
    shared_ptr<Object> C = make_shared<Object>(B);
    vector<shared_ptr<Value> > params;
    params.push_back(C->__Get__("hello"));
    _invoke(scope->*"console"->*"log", scope, params);
  }
}
