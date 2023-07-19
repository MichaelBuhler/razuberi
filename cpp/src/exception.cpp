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

TypeError::TypeError (string message) : EcmaScriptRuntimeError() {
  this->message = message;
}

string TypeError::toString () const {
  return "TypeError: " + this->message;
}
