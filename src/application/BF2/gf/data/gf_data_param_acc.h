#pragma once
#include "types.h"

namespace gf {

enum GimmickType {};

class DataParamAcc {
public:
  DataParamAcc(u32 objectType, u32 id, GimmickType gimmickType);
  virtual ~DataParamAcc();

  bool isValid() const;
  const char *getModelResourceName() const;
  u32 getBlade(int slot, bool isVirtual) const;

private:
  u8 _08[0x18 - 0x08];
};

} // namespace gf
