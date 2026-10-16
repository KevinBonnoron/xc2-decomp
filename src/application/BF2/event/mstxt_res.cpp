#include "event/mstxt_res.h"

#include "bdat.h"
#include "event/extend.h"
#include "event/res_manager.h"
#include "framework/lang_util.h"
#include "fw/fw_bdat_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

MstxtRes::MstxtRes(const char *path) : flags(0), path(path) {
  mName = mm::mtl::Singleton<Extend>::getPtr()->filename(path);
  mName += "_ms";
  mm::mtl::FixStr<64> bdatPath;
  bdatPath.format("bdat/%s/%s.bdat", fw::LangUtil::getLangFolder().c_str(), mName.c_str());
  mm::mtl::Singleton<ResManager>::getPtr()->load(bdatPath.c_str(), this, false);
  flags |= FLAG_LOADING;
}

void MstxtRes::registerBdat() {
  if ((flags & (FLAG_LOADING | FLAG_LOADED | FLAG_REGISTERED)) != FLAG_LOADED) {
    return;
  }
  fw::BdatManager::loadBdatFromMemory(2, mm::mtl::Singleton<ResManager>::getPtr()->adr(mName.c_str(), nullptr));
  flags |= FLAG_REGISTERED;
}

unsigned char *MstxtRes::getFp() { return fw::BdatManager::getFp(mName.c_str()); }

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

int MstxtRes::getTop() const { return Bdat::getIdTop(fw::BdatManager::getFp(mName.c_str())); }

int MstxtRes::getCount() const { return Bdat::getIdCount(fw::BdatManager::getFp(mName.c_str())); }

} // namespace event
