#pragma once
#include <stddef.h>

#include "event/i_manager.h"
#include "event/i_res_event.h"
#include "event/i_res_pack_event.h"
#include "event/res_pack_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/noncopyable.h"
#include "types.h"

namespace fw {
class RenderResource;
} // namespace fw

namespace event {

class ResManager : public IManager, public mm::mtl::NoncopyableBase, public IResPackEvent {
public:
  static constexpr u32 ITEM_COUNT = 512;

  enum {
    FLAG_DISP = 1 << 0,
  };

  enum {
    SCROLL_UP_BUTTON = 1 << 12,
    SCROLL_DOWN_BUTTON = 1 << 14,
  };

  struct Item {
    static constexpr u32 EVENT_COUNT = 96;

    Item(const char *path, IResEvent *event, bool isPackOnly, RES_RESULT_TYPE result, void *adr, size_t size, bool isPackLoaded);
    Item();
    void addRef(IResEvent *event);

    mm::mtl::FixStr<256> path;
    IResEvent *mEvents[EVENT_COUNT];
    bool mIsPackOnly;
    u32 mCallbackIndex;
    u32 mEventCount;
    fw::RenderResource *mResource;
    void *mAdr;
    size_t mSize;
    RES_RESULT_TYPE mResult;
    bool mIsPackLoaded;
  };

  ResManager();
  virtual ~ResManager() {}
  void clear();
  void update();
  void updateNormal();
  void execCallback(Item *item);
  void render();
  static const char *filename(const char *path);
  void loadPack(const char *path);
  void load(const char *path, IResEvent *event, bool isPackOnly);
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

static_assert(sizeof(ResManager::Item) == 0x438, "");
static_assert(sizeof(ResManager) == 0x10c0, "");

} // namespace event
