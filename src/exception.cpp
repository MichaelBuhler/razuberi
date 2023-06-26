#include "exception.h"

using namespace std;

NotImplementedException::NotImplementedException () {}

NotImplementedException::NotImplementedException (string message) {
  this->message = message;
}

string NotImplementedException::toString () {
  return "NotImplementedException: " +  this->message;
}

TypeError::TypeError (string message) : RuntimeException() {
  this->message = message;
}

string TypeError::toString () {
  return "TypeError: " + this->message;
}
