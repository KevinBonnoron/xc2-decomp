// Unit evidence (game 1.0.0): the ten window files are one unit (0x710075e3c4 to 0x710076b800, then the destructors the unit emits last, from
// 0x710076b898). Clang places a function where it is first referenced, so the order of the files is read from the functions nothing references
// earlier (constructors, the deleting destructors, entry points); a strong function of a later file called by an earlier one sits inside the
// earlier block (WinProc's constructor and destructor at 0x710075e75c and 0x710075e9a4 sit inside ProcDesktop's):
//   proc_desktop      0x710075e3c4 .. 0x710075ff38
//   proc_exception    0x710075ffdc .. 0x7100760e60
//   proc_mouse        0x7100760e78 .. 0x7100761a1c
//   win_proc          0x7100761b68 (deleting destructor) .. 0x71007624ac; its other functions are first referenced from the files above
//   win_proc_root     0x7100762578 .. 0x71007629f4
//   win_split_frame   0x7100762abc .. 0x7100763b88, before the first function WinView defines itself (the constructor, 0x7100763cbc)
//   win_view          0x7100763cbc .. 0x71007686d8; WinView::setRootRenderWID (0x7100763314) and getClientRect (0x71007639a8) sit inside the
//                     win_split_frame block: inlined there, so first referenced there, and called from nowhere
//   win_view_frame    0x71007686f4 (constructor) .. 0x710076ae28
//   win_view_port     0x710076ae4c
//   win_view_root     0x710076ae90 (constructor) .. 0x710076b800
// The longest increasing subsequence of the function labels of our assembly output, in order, against the game's addresses (283 named functions,
// aliases counted once; a measure of the order, not a proof) is 180 in this order and 147 in the previous one (win_proc second, win_view_root
// before win_view, win_view before win_split_frame); no function changed its match. The GOT does not decide the unit: every global of
// default visibility, defined in the unit or not, is read through the GOT in the game and in our objects.
// clang-format off
#include "proc_desktop.cpp"
#include "proc_exception.cpp"
#include "proc_mouse.cpp"
#include "win_proc.cpp"
#include "win_proc_root.cpp"
#include "win_split_frame.cpp"
#include "win_view.cpp"
#include "win_view_frame.cpp"
#include "win_view_port.cpp"
#include "win_view_root.cpp"
// clang-format on
