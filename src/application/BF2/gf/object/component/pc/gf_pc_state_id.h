#pragma once

namespace gf {
namespace pc {

enum STATE_ID {
  STATE_ID_UNKNOWN_0 = 0,   // Inferred role: state id field; original name unknown.
  STATE_ID_UNKNOWN_1 = 1,   // Inferred role: state id field on ground; original name unknown.
  STATE_ID_UNKNOWN_2 = 2,   // Inferred role: state id field start; original name unknown.
  STATE_ID_UNKNOWN_3 = 3,   // Inferred role: state id field idle; original name unknown.
  STATE_ID_UNKNOWN_4 = 4,   // Inferred role: state id field idle turn; original name unknown.
  STATE_ID_UNKNOWN_5 = 5,   // Inferred role: state id field stop brake; original name unknown.
  STATE_ID_UNKNOWN_6 = 6,   // Inferred role: state id field move common; original name unknown.
  STATE_ID_UNKNOWN_7 = 7,   // Inferred role: state id field move; original name unknown.
  STATE_ID_UNKNOWN_8 = 8,   // Inferred role: state id field turn; original name unknown.
  STATE_ID_UNKNOWN_9 = 9,   // Inferred role: state id field access; original name unknown.
  STATE_ID_UNKNOWN_10 = 10, // Inferred role: state id field talk; original name unknown.
  STATE_ID_UNKNOWN_11 = 11, // Inferred role: state id field air; original name unknown.
  STATE_ID_UNKNOWN_12 = 12, // Inferred role: state id field jump; original name unknown.
  STATE_ID_UNKNOWN_13 = 13, // Inferred role: state id field land; original name unknown.
  STATE_ID_UNKNOWN_14 = 14, // Inferred role: state id field land big; original name unknown.
  STATE_ID_UNKNOWN_15 = 15, // Inferred role: state id field fall; original name unknown.
  STATE_ID_UNKNOWN_16 = 16, // Inferred role: state id field prepare big jump; original name unknown.
  STATE_ID_UNKNOWN_17 = 17, // Inferred role: state id field big jump; original name unknown.
  STATE_ID_UNKNOWN_18 = 18, // Inferred role: state id field water; original name unknown.
  STATE_ID_UNKNOWN_19 = 19, // Inferred role: state id field water normal; original name unknown.
  STATE_ID_UNKNOWN_20 = 20, // Inferred role: state id field water idle; original name unknown.
  STATE_ID_UNKNOWN_21 = 21, // Inferred role: state id field water idle turn; original name unknown.
  STATE_ID_UNKNOWN_22 = 22, // Inferred role: state id field water swim; original name unknown.
  STATE_ID_UNKNOWN_23 = 23, // Inferred role: state id field water brake; original name unknown.
  STATE_ID_UNKNOWN_24 = 24, // Inferred role: state id field water dive; original name unknown.
  STATE_ID_UNKNOWN_25 = 25, // Inferred role: state id field water sink; original name unknown.
  STATE_ID_UNKNOWN_26 = 26, // Inferred role: state id field water rise; original name unknown.
  STATE_ID_UNKNOWN_27 = 27, // Inferred role: state id field water swim sink; original name unknown.
  STATE_ID_UNKNOWN_28 = 28, // Inferred role: state id field water swim rise; original name unknown.
  STATE_ID_UNKNOWN_29 = 29, // Inferred role: state id field water prepare warp; original name unknown.
  STATE_ID_UNKNOWN_30 = 30, // Inferred role: state id field water warp dive; original name unknown.
  STATE_ID_UNKNOWN_31 = 31, // Inferred role: state id field water warp rise; original name unknown.
  STATE_ID_UNKNOWN_32 = 32, // Inferred role: state id field water warp rise buddy; original name unknown.
  STATE_ID_UNKNOWN_33 = 33, // Inferred role: state id field water dead; original name unknown.
  STATE_ID_UNKNOWN_34 = 34, // Inferred role: state id field water dead dive; original name unknown.
  STATE_ID_UNKNOWN_35 = 35, // Inferred role: state id field water dead sink; original name unknown.
  STATE_ID_UNKNOWN_36 = 36, // Inferred role: state id field water dead rise; original name unknown.
  STATE_ID_UNKNOWN_37 = 37, // Inferred role: state id field water dead idle; original name unknown.
  STATE_ID_UNKNOWN_38 = 38, // Inferred role: state id field wall; original name unknown.
  STATE_ID_UNKNOWN_39 = 39, // Inferred role: state id field wall performance; original name unknown.
  STATE_ID_UNKNOWN_40 = 40, // Inferred role: state id field wall adsorption ground; original name unknown.
  STATE_ID_UNKNOWN_41 = 41, // Inferred role: state id field wall adsorption air; original name unknown.
  STATE_ID_UNKNOWN_42 = 42, // Inferred role: state id field wall adsorption under ground; original name unknown.
  STATE_ID_UNKNOWN_43 = 43, // Inferred role: state id field wall climb end; original name unknown.
  STATE_ID_UNKNOWN_44 = 44, // Inferred role: state id field wall land; original name unknown.
  STATE_ID_UNKNOWN_45 = 45, // Inferred role: state id field on wall; original name unknown.
  STATE_ID_UNKNOWN_46 = 46, // Inferred role: state id field wall idle; original name unknown.
  STATE_ID_UNKNOWN_47 = 47, // Inferred role: state id field wall move; original name unknown.
  STATE_ID_UNKNOWN_48 = 48, // Inferred role: state id field wall prepare jump; original name unknown.
  STATE_ID_UNKNOWN_49 = 49, // Inferred role: state id field wall jump; original name unknown.
  STATE_ID_UNKNOWN_50 = 50, // Inferred role: state id field wall jump start; original name unknown.
  STATE_ID_UNKNOWN_51 = 51, // Inferred role: state id field wall jump move; original name unknown.
  STATE_ID_UNKNOWN_52 = 52, // Inferred role: state id field wall jump end; original name unknown.
  STATE_ID_UNKNOWN_53 = 53, // Inferred role: state id field slide; original name unknown.
  STATE_ID_UNKNOWN_54 = 54, // Inferred role: state id field slide move; original name unknown.
  STATE_ID_UNKNOWN_55 = 55, // Inferred role: state id field slide land brake; original name unknown.
  STATE_ID_UNKNOWN_56 = 56, // Inferred role: state id field lure; original name unknown.
  STATE_ID_UNKNOWN_57 = 57, // Inferred role: state id field ride on; original name unknown.
  STATE_ID_UNKNOWN_58 = 58, // Inferred role: state id field dead; original name unknown.
  STATE_ID_UNKNOWN_59 = 59, // Inferred role: state id field alive; original name unknown.
  STATE_ID_UNKNOWN_60 = 60, // Inferred role: state id field air dead; original name unknown.
  STATE_ID_UNKNOWN_61 = 61, // Inferred role: state id field extra control; original name unknown.
  STATE_ID_UNKNOWN_62 = 62, // Inferred role: state id battle; original name unknown.
  STATE_ID_UNKNOWN_63 = 63, // Inferred role: state id battle start; original name unknown.
  STATE_ID_UNKNOWN_64 = 64, // Inferred role: state id battle idle; original name unknown.
  STATE_ID_UNKNOWN_65 = 65, // Inferred role: state id battle put out weapon; original name unknown.
  STATE_ID_UNKNOWN_66 = 66, // Inferred role: state id battle put away weapon; original name unknown.
  STATE_ID_UNKNOWN_67 = 67, // Inferred role: state id battle move; original name unknown.
  STATE_ID_UNKNOWN_68 = 68, // Inferred role: state id battle kizuna max; original name unknown.
  STATE_ID_UNKNOWN_69 = 69, // Inferred role: state id battle attack; original name unknown.
  STATE_ID_UNKNOWN_70 = 70, // Inferred role: state id battle arts; original name unknown.
  STATE_ID_UNKNOWN_71 = 71, // Inferred role: state id battle blade arts; original name unknown.
  STATE_ID_UNKNOWN_72 = 72, // Inferred role: state id battle blade change; original name unknown.
  STATE_ID_UNKNOWN_73 = 73, // Inferred role: state id battle sp attack; original name unknown.
  STATE_ID_UNKNOWN_74 = 74, // Inferred role: state id battle support; original name unknown.
  STATE_ID_UNKNOWN_75 = 75, // Inferred role: state id battle blade guard; original name unknown.
  STATE_ID_UNKNOWN_76 = 76, // Inferred role: state id battle repelled; original name unknown.
  STATE_ID_UNKNOWN_77 = 77, // Inferred role: state id battle down; original name unknown.
  STATE_ID_UNKNOWN_78 = 78, // Inferred role: state id battle knock back; original name unknown.
  STATE_ID_UNKNOWN_79 = 79, // Inferred role: state id battle break; original name unknown.
  STATE_ID_UNKNOWN_80 = 80, // Inferred role: state id battle dead; original name unknown.
  STATE_ID_UNKNOWN_81 = 81, // Inferred role: state id battle rescue; original name unknown.
};

} // namespace pc
} // namespace gf
