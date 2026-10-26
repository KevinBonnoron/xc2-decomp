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

    mm::mtl::FixStr<256> unknown00;     // Inferred role: path; original member name unknown.
    IResEvent *unknown108[EVENT_COUNT]; // Inferred role: events; original member name unknown.
    bool unknown408;                    // Inferred role: is pack only; original member name unknown.
    u32 unknown40c;                     // Inferred role: callback index; original member name unknown.
    u32 unknown410;                     // Inferred role: event count; original member name unknown.
    fw::RenderResource *unknown418;     // Inferred role: resource; original member name unknown.
    void *unknown420;                   // Inferred role: adr; original member name unknown.
    size_t unknown428;                  // Inferred role: size; original member name unknown.
    RES_RESULT_TYPE unknown430;         // Inferred role: result; original member name unknown.
    bool unknown434;                    // Inferred role: is pack loaded; original member name unknown.
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
  u32 unknown18;                                      // Inferred role: flags; original member name unknown.
  mm::mtl::FixedVector<Item *, ITEM_COUNT> unknown20; // Inferred role: items; original member name unknown.
  ResPackManager unknown1028;                         // Inferred role: pack manager; original member name unknown.
  s32 unknown10b8;                                    // Inferred role: loading count; original member name unknown.
  s32 unknown10bc;                                    // Inferred role: loaded count; original member name unknown.
};

static_assert(sizeof(ResManager::Item) == 0x438, "");
static_assert(sizeof(ResManager) == 0x10c0, "");

} // namespace event
