#pragma once

namespace ml {

struct CERR_STRUCT;

enum ERR_DECIDE {};

class IErrorCB {
public:
  virtual ~IErrorCB() {}
  virtual bool icbError(CERR_STRUCT *error) = 0;
  virtual void icbDecide(CERR_STRUCT *error, ERR_DECIDE decide) = 0;
};

} // namespace ml
