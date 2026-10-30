#include "event/lipsync_res.h"

#include <stddef.h>

#include "event/extend.h"
#include "event/res_manager.h"
#include "framework/lang_util.h"
#include "mm_mtl/singleton.h"

namespace event {

LipsyncRes::LipsyncRes(const char *name) : unknown08(0), m_name(name), unknown50(nullptr), unknown60(0) {
  size_t length = __builtin_strlen(name);
  if (length > 3 && (__builtin_memcmp(name, "bf", 2) == 0 || __builtin_memcmp(name, "qst", 3) == 0 || __builtin_memcmp(name, "fev", 3) == 0 || __builtin_memcmp(name, "deb", 3) == 0)) {
    mm::mtl::FixStr<256> path;
    path.format("event/lip/%s/%s", fw::LangUtil::getVoiceFolder().c_str(), name);
    mm::mtl::Singleton<ResManager>::getPtr()->load(Extend::get().lip(path.c_str()), this, false);
    unknown08 |= FLAG_LOADING;
  }
}

const char *LipsyncRes::getName() const { return m_name.c_str(); }

bool LipsyncRes::isLoading() const { return (unknown08 & FLAG_LOADING) != 0; }

void LipsyncRes::OnResEvent(const PARAM &param) {
  if (param.result == RES_RESULT_TYPE_SUCCESS) {
    unknown50.setData(param.adr);
    unknown08 |= FLAG_LOADED;
  } else {
    unknown08 &= ~FLAG_LOADED;
  }
  unknown08 &= ~FLAG_LOADING;
}

void *LipsyncRes::searchCsv(const char *name, int &size) {
  if ((unknown08 & FLAG_LOADED) != 0) {
    mm::mtl::FixStr<64> baseName(Extend::get().filename(name));
    mm::mtl::FixStr<64> fileName(Extend::get().xxlip(baseName.c_str()));
    u32 count = unknown50.getFiles();
    u32 start = unknown60;
    u32 index = start;
    do {
      if (__builtin_strcmp(unknown50.getFileName(index), fileName.c_str()) == 0) {
        size = unknown50.getFileSize(unknown60);
        return unknown50.getFileAdr(unknown60);
      }
      index = unknown60 + 1 < count ? unknown60 + 1 : 0;
      unknown60 = index;
    } while (index != start);
  }
  return nullptr;
}

} // namespace event
