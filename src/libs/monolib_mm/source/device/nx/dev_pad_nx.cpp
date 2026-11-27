#include "device/nx/dev_pad_nx.h"

#include "mm_math/mm_math.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "nn/hid.h"

namespace ml {

void DevPadNx::Impl::stateUpdate(f32 time) {
  if (unknown20 == 2) {
    updateNpad();
  }
}

void DevPadNx::Impl::updatePad(f32 time) { updateNpad(); }

void DevPadNx::Impl::stopVibration(PadData &data) {
  if (data.unknown14 && data.unknown7c && (data.unknown18 | 2) == 3) {
    u32 id = data.m_padVibrationInfo.unknown00;
    if (id != 0) {
      nn::hid::VibrationPlayer *player = getVibPlayer(id);
      if (player != nullptr && player->IsLoaded()) {
        player->Stop();
        data.unknown110.Disconnect();
        data.unknown148.Disconnect();
        data.m_padVibrationInfo = PadVibrationInfo(0);
        data.unknown78 = 0.0f;
        data.unknown7c = false;
        data.unknown7d = false;
      }
    }
  }
}

void DevPadNx::Impl::updateDebugPad(PadData &data) {
  data.unknown00 = 0;
  data.unknown04 = 0.0f;
  data.unknown08 = 0.0f;
  data.unknown0c = 0.0f;
  data.unknown10 = 0.0f;
  nn::hid::DebugPadState state;
  nn::hid::GetDebugPadState(&state);
  data.unknown14 = (state.mAttributes & 1) != 0;
  data.unknown18 = 4;
  if (state.mButtons & (1 << 0)) {
    data.unknown00 |= unknown001_2;
  }
  if (state.mButtons & (1 << 1)) {
    data.unknown00 |= unknown001_1;
  }
  if (state.mButtons & (1 << 2)) {
    data.unknown00 |= unknown001_3;
  }
  if (state.mButtons & (1 << 3)) {
    data.unknown00 |= unknown001_0;
  }
  if (state.mButtons & (1 << 4)) {
    data.unknown00 |= unknown001_4;
  }
  if (state.mButtons & (1 << 5)) {
    data.unknown00 |= unknown001_5;
  }
  if (state.mButtons & (1 << 6)) {
    data.unknown00 |= unknown001_6;
  }
  if (state.mButtons & (1 << 7)) {
    data.unknown00 |= unknown001_7;
  }
  if (state.mButtons & (1 << 12)) {
    data.unknown00 |= unknown001_13;
  }
  if (state.mButtons & (1 << 10)) {
    data.unknown00 |= unknown001_15;
  }
  if (state.mButtons & (1 << 11)) {
    data.unknown00 |= unknown001_12;
  }
  if (state.mButtons & (1 << 13)) {
    data.unknown00 |= unknown001_14;
  }
  if (state.mButtons & (1 << 8)) {
    data.unknown00 |= unknown001_9;
  }
  if (state.mButtons & (1 << 9)) {
    data.unknown00 |= unknown001_8;
  }
  data.unknown04 = state.mAnalogStickL.mX * (1.0f / 32767.0f);
  data.unknown08 = state.mAnalogStickL.mY * (1.0f / 32767.0f);
  data.unknown0c = state.mAnalogStickR.mX * (1.0f / 32767.0f);
  data.unknown10 = state.mAnalogStickR.mY * (1.0f / 32767.0f);
  // The game passes the lower limit as the value of mm::clamp and the stick as its minimum: the assertion mi <= ma
  // (line 819 of mm_math.h) tests the stick against 1.0f.
  data.unknown04 = mm::clamp(-1.0f, data.unknown04, 1.0f);
  data.unknown08 = mm::clamp(-1.0f, data.unknown08, 1.0f);
  data.unknown0c = mm::clamp(-1.0f, data.unknown0c, 1.0f);
  data.unknown10 = mm::clamp(-1.0f, data.unknown10, 1.0f);
}

nn::hid::VibrationPlayer *DevPadNx::Impl::getVibPlayer(u32 id) {
  if (id - 1 < 0x3f) {
    return &unknown38[id].unknown18;
  }
  return nullptr;
}

u32 DevPadNx::getLocalStyle(int padNo) const { return unknown548->unknown003(padNo).unknown18; }

int DevPadNx::getLocalUserSelectPadID() const {
  const Impl *impl = unknown548.operator->();
  return impl->unknown4544 != impl->unknown4540 ? impl->unknown4544 : 4;
}

u32 DevPadNx::getLocalBtn(int padNo) const { return unknown548->unknown003(padNo).unknown00; }

f32 DevPadNx::getLocalALX(int padNo) const { return unknown548->unknown003(padNo).unknown04; }

f32 DevPadNx::getLocalALY(int padNo) const { return unknown548->unknown003(padNo).unknown08; }

f32 DevPadNx::getLocalARX(int padNo) const { return unknown548->unknown003(padNo).unknown0c; }

f32 DevPadNx::getLocalARY(int padNo) const { return unknown548->unknown003(padNo).unknown10; }

void DevPadNx::playLocalVibration(int padNo, const PadVibrationInfo &info) { unknown548->playVibration(unknown548->unknown003(padNo), info); }

void DevPadNx::stopLocalVibration(int padNo) { unknown548->stopVibration(unknown548->unknown003(padNo)); }

void DevPadNx::setUserSelectControllerID(u32 id) {
  DevPadNx *pad = static_cast<DevPadNx *>(get());
  if (pad == nullptr) {
    return;
  }
  Impl *impl = pad->unknown548.operator->();
  impl->unknown4544 = -1;
  for (int i = 0; i < 4; i++) {
    if (impl->unknown24[i] == id) {
      impl->unknown4544 = i;
      break;
    }
  }
}

void DevPadNx::updateDevice(f32 time) {
  Impl *impl = unknown548.operator->();
  if (impl->unknown0000.isValid()) {
    impl->unknown0000(time);
  }
}

bool DevPadNx::createDevice() { return true; }

void DevPadNx::releaseDevice() { unknown548->release(); }

} // namespace ml

template void mm::mtl::Delegate<void(float)>::memberFuncInvoker<ml::DevPadNx::Impl>(const mm::mtl::Delegate<void(float)> *, float);
