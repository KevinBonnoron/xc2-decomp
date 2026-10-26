#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrResMdoPos;
struct MdsPosKeepData;

struct MdsInstObjPosData {
  enum Flag {
    FLAG_LOOP = 0x1,
    FLAG_NODE_ANM = 0x8,
    FLAG_POS_ANM = 0x10,
    FLAG_POS_MATRIX = 0x20,
    FLAG_SWITCH = 0x80,
    FLAG_DISP_OFF = 0x200,
  };

  u32 unknown00; // Inferred role: name offset; original member name unknown.
  u8 _04[0x08 - 0x04];
  u16 unknown08; // Inferred role: id; original member name unknown.
  union {
    u16 flags;
    struct {
      u8 isLoop : 1;
      u8 isRandomStart : 1;
      u8 : 1;
      u8 isNodeAnm : 1;
      u8 isPosAnm : 1;
      u8 isPosMatrix : 1;
      u8 : 1;
      u8 isSwitch : 1;
    };
  };
  u8 unknown0c; // Inferred role: start rate; original member name unknown.
  u8 unknown0d; // Inferred role: frame scale; original member name unknown.
};

static_assert(offsetof(MdsInstObjPosData, unknown08) == 0x08, "");
static_assert(offsetof(MdsInstObjPosData, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsInstObjPosData, unknown0d) == 0x0d, "");

struct MdsInstAnmParamInfo {
  u32 unknown00; // Inferred role: key offset; original member name unknown.
  u8 _04[0x06 - 0x04];
  u16 unknown06; // Inferred role: key count; original member name unknown.
  u16 unknown08; // Inferred role: start frame; original member name unknown.
  u16 unknown0a; // Inferred role: end frame; original member name unknown.
};

static_assert(offsetof(MdsInstAnmParamInfo, unknown06) == 0x06, "");
static_assert(offsetof(MdsInstAnmParamInfo, unknown08) == 0x08, "");
static_assert(offsetof(MdsInstAnmParamInfo, unknown0a) == 0x0a, "");

struct MdsInstAnmNodeData {
  u8 _00[0x02 - 0x00];
  u16 unknown02; // Inferred role: frame max; original member name unknown.
  u32 unknown04; // Inferred role: coli param offset; original member name unknown.
};

static_assert(offsetof(MdsInstAnmNodeData, unknown02) == 0x02, "");
static_assert(offsetof(MdsInstAnmNodeData, unknown04) == 0x04, "");

struct MdsInstAnmSwitch {
  enum Flag {
    FLAG_FRAME = 0x1,
    FLAG_LOOP = 0x2,
  };

  u16 unknown00;        // Inferred role: flags; original member name unknown.
  u8 unknown02;         // Inferred role: id; original member name unknown.
  u16 unknown04_0 : 16; // Inferred role: start frame; original member name unknown.
  u16 unknown06_0 : 16; // Inferred role: end frame; original member name unknown.
  u8 _08[0x24 - 0x08];
};

static_assert(offsetof(MdsInstAnmSwitch, unknown02) == 0x02, "");

static_assert(sizeof(MdsInstAnmSwitch) == 0x24, "");

// Inferred type: instance animation object header; the original type name is unknown.
struct MdsInstAnmObj {
  u8 _00[0x3e];
  u16 unknown3e;
};

static_assert(offsetof(MdsInstAnmObj, unknown3e) == 0x3e, "");

class DrResMdoPosInstAnm {
public:
  DrResMdoPosInstAnm(const MdsInstAnmObj *anm, const u8 *data, const MdsPosKeepData *keep);
  void setup(f32 frame);
  void getAnmMatrix(mm::Mat44 *matrix, f32 frame) const;
  void update();
  void setMatrix(const mm::Mat44 &matrix);
  void getMatrix(mm::Mat44 &matrix) const;
  void setAnmFrame(u16 startFrame, u16 maxFrame);
  static void anmInsPosParm_TranX(mm::Vec3 *transform, f32 value);
  static void anmInsPosParm_TranY(mm::Vec3 *transform, f32 value);
  static void anmInsPosParm_TranZ(mm::Vec3 *transform, f32 value);
  static void anmInsPosParm_RotX(mm::Vec3 *transform, f32 value);
  static void anmInsPosParm_RotY(mm::Vec3 *transform, f32 value);
  static void anmInsPosParm_RotZ(mm::Vec3 *transform, f32 value);
  static void anmInsPosParm_SclX(mm::Vec3 *transform, f32 value);
  static void anmInsPosParm_SclY(mm::Vec3 *transform, f32 value);
  static void anmInsPosParm_SclZ(mm::Vec3 *transform, f32 value);

  const MdsInstAnmObj *unknown00;  // Inferred role: instance animation; original member name unknown.
  const u8 *unknown08;             // Inferred role: animation data; original member name unknown.
  const MdsPosKeepData *unknown10; // Inferred role: position keep data; original member name unknown.
  u8 _018[0x020 - 0x018];
  mm::Mat44 unknown20; // Inferred role: matrix; original member name unknown.
  u8 _060[0x090 - 0x060];
  mm::Mat44 unknown90[2]; // Inferred role: dbl matrices; original member name unknown.
  u8 _110[0x150 - 0x110];
  u16 unknown150; // Inferred role: dbl flags; original member name unknown.
  u16 unknown152; // Inferred role: max frame; original member name unknown.
  u16 unknown154; // Inferred role: start frame; original member name unknown.
};

static_assert(offsetof(DrResMdoPosInstAnm, unknown00) == 0x00, "");
static_assert(offsetof(DrResMdoPosInstAnm, unknown20) == 0x020, "");
static_assert(offsetof(DrResMdoPosInstAnm, unknown90) == 0x090, "");
static_assert(offsetof(DrResMdoPosInstAnm, unknown150) == 0x150, "");
static_assert(offsetof(DrResMdoPosInstAnm, unknown152) == 0x152, "");
static_assert(offsetof(DrResMdoPosInstAnm, unknown154) == 0x154, "");

class DrResMdoInstPartsObj {
public:
  enum Flag {
    FLAG_LOOP = 0x4,
  };

  DrResMdoInstPartsObj(const u8 *data, const MdsInstObjPosData *info);
  void setDisp(bool disp);
  bool isDisp() const;
  f32 getSimpleParamAttr(const MdsInstAnmParamInfo *param, f32 frame) const;

  virtual ~DrResMdoInstPartsObj() {}
  virtual void setPosFrame(f32 frame) {}
  virtual f32 getPosFrame() const { return 0.0f; }
  virtual f32 getPosMaxFrame() const { return 0.0f; }
  virtual f32 getPosStartFrame() const { return 0.0f; }
  virtual void setNodeFrame(f32 frame) {}
  virtual f32 getNodeFrame() const { return 0.0f; }
  virtual f32 getCalcNodeFrame() const { return 0.0f; }
  virtual f32 getCalcOldNodeFrame() const { return 0.0f; }
  virtual f32 getNodeMaxFrame() const { return 0.0f; }
  virtual f32 getNodeStartFrame() const { return 0.0f; }
  virtual u32 getSwitchID() const { return 0; }
  virtual void setSwitchID(u8 id) {}
  virtual u32 getSwitchMax() const { return 0; }
  virtual u32 getSwitchIndex(u32 index) const { return 1; }
  virtual void update() {}
  virtual void getMatrix(mm::Mat44 &matrix) const;
  virtual void getAnmMatrix(mm::Mat44 &matrix) const { getMatrix(matrix); }
  virtual void setMatrix(const mm::Mat44 &matrix) {}

  union Flags {
    u32 unknown00; // Inferred role: all; original member name unknown.
    struct {
      u32 : 2;
      bool isLoop : 1;
      bool isColiOff : 1;
      bool isColiSkipData : 1;
      u32 : 27;
    };
  };

  Flags unknown08;                    // Inferred role: flags; original member name unknown.
  const char *unknown10;              // Inferred role: names; original member name unknown.
  const MdsInstObjPosData *unknown18; // Inferred role: info; original member name unknown.
  const mm::Mat44 *unknown20;         // Inferred role: matrix; original member name unknown.
  f32 unknown28;                      // Inferred role: alpha; original member name unknown.
};

static_assert(offsetof(DrResMdoInstPartsObj, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoInstPartsObj, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoInstPartsObj, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoInstPartsObj, unknown20) == 0x20, "");
static_assert(offsetof(DrResMdoInstPartsObj, unknown28) == 0x28, "");

class DrResMdoInstPartsAnm : public DrResMdoInstPartsObj {
public:
  DrResMdoInstPartsAnm(const u8 *data, const MdsInstObjPosData *info);
  ~DrResMdoInstPartsAnm() override;
  void setPosFrame(f32 frame) override { m_posFrame = frame; }
  f32 getPosFrame() const override { return m_posFrame; }
  f32 getPosMaxFrame() const override {
    if (unknown30 == nullptr) {
      return 0.0f;
    }
    return unknown30->unknown152 * unknown54;
  }
  f32 getPosStartFrame() const override {
    if (unknown30 == nullptr || unknown18->unknown0c == 0) {
      return 0.0f;
    }
    return unknown18->unknown0c * (1.0f / 255.0f) * unknown30->unknown152;
  }
  void setNodeFrame(f32 frame) override;
  f32 getNodeFrame() const override;
  f32 getCalcNodeFrame() const override { return unknown5c + unknown44 * unknown58; }
  f32 getCalcOldNodeFrame() const override { return unknown5c + unknown48 * unknown58; }
  f32 getNodeMaxFrame() const override { return unknown5e * unknown54; }
  f32 getNodeStartFrame() const override {
    if (unknown5e == 0 || unknown18->unknown0c == 0) {
      return 0.0f;
    }
    return unknown18->unknown0c * (1.0f / 255.0f) * unknown5e;
  }
  u32 getSwitchID() const override { return m_switchID; }
  void setSwitchID(u8 id) override;
  void updateSwitch();
  u32 getSwitchMax() const override { return m_switchMax; }
  u32 getSwitchIndex(u32 index) const override;
  void update() override;
  void getMatrix(mm::Mat44 &matrix) const override;
  void getAnmMatrix(mm::Mat44 &matrix) const override;
  void setMatrix(const mm::Mat44 &matrix) override;
  void setNodeAnmData(const MdsInstAnmNodeData *data);
  void setPosAnmData(DrResMdoPosInstAnm *posAnm, DrResMdoPos *pos);

  DrResMdoPosInstAnm *unknown30; // Inferred role: pos anm; original member name unknown.
  DrResMdoPos *unknown38;        // Inferred role: pos; original member name unknown.
  f32 m_posFrame;
  f32 unknown44;                        // Inferred role: node frame; original member name unknown.
  f32 unknown48;                        // Inferred role: old node frame; original member name unknown.
  f32 unknown4c[2];                     // Inferred role: dbl node frames; original member name unknown.
  f32 unknown54;                        // Inferred role: frame scale; original member name unknown.
  f32 unknown58;                        // Inferred role: inv frame scale; original member name unknown.
  u16 unknown5c;                        // Inferred role: node start; original member name unknown.
  u16 unknown5e;                        // Inferred role: node max; original member name unknown.
  const MdsInstAnmParamInfo *unknown60; // Inferred role: coli param; original member name unknown.
  const MdsInstAnmSwitch *unknown68;    // Inferred role: switches; original member name unknown.
  u8 m_switchID;
  u8 m_switchMax;
};

static_assert(offsetof(DrResMdoInstPartsAnm, unknown30) == 0x30, "");
static_assert(offsetof(DrResMdoInstPartsAnm, m_posFrame) == 0x40, "");
static_assert(offsetof(DrResMdoInstPartsAnm, unknown4c) == 0x4c, "");
static_assert(offsetof(DrResMdoInstPartsAnm, unknown54) == 0x54, "");
static_assert(offsetof(DrResMdoInstPartsAnm, unknown5c) == 0x5c, "");
static_assert(offsetof(DrResMdoInstPartsAnm, unknown60) == 0x60, "");
static_assert(offsetof(DrResMdoInstPartsAnm, unknown68) == 0x68, "");
static_assert(offsetof(DrResMdoInstPartsAnm, m_switchID) == 0x70, "");
static_assert(offsetof(DrResMdoInstPartsAnm, m_switchMax) == 0x71, "");

class DrResMdoInstPartsGlbID : public DrResMdoInstPartsObj {
public:
  DrResMdoInstPartsGlbID(const u8 *data, const MdsInstObjPosData *info);
  ~DrResMdoInstPartsGlbID() override;
};

struct DrResMdoInstAnmHeader {
  u8 _00[0x04 - 0x00];
  u32 unknown04; // Inferred role: object max; original member name unknown.
  u32 unknown08; // Inferred role: anm max; original member name unknown.
};

static_assert(offsetof(DrResMdoInstAnmHeader, unknown04) == 0x04, "");
static_assert(offsetof(DrResMdoInstAnmHeader, unknown08) == 0x08, "");

class DrResMdoInstAnmObj {
public:
  DrResMdoInstAnmObj();
  void release();
  int getObjIdx(const char *name);

  DrResMdoInstPartsObj *getObj(u32 index) const {
    if (unknown00 == nullptr) {
      return nullptr;
    }
    return unknown08[index];
  }

  const DrResMdoInstAnmHeader *unknown00; // Inferred role: header; original member name unknown.
  DrResMdoInstPartsObj **unknown08;       // Inferred role: objs; original member name unknown.
  void *unknown10;                        // Inferred role: data; original member name unknown.
  void *unknown18;                        // Inferred role: data; original member name unknown.
  void *unknown20;                        // Inferred role: data; original member name unknown.
  void *unknown28;                        // Inferred role: data; original member name unknown.
};

static_assert(offsetof(DrResMdoInstAnmObj, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoInstAnmObj, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoInstAnmObj, unknown28) == 0x28, "");
static_assert(sizeof(DrResMdoInstAnmObj) == 0x30, "");

} // namespace ml
