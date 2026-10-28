#pragma once
#include <stddef.h>

#include "ml/critical_section.h"
#include "ml/reslist.h"
#include "ml/work_event.h"
#include "scn/scn_render_callback.h"
#include "types.h"

namespace ml {

class DebDraw;
class Scn;
class ScnObj;
class ScnObjCam;
class WinView;

class ScnPoolObj : public IWorkEvent, public IScnRender {
public:
  ~ScnPoolObj() override;
  bool isValidInsert(u16 type) const;
  bool insert(ScnObj *obj);
  bool isExistLgtEnv() const;
  bool release(ScnObj *obj);
  void release(u16 type);
  void deleteObj();
  void update();
  void renderDebug(DebDraw *debDraw);
  ScnObjCam *getCam(const WinView *view);
  reslist<ScnObj *> *getList(u16 type);
  const reslist<ScnObj *> *getList(u16 type) const;

  CriticalSection unknown10;    // Inferred role: update lock; original member name unknown.
  CriticalSection unknown38;    // Inferred role: list lock; original member name unknown.
  Scn *unknown60;               // Inferred role: scn; original member name unknown.
  reslist<ScnObj *> unknown68;  // Inferred role: camera list; original member name unknown.
  reslist<ScnObj *> unknowna8;  // Inferred role: model list; original member name unknown.
  reslist<ScnObj *> unknowne8;  // Inferred role: list of type 3 objects; original member name unknown.
  reslist<ScnObj *> unknown128; // Inferred role: light list; original member name unknown.
  reslist<ScnObj *> unknown168; // Inferred role: ibl list; original member name unknown.
  reslist<ScnObj *> unknown1a8; // Inferred role: clip list; original member name unknown.
  reslist<ScnObj *> unknown1e8; // Inferred role: released object list; original member name unknown.
};

static_assert(offsetof(ScnPoolObj, unknown10) == 0x10, "");
static_assert(offsetof(ScnPoolObj, unknown38) == 0x38, "");
static_assert(offsetof(ScnPoolObj, unknown60) == 0x60, "");
static_assert(offsetof(ScnPoolObj, unknown68) == 0x68, "");
static_assert(offsetof(ScnPoolObj, unknowna8) == 0xa8, "");
static_assert(offsetof(ScnPoolObj, unknowne8) == 0xe8, "");
static_assert(offsetof(ScnPoolObj, unknown128) == 0x128, "");
static_assert(offsetof(ScnPoolObj, unknown168) == 0x168, "");
static_assert(offsetof(ScnPoolObj, unknown1a8) == 0x1a8, "");
static_assert(offsetof(ScnPoolObj, unknown1e8) == 0x1e8, "");

} // namespace ml
