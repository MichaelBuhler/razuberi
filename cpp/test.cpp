#include <string>
#include <vector>

#include "razuberi.h"

using namespace std;

void run (shared_ptr<Scope> scope) {
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
    shared_ptr<Object> A = make_shared<Object>(static_pointer_cast<Object>(scope->*"console"), nullptr);
    A->__Put__("hello", make_shared<String>("world"));
    shared_ptr<Object> B = make_shared<Object>(A, nullptr);
    shared_ptr<Object> C = make_shared<Object>(B, nullptr);
    _call(scope->*"console"->*"log", C->*"hello");
  }
  _call(scope->*"console"->*"log", _new(scope->*"Boolean", make_shared<Boolean>(true)));
  {
    shared_ptr<Object> str = _new(scope->*"String", make_shared<String>("Hello, world!"));
    shared_ptr<Value> c = _call(str->*"charAt", make_shared<Number>(1));
    _call(scope->*"console"->*"log", (
      str,
      str->*"length",
      c
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
    make_shared<String>("Hello,") + make_shared<String>("world!") + make_shared<Number>(123.456)
  ));
  _assign(scope->*"console"->*"hello", make_shared<String>("world"));
  _call(scope->*"console"->*"log", scope->*"console"->*"hello");
}
