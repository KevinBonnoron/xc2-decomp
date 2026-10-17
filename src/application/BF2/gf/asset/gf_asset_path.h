#pragma once

namespace gf {

class GfAssetPath {
public:
  static const char *getSePack() {
    static const char *s_szSe = "/sound/se/";
    return s_szSe;
  }

  static const char *getMdoModel() {
    static const char *s_szMdo = "/model/";
    return s_szMdo;
  }

  static const char *getEvt() {
    static const char *s_szEvt = "/event/mot/";
    return s_szEvt;
  }

  static const char *getMdoMap() {
    static const char *s_szMdo = "/map/";
    return s_szMdo;
  }

  static const char *getEff() {
    static const char *s_szEff = "/effect/";
    return s_szEff;
  }

  static const char *getStp() {
    static const char *s_szStp = "/sound/tag/trigger/";
    return s_szStp;
  }
};

} // namespace gf
