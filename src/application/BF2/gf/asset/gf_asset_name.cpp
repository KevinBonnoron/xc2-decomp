#include "gf/asset/gf_asset_name.h"
#include <stdlib.h>

#include <string.h>

#include "gf/data/gf_object_type.h"
#include "gf/util/gf_util.h"

namespace gf {

static const char *const unknown001[10] = {"ma", "", "pc", "bl", "en", "np", "mb", "oj", "", "wp"}; // Inferred role: object type prefixes; original name unknown.

// Inferred role: copies the two characters of an id out of an asset name; original name unknown.
static mm::mtl::FixStr<16> unknown002(const mm::mtl::FixStr<16> &name, int start) {
  mm::mtl::FixStr<16> id;
  if (name.length() != 0) {
    name.unknown001(id, start, 2);
  }
  return id;
}

GfAssetName::GfAssetName(const char *name) { set(name); }

void GfAssetName::set(const char *name) {
  unknown00.clear();
  unknown14.clear();
  if (name != nullptr) {
    const char *file = util::getFilePtrFromPath(name);
    int length = file - name;
    unknown00 = file;
    if (length > 0) {
      mm::mtl::FixStr<128> path = name;
      mm::mtl::FixStr<128> directory;
      if (path.length() != 0) {
        int count = length != -1 ? length : path.length();
        path.unknown001(directory, 0, count);
      }
      unknown14 = directory.c_str();
    }
  }
}

void GfAssetName::set(u32 type, u32 idUpper, u32 idMiddle, u32 idLower) {
  clear();
  const char *prefix = getPrefix(type);
  if (strlen(prefix) == 2) {
    unknown00 = prefix;
    unknown00 += "000000";
    setIdUpper(idUpper);
    setIdMiddle(idMiddle);
    setIdLower(idLower);
  }
}

void GfAssetName::clear() {
  unknown00.clear();
  unknown14.clear();
}

const char *GfAssetName::getPrefix(u32 type) {
  if (type - 1 < 10) {
    return unknown001[static_cast<int>(type - 1)];
  }
  return "";
}

void GfAssetName::setObjType(u32 type) { unknown14 = getPrefix(type); }

void GfAssetName::setIdUpper(u32 id) {
  unknown00[2] = '0' + id / 10;
  unknown00[3] = '0' + id % 10;
}

void GfAssetName::setIdMiddle(u32 id) {
  unknown00[4] = '0' + id / 10;
  unknown00[5] = '0' + id % 10;
}

void GfAssetName::setIdLower(u32 id) {
  unknown00[6] = '0' + id / 10;
  unknown00[7] = '0' + id % 10;
}

bool GfAssetName::hasCategory() const { return unknown00.length() > 9; }

const char *GfAssetName::getCategory() const {
  if (unknown00.length() > 9) {
    return unknown00.c_str() + 8;
  }
  return nullptr;
}

void GfAssetName::cutCategory() {
  if (unknown00.length() > 9) {
    unknown00.resize(8);
  }
}

void GfAssetName::setCategory(const char *category) {
  if (unknown00.length() == 8) {
    unknown00 += category;
  } else if (unknown00.length() == 10) {
    unknown00[8] = category[0];
    unknown00[9] = category[1];
  }
}

const char *GfAssetName::getName() {
  unknown38.format("%s%s", unknown14.c_str(), unknown00.c_str());
  return unknown38.c_str();
}

bool GfAssetName::isValid() const { return getObjType() != 0; }

u32 GfAssetName::getObjType() const {
  if (unknown00.length() < 8) {
    return OBJECT_TYPE_NONE;
  }

  const char *name = unknown00.c_str();
  for (int i = 2; i < 8; i++) {
    if (name[i] < '0' || name[i] > '9') {
      return OBJECT_TYPE_NONE;
    }
  }

  mm::mtl::FixStr<128> prefix = unknown00.c_str();
  if (prefix.length() > 2) {
    prefix.resize(2);
  }

  if (strcmp(prefix.c_str(), "pc") == 0) {
    return OBJECT_TYPE_PC;
  }
  if (strcmp(prefix.c_str(), "bl") == 0) {
    return OBJECT_TYPE_BLADE;
  }
  if (strcmp(prefix.c_str(), "en") == 0) {
    return OBJECT_TYPE_ENEMY;
  }
  if (strcmp(prefix.c_str(), "ma") == 0) {
    return OBJECT_TYPE_MAP;
  }
  if (strcmp(prefix.c_str(), "np") == 0) {
    return OBJECT_TYPE_NPC;
  }
  if (strcmp(prefix.c_str(), "mb") == 0) {
    return OBJECT_TYPE_MOB;
  }
  if (strcmp(prefix.c_str(), "wp") == 0) {
    return OBJECT_TYPE_PC_WEAPON;
  }
  if (strcmp(prefix.c_str(), "oj") == 0) {
    return OBJECT_TYPE_GIMMICK;
  }
  return OBJECT_TYPE_NONE;
}

int GfAssetName::getValue(const char *text) const { return atoi(text); }

int GfAssetName::getIdUpper() const {
  mm::mtl::FixStr<128> text = unknown002(unknown00, 2).c_str();
  return getValue(text.c_str());
}

int GfAssetName::getIdMiddle() const {
  mm::mtl::FixStr<128> text = unknown002(unknown00, 4).c_str();
  return getValue(text.c_str());
}

int GfAssetName::getIdLower() const {
  mm::mtl::FixStr<128> text = unknown002(unknown00, 6).c_str();
  return getValue(text.c_str());
}

} // namespace gf
