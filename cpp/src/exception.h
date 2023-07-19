#pragma once

#include <string>

class RazuberiException {
  protected: std::string message;
  public: RazuberiException ();
  public: virtual std::string toString () const = 0;
};

class NotImplementedException : public RazuberiException {
  public: NotImplementedException (std::string message);
  public: std::string toString () const;
};

class ImplementationException : public RazuberiException {
  public: ImplementationException (std::string message);
  public: std::string toString () const;
};

class EcmaScriptRuntimeError {
  protected: std::string message;
  public: EcmaScriptRuntimeError ();
  public: virtual std::string toString () const = 0;
};
