#include <memory>
#include <string>
#include <vector>

#include "razuberi.h"

using namespace std;

shared_ptr<Value> MyConstructor (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> >);
shared_ptr<Value> MyConstructor_prototype_toString (shared_ptr<Scope>, shared_ptr<Value>, vector<shared_ptr<Value> >);

void _run (shared_ptr<Scope> scope) {
  scope->declare("MyConstructor", _fn(scope, MyConstructor));
  (scope->*"console"->*"log").call((
    make_shared<Undefined>(),
    make_shared<Null>(),
    make_shared<Boolean>(true),
    make_shared<Boolean>(false),
    make_shared<Number>(123.45),
    scope->*"NaN",
    Number::makeInfinity(true),
    make_shared<String>("Hello, world!")
  ));
  {
    scope->*"A" = make_shared<Object>();
    scope->*"A"->*"hello" = make_shared<String>("world");
    scope->*"B" = make_shared<Object>(static_pointer_cast<Object>(GetValue(scope->*"A")));
    scope->*"C" = make_shared<Object>(static_pointer_cast<Object>(GetValue(scope->*"B")));
    (scope->*"console"->*"log").call(scope->*"C"->*"hello");
  }
  (scope->*"console"->*"log").call(_new(scope->*"Boolean", make_shared<Boolean>(true)));
  {
    scope->*"str" = _new(scope->*"String", make_shared<String>("Hello, world!"));
    scope->*"c" = (scope->*"str"->*"charAt").call(make_shared<Number>(1));
    (scope->*"console"->*"log").call((
      scope->*"str",
      scope->*"str"->*"length",
      scope->*"c"
    ));
  }
  {
    shared_ptr<Value> oneTwoThree = make_shared<Number>(123);
    shared_ptr<Value> NaN = Number::makeNaN();
    shared_ptr<Value> Infinity = Number::makeInfinity();
    shared_ptr<Value> NegativeInfinity = Number::makeInfinity(true);
    (scope->*"console"->*"log").call((
      oneTwoThree + oneTwoThree,
      oneTwoThree - oneTwoThree,
      oneTwoThree + NaN,
      Infinity + oneTwoThree,
      Infinity + NegativeInfinity,
      oneTwoThree - Infinity
    ));
  }
  (scope->*"console"->*"log").call((
    make_shared<String>("Hello,"),
    scope->*"NaN" + (_new(scope->*"Object")->*"toString").call()
  ));
  scope->*"console"->*"hello" = make_shared<String>("world");
  (scope->*"console"->*"log").call(scope->*"console"->*"hello");
  scope->*"MyConstructor"->*"prototype"->*"toString" = _fn(scope, MyConstructor_prototype_toString);
  (scope->*"console"->*"log").call(_new(scope->*"MyConstructor"));
}

shared_ptr<Value> MyConstructor (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {
  return nullptr;
}

shared_ptr<Value> MyConstructor_prototype_toString (shared_ptr<Scope> scope, shared_ptr<Value> _this, vector<shared_ptr<Value> > arguments) {
  return make_shared<String>("this is a stringified instance of MyConstructor");
}
