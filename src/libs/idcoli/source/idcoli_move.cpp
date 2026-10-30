#include <math.h>

#include "idcoli/idcoli.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

const f32 IDColiMove::s_fBaseWallDot = 0.17364822f;
const f32 IDColiMove::s_fLandingAngle = 0.49999997f;
const f32 IDColiMove::s_fLandingVecChk = -0.8660254f;

IDColiMove::IDColiMove() {
  unknown04 = 0.0f;
  unknown1b8 = 1.0f;
  unknown1bc = 2.0f;
  m_angle = 45.0f;
  m_floor = 0.4f;
  m_down = 0.05f;
  unknown1f1 = false;
  unknown1f5 = false;
  unknown124 = 0;
  unknown1f3 = false;
  unknown1ef = false;
  unknown1eb = false;
  unknown1ec = false;
  m_accuracy = false;
  unknown1ee = false;
}

void IDColiMove::setShapeParms(f32 radius, f32 height) {
  unknown1b8 = radius;
  unknown1bc = height;
}

void IDColiMove::setAngle(f32 angle) { m_angle = angle; }

void IDColiMove::setFloor(f32 floor) { m_floor = floor; }

void IDColiMove::setDown(f32 down) { m_down = down; }

void IDColiMove::setAccuracy(bool accuracy) { m_accuracy = accuracy; }

bool IDColiMove::moveColi(const mm::Vec3 &position, const mm::Vec3 &move) {
  mm::Vec3 positions[32];
  mm::Vec3 normals[32];
  u32 bits[3];
  unknown10.unknown00 = 2;
  unknown10.unknowne4 = 32;
  unknown10.unknownb8 = positions;
  unknown10.unknownc0 = normals;
  unknown10.unknownd8 = bits;
  unknown10.unknown108 = nullptr;
  unknown1e0 = nullptr;
  setupParms(move);
  unknown170 = position;
  unknown1d4 = unknown170.y + unknown1b8 * 2.0f;
  unknown1cc = unknown1b8 * unknown1b8;
  calcCheckParams(unknown140);
  unknown150 = unknown170;
  unknown150.y += unknown1b8;
  unknown160 = unknown150;
  unknown1ea = false;
  for (int i = 0; i < unknown1dc; i++) {
    unknown150 += unknown190;
    if (testWallCheck() && unknown10.unknowne0 != 0) {
      wrlResTempVec wallVec[32];
      unknown120 = 0;
      unknown1f0 = false;
      unknown1f2 = false;
      calcColiBaseParms(wallVec);
    }
  }
  calcDownVec();
  if (testVecYCheck(unknown190)) {
    calcColiYVecParms(unknown190.y);
  } else {
    unknown130 = unknown150;
  }
  if (calcAABBCheck()) {
    unknown1eb = true;
    unknown1ec = true;
  }
  unknown130 -= unknown170;
  return unknown1eb;
}

void IDColiMove::setupParms(const mm::Vec3 &move) {
  unknown140 = move;
  unknown1e8 = false;
  unknown1e9 = false;
  unknown1eb = false;
  unknown1ec = false;
  unknown1ee = false;
  unknown1ef = false;
  unknown1f0 = false;
  unknown1f2 = false;
  unknown1f4 = false;
  unknown124 = 0;
  unknown1d0 = cosf(m_angle * 0.017453292f);
  f32 moveX = unknown140.x;
  f32 moveZ = unknown140.z;
  if (m_accuracy && (fabsf(moveX) >= 0.001f || fabsf(moveZ) >= 0.001f)) {
    unknown1a0.x = -moveX;
    unknown1a0.y = 0.0f;
    unknown1a0.z = -moveZ;
    f32 length = sqrtf(unknown1a0.x * unknown1a0.x + unknown1a0.y * unknown1a0.y + unknown1a0.z * unknown1a0.z);
    if (length <= 0.000001f) {
      unknown1a0 = mm::Vec3::zero;
    } else {
      f32 scale = 1.0f / length;
      unknown1a0.x = scale * unknown1a0.x;
      unknown1a0.y = scale * unknown1a0.y;
      unknown1a0.z = scale * unknown1a0.z;
    }
    unknown1f3 = true;
  } else {
    unknown1f3 = false;
  }
}

void IDColiMove::calcCheckParams(const mm::Vec3 &move) {
  unknown190 = move;
  unknown1dc = 1;
  f32 length = sqrtf(unknown190.x * unknown190.x + unknown190.y * unknown190.y + unknown190.z * unknown190.z);
  unknown1b0 = length * 0.5f;
  if (length >= 0.01f) {
    unknown1dc = static_cast<int>(length / unknown1b8);
    if (unknown1dc == 0) {
      if (m_accuracy) {
        if (unknown1ef) {
          unknown1dc = 8;
          unknown1ef = false;
        } else {
          unknown1dc = 3;
        }
      } else {
        if (unknown1ef) {
          unknown1dc = 5;
          unknown1ef = false;
        } else {
          unknown1dc = 2;
        }
      }
      unknown190 *= 1.0f / unknown1dc;
    } else {
      if (m_accuracy) {
        if (unknown1ef) {
          unknown1dc *= 8;
          unknown1ef = false;
        } else {
          unknown1dc *= 3;
        }
      } else {
        if (unknown1ef) {
          unknown1dc *= 5;
          unknown1ef = false;
        } else {
          unknown1dc *= 2;
        }
      }
      unknown190 *= 1.0f / length;
      unknown190 *= length / unknown1dc;
    }
  }
  unknown1b4 = sqrtf(unknown190.x * unknown190.x + unknown190.y * unknown190.y + unknown190.z * unknown190.z);
}

void IDColiMove::calcDownVec() {
  unknown150.y -= unknown1b8;
  unknown190 = mm::Vec3(unknown150.x, unknown150.y + unknown1b8 * 2.0f, unknown150.z);
  unknown1d8 = -(unknown1b8 * 2.0f);
  if (unknown140.y <= 0.0f) {
    if (!unknown1ee) {
      unknown1d8 -= m_down;
      if (unknown1d4 < unknown190.y) {
        unknown1d8 += unknown1d4 - unknown190.y;
      }
    }
  } else {
    unknown1d8 = 0.0f;
  }
}

bool IDColiMove::calcAABBCheck() {
  mm::Vec3 max;
  mm::Vec3 min;
  bool isOut = false;
  if (IDColiManager::get()->getGrandAABB(max, min)) {
    if (unknown130.y <= min.y - 50.0f) {
      unknown130.y = min.y - 50.0f;
      isOut = true;
    }
  }
  unknown130.y += unknown1b8;
  return isOut;
}

bool IDColiMove::moveColi(IDColiObj *object, const mm::Vec3 &move) {
  if (object->unknown18 & 4) {
    unknown130 = move;
    return true;
  }

  mm::Vec3 positions[32];
  mm::Vec3 normals[32];
  u32 bits[3];
  unknown1e0 = static_cast<IDColiObjChar *>(object);
  unknown10.unknown00 = 2;
  unknown10.unknowne4 = 32;
  unknown10.unknownb8 = positions;
  unknown10.unknownc0 = normals;
  unknown10.unknownd8 = bits;
  unknown10.unknown108 = object;
  setupParms(move);
  unknown10.unknowne8 = static_cast<IDColiObjChar *>(object)->unknownc8;
  m_down = static_cast<IDColiObjChar *>(object)->unknown220;
  calcCheckParams(unknown140);
  unknown1f5 = false;
  if ((object->unknown18 & 8) && !(object->unknown20 & IDColiObj::FLAG_LANDING)) {
    unknown1f5 = true;
  }
  if (object->unknown1c & 0x100) {
    return moveDataColi();
  }
  IDColiObjChar *character = static_cast<IDColiObjChar *>(object);
  IDColiPrimitive::s_CallBasePos[character->unknownc4](unknown170, unknown180, unknown1ea, unknown1b8, unknown1bc, character->unknownd0);
  return moveDefColi();
}

void IDColiMove::setupBaseColiParam() {
  unknown1cc = unknown1b8 * unknown1b8;
  unknown1d4 = unknown170.y + unknown1b8 * 2.0f;
  unknown1ea = unknown1bc - unknown1b8 * 2.0f > 0.01f;
  if (!unknown1ea) {
    unknown1bc = unknown1b8 * 2.0f;
  }
  unknown150 = unknown170;
  unknown160 = unknown170;
  if (unknown1ea) {
    unknown160 += unknown180;
  }
}

void IDColiMove::calcColiShapeParms() {
  wrlResTempVec wallVec[32];
  unknown120 = 0;
  f32 scale;
  if (unknown1ea) {
    scale = 1.0f / (unknown180.x * unknown180.x + unknown180.y * unknown180.y + unknown180.z * unknown180.z);
  } else {
    scale = 1.0f;
  }
  u32 count = unknown10.unknowne0;
  for (u32 i = 0; i < count; i++) {
    const mm::Vec3 &position = unknown10.unknownb8[i];
    mm::Vec3 push = unknown150 - position;
    if (unknown1ea) {
      mm::Vec3 offset = position - unknown150;
      f32 rate = scale * (offset.x * unknown180.x + offset.y * unknown180.y + offset.z * unknown180.z);
      if (rate < 0.0f) {
        rate = 0.0f;
      }
      if (rate > 1.0f) {
        rate = 1.0f;
      }
      push = unknown150 + unknown180 * rate - position;
    }
    f32 lengthSq = push.x * push.x + push.y * push.y + push.z * push.z;
    if (lengthSq <= unknown1cc) {
      f32 length = sqrtf(lengthSq);
      if (length <= 0.001f) {
        push *= unknown1b8 - length;
      } else {
        mm::Vec3 direction = push;
        f32 directionLength = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
        if (directionLength <= 0.000001f) {
          direction = mm::Vec3::zero;
        } else {
          f32 directionScale = 1.0f / directionLength;
          direction.x = directionScale * direction.x;
          direction.y = directionScale * direction.y;
          direction.z = directionScale * direction.z;
        }
        const mm::Vec3 &normal = unknown10.unknownc0[i];
        if (direction.x * normal.x + direction.y * normal.y + direction.z * normal.z <= -0.9888f) {
          push = normal;
          push *= unknown1b8 - length;
        } else {
          push *= (1.0f / length) * (unknown1b8 - length);
        }
      }
      unknown150 += push;
      if (!unknown1eb && unknown10.unknownc0[i].y > 0.0f) {
        unknown1eb = calcWallHitChkVec(unknown10.unknownc0[i], unknown10.unknownb8[i], wallVec);
      }
    }
  }
}

bool IDColiMove::calcColiStateParams() {
  wrlResTempVec wallVec[32];
  bool isHit = false;
  u32 count = unknown10.unknowne0;
  unknown120 = 0;
  unknown1f1 = true;
  f32 deceleration = 0.0f;
  f32 top = unknown150.y + unknown1b8 * -2.0f + unknown1bc;
  bool isCeiling = unknown190.y > 0.0f;
  for (u32 i = 0; i < count; i++) {
    if (!isCeiling && unknown10.unknownb8[i].y >= top && unknown10.unknownc0[i].y <= 0.0f) {
      calcVecDeceleration(deceleration, unknown10.unknownc0[i]);
      isCeiling = true;
    }
    if (!isHit) {
      u32 *flags = unknown10.unknownd8;
      u32 isStock = flags[i >> 5] & (1 << (i & 31));
      f32 normalY = unknown10.unknownc0[i].y;
      f32 floor = unknown1d0;
      if (isStock) {
        if (normalY >= -0.01f) {
          isHit = calcWallHitChkVec(unknown10.unknownc0[i], unknown10.unknownb8[i], wallVec);
        }
      } else if (normalY > -0.01f && normalY <= floor) {
        isHit = calcWallHitChkVec(unknown10.unknownc0[i], unknown10.unknownb8[i], wallVec);
      }
    }
  }
  unknown1f1 = false;
  if (unknown140.y < 0.0f) {
    unknown1f4 |= isHit;
  }
  return true;
}

bool IDColiMove::calcWallHitChkVec(const mm::Vec3 &normal, const mm::Vec3 &position, wrlResTempVec *wallVec) {
  if (unknown140.y <= 0.0f) {
    f32 x = position.x - unknown150.x;
    f32 z = position.z - unknown150.z;
    f32 length = sqrtf(x * x + z * z);
    if (length >= 0.01f) {
      if (unknown1f0) {
        return true;
      }
    } else {
      if (unknown1f1) {
        return false;
      }
      if (unknown120 != 0) {
        return true;
      }
      unknown1f0 = true;
      return false;
    }
    x *= 1.0f / length;
    z *= 1.0f / length;
    if (normal.y > 0.01f) {
      unknown1f2 = true;
    }
    if (unknown1f2 && unknown120 != 0) {
      for (int i = 0; i < unknown120; i++) {
        if (x * wallVec[i].unknown00 + z * wallVec[i].unknown04 < s_fLandingVecChk) {
          return true;
        }
      }
      if (unknown120 >= 2) {
        f32 angle = atan2f(x, z);
        f32 leftZ = cosf(2.0943952f - angle);
        f32 leftX = -sinf(2.0943952f - angle);
        f32 rightZ = cosf(-2.0943952f - angle);
        f32 rightX = -sinf(-2.0943952f - angle);
        u32 side = 0;
        for (int i = 0; i < unknown120; i++) {
          if (!(side & 1) && wallVec[i].unknown00 * leftX + wallVec[i].unknown04 * leftZ >= s_fLandingAngle) {
            side |= 1;
            if (side == 3) {
              return true;
            }
          }
          if (!(side & 2) && wallVec[i].unknown00 * rightX + wallVec[i].unknown04 * rightZ >= s_fLandingAngle) {
            side |= 2;
            if (side == 3) {
              return true;
            }
          }
        }
      }
    }
    if (unknown120 < 32) {
      wallVec[unknown120].unknown00 = x;
      wallVec[unknown120].unknown04 = z;
      unknown120++;
    }
  }
  return false;
}

void IDColiMove::calcVecDeceleration(f32 &value, mm::Vec3 vector) {
  if (unknown1f3) {
    f32 dot = unknown1a0.x * vector.x + unknown1a0.z * vector.z;
    if (dot > value) {
      value = dot;
    }
  }
}

bool IDColiMove::calcColiSubShapeParms() {
  wrlResTempVec wallVec[32];
  f32 scale;
  if (unknown1ea) {
    scale = 1.0f / (unknown180.x * unknown180.x + unknown180.y * unknown180.y + unknown180.z * unknown180.z);
  } else {
    scale = 1.0f;
  }
  bool isHit = false;
  u32 count = unknown10.unknowne0;
  for (u32 i = 0; i < count; i++) {
    const mm::Vec3 &position = unknown10.unknownb8[i];
    mm::Vec3 push = unknown150 - position;
    if (unknown1ea) {
      mm::Vec3 offset = position - unknown150;
      f32 rate = scale * (offset.x * unknown180.x + offset.y * unknown180.y + offset.z * unknown180.z);
      if (rate < 0.0f) {
        rate = 0.0f;
      }
      if (rate > 1.0f) {
        rate = 1.0f;
      }
      push = unknown150 + unknown180 * rate - position;
    }
    f32 lengthSq = push.x * push.x + push.y * push.y + push.z * push.z;
    if (lengthSq <= unknown1cc) {
      f32 length = sqrtf(lengthSq);
      if (length <= 0.001f) {
        push *= unknown1b8 - length;
      } else {
        mm::Vec3 direction = push;
        f32 directionLength = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
        if (directionLength <= 0.000001f) {
          direction = mm::Vec3::zero;
        } else {
          f32 directionScale = 1.0f / directionLength;
          direction.x = directionScale * direction.x;
          direction.y = directionScale * direction.y;
          direction.z = directionScale * direction.z;
        }
        const mm::Vec3 &normal = unknown10.unknownc0[i];
        if (direction.x * normal.x + direction.y * normal.y + direction.z * normal.z <= -0.9888f) {
          push = normal;
          push *= unknown1b8 - length;
        } else {
          push *= (1.0f / length) * (unknown1b8 - length);
        }
      }
      unknown150 += push;
      if (!isHit && unknown10.unknownc0[i].y > 0.0f) {
        isHit = calcWallHitChkVec(unknown10.unknownc0[i], unknown10.unknownb8[i], wallVec);
      }
    }
  }
  return isHit;
}

} // namespace idcoli
