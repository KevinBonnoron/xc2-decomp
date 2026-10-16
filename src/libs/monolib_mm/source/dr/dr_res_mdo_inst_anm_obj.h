#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrResMdoPos;

struct MdsInstObjPosData {
  enum Flag {
    FLAG_LOOP = 0x1,
    FLAG_NODE_ANM = 0x8,
    FLAG_POS_ANM = 0x10,
    FLAG_POS_MATRIX = 0x20,
    FLAG_SWITCH = 0x80,
    FLAG_DISP_OFF = 0x200,
  };

  u32 nameOffset;
  u8 _04[0x08 - 0x04];
  u16 id;
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
  u8 startRate;
  u8 frameScale;
};

static_assert(offsetof(MdsInstObjPosData, id) == 0x08, "");
static_assert(offsetof(MdsInstObjPosData, startRate) == 0x0c, "");
static_assert(offsetof(MdsInstObjPosData, frameScale) == 0x0d, "");

struct MdsInstAnmParamInfo {
  u32 keyOffset;
  u8 _04[0x06 - 0x04];
  u16 keyCount;
  u16 startFrame;
  u16 endFrame;
};

static_assert(offsetof(MdsInstAnmParamInfo, keyCount) == 0x06, "");
static_assert(offsetof(MdsInstAnmParamInfo, startFrame) == 0x08, "");
static_assert(offsetof(MdsInstAnmParamInfo, endFrame) == 0x0a, "");

struct MdsInstAnmNodeData {
  u8 _00[0x02 - 0x00];
  u16 frameMax;
  u32 coliParamOffset;
};

static_assert(offsetof(MdsInstAnmNodeData, frameMax) == 0x02, "");
static_assert(offsetof(MdsInstAnmNodeData, coliParamOffset) == 0x04, "");

struct MdsInstAnmSwitch {
  enum Flag {
    FLAG_FRAME = 0x1,
    FLAG_LOOP = 0x2,
  };

  u16 flags;
  u8 id;
  u16 startFrame : 16;
  u16 endFrame : 16;
  u8 _08[0x24 - 0x08];
};

static_assert(offsetof(MdsInstAnmSwitch, id) == 0x02, "");

static_assert(sizeof(MdsInstAnmSwitch) == 0x24, "");

class DrResMdoPosInstAnm {
public:
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

  u8 _000[0x020 - 0x000];
  mm::Mat44 m_matrix;
  u8 _060[0x090 - 0x060];
  mm::Mat44 m_dblMatrices[2];
  u8 _110[0x150 - 0x110];
  u16 m_dblFlags;
  u16 m_maxFrame;
  u16 m_startFrame;
};

static_assert(offsetof(DrResMdoPosInstAnm, m_matrix) == 0x020, "");
static_assert(offsetof(DrResMdoPosInstAnm, m_dblMatrices) == 0x090, "");
static_assert(offsetof(DrResMdoPosInstAnm, m_dblFlags) == 0x150, "");
static_assert(offsetof(DrResMdoPosInstAnm, m_maxFrame) == 0x152, "");
static_assert(offsetof(DrResMdoPosInstAnm, m_startFrame) == 0x154, "");

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
    u32 all;
    struct {
      u32 : 2;
      bool isLoop : 1;
      bool isColiOff : 1;
      bool isColiSkipData : 1;
      u32 : 27;
    };
  };

  Flags m_flags;
  const char *m_names;
  const MdsInstObjPosData *m_info;
  const mm::Mat44 *m_matrix;
  f32 m_alpha;
};

static_assert(offsetof(DrResMdoInstPartsObj, m_flags) == 0x08, "");
static_assert(offsetof(DrResMdoInstPartsObj, m_names) == 0x10, "");
static_assert(offsetof(DrResMdoInstPartsObj, m_info) == 0x18, "");
static_assert(offsetof(DrResMdoInstPartsObj, m_matrix) == 0x20, "");
static_assert(offsetof(DrResMdoInstPartsObj, m_alpha) == 0x28, "");

class DrResMdoInstPartsAnm : public DrResMdoInstPartsObj {
public:
  DrResMdoInstPartsAnm(const u8 *data, const MdsInstObjPosData *info);
  ~DrResMdoInstPartsAnm() override;
  void setPosFrame(f32 frame) override { m_posFrame = frame; }
  f32 getPosFrame() const override { return m_posFrame; }
  f32 getPosMaxFrame() const override {
    if (m_posAnm == nullptr) {
      return 0.0f;
    }
    return m_posAnm->m_maxFrame * m_frameScale;
  }
  f32 getPosStartFrame() const override {
    if (m_posAnm == nullptr || m_info->startRate == 0) {
      return 0.0f;
    }
    return m_info->startRate * (1.0f / 255.0f) * m_posAnm->m_maxFrame;
  }
  void setNodeFrame(f32 frame) override;
  f32 getNodeFrame() const override;
  f32 getCalcNodeFrame() const override { return m_nodeStart + m_nodeFrame * m_invFrameScale; }
  f32 getCalcOldNodeFrame() const override { return m_nodeStart + m_oldNodeFrame * m_invFrameScale; }
  f32 getNodeMaxFrame() const override { return m_nodeMax * m_frameScale; }
  f32 getNodeStartFrame() const override {
    if (m_nodeMax == 0 || m_info->startRate == 0) {
      return 0.0f;
    }
    return m_info->startRate * (1.0f / 255.0f) * m_nodeMax;
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

  DrResMdoPosInstAnm *m_posAnm;
  DrResMdoPos *m_pos;
  f32 m_posFrame;
  f32 m_nodeFrame;
  f32 m_oldNodeFrame;
  f32 m_dblNodeFrames[2];
  f32 m_frameScale;
  f32 m_invFrameScale;
  u16 m_nodeStart;
  u16 m_nodeMax;
  const MdsInstAnmParamInfo *m_coliParam;
  const MdsInstAnmSwitch *m_switches;
  u8 m_switchID;
  u8 m_switchMax;
};

static_assert(offsetof(DrResMdoInstPartsAnm, m_posAnm) == 0x30, "");
static_assert(offsetof(DrResMdoInstPartsAnm, m_posFrame) == 0x40, "");
static_assert(offsetof(DrResMdoInstPartsAnm, m_dblNodeFrames) == 0x4c, "");
static_assert(offsetof(DrResMdoInstPartsAnm, m_frameScale) == 0x54, "");
static_assert(offsetof(DrResMdoInstPartsAnm, m_nodeStart) == 0x5c, "");
static_assert(offsetof(DrResMdoInstPartsAnm, m_coliParam) == 0x60, "");
static_assert(offsetof(DrResMdoInstPartsAnm, m_switches) == 0x68, "");
static_assert(offsetof(DrResMdoInstPartsAnm, m_switchID) == 0x70, "");
static_assert(offsetof(DrResMdoInstPartsAnm, m_switchMax) == 0x71, "");

class DrResMdoInstPartsGlbID : public DrResMdoInstPartsObj {
public:
  DrResMdoInstPartsGlbID(const u8 *data, const MdsInstObjPosData *info);
  ~DrResMdoInstPartsGlbID() override;
};

struct DrResMdoInstAnmHeader {
  u8 _00[0x04 - 0x00];
  u32 objMax;
  u32 anmMax;
};

static_assert(offsetof(DrResMdoInstAnmHeader, objMax) == 0x04, "");
static_assert(offsetof(DrResMdoInstAnmHeader, anmMax) == 0x08, "");

class DrResMdoInstAnmObj {
public:
  int getObjIdx(const char *name);

  DrResMdoInstPartsObj *getObj(u32 index) const {
    if (m_header == nullptr) {
      return nullptr;
    }
    return m_objs[index];
  }

  const DrResMdoInstAnmHeader *m_header;
  DrResMdoInstPartsObj **m_objs;
};

static_assert(offsetof(DrResMdoInstAnmObj, m_objs) == 0x08, "");

} // namespace ml
