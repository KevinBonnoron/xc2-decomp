#pragma once
#include <stddef.h>

#include "gf/event/gf_event.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_cond.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "types.h"

struct CBdatWrapper;

namespace fw {
struct UpdateInfo;
}

namespace gf {

class GfMenuCallContext;
struct GfSetupParam;

class GfAutoTalk {
public:
  struct CreateInfo {
    CreateInfo() : unknown00(nullptr), unknown08(nullptr), unknown10(-1) {}

    u8 *unknown00; // Inferred role: auto talk bdat; original member name unknown.
    u8 *unknown08; // Inferred role: message bdat; original member name unknown.
    int unknown10; // Inferred role: bdat id; original member name unknown.
  };

  struct BdatInfo {
    BdatInfo() : unknown00(0), unknown02(0), unknown04(0), unknown06(0), unknown08(0), unknown0a(0) {}

    void create(const CBdatWrapper &bdat, int id);
    void dispose();
    // Inferred helper: tells whether the row names a mob; original name unknown.
    bool unknown001() const { return unknown00 != 0; }

    u16 unknown00; // Inferred role: MOBID; original member name unknown.
    u16 unknown02; // Inferred role: Range; original member name unknown.
    u16 unknown04; // Inferred role: Condition; original member name unknown.
    u16 unknown06; // Inferred role: Text; original member name unknown.
    u16 unknown08; // Inferred role: Ontime; original member name unknown.
    u16 unknown0a; // Inferred role: BeforeID; original member name unknown.
  };

  GfAutoTalk(const CreateInfo *info = nullptr);
  virtual ~GfAutoTalk() { dispose(); }
  void create(const CreateInfo &info);
  bool isValid() const;
  bool isDispEnd() const;
  void dispose();
  void disposeMenuObj();
  void update(f32 deltaTime);
  void updateMenuObj();
  bool canDispText() const;
  void createMenuObj();

  CreateInfo m_createInfo;              // Inferred role: create info; original member name unknown.
  BdatInfo m_bdatInfo;                  // Inferred role: bdat info; original member name unknown.
  gmk::DistHvCond m_distHvCond;         // Inferred role: talk range; original member name unknown.
  gmk::GmkAcc m_gmkAcc;                 // Inferred role: mob gimmick; original member name unknown.
  GfMenuCallContext *m_menuCallContext; // Inferred role: balloon context; original member name unknown.
  bool unknown80;                       // Inferred role: text displayed; original member name unknown.
  f32 unknown84;                        // Inferred role: remaining display time; original member name unknown.
};

static_assert(offsetof(GfAutoTalk, m_createInfo) == 0x08, "");
static_assert(offsetof(GfAutoTalk, m_bdatInfo) == 0x20, "");
static_assert(offsetof(GfAutoTalk, m_distHvCond) == 0x2c, "");
static_assert(offsetof(GfAutoTalk, m_gmkAcc) == 0x38, "");
static_assert(offsetof(GfAutoTalk, m_menuCallContext) == 0x78, "");
static_assert(offsetof(GfAutoTalk, unknown80) == 0x80, "");
static_assert(offsetof(GfAutoTalk, unknown84) == 0x84, "");
static_assert(sizeof(GfAutoTalk) == 0x88, "");

class GfAutoTalkList : public mm::mtl::IntrusiveListNode<GfAutoTalkList> {
public:
  struct CreateInfo {
    CreateInfo() : unknown00(0), unknown08(nullptr), unknown10(nullptr) {}

    int unknown00; // Inferred role: gimmick set id; original member name unknown.
    u8 *unknown08; // Inferred role: auto talk bdat; original member name unknown.
    u8 *unknown10; // Inferred role: message bdat; original member name unknown.
  };

  GfAutoTalkList(const CreateInfo *info);
  virtual ~GfAutoTalkList() { dispose(); }
  void create(const CreateInfo &info);
  void dispose();
  void update(f32 deltaTime);

  CreateInfo m_createInfo;               // Inferred role: create info; original member name unknown.
  mm::mtl::Vector<GfAutoTalk> unknown30; // Inferred role: auto talks; original member name unknown.
};

static_assert(offsetof(GfAutoTalkList, m_createInfo) == 0x18, "");
static_assert(offsetof(GfAutoTalkList, unknown30) == 0x30, "");
static_assert(sizeof(GfAutoTalkList) == 0x58, "");

class GfAutoTalkManager : public mm::mtl::PtrSingleton<GfAutoTalkManager>, public IGfEvent {
public:
  GfAutoTalkManager(const GfSetupParam &param);
  ~GfAutoTalkManager() override {
    dispose();
    GfEvent::removeEventCallback(this);
  }
  const GfAutoTalk *findGfAutoTalkByBdatId(u8 *bdat, int id) const;
  static void build(const GfSetupParam &param);
  void create();
  static void destroy();
  static bool isInitialized();
  static void update(const fw::UpdateInfo &info);
  void update(f32 deltaTime);
  void dispose();
  void seqInit(f32 deltaTime);
  void clearAutoTalkLists();
  bool createAutoTalkList(int gmkSet);
  void disposeAutoTalkList(int gmkSet);
  void seqUpdate(f32 deltaTime);
  void gevReloadBdat(RELOAD_BDAT reload, u32 value) override;

  mm::mtl::IntrusiveList<GfAutoTalkList> unknown10;    // Inferred role: auto talk lists of the gimmick sets; original member name unknown.
  void (GfAutoTalkManager::*unknown28)(f32 deltaTime); // Inferred role: current sequence (seqInit, seqUpdate); original member name unknown.
};

static_assert(offsetof(GfAutoTalkManager, unknown10) == 0x10, "");
static_assert(offsetof(GfAutoTalkManager, unknown28) == 0x28, "");
static_assert(sizeof(GfAutoTalkManager) == 0x38, "");

} // namespace gf
