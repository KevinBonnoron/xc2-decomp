#pragma once
#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfFieldLod : public mm::mtl::PtrSingleton<GfFieldLod> {
public:
  int findBdatIdByLodId(u16 lodId) const;
  bool isAnimReverse(int bdatId) const;
  void setFade(int bdatId, bool isFadeIn, bool isImmediate);
  void setAnimReverse(int bdatId, bool isReverse, bool isSkip);
  bool isFadeOut(int bdatId) const;
  bool findTransform(mm::Mat44 &matrix, int bdatId) const;
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  void gevPlayEvent(GEV event, u32 value);
  static void validateByInitData();
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
};

} // namespace gf
