#pragma once
#include <stddef.h>

#include "gf/event/gf_event.h"
#include "gf/field/gf_fobj_dropitem.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/scom/gf_scom_obj.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;
struct GF_OBJ_HANDLE;

// Layout from its constructor (0x71002ed008), end, start and the seq* functions.
class GfFieldTbox : public mm::mtl::PtrSingleton<GfFieldTbox> {
public:
  typedef void (GfFieldTbox::*Sequence)(f32 deltaTime);

  GfFieldTbox(const GfSetupParam &param);
  ~GfFieldTbox();
  void create(const GfSetupParam &param);
  bool isDropitemsEmitted() const;
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  void end();
  void dispose();
  void start(GF_OBJ_HANDLE *handle);
  void createDropitemEmitter(const GfDropitemEmitter::CreateInfo &info);
  void update(f32 deltaTime);
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  void seqWaitCheckFs(f32 deltaTime);
  void seqCheckFs(f32 deltaTime);
  void seqWaitUIEnd(f32 deltaTime);
  void seqWaitOpenFieldTbox(f32 deltaTime);
  void seqWaitDigEnd(f32 deltaTime);
  void seqWaitDropBegin(f32 deltaTime);

  // Inferred helper: creates the treasure quest command when the gimmick task end check of the bound gimmick returns check; original name unknown.
  void unknown001(u32 check, f32 delay) {
    gmk::AGmkBase *gmk = gmk::getBindedGmkInst(unknown18);
    if (gmk != nullptr) {
      gmk::GmkType type = gmk->getGmkType();
      u32 gimmick = gmk->unknown20.unknown18;
      if (GfQuestUtil::getGimmickTaskEndCheck(type, gimmick) == check) {
        SCOM_QUEST_GIMMICK::createTresure(gimmick, delay);
      }
    }
  }

  f32 unknown08;               // Inferred role: wait time before the field skill check; original member name unknown.
  f32 unknown0c;               // Inferred role: wait time before the opening; original member name unknown.
  bool unknown10;              // Inferred role: created; original member name unknown.
  bool unknown11;              // Inferred role: field skill window closed; original member name unknown.
  bool unknown12;              // Inferred role: field skill check succeeded; original member name unknown.
  GF_OBJ_HANDLE *unknown18;    // Inferred role: treasure box object; original member name unknown.
  int unknown20;               // Inferred role: RSC_ID of the treasure box; original member name unknown.
  bool unknown24;              // Inferred role: buried treasure box; original member name unknown.
  Sequence unknown28;          // Inferred role: sequence; original member name unknown.
  f32 unknown38;               // Inferred role: elapsed time; original member name unknown.
  GfDropitemEmitter unknown40; // Inferred role: dropitem emitter; original member name unknown.
};

static_assert(offsetof(GfFieldTbox, unknown08) == 0x08, "");
static_assert(offsetof(GfFieldTbox, unknown10) == 0x10, "");
static_assert(offsetof(GfFieldTbox, unknown12) == 0x12, "");
static_assert(offsetof(GfFieldTbox, unknown18) == 0x18, "");
static_assert(offsetof(GfFieldTbox, unknown20) == 0x20, "");
static_assert(offsetof(GfFieldTbox, unknown24) == 0x24, "");
static_assert(offsetof(GfFieldTbox, unknown28) == 0x28, "");
static_assert(offsetof(GfFieldTbox, unknown38) == 0x38, "");
static_assert(offsetof(GfFieldTbox, unknown40) == 0x40, "");
static_assert(sizeof(GfFieldTbox) == 0xa0, "");

} // namespace gf
