#pragma once
#include "bdat.h"
#include "types.h"

struct CBdatWrapper {
  unsigned long getValCheck(const char *name, int id, int type) const { return Bdat::getValCheck(data, name, id, type); }
  Bdat::Value getValCheck(u8 *member, u32 id, int type) const { return Bdat::getValCheck(data, member, id, type); }
  Bdat::Value getArrayValCheck(u8 *member, u32 id, u32 index, int type) const { return Bdat::getArrayValCheck(data, member, id, index, type); }
  int getFlagVal(u8 *member, u32 id, u8 *flag) const { return Bdat::getFlagVal(data, member, id, flag); }

  u8 *data;
};

namespace gf {

class GfBdatRefresh {
public:
  virtual void bdatRefresh() = 0;
};

} // namespace gf
