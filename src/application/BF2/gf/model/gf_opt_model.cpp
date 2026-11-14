#include "framework/message/message_object.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_chrbl.h"
#include "gf/data/gf_bdat_chrdr.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_mount.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_append.h"
#include "gf/object/gf_append_info.h"
#include "gf/object/gf_append_util.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_util.h"
#include "gf/util/gf_util.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {
class GfInitParamDriver;
struct GF_OBJ_HANDLE;

// Inferred table: bone names of the belonging models; original name unknown.
static const char *const unknown001[] = {"", "EX_wp_L", "EX_wp_R", "EX_back"};

// Inferred helper: adds the belonging append of a resource mounted to a bone of unknown001; original name unknown.
static void unknown002(GfAppendInfo &info, u32 bone, u32 rsc) {
  if (rsc == 0) {
    return;
  }
  GfBdatRsc *bdatRsc = GfBdatRsc::get();
#line 544
  GfAppend *append = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8)
      GfAppend(bdatRsc->getRscNpcWpnModel(rsc), bdatRsc->getRscNpcWpnMotion(rsc), info.unknown00[info.unknownb0].size(), rsc, 1.0f, info.unknownb0 != 0);
  GfAppend::MOUNT_INFO mount;
  mount.unknown14 = OPTMNT_UNKNOWN_2;
  mount.unknown00 = unknown001[bone];
  append->addMount(mount);
  info.unknown00[info.unknownb0].push_back(append);
}

// Inferred helper: replaces the appends with the belonging model of a driver; original name unknown.
static void unknown003(GfAppendInfo &info, const GfInitParamDriver &param) {
  info.unknown001();
#line 632
  GfAppend *append =
      new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfAppend(GfDataDriver::getBelongingModelName(param), "", info.unknown00[info.unknownb0].size(), 0, 1.0f, info.unknownb0 != 0);
  GfAppend::MOUNT_INFO mount;
  mount.unknown14 = OPTMNT_UNKNOWN_2;
  mount.unknown00 = GfDataDriver::getBelongingMountBone();
  append->addMount(mount);
  mount.unknown14 = OPTMNT_UNKNOWN_1;
  mount.unknown00 = GfDataDriver::getBelongingMountBone();
  append->addMount(mount);
  info.unknown00[info.unknownb0].push_back(append);
}

// Inferred helper: replaces the appends with the extra mount model of a driver; original name unknown.
static void unknown004(GfAppendInfo &info, u32 rsc, const char *bone) {
  info.unknown001();
  GfBdatRsc *bdatRsc = GfBdatRsc::get();
#line 584
  GfAppend *append = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8)
      GfAppend(bdatRsc->getRscNpcListModel(rsc), bdatRsc->getRscNpcListMotion(rsc), info.unknown00[info.unknownb0].size(), rsc, 1.0f, info.unknownb0 != 0);
  GfAppend::MOUNT_INFO mount;
  mount.unknown14 = OPTMNT_UNKNOWN_2;
  mount.unknown00 = bone;
  append->addMount(mount);
  info.unknown00[info.unknownb0].push_back(append);
}

// Inferred helper: adds the append of a party weapon resource; original name unknown.
static void unknown005(GfAppendInfo &info, u32 rsc, const char *bone1, const char *bone2, const char *bone3) {
  if (rsc == 0) {
    return;
  }
  GfBdatRsc *bdatRsc = GfBdatRsc::get();
#line 61
  GfAppend *append = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8)
      GfAppend(bdatRsc->getRSC_PcWpnModel(rsc), bdatRsc->getRSC_PcWpnMotion(rsc), info.unknown00[info.unknownb0].size(), rsc, 1.0f, info.unknownb0 != 0);
  GfAppend::MOUNT_INFO mount;
  mount.unknown14 = OPTMNT_UNKNOWN_1;
  mount.unknown00 = bone1 != nullptr ? bone1 : "";
  append->addMount(mount);
  mount.unknown14 = OPTMNT_UNKNOWN_2;
  mount.unknown00 = bone2 != nullptr ? bone2 : "";
  append->addMount(mount);
  mount.unknown14 = OPTMNT_UNKNOWN_4;
  mount.unknown00 = bone1 != nullptr ? bone1 : "";
  append->addMount(mount);
  mount.unknown14 = OPTMNT_UNKNOWN_3;
  mount.unknown00 = bone3 != nullptr ? bone3 : "";
  append->addMount(mount);
  info.unknown00[info.unknownb0].push_back(append);
}

// Inferred helper: adds the append of an enemy weapon resource; original name unknown.
static void unknown006(GfAppendInfo *info, u32 rsc, GF_OBJ_HANDLE *owner) {
  if (rsc == 0) {
    return;
  }
  GfBdatRsc *bdatRsc = GfBdatRsc::get();
#line 348
  GfAppend *append = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8)
      GfAppend(bdatRsc->getRscEnWpnModel(rsc), bdatRsc->getRscEnWpnMotion(rsc), info->unknown00[info->unknownb0].size(), rsc, bdatRsc->getRscEnWpnScale(rsc) * 0.01f, info->unknownb0 != 0);
  GfAppend::MOUNT_INFO mount;
  mount.unknown14 = OPTMNT_UNKNOWN_1;
  mount.unknown00 = bdatRsc->getRscEnWpnMtpOutChara(rsc);
  append->addMount(mount);
  mount.unknown14 = OPTMNT_UNKNOWN_2;
  mount.unknown00 = bdatRsc->getRscEnWpnMtpInChara(rsc);
  append->addMount(mount);
  if (owner != unknown020) {
    mount.unknown14 = OPTMNT_UNKNOWN_3;
    mount.unknown00 = bdatRsc->getRscEnWpnMtpOutChara(rsc);
    append->addMount(mount);
  }
  info->unknown00[info->unknownb0].push_back(append);
}

// Inferred helper: first driver sharing the name of a driver; original name unknown.
static u32 unknown007(u32 driver) {
  u32 id = 1;
  if (driver != 0) {
    id = driver;
  }
  GfBdatChrDr *bdatDriver = GfBdatChrDr::get();
  u32 name = bdatDriver->getChrDrName(id);
  for (u32 index = bdatDriver->getChrDrStart(); index < bdatDriver->getChrDrEnd(); index++) {
    if (name == bdatDriver->getChrDrName(index)) {
      return index;
    }
  }
  return id;
}

// Inferred helper: driver of the weapon mount tables; original name unknown.
static u32 unknown008(GFATTACH attach, u32 driver, u32 blade) {
  if (attach == GFATTACH_UNKNOWN_3) {
    if (driver == 1 && blade == BLADE_HOMURA) {
      return DRIVER_UNKNOWN_11;
    }
    if (driver == 1 && blade == BLADE_UNKNOWN_1011) {
      return DRIVER_UNKNOWN_12;
    }
  }
  return unknown007(driver);
}

// Inferred helper: second driver of the weapon mount tables; original name unknown.
static u32 unknown009(GFATTACH attach, u32 driver, u32 blade) {
  u32 index = unknown008(attach, driver, blade);
  if (blade == BLADE_UNKNOWN_1040) {
    index = DRIVER_UNKNOWN_10;
  }
  return index;
}

// Inferred helper: driver using a weapon type; original name unknown.
static u32 unknown010(u32 wpnType, u32 blade) {
  if (blade == BLADE_UNKNOWN_1078 || blade == BLADE_UNKNOWN_1079) {
    return DRIVER_UNKNOWN_13;
  }
  GfBdatChrDr *bdatDriver = GfBdatChrDr::get();
  for (u32 driver = bdatDriver->getChrDrStart(); driver < bdatDriver->getChrDrEnd(); driver++) {
    if (bdatDriver->getChrDrWpnType(driver, wpnType - 1) != 0) {
      return unknown007(driver);
    }
  }
  return 0;
}

// Inferred helper: second driver using a weapon type; original name unknown.
static u32 unknown011(u32 wpnType, u32 blade) {
  u32 index = unknown010(wpnType, blade);
  if (blade == BLADE_UNKNOWN_1040) {
    index = DRIVER_UNKNOWN_10;
  }
  return index;
}

// Inferred helper: tests that both hands of a blade use the same private weapon; original name unknown.
static bool unknown012(u32 blade) {
  GfBdatChrBl *bdatBlade = GfBdatChrBl::get();
  u32 weapon = bdatBlade->getChrBlPrivateWpnR(blade);
  return weapon != 0 && weapon == bdatBlade->getChrBlPrivateWpnL(blade);
}

// Inferred helper: tests that the weapon is the private weapon of a blade; original name unknown.
static bool unknown013(GfBdatItem *bdatItem, GfBdatChrBl *bdatBlade, u32 weapon, u32 blade, bool isViewer) {
  bool isPrivate = bdatItem->isPcWpnFlagPrivate(weapon);
  if (((!isViewer && isPrivate) || bdatBlade->isChrBlFlagOnlyWpn(blade)) && !GfDataBlade::isCommonBlade(blade)) {
    if (bdatBlade->getChrBlPrivateWpnR(blade) != 0) {
      return true;
    }
    if (bdatBlade->getChrBlPrivateWpnL(blade) != 0) {
      return true;
    }
  }
  return false;
}

// Inferred helper: adds the appends of a weapon set; original name unknown.
static void unknown014(GfAppendInfo &info, u32 driver, u32 driver2, u32 weapon, u32 blade, u32 wpnType, bool isViewer) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  GfBdatRsc *bdatRsc = GfBdatRsc::get();
  GfBdatChrBl *bdatBlade = GfBdatChrBl::get();
  bool isBladeWeapon = unknown013(bdatItem, bdatBlade, weapon, blade, isViewer);

  const char *outR2 = "EX_wp_R";
  const char *inR = "EX_back";
  const char *outR = outR2;
  if (driver != 0) {
    outR = bdatRsc->getRSC_PcWpnMountWpnOutR(driver, wpnType);
    inR = bdatRsc->getRSC_PcWpnMountWpnInR(driver, wpnType);
    outR2 = bdatRsc->getRSC_PcWpnMountWpnOutR(driver2, wpnType);
  }
  u32 rscR = isBladeWeapon ? bdatBlade->getChrBlPrivateWpnR(blade) : bdatItem->getPcWpnRscR(weapon);
  if (rscR != 0) {
    info.unknownb0 = 0;
    unknown005(info, rscR, outR, inR, outR2);
  }

  bool hasAlternate = false;
  if ((isBladeWeapon || unknown012(blade)) && GfDataBlade::isNeedChangeWeapon(blade)) {
    const char *altOutR = bdatRsc->getRSC_PcWpnMountWpnOutR(driver, wpnType);
    const char *altInR = bdatRsc->getRSC_PcWpnMountWpnInR(driver, wpnType);
    const char *altInR2 = bdatRsc->getRSC_PcWpnMountWpnInR(driver2, wpnType);
    u32 altRscR = bdatBlade->getChrBlPrivateWpnR_Driver(blade);
    if (unknown012(blade)) {
      altRscR = rscR;
    }
    if (altRscR != 0) {
      hasAlternate = true;
      info.unknownb0 = 1;
      unknown005(info, altRscR, altOutR, altInR, altInR2);
      info.unknownb0 = 0;
    }
  }

  const char *outL = "EX_wp_L";
  const char *inL = "EX_back";
  const char *outL2 = outL;
  if (driver != 0) {
    outL = bdatRsc->getRSC_PcWpnMountWpnOutL(driver, wpnType);
    inL = bdatRsc->getRSC_PcWpnMountWpnInL(driver, wpnType);
    outL2 = bdatRsc->getRSC_PcWpnMountWpnOutL(driver2, wpnType);
  }
  u32 rscL = isBladeWeapon ? bdatBlade->getChrBlPrivateWpnL(blade) : bdatItem->getPcWpnRscL(weapon);
  if (rscL == 0 && unknown012(blade)) {
    rscL = rscR;
  }
  if (rscL != 0) {
    unknown005(info, rscL, outL, inL, outL2);
  }

  if (isBladeWeapon && GfDataBlade::isNeedChangeWeapon(blade)) {
    const char *altOutL = bdatRsc->getRSC_PcWpnMountWpnOutL(driver, wpnType);
    const char *altInL = bdatRsc->getRSC_PcWpnMountWpnInL(driver, wpnType);
    const char *altOutL2 = bdatRsc->getRSC_PcWpnMountWpnOutL(driver2, wpnType);
    u32 altRscL = bdatBlade->getChrBlPrivateWpnL_Driver(blade);
    if (altRscL != 0) {
      hasAlternate = true;
      info.unknownb0 = 1;
      unknown005(info, altRscL, altOutL, altInL, altOutL2);
      info.unknownb0 = 0;
    }
  }
  info.unknownb0 = hasAlternate;
}

void GfAppendUtil::setupPartyBlade(GFATTACH attach, GF_OBJ_HANDLE *handle, u32 weapon, u32 driver, u32 blade) {
  if (weapon == 0) {
    return;
  }
  u32 wpnType = GfBdatItem::get()->getPcWpnWpnType(weapon);
  GfAppendInfo *info = GfObjUtil::getAppendInfo(handle, attach);
  if (info == nullptr) {
    return;
  }
  info->unknown001();
  if (GfObjUtil::getObjType(handle) == OBJECT_TYPE_BLADE) {
    DataParamAcc param(handle);
    blade = param.getValidBdatId();
  }
  u32 index = unknown008(attach, driver, blade);
  unknown014(*info, index, unknown009(attach, driver, blade), weapon, blade, wpnType, false);
}

void GfAppendUtil::setupWeapon(GFATTACH attach, GfAppendInfo &info, u32 weapon, u32 driver, u32 blade, bool isViewer) {
  if (weapon == 0) {
    return;
  }
  u32 wpnType = GfBdatItem::get()->getPcWpnWpnType(weapon);
  info.unknown001();
  u32 index = unknown008(attach, driver, blade);
  unknown014(info, index, index, weapon, blade, wpnType, isViewer);
}

void GfAppendUtil::setupActViewer(GFATTACH attach, GF_OBJ_HANDLE *handle, u32 weapon, u32 driver, u32 blade) {
  if (weapon == 0) {
    return;
  }
  u32 wpnType = GfBdatItem::get()->getPcWpnWpnType(weapon);
  GfAppendInfo *info = GfObjUtil::getAppendInfo(handle, attach);
  info->unknown001();
  u32 index = unknown008(attach, driver, blade);
  unknown014(*info, index, index, weapon, blade, wpnType, true);
}

void GfAppendUtil::setupEnemy(GFATTACH attach, GF_OBJ_HANDLE *handle, u32 enArrange, GF_OBJ_HANDLE *owner) {
  if (enArrange == 0) {
    return;
  }
  u32 rsc = GfDataEnemy::getRscIdByArrangeId(enArrange);
  GfAppendInfo *info = GfObjUtil::getAppendInfo(handle, attach);
  info->unknown001();
  GfBdatRsc *bdatRsc = GfBdatRsc::get();
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  for (u32 index = 0; index < 5; index++) {
    u32 weapon = bdatRsc->getRscEnWeaponNum(rsc, index);
    if (weapon != 0) {
      u32 rscR = bdatBattle->getWpn_EnRscR(weapon);
      u32 rscL = bdatBattle->getWpn_EnRscL(weapon);
      unknown006(info, rscR, owner);
      unknown006(info, rscL, owner);
    }
  }
}

void GfAppendUtil::setupEventActEnemy(GFATTACH attach, GF_OBJ_HANDLE *handle, u32 enArrange) {
  if (enArrange == 0) {
    return;
  }
  u32 rsc = GfDataEnemy::getRscIdByArrangeId(enArrange);
  GfAppendInfo *info = GfObjUtil::getAppendInfo(handle, attach);
  info->unknown001();
  GfBdatRsc *bdatRsc = GfBdatRsc::get();
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  for (u32 index = 0; index < 5; index++) {
    u32 weapon = bdatRsc->getRscEnWeaponNum(rsc, index);
    if (weapon != 0) {
      u32 rscR = bdatBattle->getWpn_EnRscR(weapon);
      u32 rscL = bdatBattle->getWpn_EnRscL(weapon);
      unknown006(info, rscR, unknown020);
      unknown006(info, rscL, unknown020);
    }
  }
  if (info->unknown00[info->unknownb0].empty()) {
    u32 blade = GfDataEnemy::getEquipBlade(enArrange);
    if (blade != 0) {
      u32 weapon = GfDataBlade::getBladeWeapon(blade);
      if (weapon != 0) {
        DataParamAcc param(handle);
        u32 wpnType = GfBdatItem::get()->getPcWpnWpnType(weapon);
        u32 index = unknown010(wpnType, blade);
        unknown014(*info, index, unknown011(wpnType, blade), weapon, blade, wpnType, false);
      }
    }
  }
}

void GfAppendUtil::setupEnemyBlade(GFATTACH attach, GF_OBJ_HANDLE *handle, u32 enArrange, GF_OBJ_HANDLE *owner, GF_OBJ_HANDLE *bladeHandle) {
  GfAppendInfo *info = GfObjUtil::getAppendInfo(handle, attach);
  info->unknown001();
  GfObjAcc acc(bladeHandle);
  if (acc.isValid()) {
    u32 weapon = GfDataBlade::getBladeWeapon(acc.getBladeId());
    if (weapon != 0) {
      DataParamAcc param(handle);
      u32 wpnType = GfBdatItem::get()->getPcWpnWpnType(weapon);
      u32 index = unknown010(wpnType, acc.getBladeId());
      unknown014(*info, index, unknown011(wpnType, acc.getBladeId()), weapon, acc.getBladeId(), wpnType, false);
    }
  }
}

void GfAppendUtil::setupEnemyBladeWithNoDriver(GFATTACH attach, GF_OBJ_HANDLE *handle, u32 blade, GF_OBJ_HANDLE *owner) {
  GfAppendInfo *info = GfObjUtil::getAppendInfo(handle, attach);
  info->unknown001();
  if (blade != 0) {
    u32 weapon = GfDataBlade::getBladeWeapon(blade);
    if (weapon != 0) {
      DataParamAcc param(handle);
      u32 wpnType = GfBdatItem::get()->getPcWpnWpnType(weapon);
      u32 index = unknown010(wpnType, blade);
      unknown014(*info, index, unknown011(wpnType, blade), weapon, blade, wpnType, false);
    }
  }
}

void GfAppendUtil::setupBelonging(GF_OBJ_HANDLE *handle, u32 param2, u32 param3, u32 param4, u32 param5) {
  GfAppendInfo *info = GfObjUtil::getAppendInfo(handle, GFATTACH_UNKNOWN_2);
  info->unknown001();
  if (param3 != 0) {
    unknown002(*info, param2, param3);
  }
  if (param5 != 0) {
    unknown002(*info, param4, param5);
  }
}

void GfAppendUtil::setupExtraModel(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *owner) {
  GfObjAcc acc(owner);
  if (acc.getType() == OBJECT_TYPE_PC) {
    u32 rsc = GfDataDriver::getExtraMountNpcRsc(acc.getDriverId());
    if (rsc != 0) {
      const char *bone = GfDataDriver::getExtraMountBone(acc.getDriverId());
      if (bone != nullptr && *bone != '\0') {
        GfAppendInfo *info = GfObjUtil::getAppendInfo(handle, GFATTACH_UNKNOWN_1);
        if (info != nullptr) {
          unknown004(*info, rsc, bone);
        }
      }
    }
  }
}

void GfAppendUtil::setupBelongingForDriver(GF_OBJ_HANDLE *handle, const GfInitParamDriver &param) {
  GfObjAcc acc(handle);
  GfDataDriver::getBelongingMountBone();
  GfAppendInfo *info = GfObjUtil::getAppendInfo(handle, GFATTACH_UNKNOWN_2);
  if (info != nullptr) {
    unknown003(*info, param);
  }
}

void GfAppendHandles::sendMessage(fw::MessageObject *sender, fw::Message &message) const {
  for (u32 index = 0; index < 10; index++) {
    GfObj *obj = GfObjUtil::getObj(getCurrentHandles()[index]);
    if (obj != nullptr) {
      static_cast<fw::MessageObject *>(obj)->recieveMessage(sender, message);
    }
  }
}

void GfAppendHandles::setAlpha(f32 alpha) {
  for (u32 index = 0; index < 10; index++) {
    GfObjAcc acc(getCurrentHandles()[index]);
    acc.setAlphaNormal(alpha);
  }
}

void GfAppendHandles::destroy(mm::mtl::FixedArray<GF_OBJ_HANDLE *, 10> &handles) {
  for (u32 index = 0; index < 10; index++) {
    GF_OBJ_HANDLE *handle = handles[index];
    if (handle != unknown020) {
      handles[index] = unknown020;
      GfObjUtil::destroy(handle);
    }
  }
}

void GfAppendHandles::destroy() {
  destroy(unknown08);
  destroy(unknown58);
}

void GfAppendHandles::eraseHandle(mm::mtl::FixedArray<GF_OBJ_HANDLE *, 10> &handles, GF_OBJ_HANDLE *handle) {
  for (u32 index = 0; index < 10; index++) {
    if (handles[index] == handle) {
      handles[index] = unknown020;
      return;
    }
  }
}

void GfAppendHandles::eraseHandle(GF_OBJ_HANDLE *handle) {
  eraseHandle(unknown08, handle);
  eraseHandle(unknown58, handle);
}

GfAppend::GfAppend() : unknown00(), m_modelName(nullptr), m_motionName(nullptr), m_mountIndex(0xffff), m_rscID(0), unknown7c(1.0f), unknown80(false) {}

GfAppend::GfAppend(const char *modelName, const char *motionName, u16 mountIndex, u16 rscID, f32 scale, bool multiMount)
    : unknown00(), m_modelName(modelName), m_motionName(motionName), m_mountIndex(mountIndex), m_rscID(rscID), unknown7c(scale), unknown80(multiMount) {}

const char *GfAppend::getBone(OPTMNT mount) const {
  for (const MOUNT_INFO *it = unknown00.begin(); it != unknown00.end(); ++it) {
    if (it->unknown14 == mount) {
      return it->unknown00.c_str();
    }
  }

  return "";
}

void GfAppend::addMount(MOUNT_INFO &info) { unknown00.push_back(info); }

const char *GfAppend::getModelName() const { return m_modelName; }

const char *GfAppend::getMotionName() const { return m_motionName; }

const char *GfAppend::getResourceName() const { return util::getFilePtrFromPath(m_modelName); }

const char *GfAppend::getAsmFileName() const { return util::getFilePtrFromPath(m_motionName); }

u16 GfAppend::getMountIndex() const { return m_mountIndex; }

u16 GfAppend::getRscID() const { return m_rscID; }

} // namespace gf
