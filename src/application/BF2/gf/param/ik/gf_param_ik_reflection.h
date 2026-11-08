#pragma once

namespace fw {
class Reflection;
} // namespace fw

namespace gf {

fw::Reflection *createLookAtIKReflection();
fw::Reflection *createSpineIKReflection();
fw::Reflection *createSPCIKReflection();
fw::Reflection *createSpineRotateIKReflection();
fw::Reflection *createFootIKReflection();

} // namespace gf
