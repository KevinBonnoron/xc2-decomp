#include "gf/asset/gf_asset_util.h"

namespace gf {

namespace {

const char *const unknown001[] = {
    "atEmpty",  "atProg",      "atDebug",     "atMap",       "atPc",   "atPcCom", "atBlade", "atBladeCom", "atWeapon", "atWeaponEff",
    "atEneNpc", "atEneNpcMot", "atEneNpcArc", "atEneNpcEff", "atFobj", "atMobj",  "atPcWm",  "atOption",   "atTemp",   "atSound"}; // Inferred role: names of GfAssetType; original name unknown.

} // namespace

const char *GfAssetUtil::getAssetTypeName(GfAssetType type) { return unknown001[type]; }

} // namespace gf
