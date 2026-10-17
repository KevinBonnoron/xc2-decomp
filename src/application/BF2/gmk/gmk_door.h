#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkDoorGob;

class GmkDoor : public AGmkBase {
public:
  struct BdatInfo {
    bool isGfObjMustExist() const;
    bool isPhantomMustExist() const;
    bool isLoadSaveData() const;
    bool isPopCondMatched() const;
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);

    u16 condition;
    u8 responseType;
    u8 responseCharacter;
    u16 nameRadius;
    u16 lodModel;
    u16 missMsgId;
    bool isOpenLodAnime;
    bool isOpenSeMapPack;
    u16 openSe;
    u8 openSeSize;
    const char *openCameraGimmickId;
    u8 openCameraGimmickAttribute;
    bool isCloseLodAnime;
    bool isCloseSeMapPack;
    u16 closeSe;
    u8 closeSeSize;
    const char *closeCameraGimmickId;
    u8 closeCameraGimmickAttribute;
    f32 doorNextWait;
    const char *specialCloseCameraGimmickId;
    u8 specialCloseCameraGimmickAttribute;
    bool isGmkCameraPos;
    BootedGmkCond bootedGmk;
    BootedGmkCond opBootedGmk;
    BootedGmkCond specialPopBootedGmk;
  };

  static const GmkType GMK_TYPE = GMK_TYPE_DOOR;

  ~GmkDoor() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0x360 - 0x48];
};

static_assert(sizeof(GmkDoor::BdatInfo) == 0x48, "");
static_assert(sizeof(GmkDoor) == 0x360, "");

typedef TGmkList<GmkDoor, GmkDoor::BdatInfo, 0x524f4f44, 2, GmkDoorGob> GmkDoorList;

} // namespace gmk
