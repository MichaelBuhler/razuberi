#pragma once

#include <string>

class RazuberiException {
  protected: std::string message;
  public: RazuberiException ();
  public: virtual std::string toString () = 0;
};

class NotImplementedException : public RazuberiException {
  public: NotImplementedException (std::string message);
  public: std::string toString ();
};

class ImplementationException : public RazuberiException {
  public: ImplementationException (std::string message);
  public: std::string toString ();
};

class EcmaScriptRuntimeError {
  protected: std::string message;
  public: EcmaScriptRuntimeError ();
  public: virtual std::string toString () = 0;
};


class TypeError : public EcmaScriptRuntimeError {
  public: TypeError (std::string message);
  public: std::string toString ();
};

class ReferenceError : public EcmaScriptRuntimeError {
  public: ReferenceError (std::string message);
  public: std::string toString ();
};
