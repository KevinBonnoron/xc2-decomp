#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
struct MdsMpfObjData;

class DrMdoCtlMpfWork {
public:
  // Inferred role: object select buffer; original type name unknown.
  struct unknown001 {
    u8 _00[0x20];
    u16 unknown20; // Inferred role: object check; original member name unknown.
    u8 _22[0x40 - 0x22];
  };

  DrMdoCtlMpfWork();
  static int calcRenderListWork(int count, const MdsMpfObjData *data);
  void changeMemWork(const MdsMpfObjData *data);
  u16 getObjChk(int index);

  u8 _00[0x20 - 0x00];
  unknown001 *unknown20; // Inferred role: object select buffers; original member name unknown.
  u8 _28[0x38 - 0x28];
  const MdsMpfObjData *unknown38; // Inferred role: object data; original member name unknown.
};

static_assert(sizeof(DrMdoCtlMpfWork::unknown001) == 0x40, "");
static_assert(offsetof(DrMdoCtlMpfWork::unknown001, unknown20) == 0x20, "");
static_assert(offsetof(DrMdoCtlMpfWork, unknown20) == 0x20, "");
static_assert(offsetof(DrMdoCtlMpfWork, unknown38) == 0x38, "");

} // namespace ml
