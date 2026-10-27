#include "anm/anm_pose.h"

#include "anm/anm_qs_transform.h"
#include "anm/anm_skeleton.h"
#include "anm/anm_transform_util.h"
#include "mm/mm_std_base.h"

namespace anm {

Pose::~Pose() { unknown001(unknown18); }

const QsTransform &Pose::getBoneModelSpace(u16 boneID) {
  if (testBoneFlag(boneID, BONE_MODEL_SPACE_DIRTY)) {
    calcBoneModelSpace(boneID);
  }
  return unknown48[boneID];
}

const QsTransform &Pose::getBoneLocalSpace(u16 boneID) {
  if (testBoneFlag(boneID, BONE_LOCAL_SPACE_DIRTY)) {
    MM_ASSERT(!testBoneFlag(boneID, BONE_MODEL_SPACE_DIRTY));
    const QsTransform &model = unknown48[boneID];
    u16 parentID = unknown18->unknown20[boneID];
    if (parentID == 0xffff) {
      unknown20[boneID] = unknown48[boneID];
    } else {
      if (testBoneFlag(parentID, BONE_MODEL_SPACE_DIRTY)) {
        calcBoneModelSpace(parentID);
      }
      const QsTransform &parentModel = unknown48[parentID];
      QsTransform &local = unknown20[boneID];
      QsTransform inverse;
      TransformUtil::invert(parentModel, &inverse);
      TransformUtil::mul(inverse, model, &local);
    }
    unknown002(boneID, BONE_LOCAL_SPACE_DIRTY, false);
  }
  return unknown20[boneID];
}

void Pose::setBoneLocalSpace(u16 boneID, const QsTransform &transform) {
  makeAllChildrenLocalSpace(boneID);
  unknown20[boneID] = transform;
  unknown002(boneID, BONE_MODEL_SPACE_DIRTY, true);
  unknown88 &= ~2;
}

void Pose::makeAllChildrenLocalSpace(u16 boneID) {
  u32 boneCount = unknown18->unknown30.size();
  unknown002(boneID, BONE_UNKNOWN_2, true);
  u16 first = boneID + 1;
  for (u16 i = first; i < boneCount; i++) {
    u16 parentID = unknown18->unknown20[i];
    if (parentID != 0xffff && testBoneFlag(parentID, BONE_UNKNOWN_2)) {
      getBoneLocalSpace(i);
      unknown002(i, BONE_UNKNOWN_2, true);
      unknown88 &= ~2;
    }
  }
  for (u16 i = first; i < boneCount; i++) {
    if (testBoneFlag(i, BONE_UNKNOWN_2)) {
      unknown002(i, BONE_UNKNOWN_2, false);
      unknown002(i, BONE_MODEL_SPACE_DIRTY, true);
    }
  }
  unknown002(boneID, BONE_UNKNOWN_2, false);
}

void Pose::setBoneModelSpace(u16 boneID, const QsTransform &transform, PROPAGATE_TYPE propagate) {
  if (propagate == PROPAGATE_TYPE_UNKNOWN_0) {
    makeAllChildrenModelSpace(boneID);
  } else {
    makeAllChildrenLocalSpace(boneID);
  }
  unknown48[boneID] = transform;
  unknown002(boneID, BONE_LOCAL_SPACE_DIRTY, true);
  unknown88 &= ~1;
}

void Pose::makeAllChildrenModelSpace(u16 boneID) {
  u32 boneCount = unknown18->unknown30.size();
  for (u16 i = boneID + 1; i < boneCount; i++) {
    if (unknown18->unknown20[i] == boneID) {
      getBoneModelSpace(i);
      unknown002(i, BONE_LOCAL_SPACE_DIRTY, true);
      unknown88 &= ~1;
    }
  }
}

QsTransform &Pose::accessBoneLocalSpace(u16 boneID) {
  makeAllChildrenLocalSpace(boneID);
  getBoneLocalSpace(boneID);
  unknown002(boneID, BONE_MODEL_SPACE_DIRTY, true);
  unknown88 &= ~2;
  return unknown20[boneID];
}

QsTransform &Pose::accessBoneModelSpace(u16 boneID, PROPAGATE_TYPE propagate) {
  if (propagate == PROPAGATE_TYPE_UNKNOWN_0) {
    makeAllChildrenModelSpace(boneID);
  } else {
    makeAllChildrenLocalSpace(boneID);
  }
  getBoneModelSpace(boneID);
  unknown002(boneID, BONE_LOCAL_SPACE_DIRTY, true);
  unknown88 &= ~1;
  return unknown48[boneID];
}

void Pose::syncLocalSpace() {
  if ((unknown88 & 1) == 0) {
    u32 boneCount = unknown18->unknown30.size();
    for (u16 i = 0; i < boneCount; i++) {
      if (testBoneFlag(i, BONE_LOCAL_SPACE_DIRTY)) {
        MM_ASSERT(!testBoneFlag(i, BONE_MODEL_SPACE_DIRTY));
        const QsTransform &model = unknown48[i];
        s16 parentID = unknown18->unknown20[i];
        if (parentID == -1) {
          unknown20[i] = unknown48[i];
        } else {
          MM_ASSERT(!testBoneFlag(parentID, BONE_MODEL_SPACE_DIRTY));
          const QsTransform &parentModel = unknown48[parentID];
          QsTransform &local = unknown20[i];
          QsTransform inverse;
          TransformUtil::invert(parentModel, &inverse);
          TransformUtil::mul(inverse, model, &local);
        }
        unknown002(i, BONE_LOCAL_SPACE_DIRTY, false);
      }
    }
    unknown88 |= 1;
  }
}

void Pose::syncModelSpace() {
  if ((unknown88 & 2) == 0) {
    u32 boneCount = unknown18->unknown30.size();
    for (u16 i = 0; i < boneCount; i++) {
      if (testBoneFlag(i, BONE_MODEL_SPACE_DIRTY)) {
        MM_ASSERT(!testBoneFlag(i, BONE_LOCAL_SPACE_DIRTY));
        const QsTransform &local = unknown20[i];
        s16 parentID = unknown18->unknown20[i];
        if (parentID == -1) {
          unknown48[i] = unknown20[i];
        } else {
          MM_ASSERT(!testBoneFlag(parentID, BONE_MODEL_SPACE_DIRTY));
          const QsTransform &parentModel = unknown48[parentID];
          QsTransform &model = unknown48[i];
          TransformUtil::mul(parentModel, local, &model);
        }
        unknown002(i, BONE_MODEL_SPACE_DIRTY, false);
      }
    }
    unknown88 |= 2;
  }
}

void Pose::validateBone() {
  u32 boneCount = unknown18->unknown30.size();
  for (u16 i = 0; i < boneCount; i++) {
    MM_ASSERT(!((testBoneFlag(i, BONE_LOCAL_SPACE_DIRTY)) && (testBoneFlag(i, BONE_MODEL_SPACE_DIRTY))));
  }
  if (unknown88 & 2) {
    for (u16 i = 0; i < boneCount; i++) {
      MM_ASSERT(!testBoneFlag(i, BONE_MODEL_SPACE_DIRTY));
    }
  }
  if (unknown88 & 1) {
    for (u16 i = 0; i < boneCount; i++) {
      MM_ASSERT(!testBoneFlag(i, BONE_LOCAL_SPACE_DIRTY));
    }
  }
}

void Pose::calcMatrixModelSpace(u16 boneID, mm::Mat44 *pDst) {
  MM_ASSERT(pDst);
  if (unknown88 & 2) {
    TransformUtil::calcMatrix(unknown48[boneID], pDst);
  }
}

} // namespace anm
