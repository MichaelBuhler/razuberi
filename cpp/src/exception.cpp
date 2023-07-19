#include "exception.h"

using namespace std;

RazuberiException::RazuberiException () {}

ImplementationException::ImplementationException (string message) : RazuberiException() {
  this->message = message;
}

string ImplementationException::toString () const {
  return "ImplementationException: " + this->message;
}

NotImplementedException::NotImplementedException (string message) : RazuberiException() {
  this->message = message;
}

string NotImplementedException::toString () const {
  return "NotImplementedException: " + this->message;
}

EcmaScriptRuntimeError::EcmaScriptRuntimeError () {}
