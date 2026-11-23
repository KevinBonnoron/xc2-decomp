#pragma once
#include <stddef.h>

#include "gf/event/gf_event.h"
#include "gf/sound/gf_sound.h"
#include "ml/fixed_size_alloc.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace ml {
class ScnObjAccSeamEtcPos;
} // namespace ml

namespace gf {

struct GF_OBJ_HANDLE;

class GfFieldMapSe : public mm::mtl::PtrSingleton<GfFieldMapSe> {
public:
  struct SECOND {
    SECOND() : unknown00(-1), unknown04(0.0f) {}

    int unknown00; // Inferred role: matrix index; original member name unknown.
    f32 unknown04; // Inferred role: squared distance to the listening point; original member name unknown.
  };

  struct SEOBJ {
    SoundHandle m_soundHandle; // Inferred role: sound handle; original member name unknown.
    int unknown08;             // Inferred role: object index; original member name unknown.
    int unknown0c;             // Inferred role: matrix index; original member name unknown.
    f32 unknown10;             // Inferred role: volume; original member name unknown.
    SECOND m_SECOND;           // Inferred role: condition; original member name unknown.
    u32 unknown1c;             // Inferred role: FLD_actorSE row; original member name unknown.
  };

  struct SEDATA {
    SEDATA(int object, int matrixMax, u32 row) : unknown00(object), unknown04(matrixMax), unknown08(row), unknown0c(0) {}

    int unknown00;                               // Inferred role: object index; original member name unknown.
    int unknown04;                               // Inferred role: matrix count; original member name unknown.
    u32 unknown08;                               // Inferred role: FLD_actorSE row; original member name unknown.
    int unknown0c;                               // Inferred role: next matrix to search; original member name unknown.
    mm::mtl::FixedVector<SEOBJ *, 16> unknown10; // Inferred role: playing sound objects; original member name unknown.
    mm::mtl::FixedQueue<SECOND, 16> unknown98;   // Inferred role: matrices to activate; original member name unknown.
  };

  struct DistCompare {
    bool operator()(const SEOBJ *a, const SEOBJ *b) const;
  };

  GfFieldMapSe();
  ~GfFieldMapSe();
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  void destroy();
  void destroyMapSe();
  void dispEffPosForDebug();
  void postUpdate(const fw::UpdateInfo &info);
  void gevPause(u32 resumeBits, u32 pauseBits);
  void update(const fw::UpdateInfo &info);
  void updateSeObj(fw::UpdateInfo info);
  void gevGameMapModel(GF_OBJ_HANDLE *handle, bool isEnter);
  void createMapSe();
  void destroySeObj(SEOBJ *seObj);
  void updateSeObjDataForFindActivate(fw::UpdateInfo info, SEDATA &data, ml::ScnObjAccSeamEtcPos &acc);
  void updateSeObjDataForActivate(fw::UpdateInfo info, SEDATA &data, ml::ScnObjAccSeamEtcPos &acc);
  SECOND getSeObjCond(int matrix, int object, ml::ScnObjAccSeamEtcPos &acc) const;
  SEOBJ *createSeObj(const SECOND &cond, const SEDATA &data, ml::ScnObjAccSeamEtcPos &acc);
  f32 getVolume(const SEOBJ *seObj);
  bool isActivateMatrix(int matrix, const SEDATA &data) const;

  int unknown08;                                      // Inferred role: object count of the map seam; original member name unknown.
  mm::mtl::FixedVector<SEDATA *, 32> unknown10;       // Inferred role: sound data per object; original member name unknown.
  ml::fixed_size_alloc_inside<SEOBJ, 128> unknown118; // Inferred role: sound object pool; original member name unknown.
};

static_assert(sizeof(GfFieldMapSe::SECOND) == 0x08, "");
static_assert(offsetof(GfFieldMapSe::SEOBJ, m_SECOND) == 0x14, "");
static_assert(sizeof(GfFieldMapSe::SEOBJ) == 0x20, "");
static_assert(offsetof(GfFieldMapSe::SEDATA, unknown10) == 0x10, "");
static_assert(offsetof(GfFieldMapSe::SEDATA, unknown98) == 0x98, "");
static_assert(sizeof(GfFieldMapSe::SEDATA) == 0x128, "");
static_assert(offsetof(GfFieldMapSe, unknown08) == 0x08, "");
static_assert(offsetof(GfFieldMapSe, unknown10) == 0x10, "");
static_assert(offsetof(GfFieldMapSe, unknown118) == 0x118, "");
static_assert(sizeof(GfFieldMapSe) == 0x1150, "");

} // namespace gf
