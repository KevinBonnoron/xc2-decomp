#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class CopydataManager : public IManager, public mm::mtl::Singleton<CopydataManager> {
public:
  CopydataManager();
  virtual ~CopydataManager() {}
  void clear();
  void init();
  virtual void OnEventProc(MSG_TYPE type);
  void pause(bool isPause);
  void send(const char *format, ...);

private:
  u32 unknown10;                 // Inferred role: flags; original member name unknown.
  mm::mtl::FixStr<64> unknown14; // Inferred role: target name; original member name unknown.
  u8 _58[0x80 - 0x58];
};

static_assert(sizeof(CopydataManager) == 0x80, "");

} // namespace event
