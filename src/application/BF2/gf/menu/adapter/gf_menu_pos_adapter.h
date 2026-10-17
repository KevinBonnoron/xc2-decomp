#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

struct GF_OBJ_HANDLE;
struct MenuOffset;

class GfMenuPosAdapter : public GfMenuAdapter {
public:
  class PartyDriverConverter {
  public:
    PartyDriverConverter(u8 partyIndex) : partyIndex(partyIndex) {}
    virtual GF_OBJ_HANDLE *getGfObjHandle();

    u32 partyIndex;
  };

  GfMenuPosAdapter(ui::UIObjectPlugin *plugin);
  ~GfMenuPosAdapter() override;
  static GfMenuPosAdapter *create(u32 handle, GF_OBJ_HANDLE *objHandle, const MenuOffset *menuOffset);
  void setup(GF_OBJ_HANDLE *objHandle, const MenuOffset *menuOffset);
  static GfMenuPosAdapter *createDiffOffset(u32 handle, GF_OBJ_HANDLE *objHandle, const MenuOffset *menuOffset, u16 limitX, u16 limitY);
  static GfMenuPosAdapter *createFromPartyDriver(u32 handle, u8 partyIndex, const MenuOffset *menuOffset);
  static GfMenuPosAdapter *createWorld(u32 handle, GF_OBJ_HANDLE *objHandle, const MenuOffset *menuOffset);
  static GfMenuPosAdapter *createFixedPoint(u32 handle, const mm::Vec3 &pos, bool isWorld);
  void changeReference(GF_OBJ_HANDLE *objHandle, const MenuOffset *menuOffset);
  void changeFixedPoint(const mm::Vec3 &pos);
  void update(const fw::UpdateInfo &info) override;

  GF_OBJ_HANDLE *objHandle;
  mm::Vec3 offset;
  mm::mtl::FixStr<16> boneName;
  mm::Vec3 worldPos;
  bool isWorld;
  bool isFixedPoint;
  bool isDiffOffset;
  mm::Pnt<s16> screenOffset;
  PartyDriverConverter *converter;
};

static_assert(offsetof(GfMenuPosAdapter, objHandle) == 0x30, "");
static_assert(offsetof(GfMenuPosAdapter, offset) == 0x40, "");
static_assert(offsetof(GfMenuPosAdapter, boneName) == 0x50, "");
static_assert(offsetof(GfMenuPosAdapter, worldPos) == 0x70, "");
static_assert(offsetof(GfMenuPosAdapter, isWorld) == 0x80, "");
static_assert(offsetof(GfMenuPosAdapter, isFixedPoint) == 0x81, "");
static_assert(offsetof(GfMenuPosAdapter, isDiffOffset) == 0x82, "");
static_assert(offsetof(GfMenuPosAdapter, screenOffset) == 0x84, "");
static_assert(offsetof(GfMenuPosAdapter, converter) == 0x88, "");
static_assert(sizeof(GfMenuPosAdapter) == 0x90, "");

} // namespace gf
