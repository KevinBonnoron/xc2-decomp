#include "event/mstxt_res.h"

#include "bdat.h"
#include "event/extend.h"
#include "event/manager.h"
#include "event/res_manager.h"
#include "framework/lang_util.h"
#include "fw/fw_bdat_manager.h"
#include "gf/menu/object/gf_menu_obj_event_subtitle.h"
#include "mm_mtl/singleton.h"

namespace event {

MstxtRes::MstxtRes(const char *path) : unknown08(0), unknown0c(path) {
  unknown30 = mm::mtl::Singleton<Extend>::getPtr()->filename(path);
  unknown30 += "_ms";
  mm::mtl::FixStr<64> bdatPath;
  bdatPath.format("bdat/%s/%s.bdat", fw::LangUtil::getLangFolder().c_str(), unknown30.c_str());
  mm::mtl::Singleton<ResManager>::getPtr()->load(bdatPath.c_str(), this, false);
  unknown08 |= FLAG_LOADING;
}

MstxtRes::~MstxtRes() { unregisterBdat(); }

void MstxtRes::unregisterBdat() {
  if (unknown08 & FLAG_REGISTERED) {
    gf::GfMenuObjEventSubtitle::endText();
    fw::BdatManager::unregistBdat(2);
    unknown08 &= ~FLAG_REGISTERED;
  }
}

void MstxtRes::OnResEvent(const PARAM &param) {
  if (param.result == RES_RESULT_TYPE_SUCCESS) {
    unknown08 |= FLAG_LOADED;
  } else if (param.result == RES_RESULT_TYPE_FAILURE) {
    mm::mtl::PtrSingleton<Manager>::get()->failureSkip();
  }
  unknown08 &= ~FLAG_LOADING;
}

void MstxtRes::registerBdat() {
  if ((unknown08 & (FLAG_LOADING | FLAG_LOADED | FLAG_REGISTERED)) != FLAG_LOADED) {
    return;
  }
  fw::BdatManager::loadBdatFromMemory(2, mm::mtl::Singleton<ResManager>::getPtr()->adr(unknown30.c_str(), nullptr));
  unknown08 |= FLAG_REGISTERED;
}

unsigned char *MstxtRes::getFp() { return fw::BdatManager::getFp(unknown30.c_str()); }

int MstxtRes::getSeatID(const char *label) {
  if (label == nullptr || *label == '\0') {
    return -1;
  }
  unsigned char *fp = getFp();
  int top = Bdat::getIdTop(fp);
  int end = Bdat::getIdEnd(fp);
  for (int id = top; id <= end; id++) {
    if (__builtin_strcmp(label, Bdat::getMSLabel(fp, id)) == 0) {
      return id;
    }
  }
  return -1;
}

const char *MstxtRes::getText(const char *label) {
  int id = getSeatID(label);
  if (id > 0) {
    return Bdat::getMSText(getFp(), id);
  }
  return "";
}

int MstxtRes::getTop() const { return Bdat::getIdTop(fw::BdatManager::getFp(unknown30.c_str())); }

int MstxtRes::getCount() const { return Bdat::getIdCount(fw::BdatManager::getFp(unknown30.c_str())); }

} // namespace event
