#include "idcoli/idcoli.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

void IDColiPrimitive::createSphere(CLSphereWork &sphere, const IDColiInput &input) {
  sphere.unknown00 = input.unknown20;
  sphere.unknown10 = input.unknown90;
}

void IDColiPrimitive::createSphere(CLSphereWork &sphere, const mm::Vec3 &center, f32 radius) {
  sphere.unknown00 = center;
  sphere.unknown10 = radius;
}

void IDColiPrimitive::createAaBbBox(mm::Vec3 &max, mm::Vec3 &min, const void *data) {
  const CLBoxWork *box = static_cast<const CLBoxWork *>(data);
  if (max.x < box->unknown80.x) {
    max.x = box->unknown80.x;
  }
  if (min.x > box->unknown90.x) {
    min.x = box->unknown90.x;
  }
  if (max.y < box->unknown80.y) {
    max.y = box->unknown80.y;
  }
  if (min.y > box->unknown90.y) {
    min.y = box->unknown90.y;
  }
  if (max.z < box->unknown80.z) {
    max.z = box->unknown80.z;
  }
  if (min.z > box->unknown90.z) {
    min.z = box->unknown90.z;
  }
}

void IDColiPrimitive::createAaBbPoli(mm::Vec3 &max, mm::Vec3 &min, const void *data) {}

void IDColiPrimitive::createBaPosSphere(mm::Vec3 &position, mm::Vec3 &unknown, bool &isRotate, f32 &radius, f32 &length, const void *data) {
  const CLSphereWork *sphere = static_cast<const CLSphereWork *>(data);
  position = sphere->unknown00;
  radius = sphere->unknown10;
  length = sphere->unknown10 + sphere->unknown10;
  isRotate = false;
  unknown = mm::Vec3(0.0f, 0.0f, 0.0f);
}

void IDColiPrimitive::createBaPosBox(mm::Vec3 &position, mm::Vec3 &unknown, bool &isRotate, f32 &radius, f32 &length, const void *data) {
  const CLBoxWork *box = static_cast<const CLBoxWork *>(data);
  position = box->unknown60;
  radius = box->unknown70.x;
  length = box->unknown70.y;
  isRotate = false;
  unknown = mm::Vec3(0.0f, 0.0f, 0.0f);
}

} // namespace idcoli
