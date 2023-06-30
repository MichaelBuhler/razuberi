#include "exception.h"

using namespace std;

RazuberiException::RazuberiException () {}

ImplementationException::ImplementationException (string message) : RazuberiException() {
  this->message = message;
}

string ImplementationException::toString () {
  return "ImplementationException: " + this->message;
}

NotImplementedException::NotImplementedException (string message) : RazuberiException() {
  this->message = message;
}

string NotImplementedException::toString () {
  return "NotImplementedException: " + this->message;
}

EcmaScriptRuntimeError::EcmaScriptRuntimeError () {}

TypeError::TypeError (string message) : EcmaScriptRuntimeError() {
  this->message = message;
}

string TypeError::toString () {
  return "TypeError: " + this->message;
}

ReferenceError::ReferenceError (string message) : EcmaScriptRuntimeError() {
  this->message = message;
}

string ReferenceError::toString () {
  return "ReferenceError: " + this->message;
}
