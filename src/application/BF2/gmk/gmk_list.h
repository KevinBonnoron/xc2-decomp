#pragma once
#include "bdat.h"
#include "framework/resource/common_resource.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_gob_event_listener.h"
#include "gmk/gmk_manager.h"
#include "ml/scn.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/vector.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace gmk {

class GmkSet;
class AGmkBase;
struct GobInfo;
struct Xform;

struct LvbChunk {
  u32 unknown00; // Inferred role: magic; original member name unknown.
  u32 unknown04; // Inferred role: size; original member name unknown.
  u32 unknown08; // Inferred role: version; original member name unknown.
  u32 unknown0c; // Inferred role: count; original member name unknown.
  u32 unknown10; // Inferred role: stride; original member name unknown.
  u32 unknown14; // Inferred role: gob info index; original member name unknown.
  u8 unknown18;  // Inferred role: flags; original member name unknown.
  u8 _19[0x20 - 0x19];
};

static_assert(sizeof(LvbChunk) == 0x20, "");

class IGmkList {
public:
  struct CreateInfo {
    CreateInfo() : unknown08(nullptr), unknown140(0.0f, 0.0f, 0.0f), unknown150(0.0f) {}

    mtl::ALLOC_HANDLE unknown00;    // Inferred role: memory; original member name unknown.
    GmkSet *unknown08;              // Inferred role: set; original member name unknown.
    mm::mtl::FixStr<256> unknown10; // Inferred role: path; original member name unknown.
    mm::mtl::FixStr<32> unknown114; // Inferred role: bdat name; original member name unknown.
    mm::Vec3 unknown140;            // Inferred role: position; original member name unknown.
    f32 unknown150;                 // Inferred role: rotation; original member name unknown.
  };

  virtual ~IGmkList() {}
  virtual GmkType getGmkType() const = 0;
  virtual bool isValid() const = 0;
  virtual const CreateInfo &getCreateInfo() const = 0;
  virtual u32 getInstNum() const = 0;
  virtual const AGmkBase *getInst(u32 index) const = 0;
  virtual u8 *getBindedBdatFp() const = 0;
  virtual void setUpdateGmkNumPerFrame(u32 num) = 0;
  virtual void create(const CreateInfo &info) = 0;
  virtual void dispose() = 0;
  virtual void update(f32 deltaTime) = 0;
  virtual bool updateImmediate() = 0;
  virtual void debugUpdateMmf() = 0;
  virtual void debugDraw() const = 0;
  virtual u32 debugGetDocId() const { return 0; }
};

template <typename T, typename BDAT_INFO, u32 MAGIC, u32 VERSION, typename GOB> class TGmkList : public IGmkList {
public:
  explicit TGmkList(u32 updateGmkNumPerFrame)
      : resource(nullptr), data(nullptr), xformChunk(nullptr), xforms(nullptr), gobInfoChunk(nullptr), gobInfos(nullptr), gmkChunk(nullptr), gmkData(nullptr), strings(nullptr), bdatFp(nullptr),
        seq(nullptr), updateGmkNumPerFrame(updateGmkNumPerFrame), updateGmkIndex(0) {
    GmkGobEventListener::createInstance();
  }

  ~TGmkList() override {
    dispose();
    GmkGobEventListener::disposeInstance();
  }

  GmkType getGmkType() const override { return T::GMK_TYPE; }

  bool isValid() const override {
    if (data == nullptr) {
      return false;
    }
    if (!createInfo.unknown114.empty() && bdatFp == nullptr) {
      return false;
    }
    if (gmkChunk == nullptr) {
      return false;
    }
    return gmkChunk->unknown00 == MAGIC;
  }

  const CreateInfo &getCreateInfo() const override { return createInfo; }
  u32 getInstNum() const override { return gmkInsts.size(); }
  const AGmkBase *getInst(u32 index) const override { return &gmkInsts[index]; }
  u8 *getBindedBdatFp() const override { return bdatFp; }
  void setUpdateGmkNumPerFrame(u32 num) override { updateGmkNumPerFrame = num; }

  void create(const CreateInfo &info) override {
    dispose();
    createInfo = info;
    resource = fw::CommonResource::request(info.unknown00, createInfo.unknown10.c_str(), 9, false);
    seq = &TGmkList::seqWaitResourceLoaded;
    if (!createInfo.unknown114.empty()) {
      bdatFp = Bdat::getFP(createInfo.unknown114.c_str());
      if (bdatFp == nullptr) {
        dispose();
      }
    }
  }

  void dispose() override {
    GmkAccManager::invalidateAccs(*this);
    seq = nullptr;
    disposeGmk();
    if (resource != nullptr) {
      resource->release();
      resource = nullptr;
    }
    createInfo = CreateInfo();
  }

  void update(f32 deltaTime) override {
    if (seq) {
      (this->*seq)(deltaTime);
    }
  }

  bool updateImmediate() override {
    bool isValidList = isValid();
    u32 savedUpdateGmkNumPerFrame = updateGmkNumPerFrame;
    u32 savedUpdateGmkIndex = updateGmkIndex;
    if (seq) {
      updateGmkNumPerFrame = getInstNum();
      updateGmkIndex = 0;
      (this->*seq)(0.0f);
    }
    updateGmkNumPerFrame = savedUpdateGmkNumPerFrame;
    updateGmkIndex = savedUpdateGmkIndex;
    return isValidList;
  }

  void debugUpdateMmf() override {
    if (!isValid()) {
      return;
    }
    if (ml::Scn::sys() == nullptr || ml::Scn::sys()->getCam(-1) == nullptr) {
      return;
    }
    const mm::Vec3 &cameraPosition = ml::Scn::sys()->getCam(-1)->renderInfo->position;
    for (T *gmk = gmkInsts.begin(); gmk != gmkInsts.end(); gmk++) {
      if (gmk->AGmkBase::unknown08.unknown08 == nullptr) {
        continue;
      }
      f32 x = cameraPosition.x - gmk->AGmkBase::unknown08.unknown08->unknown00.x;
      f32 z = cameraPosition.z - gmk->AGmkBase::unknown08.unknown08->unknown00.z;
      if (x * x + z * z > DEBUG_DISTANCE * DEBUG_DISTANCE) {
        continue;
      }
      gmk->debugUpdateMmf();
    }
  }

  void debugDraw() const override {
    if (!isValid()) {
      return;
    }
    if (ml::Scn::sys() == nullptr || ml::Scn::sys()->getCam(-1) == nullptr) {
      return;
    }
    const mm::Vec3 &cameraPosition = ml::Scn::sys()->getCam(-1)->renderInfo->position;
    for (const T *gmk = gmkInsts.begin(); gmk != gmkInsts.end(); gmk++) {
      if (gmk->AGmkBase::unknown08.unknown08 == nullptr) {
        continue;
      }
      f32 x = cameraPosition.x - gmk->AGmkBase::unknown08.unknown08->unknown00.x;
      f32 z = cameraPosition.z - gmk->AGmkBase::unknown08.unknown08->unknown00.z;
      if (x * x + z * z > DEBUG_DISTANCE * DEBUG_DISTANCE) {
        continue;
      }
      gmk->debugDraw();
    }
  }

protected:
  static constexpr f32 DEBUG_DISTANCE = 100.0f;

  virtual void createGmk(void *data);

  virtual void disposeGmk() {
    gmkInsts.destroy();
    bdatInfos.destroy();
    data = nullptr;
    xformChunk = nullptr;
    xforms = nullptr;
    gobInfoChunk = nullptr;
    gobInfos = nullptr;
    gmkChunk = nullptr;
    gmkData = nullptr;
    strings = nullptr;
  }

  virtual void onResetUpdateGmkIndex() {}

  void seqWaitResourceLoaded(f32) {
    if (resource->valid()) {
      void *assetData = resource->getAssetData();
      if (assetData == nullptr) {
        dispose();
        return;
      }
      createGmk(assetData);
      seq = &TGmkList::seqUpdate;
    }
  }

  void seqUpdate(f32 deltaTime) {
    if (!isValid() || updateGmkNumPerFrame == 0) {
      return;
    }
    u32 num = gmkInsts.size();
    if (num == 0) {
      return;
    }
    if (num <= updateGmkIndex) {
      updateGmkIndex = 0;
      onResetUpdateGmkIndex();
    }
    u32 updateNum = mm::min(updateGmkNumPerFrame, num);
    if (updateNum == 0) {
      return;
    }
    f32 updateDeltaTime = static_cast<f32>((num + updateNum - 1) / updateNum) * deltaTime;
    for (u32 i = 0; i < updateNum; i++, updateGmkIndex++) {
      if (num <= updateGmkIndex) {
        updateGmkIndex = 0;
        onResetUpdateGmkIndex();
        return;
      }
      gmkInsts[updateGmkIndex].update(updateDeltaTime);
    }
  }
  CreateInfo createInfo;
  fw::CommonResource *resource;
  void *data;
  const LvbChunk *xformChunk;
  Xform *xforms;
  const LvbChunk *gobInfoChunk;
  GobInfo *gobInfos;
  const LvbChunk *gmkChunk;
  const u8 *gmkData;
  const char *strings;
  u8 *bdatFp;
  void (TGmkList::*seq)(f32);
  mm::mtl::Vector<BDAT_INFO> bdatInfos;
  mm::mtl::Vector<T> gmkInsts;
  u32 updateGmkNumPerFrame;
  u32 updateGmkIndex;
};

} // namespace gmk
