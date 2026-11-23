#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_object_listener.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

class GfMenuScriptManager : public mm::mtl::PtrSingleton<GfMenuScriptManager> {
public:
  class ScriptListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;
  };

  // Inferred role: script slot reserved for a menu script; original name unknown.
  struct unknown001 {
    u32 unknown00;  // Inferred role: script slot of GfScriptManager; original member name unknown.
    bool unknown04; // Inferred role: slot in use; original member name unknown.
  };

  // Inferred role: script registered for a menu object; original name unknown.
  struct unknown002 {
    u32 unknown00;                 // Inferred role: script slot of GfScriptManager; original member name unknown.
    mm::mtl::FixStr<64> unknown04; // Inferred role: script name; original member name unknown.
    u32 unknown48;                 // Inferred role: id looked up by getHandle; original member name unknown.
    u32 unknown4c;                 // Inferred role: handle of the listened ui object; original member name unknown.
    int unknown50;                 // Inferred role: control id; original member name unknown.
    u8 _54[0x58 - 0x54];
    ui::EventData m_eventData;                        // Inferred role: last event taken by checkEvent; original member name unknown.
    mm::mtl::FixedQueue<ui::EventData, 16> unknown70; // Inferred role: received events; original member name unknown.
  };

  GfMenuScriptManager(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfMenuScriptManager();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void postUpdate(const fw::UpdateInfo &info);
  static bool regist(const char *script, u32 handle, u32 id);
  bool getEmptySlot(u32 &slot);
  static bool regist(u32 object, u32 handle, u32 id);
  static const char *getScriptName(u32 object);
  bool freeSlot(u32 slot);
  static u32 getHandle(u32 id);
  static bool checkEvent(u32 handle);
  static bool getEventData(u32 handle, ui::EventData &event);
  static int getCtrlId(u32 handle);
  static void setCtrlId(u32 handle, int ctrlId);

  bool unknown08;                                 // Inferred role: initialized; original member name unknown.
  mm::mtl::FixedVector<unknown002, 32> unknown10; // Inferred role: registered scripts; original member name unknown.
  unknown001 unknown4018[32];                     // Inferred role: menu script slots; original member name unknown.
  ScriptListener *m_scriptListener;               // Inferred role: listener of the registered ui objects; original member name unknown.
};

static_assert(sizeof(GfMenuScriptManager::ScriptListener) == 0x10, "");
static_assert(sizeof(GfMenuScriptManager::unknown001) == 0x8, "");
static_assert(offsetof(GfMenuScriptManager::unknown002, unknown04) == 0x4, "");
static_assert(offsetof(GfMenuScriptManager::unknown002, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuScriptManager::unknown002, unknown4c) == 0x4c, "");
static_assert(offsetof(GfMenuScriptManager::unknown002, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuScriptManager::unknown002, m_eventData) == 0x58, "");
static_assert(offsetof(GfMenuScriptManager::unknown002, unknown70) == 0x70, "");
static_assert(sizeof(GfMenuScriptManager::unknown002) == 0x200, "");
static_assert(offsetof(GfMenuScriptManager, unknown08) == 0x8, "");
static_assert(offsetof(GfMenuScriptManager, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuScriptManager, unknown4018) == 0x4018, "");
static_assert(offsetof(GfMenuScriptManager, m_scriptListener) == 0x4118, "");
static_assert(sizeof(GfMenuScriptManager) == 0x4120, "");

} // namespace gf
