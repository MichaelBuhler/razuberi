#pragma once

#include <string>

class NotImplementedException {
  private: std::string message;
  public: NotImplementedException ();
  public: NotImplementedException (std::string message);
  public: std::string toString ();
};

class RuntimeException {
  protected: std::string message;
  public: virtual std::string toString () = 0;
};

class TypeError : public RuntimeException {
  public: TypeError (std::string message);
  public: std::string toString ();
};
