#include "mm_math/mm_cube.h"

#include "mm_math/mm_line2.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_vec3.h"

namespace mm {

f32 Cube::m_fHalfLength = 0.5f;

static const Vec3 s_baseVertices[8] = {
    Vec3(0.5f, 0.5f, 0.5f),
    Vec3(-0.5f, 0.5f, 0.5f),
    Vec3(-0.5f, 0.5f, -0.5f),
    Vec3(0.5f, 0.5f, -0.5f),
    Vec3(0.5f, -0.5f, 0.5f),
    Vec3(-0.5f, -0.5f, 0.5f),
    Vec3(-0.5f, -0.5f, -0.5f),
    Vec3(0.5f, -0.5f, -0.5f),
};

static const Plane s_basePlanes[6] = {
    Plane(Vec3(0.0f, 1.0f, 0.0f), 0.5f),
    Plane(Vec3(0.0f, -1.0f, 0.0f), 0.5f),
    Plane(Vec3(1.0f, 0.0f, 0.0f), 0.5f),
    Plane(Vec3(-1.0f, 0.0f, 0.0f), 0.5f),
    Plane(Vec3(0.0f, 0.0f, -1.0f), 0.5f),
    Plane(Vec3(0.0f, 0.0f, 1.0f), 0.5f),
};

static const Line2 s_baseLines[12] = {
    {Vec3(1.0f, 0.0f, 0.0f), Vec3(0.5f, 0.5f, 0.5f), Vec3(-0.5f, 0.5f, 0.5f)},
    {Vec3(0.0f, 0.0f, 1.0f), Vec3(-0.5f, 0.5f, 0.5f), Vec3(-0.5f, 0.5f, -0.5f)},
    {Vec3(-1.0f, 0.0f, 0.0f), Vec3(-0.5f, 0.5f, -0.5f), Vec3(0.5f, 0.5f, -0.5f)},
    {Vec3(0.0f, 0.0f, -1.0f), Vec3(0.5f, 0.5f, -0.5f), Vec3(0.5f, 0.5f, 0.5f)},
    {Vec3(1.0f, 0.0f, 0.0f), Vec3(0.5f, -0.5f, 0.5f), Vec3(-0.5f, -0.5f, 0.5f)},
    {Vec3(0.0f, 0.0f, 1.0f), Vec3(-0.5f, -0.5f, 0.5f), Vec3(-0.5f, -0.5f, -0.5f)},
    {Vec3(-1.0f, 0.0f, 0.0f), Vec3(-0.5f, -0.5f, -0.5f), Vec3(0.5f, -0.5f, -0.5f)},
    {Vec3(0.0f, 0.0f, -1.0f), Vec3(0.5f, -0.5f, -0.5f), Vec3(0.5f, -0.5f, 0.5f)},
    {Vec3(0.0f, 1.0f, 0.0f), Vec3(0.5f, 0.5f, 0.5f), Vec3(0.5f, -0.5f, 0.5f)},
    {Vec3(0.0f, 1.0f, 0.0f), Vec3(-0.5f, 0.5f, 0.5f), Vec3(-0.5f, -0.5f, 0.5f)},
    {Vec3(0.0f, 1.0f, 0.0f), Vec3(-0.5f, 0.5f, -0.5f), Vec3(-0.5f, -0.5f, -0.5f)},
    {Vec3(0.0f, 1.0f, 0.0f), Vec3(0.5f, 0.5f, -0.5f), Vec3(0.5f, -0.5f, -0.5f)},
};

f32 Cube::getHalfLength() { return m_fHalfLength; }

const Vec3 *Cube::getBaseVertices() { return s_baseVertices; }

const Plane *Cube::getBasePlanes() { return s_basePlanes; }

const Line2 *Cube::getBaseLines() { return s_baseLines; }

bool Cube::isCollide(const PrimBase &prim) const {
  switch (prim.type) {
  case TYPE_CUBE:
    return isCollideCube(prim);
  case TYPE_SPHERE:
    return isCollideSphere(prim);
  case TYPE_CYLINDER:
    return prim.isCollide(*this);
  }
  return false;
}

} // namespace mm
