#pragma once
#include <stddef.h>

#include "ml/scn_obj_model.h"

namespace ml {
class DrMdlObj;
class Scn;
class ScnObj;

class ScnObjClipDySys {
public:
  static ScnObj *create(Scn *scn, const void *data, int screen);
};

class ScnObjEnvColiDr {
public:
  static ScnObj *create(Scn *scn, const void *data, int screen);
};

class ScnObjIBLDr {
public:
  static ScnObj *create(Scn *scn, const void *data, int screen);
};

class ScnObjLightDrSys {
public:
  static ScnObj *create(Scn *scn, const void *data, int screen);
};

class ScnObjModelDrSys : public ScnObjModel {
public:
  DrMdlObj *m_drMdl;
};

static_assert(offsetof(ScnObjModelDrSys, m_drMdl) == 0x3d8, "");

class ScnObjModelDrSysStandard : public ScnObjModelDrSys {
public:
  static ScnObjModelDrSysStandard *create(Scn *scn, const void *data, const char *name, int screen);
};

} // namespace ml
