#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/ui_object_plugin.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIObjectSyncPlugin : public UIObjectPlugin {
public:
  enum TargetFlag {
    TARGET_POS = 1 << 0,
    TARGET_POS_CENTER = 1 << 1,
    TARGET_SCALE = 1 << 2,
    TARGET_ROT = 1 << 3,
    TARGET_ALPHA = 1 << 4,
    TARGET_DISP = 1 << 5,
    TARGET_DISP_REVERSE = 1 << 6,
  };

  static mm::mtl::RTTI m_rtti;

  UIObjectSyncPlugin();
  virtual ~UIObjectSyncPlugin();
  static UIObjectSyncPlugin *create(u32 handle);
  void setTargetObject(u32 handle);
  void setTargetFlag(u32 flags);
  virtual void execute(UIObjectAcc &acc);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual bool isNeedUpdate(UIObjectAcc &acc);

  u32 m_targetObject;
  u32 m_targetFlag;
};

static_assert(offsetof(UIObjectSyncPlugin, m_targetObject) == 0x1c, "");
static_assert(offsetof(UIObjectSyncPlugin, m_targetFlag) == 0x20, "");
static_assert(sizeof(UIObjectSyncPlugin) == 0x28, "");

} // namespace ui
