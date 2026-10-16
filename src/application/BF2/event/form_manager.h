#pragma once
#include "event/i_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
struct Mat44;
struct Vec3;
} // namespace mm

namespace event {

class FormManager : public IManager, public mm::mtl::Singleton<FormManager> {
public:
  FormManager();
  virtual ~FormManager() {}
  bool replace(u32 id, int npcId);
  bool replace(u32 id, const mm::Mat44 &matrix);
  bool replace(u32 id, const mm::Vec3 &pos, f32 rot);
  static void adjestPosY(mm::Vec3 &pos);
  u32 getReplaceNum(u32 id) const;
  virtual void OnEventProc(MSG_TYPE type);
};

static_assert(sizeof(FormManager) == 0x10, "");

} // namespace event
