#pragma once
#include "event/block_time.h"
#include "event/block_wtr.h"
#include "event/i_manager.h"
#include "ml/work_event.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace event {

class BlockManager : public IManager, public ml::IWorkEvent, public mm::mtl::Singleton<BlockManager> {
public:
  static constexpr u32 BLOCK_COUNT = 32;

  BlockManager();
  virtual ~BlockManager() {}
  void create(mtl::ALLOC_HANDLE handle);
  void destroy();
  void initWtr(void *data, u32 size, mtl::ALLOC_HANDLE handle);
  void initTime(void *data, u32 size, mtl::ALLOC_HANDLE handle);
  bool isWtrBlock(u32 id);
  bool isTimeBlock(u32 id);

private:
  void *unknown18;                                        // Inferred role: wtr data; original member name unknown.
  void *unknown20;                                        // Inferred role: time data; original member name unknown.
  mm::mtl::FixedArray<BlockWtr, BLOCK_COUNT> unknown28;   // Inferred role: wtrs; original member name unknown.
  mm::mtl::FixedArray<BlockTime, BLOCK_COUNT> unknown428; // Inferred role: times; original member name unknown.
};

static_assert(sizeof(BlockManager) == 0x528, "");

} // namespace event
