#pragma once
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class MdlstmData : public mm::mtl::Singleton<MdlstmData> {
public:
  static constexpr u32 INFO_COUNT = 1;

  struct Info {
    mm::mtl::FixStr<128> unknown00; // Inferred role: resource name; original member name unknown.
    u32 unknown84;                  // Inferred role: kind of resource (1 driver, 2 blade, 4 enemy, 5 weapon); original member name unknown.
    int unknown88;                  // Inferred role: bdat id; original member name unknown.
    int unknown8c;                  // Inferred role: blade bdat id of a weapon; original member name unknown.
    bool unknown90;                 // Inferred role: is left weapon; original member name unknown.
  };

  virtual ~MdlstmData() {}
  void clear();
  void addReplaceInfo(const Info &info);

private:
  mm::mtl::FixedVector<Info, INFO_COUNT> unknown08; // Inferred role: replace infos; original member name unknown.
};

static_assert(sizeof(MdlstmData::Info) == 0x94, "");
static_assert(sizeof(MdlstmData) == 0xa8, "");

} // namespace event
