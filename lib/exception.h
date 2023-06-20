#pragma once

#include <string>

using namespace std;

class NotImplementedException {
  private: string message;
  public: NotImplementedException ();
  public: NotImplementedException (string message);
  public: string toString ();
};

class RuntimeException {
  protected: string message;
  public: virtual string toString () = 0;
};

class TypeError : public RuntimeException {
  public: TypeError (string message);
  public: string toString ();
};
