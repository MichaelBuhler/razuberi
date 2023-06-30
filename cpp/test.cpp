#include <string>
#include <vector>

#include "razuberi.h"

using namespace std;

void run (shared_ptr<Scope> scope) {
  {
    vector<shared_ptr<Value> > args;
    args.push_back(make_shared<Undefined>());
    args.push_back(make_shared<Null>());
    args.push_back(make_shared<Boolean>(true));
    args.push_back(make_shared<Boolean>(false));
    args.push_back(make_shared<Number>(123.45));
    args.push_back(scope->*"NaN");
    args.push_back(Number::makeInfinity(true));
    args.push_back(make_shared<String>("Hello, world!"));
    _call(scope->*"console", "log", scope, args);
  }
  {
    shared_ptr<Object> A = make_shared<Object>(static_pointer_cast<Object>(scope->*"console"), nullptr);
    A->__Put__("hello", make_shared<String>("world"));
    shared_ptr<Object> B = make_shared<Object>(A, nullptr);
    shared_ptr<Object> C = make_shared<Object>(B, nullptr);
    vector<shared_ptr<Value> > args;
    args.push_back(C->__Get__("hello"));
    _call(scope->*"console", "log", scope, args);
  }
  {
    vector<shared_ptr<Value> > args;
    args.push_back(make_shared<Boolean>(true));
    shared_ptr<Object> tmp = _new(scope->*"Boolean", args);
    {
      vector<shared_ptr<Value> > args;
      args.push_back(tmp);
      _call(scope->*"console", "log", scope, args);
    }
  }
  {
    vector<shared_ptr<Value> > args;
    args.push_back(make_shared<String>("Hello, world!"));
    shared_ptr<Object> str = _new(scope->*"String", args);
    {
      vector<shared_ptr<Value> > args;
      args.push_back(make_shared<Number>(1));
      shared_ptr<Value> c = _call(str, "charAt", scope, args);
      {
        vector<shared_ptr<Value> > args;
        args.push_back(str);
        args.push_back(str->*"length");
        args.push_back(c);
        _call(scope->*"console", "log", scope, args);
      }
    }
  }
  {
    shared_ptr<Value> oneTwoThree = make_shared<Number>(123);
    shared_ptr<Value> NaN = Number::makeNaN();
    shared_ptr<Value> Infinity = Number::makeInfinity();
    shared_ptr<Value> NegativeInfinity = Number::makeInfinity(true);
    vector<shared_ptr<Value> > args;
    args.push_back(oneTwoThree + oneTwoThree);
    args.push_back(oneTwoThree - oneTwoThree);
    args.push_back(oneTwoThree + NaN);
    args.push_back(Infinity + oneTwoThree);
    args.push_back(Infinity + NegativeInfinity);
    args.push_back(oneTwoThree - Infinity);
    _call(scope->*"console", "log", scope, args);
  }
}
