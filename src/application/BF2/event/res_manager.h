#pragma once
#include <stddef.h>

#include "event/i_manager.h"
#include "event/i_res_pack_event.h"
#include "event/res_pack_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/noncopyable.h"
#include "types.h"

namespace event {

class IResEvent;

class ResManager : public IManager, public mm::mtl::NoncopyableBase, public IResPackEvent {
public:
  static constexpr u32 ITEM_COUNT = 512;

  enum {
    FLAG_DISP = 1 << 0,
  };

  struct Item;

  ResManager();
  virtual ~ResManager() {}
  void clear();
  void update();
  void updateNormal();
  void execCallback(Item *item);
  void render();
  static const char *filename(const char *path);
  void loadPack(const char *path);
  void load(const char *path, IResEvent *event, bool isPriority);
  Item *search(const char *path);
  void *adr(const char *path, size_t *size);
  bool isLoading();
  virtual void OnPackEvent(const PARAM &param);
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 flags;
  mm::mtl::FixedVector<Item *, ITEM_COUNT> mItems;
  ResPackManager mPackManager;
  s32 mLoadingCount;
  u32 mLoadedCount;
};

static_assert(sizeof(ResManager) == 0x10c0, "");

} // namespace event
