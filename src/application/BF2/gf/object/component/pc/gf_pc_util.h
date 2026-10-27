#pragma once

namespace ai {
class State;
} // namespace ai

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

class GfComPropertyPc;

namespace pc {

bool IsBuddy(GfComPropertyPc &property);
bool isEnableTurn(GfComPropertyPc &property, const mm::Vec3 &direction);
bool isBuddyPcMove(GfComPropertyPc &property);
bool isWallState(ai::State *state);
const mm::Vec3 &getTargetFront();

} // namespace pc
} // namespace gf
