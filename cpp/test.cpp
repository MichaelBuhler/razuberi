#include <string>
#include <vector>

#include "razuberi.h"
#include "reference.h"

using namespace std;

void run (Scope& scope) {
  _call(scope->*"console"->*"log", (
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
    _call(scope->*"console"->*"log", scope->*"C"->*"hello");
  }
  _call(scope->*"console"->*"log", _new(scope->*"Boolean", make_shared<Boolean>(true)));
  {
    scope->*"str" = _new(scope->*"String", make_shared<String>("Hello, world!"));
    scope->*"c" = _call(scope->*"str"->*"charAt", make_shared<Number>(1));
    _call(scope->*"console"->*"log", (
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
    _call(scope->*"console"->*"log", (
      oneTwoThree + oneTwoThree,
      oneTwoThree - oneTwoThree,
      oneTwoThree + NaN,
      Infinity + oneTwoThree,
      Infinity + NegativeInfinity,
      oneTwoThree - Infinity
    ));
  }
  _call(scope->*"console"->*"log", (
    scope->*"Boolean",
    make_shared<String>("Hello,"),
    scope->*"NaN" + _call(_new(scope->*"Object")->*"toString")
  ));
  scope->*"console"->*"hello" = make_shared<String>("world");
  _call(scope->*"console"->*"log", scope->*"console"->*"hello");
}
