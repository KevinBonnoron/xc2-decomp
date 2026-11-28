# Decisions

The rules that apply to one question that comes back all the time: *the game's code only matches with a form that looks odd: is that form original code, or is it steering the compiler?* Each rule states what is accepted or refused, the technical reason, its scope and its evidence. Read this file before you write a single-use local, a `{}` block, a repeated store, a helper that only one function calls, a cast, or a retype, and before you drop one of them because "it only changes register allocation".

Source comments cite these texts: `ruling 2`, `P2`, `decision 48`, `decision 2026-11-14 #26` (the historical label of decision 26 below). The numbering is stable: new decisions are added at the end and nothing is renumbered.

## How the texts relate

- **Rulings 1 to 9** are the base rules, about single-use locals, scopes, orders, statements without effect, erased arguments, bit helpers, duplicated source and one-user helpers. Each decision cites them as `ruling N`.
- **Principles P1 to P5** generalise the rulings. A question that a ruling answers is answered by the ruling; a question that only a principle covers is answered by the principle.
- **Decisions 1 to 59** apply the rulings and principles to a specific form in a specific function, or settle a case that no ruling covers.
- A form that no ruling, principle or decision covers is not extended from the nearest one by analogy: it is reported with its evidence (assembly, addresses, forms tried).
- **Reserved areas.** The `ui` namespace (see [CONTRIBUTING.md](../CONTRIBUTING.md)) and the libraries `battle`, `eflib`, `grlib`, `anmlib`, `wnd` and the SDK declarations of `nn` are reserved for the contributor who works on them. A function that needs a change there is left alone and the needed change is reported to that contributor; no file of a reserved area is edited for a match, because the edit would conflict with that work (principle P5).

## The rulings

The numbers are stable; comments cite them as `ruling N`.

1. **Single-use local whose initialiser holds a call.**
   - **Rule.** Accepted when the local gives the game's real call order.
   - **Why.** The local places the call before another operation; the assembly shows that order, so it is a visible position and not a register choice.
   - **Scope.** Code already on `main` that matches stays. A local that only reads a member (no call in its initialiser) is ruling 2.
   - **Evidence.** `seqWaitTalkEnd`.
2. **Single-use local that only reads a member.**
   - **Rule.** Accepted when the load it places is the game's.
   - **Why.** The game loads the member before another call or load, and the local is what puts the load there; the assembly shows the position.
   - **Scope.** Precedents on `main` stay.
   - **Evidence.** `initMpfMapParts`.
3. **`{}` block around a variable without destructor, or a braced temporary (`create({...})`).**
   - **Rule.** Accepted when the game's stack layout proves that the lifetime ends there.
   - **Why.** The slot is reused afterwards, which only a scope that ends there produces (a temporary, a braced local and a plain local give different slots).
   - **Scope.** Only where the slot reuse is shown.
   - **Evidence.** `GfMenuObjBlDetail::create` (second cause), `GfMenuObjEvTheater::initialize`.
4. **A declaration or assignment order that only changes register allocation.**
   - **Rule.** Accepted when it is the only order that matches and the order itself is plausible code (`int y = 0; int x = 0;`, fields assigned in parameter order).
   - **Why.** The order is source a programmer writes; it costs no extra construct.
   - **Scope.** Refused when it needs otherwise useless locals. Still refused: the three `GfGameFlag` functions, whose bit-flag reader in `include/mm_mtl/bitflag.h` needs two single-use locals (`word`, `mask`) (decision 9).
   - **Evidence.** Matched with this rule: `shadowRender`, `createLookIK`.
5. **A statement without effect that the game's code really holds.**
   - **Rule.** Accepted when the assembly shows the operation: an extra `clear()` loop, a second release of a pointer already nulled, `if (x) ...; if (!x) ...` kept as two tests.
   - **Why.** The binary contains the operation, so the source contains the statement.
   - **Scope.** The statement must be visible in the assembly.
   - **Evidence.** `EffectLodManager::term`, `~GfMenuObjWorldMap`, `VoicePlayer::update`; the `DrLightObjGlobalIBL` constructor already on `main` stays.
6. **An argument the compiler erased.**
   - **Rule.** Keep the parameter and pass the most plausible expression, with a comment saying that the game never sets the register and that the original expression cannot be checked.
   - **Why.** When the callee is defined in the same translation unit and never reads the parameter, clang drops the value and the register is never set. The mangled symbol proves the parameter exists.
   - **Scope.** Only for a callee in the same unit that never reads the parameter.
   - **Evidence.** `DrMdoNomAfterImage::update` with `model->m_offsetPos`.
7. **A bit-table index the game computes unsigned (`lsr`) from a signed counter.**
   - **Rule.** Use one shared inline bit-test helper (inferred name `unknownNNN`, `u32` index, a comment with its role) instead of `static_cast<u32>(i) >> 5` at each call site. If the helper does not match somewhere, report it before choosing another form.
   - **Why.** The unsigned shift of a signed counter is one operation of the game; one helper states it once instead of repeating a cast at every user.
   - **Scope.** Bit-table indices of this shape.
   - **Evidence.** `readMpfModelCheck` (which also calls `DrMan::isGblIdx` instead of repeating it), `dr_mdo_ctl_seam_light.cpp` and `dr_mdo_ctl_seam_read.cpp`, which had the cast.
8. **Code the original source genuinely duplicates.**
   - **Rule.** When another game function's statements are written again in a second function, and no call, unit grouping or flag reproduces the binary, write the statements out again, with a comment naming the function they repeat and the evidence (the instruction counts of the call form, measured, not copied). No macro: the binary shows repeated statements, and a macro is a construct with a name that the binary cannot show (AGENTS.md: macros leave no trace), so writing the statements out is the form the evidence supports.
   - **Why.** A helper holding the block is simplified on its own before it is inlined, which the block inside the caller is not; when the helper form always misses, the source repeated the block. The proof is the failed call form, not a preference (see [lessons](lessons.md), "Inlined helpers and duplicated source").
   - **Scope.** Only after the call form has been measured and does not match (P4).
   - **Evidence.** `VoiceManager::playAuto` and `preloadAuto`, `GfMenuObjItemList2::ItemListListener::reciveEvent`; the six `IDColiGrandObj` callback blocks stay written out.
9. **An inline helper with a single user.**
   - **Rule.** Accepted when no other valid form matches. The helper gets a *descriptive* name marked `// Inferred name; ...` (as macros do), not `unknownNNN`; it is renamed if Torna or Xenoblade DE later shows a symbol. The forms tried without it are listed in a comment, with the address of its user. AGENTS.md holds the exact marker comment.
   - **Why.** The helper's only proof is that its user matches with it and does not without it (clang optimises a separate function before inlining it; `LocatorReach::update` tests two members in one 32-bit load only through a helper). Like a macro, it is evidenced only by code generation and has no symbol, so the `unknownNNN` numbering, meant for functions that exist in the binary, does not apply. The descriptive name is marked as inferred and is replaced if a sibling build gives a symbol.
   - **Scope.** One user; a helper with several users stays `unknownNNN` (decision 26 is the only exception).
   - **Evidence.** `LocatorReach::update` (with its D0/D2, `getPos`, `getPosNum`), `StateFieldIdle::isEnableUnique`, `QuestID::unknown001`, `DevGraphQue`.

## The principles

Derived from rulings 1 to 9; they cover every question after them.

- **P1.** A member's or variable's type follows the game's own accesses, in any game function, matched or not. An existing type that nothing proves has no priority over the one the accesses show.
- **P2.** A single-use local is accepted when its position is visible in the game's instruction order: it places a call (ruling 1), a load (ruling 2) or a computation before another call, load or store, or it reproduces the game's block shape. It stays refused when its only effect is register allocation (the `GfGameFlag` `word`/`mask` locals stay refused, decision 9).
- **P3.** A statement or store that the game's code holds is written, including redundant zero or non-zero stores visible in the assembly, and the same statement repeated where the same source pattern repeats (ruling 5).
- **P4.** Among forms that match, prefer the most natural code. The duplication of ruling 8 is allowed only when the call or helper provably does not match.
- **P5.** Reserved areas are never edited for a match; the needed change is reported to the contributor of the area.

## Index by topic

- Single-use locals, scopes, stores: 1, 2, 3, 10 to 14, 16, 17, 21, 33, 39, 44, 49.
- Member and variable types: 4, 6, 18, 19, 20, 35, 36, 48.
- Casts and byte offsets: 38, 40, 45, 47, 53, 54, 55.
- Helpers, names and written-out code: 25 to 32, 41, 42, 50, 58.
- Devices kept out of the tree (declared but undefined specialisations, `inline` under the real name): 41, 51.
- Refusals: 9, 43, 46, 53.
- Embedded public libraries (zlib, utf8.h, FastLZ): 59.
- Changes needed in a reserved area: 22, 37, 52.

## The decisions

Each entry gives the rule, the reason, its scope and its evidence: a commit of `main`, or a game function and address.

### 1. A `bool` carried out of a `{}` block

- **Rule.** A fade function declares `bool isChange` before a `{}` block (ruling 3) and reads it after the block. Accepted, as part of ruling 3.
- **Why.** The flag is what the game keeps alive across the block; the slot of the block's own variable is what it reuses.
- **Scope.** Only where the block itself is justified by the stack layout.

### 2. `GfMenuObjInn::DriverListener`: a store after `getPos` and a `u32` local

- **Rule.** `CtrlParam::unknown04 = 0` is written after the `getPos` call, and the listener keeps a `u32 driver` local. Accepted.
- **Why.** The zero is part of the game's 64-bit store that comes after the call (P3), and the local places a call (ruling 1).
- **Evidence.** The store pair in `GfMenuObjInn::DriverListener::reciveEvent`.

### 3. `OpenParam()` constructor of the menu objects

- **Rule.** The constructor zeroes both `unknown18` and `unknown1c`, as the game's `new OpenParam()` does. The `param.unknown1c = 0` that `GfMenuObjInn` had written becomes dead and is dropped if `GfMenuObjInn` still matches. `GfMenuObjBladeSet` is written with `param.unknown18 = 0;`.
- **Why.** The constructor was incomplete compared with `GfMenuObjBladeSet::detailOpen`; the game's `stp wzr, w8` shows the store (P3).
- **Evidence.** `GfMenuObjBladeSet::detailOpen`.

### 4. `DrPixlShadowObjDir::unknown338` as two floats

- **Rule.** Two `f32` members instead of a `Pnt<f32>`.
- **Why.** Every reader loads a single float; `Pnt<f32>` was a mechanical guess (P1).

### 5. `setInputDirPow` writes the matrix column by column

- **Rule.** The three axes are written as the columns of the matrix. Accepted (ruling 4).
- **Why.** It is plausible code and the only order that matches.

### 6. `FixedVectorUnit<16>` as `u16[8]`

- **Rule.** The current unit stays; the three `DevTouch` functions (`getPos`, `getMove`, `itDown`) stay blocked.
- **Why.** A halfword unit would make them match but it is not a superset of the current one: it breaks `fw::ColiCheckCallback::coli_callback` (a `float[4]` unit does the same and other units are worse). Nothing proves either unit.
- **Scope.** An earlier assumption that the halfword unit matched a strict superset was wrong; the measurement overrides it.

### 7. `setupTreeList`: a local copy of a table entry

- **Rule.** `mm::Vec3 inverse = unknown90[level];` in `idcoli::IDColiTreeTop::setupTreeList` is accepted.
- **Why.** A local copy of a table entry is natural code. The copy had been removed because it only chooses the loop base pointer; the helper `ColiLinkList::unknown002` and an operand swap in `initCehckTree` had been written for it instead.
- **Scope.** P2: a copy of this kind must be natural code, not a register steer.

### 8. `getFieldSkillFromGimmik`: two variables

- **Rule.** The function keeps the raw `u16` and its widened `u32`. Accepted.
- **Why.** The game holds both values (x22 and w21).

### 9. `GfGameFlag` bit-flag reader: the `word` and `mask` locals

- **Rule.** Refused. The reader in `include/mm_mtl/bitflag.h` matches only with two single-use locals (`word`, `mask`); the three `GfGameFlag` functions stay blocked.
- **Why.** The only effect of the locals is register allocation (P2).
- **Scope.** This is the standing example of the limit of P2. Decisions 44 and 57 accept register-sensitive locals only on evidence of a `-g` debug-value effect, which is absent here.

### 10. `GfMenuGfObjAdapter::create`: `bool isUpdateAfter` before `operator new`

- **Rule.** Accepted (P2).
- **Why.** The local places the flag before the allocation call.

### 11. `updateSepia` and `incSuppressEnemy`

- **Rule.** The three flags of `updateSepia` and the locals of `incSuppressEnemy` are accepted (rulings 1 and 2).

### 12. `execAbsSummon`: a local holding a call

- **Rule.** Accepted (P2).
- **Why.** The local holds a call and its effect is the shape of the blocks.

### 13. `createSearchObj`: a repeated store in the first block

- **Rule.** Accepted (P3).
- **Why.** The first block repeats a store that the second block also has, and the assembly shows it in both: the same statement repeats where the same pattern repeats.

### 14. `createMotionBlendObj`: `u32 offset`

- **Rule.** Accepted (P2).
- **Why.** The local reproduces the block shape.

### 15. `#pragma pack` of the VM `unknown004`

- **Rule.** `pack(push, 1)`, with a comment that an alignment of 2 also matches.
- **Why.** The game's loads exclude an alignment of 4.
- **Evidence.** `vmArgFunctionGet` and `vmOCNameGet` match with it.

### 16. `vmThreadGetOC`: `package` and `function` locals

- **Rule.** Accepted (P2).
- **Why.** They place the `add` before the `sbfiz`.

### 17. `DrPixlShadowRaytrace::debugRender`: `int y = halfHeight + 1;`

- **Rule.** Accepted (P2).
- **Why.** The local places the `add` before the load.

### 18. `applyLinearVelocityAndRotY`: `unknownb0` as `f32`

- **Rule.** The member is `f32` (it was `u32`). Accepted (P1).
- **Why.** Two game functions use it as a float.

### 19. FieldSkill: `u16 unknown5c` as two `bool`

- **Rule.** Two `bool` members. Accepted (P1).
- **Why.** The game accesses the member by bytes in two functions.

### 20. A pair struct proven by one 64-bit store

- **Rule.** Accepted: two adjacent members that the game stores as a unit with one 64-bit store, and does not merge with their neighbour, form a sub-object (a pair struct).
- **Why.** The unit store is evidence of a sub-object.
- **Evidence.** `EnvironmentInfo`, `Minimap2`; `ArtsPalette` and `Compass` already on `main`.

### 21. `int ctrl = startPresetCtrl(...)`

- **Rule.** Accepted (P2).
- **Why.** The local fixes the order of two stores that come after the call.

### 22. `Queue::erase`, `size()` and `GfMenuObjExpGet::OpenParam() {}`

The seven `mm::mtl::Queue<T>::erase` instantiations of the `GfMenuObj...Info` classes (and `GfMenuObjExpGet::removeExpGet`) match with a fix of `include/mm_mtl/queue.h`. Three points:

1. **`size()` returns `size_t`.** The `size() != 0` assert reads the size as 64 bits, so `size()` must return `size_t`; that breaks the one function that reads it as 32 bits, `anm::ThreadPool::threadFunc` in the reserved `anmlib`. Rule: `threadFunc` calls `anm::JobQueue::getJobCount()`, the accessor that Xenoblade DE keeps out of line (symbol `_ZNK3anm8JobQueue11getJobCountEv`, XC1DE 0x7100918220: `ldr w0, [x0, #0x10]; ret`). That change is a request to the contributor of `anmlib`; until it lands the `erase` instantiations are not applied.
2. **The two discarded `at()` asserts.** After the shifting loop the game holds two `at()` asserts whose results it drops. Rule: the implementation uses the two semantically meaningful slots (the vacated end slot). The two asserts leave no operand in the binary, so any slot matches; the meaningful one is chosen for readability (P4). Ruling 5 covers that two calls exist, not which slots.
3. **`GfMenuObjExpGet::OpenParam() {}`.** `Queue<ExpGetInfo>::erase` copies 28 of the 32 bytes of the element, which needs an empty constructor, proven only by this instantiation. Accepted as a language rule, like `GmkDmgPhantom()` (decision 24); every user still matches. Applied.

### 23. `DevFileJobReadDvd::wkUpdate`: a bare `isSuspend();`

- **Rule.** Write the test `if (DevFileTh::isSuspend()) { return; }`.
- **Why.** A bare accessor call is not original code; the test gives the same bytes.

### 24. `List::erase` and `GmkDmgPhantom()`

- **Rule.** Kept as they are on `main`.
- **Why.** Both match as written and no access or symbol shows another form (P4: a matching natural form is not changed).
- **Evidence.** Decision 22 (3) cites `GmkDmgPhantom()` as the language rule for a constructor that only an instantiation proves.

### 25. `DevGraphQue::pushWholeRect` against the block form

- **Rule.** Kept as a helper.
- **Why.** `popRect` shows the same pattern (ruling 9).

### 26. The 20 event `setFlag` and `setDispFlag` helpers

- **Rule.** Kept with their descriptive names, plus the marker comment `// Inferred name`. They are the only exception to `unknownNNN` for helpers with several users (AGENTS.md). Source comments cite this as `decision 2026-11-14 #26`.
- **Why.** These private helpers have the same role in every event class (set or clear a flag bit), so one consistent descriptive name across the 20 classes is clearer than per-file numbering.

### 27. `setCategoryMute` setter

- **Rule.** Kept.
- **Why.** A setter on the category is plausible; the local form would also pass P2.

### 28. `IDColiTreeTop::unknown036` bit helper

- **Rule.** Kept: ruling 7 extended to this bit helper.
- **Why.** The reason of ruling 7 applies unchanged (the game computes a bit-table index unsigned from a signed counter); no new construct.

### 29. `getClientScissorRect1`: the body inlined again

- **Rule.** Kept: ruling 8 plus ruling 2.
- **Why.** The reasons of rulings 8 (the body is genuinely repeated) and 2 (the load it places is the game's) apply unchanged; no new construct.

### 30. Declaration orders of ruling 4

- **Rule.** Kept (ruling 4).
- **Why.** `DrAPCache::begin`, `InsertNext`, `calcDistSub` and `releaseTreeList` use orders that only change register allocation but read as plausible code.

### 31. The ten `fontLayerXxx` lookups

- **Rule.** One shared helper (`unknownNNN`, ten users) instead of ten written-out copies.
- **Why.** It matches, so the proof that ruling 8 requires (the call form does not match) is not made (P4).

### 32. `IDevFontInfo::unknown50()`

- **Rule.** Accepted: a virtual function.
- **Why.** A call at its vtable offset proves it.

### 33. `BgmManager::clear`: redundant `unknown63 = false`

- **Rule.** Accepted (P3) when the assembly shows the store.
- **Why.** It does: `strb wzr, [sp, #107]` after the zeroing `stur xzr` of the `EventBgmSetup`, 0x71000aa2d0.
- **Scope.** `BgmManager::clear` matches with the store (42 instructions) since the `oc-dec-untouchedgf` integration: the flag and fade values are read into the locals `fadeSeconds` (the `FrameManager` call, ruling 1) and `isHandOver` (the flag load, ruling 2) before the four stores, in the order `4c, 62, 63, 61`, as the comment of the function says (41 instructions without both locals, and with only one of them). `OnEventProc` (59 against 60 at the time) is not written.

### 34. `found.unknown00 == m_end`

- **Rule.** Accepted: the test of an iterator against the end.
- **Why.** Comparing an iterator with the end is the ordinary container idiom, and the game compares with the stored end pointer in each of the listed functions.
- **Evidence.** `ScnPoolObj::release` (twice), `updateMsg`, `setCurrent`.

### 35. `DrPixlPostObjBloom`: six render targets

- **Rule.** Retype the six bloom members to `DrPixlRenderTarget *`, rework the release helper, write `debugRender` and `calculateDownScaleImpl`, and remove the cast in `bloomLensFlare`.
- **Why.** The constructor allocates that type (P1).

### 36. `unknown169`: a 16-byte struct in four detail menus

- **Rule.** Accepted.
- **Why.** One sub-object is cleared as a unit after the other members, the same way in four classes.

### 37. `DevPadNx` and `EventData::unknown0c_f32`

- **Rule.** `include/nn/hid.h` (DevPadNx) and `EventData::unknown0c_f32` (MainMenu2BG) are in reserved areas: the change is requested from the contributor of the area, not made (P5).

### 38. Reading a binary blob at byte offsets

- **Rule.** Kept: `plugin/bdat.cpp` reads the BDAT blob with byte-offset readers (`unknown005`, `unknown006`: `reinterpret_cast<u32 *>(bin + offset)`) and `pack(1)` on the sheet header (as decision 15). The same applies to `dr/dr_env_coli_obj.cpp`, which parses the loaded environment-collision resource at byte offsets (`unknown006`, `007`, `008`, the `EnvColiPostData` lists) and reads the cloud parameter records (`unknown011` to `unknown015`) of `updateCloudParams` the same way.
- **Why.** The game adds the offset in bytes; a typed array would give a scaled address.
- **Scope.** `reinterpret_cast` stays refused elsewhere; decisions 47 and 54 extend the list.

### 39. `BgmEvent::isInvalidRequestBgmFile`: single-use `eventName`

- **Rule.** Kept (P2).
- **Why.** The local holds `c_str()`, whose address the game computes before the other operand's: the instruction order is visible, not a register choice, and `c_str()` is a call in the source even when inlined.

### 40. `DrMdoGrpObj` constructor: one allocation carved into two arrays

- **Rule.** Kept: the constructor allocates one block and carves a list array and a pointer array from it with `static_cast<T **>(static_cast<void *>(unknown28 + count))`.
- **Why.** The game really carves one block; a cast through `void *` within one allocation is the original's own code, not steering.
- **Evidence.** 0x71007cf6b0.

### 41. `CharaEvaPlayer::setSpMotWeapon` defined `inline` under its real name

- **Rule.** Kept: the function is defined `inline` under its real name so that `CharaEvaPlayer::update` inlines it, and the standalone copy stays a target (listed by `check`).
- **Why.** The game inlines exactly this body into `update`; the standalone copy matches except one store order. A renamed helper would be less faithful.
- **Scope.** Not a licence to hide a function that does not match with `inline`, `static`, an anonymous namespace or a renamed copy. Such a device needs its own decision (see decision 51); a function that does not match is removed from the tree instead.

### 42. `DrEnvColiParameter::updateCloudParams`: loops or written out

- **Rule.** Everything is written out.
- **Why.** Runs of up to 14 elements also match as loops; longer runs only match written out. The long runs show that the original wrote one statement per parameter, and a function that mixes loops and written-out runs is less plausible than one consistent style.

### 43. rcha `setup` name tables and hidden visibility

- **Rule.** Refused: `__attribute__((visibility("hidden")))` on each name table. The seven rcha functions stay blocked.
- **Why.** The tables match only with the attribute, but a per-symbol attribute only steers code generation and nothing shows that the original had one. The library is not hidden as a whole.
- **Evidence.** The `CRchaEx` constructor reads its vtable through the GOT (0x710069eb34).
- **Scope.** Not a final refusal if evidence of the attribute appears.

### 44. `GfMenuObjHana::moveCharSubMenuIn`: `u32 move = 0;`

- **Rule.** Kept.
- **Why.** The initialiser is dead (every path assigns the variable), yet the game's `mov w0, wzr` is hoisted above the branch only with it when compiled with `-g` (238 against 240 instructions; no difference without `-g`). A default-valued local is ordinary code, and the debug-info effect shows that the original had it. A separate variable holding the argument `0` would invent a name.
- **Evidence.** Commit `cbb63953d`.

### 45. `ml::CacheDraw` primitive records

- **Rule.** `DRPNT`, `DRLINE`, `DRTRI`, `DRCUBE`, `DRARROW` and the others have members of type `mm::Vec3NA` and, in the `flush` functions only, `reinterpret_cast<const mm::Vec3 &>(member)` at the binding, with this evidence in a comment.
- **Why.** The records hold 12-byte vectors at 0xc, 0x18 and 0x24 (record sizes 0x18, 0x28... written by the `render*` constructors) and pass them by address, with no temporary, to functions whose mangled names take `const mm::Vec3 &`. The original necessarily converted a 12-byte field to the reference of the 16-byte type: no cast-free typing gives both the stride and the mangled parameter.
- **Scope.** Not a licence for other casts; the constructor copy form (64-bit plus 32-bit loads) is still open.
- **Evidence.** `DRCUBE::flush` 0x71007065c0: `add x8,x0,#0xc; add x2,x0,#0x18; b renderCube`; commit `8e052a399`.

### 46. A flat `f32[16]` view of `mm::Mat44`

- **Rule.** Refused. `DrPixlPostObjCubeMapIBL::getViewMatrixForFiltering` and the `CubeMapMultiIBL` one stay blocked.
- **Why.** The functions produce the game's 64-bit merged constant stores only through `f32 *m = &matrix.rows[0][0]; m[0..15]` (the natural `rows[r][c]` gives 74 instructions, the flat view 70). Walking past the first row is out of bounds, and nothing in the game's symbols shows a flat accessor, union or 16-float constructor on `mm::Mat44` (no `_ZN2mm5Mat44` get, set, data or `operator[]` symbol); a layout change on a shared math type needs such evidence.
- **Scope.** Revisit if a sibling build shows a flat member.
- **Evidence.** Commit `214ed626b`.

### 47. gmk `getBdatInfo()` accessors

- **Rule.** Accepted, as an extension of decision 38: about twenty gmk headers on `main`, and one more in `GmkNpcIdInfo`/`GmkEnemyInsts`, have one-line `getBdatInfo()` accessors that read the bound BDAT record through `reinterpret_cast`.
- **Why.** It is the same BDAT blob reading, at the gimmick's bound record.
- **Scope.** The accessor stays exactly the existing one-liner; no other cast is covered.
- **Evidence.** Commit `e10c5b530`.

### 48. Flag words read with byte loads: `mm::mtl::unknown027<32>`

- **Rule.** A flag or state word that the game reads with byte loads, and that clang widens to `ldr x` plus `lsr` when the member is typed `u32` (a 4-byte member at an 8-aligned offset, next to a member read right after it), is retyped to `mm::mtl::unknown027<32>`, the bit set of `include/mm_mtl/bitflag.h`; the enumerators become bit indices.
- **Why.** The bit set's align-4 `this` keeps the narrow load.
- **Scope.** Accepted when the siblings of the class use the same bit set at the same offsets (`BouManager` and `ManiManager` for `event::Manager`) or when the game's accesses are bit tests by index; the comment says which.
- **Evidence.** Commit `e10c5b530` (`event::Manager::end`, `stop`, `fw::FootPlacementIKSolver::getRaycastUp`).

### 49. The named sender local of the message senders

- **Rule.** `GfObj *obj = static_cast<GfObj *>(...); component->recieveMessage(obj, message)` is accepted.
- **Why.** In `WaterInPlugin::onEvent` the named local changes only the register allocation, but the same form is required in `GfComProperty::onDamage`, `onHeal` and `FootStepPlugin::emissionEffect` already on `main` (each fails without it in the same way). One consistent form in four game functions is a repeated source idiom of the message senders, unlike a one-off register steer.
- **Scope.** Not extended to unrelated single-use locals.
- **Evidence.** Commit `2b143a2a4`.

### 50. New enumerators of an enum whose own name is invented

- **Rule.** New enumerators keep the existing `unknownNNN_N` form (the enum `unknown027` of the dr files has 22 enumerators `unknown027_N` on `main`, about 35 uses).
- **Why.** Mixing two styles in one enum is worse, and the AGENTS.md `<PREFIX>_UNKNOWN_<N>` rule presupposes a prefix shared by named siblings, which such an enum does not have.
- **Scope.** A repository-wide normalisation is a separate cleanup commit.
- **Evidence.** Commit `53aada686`.

### 51. A declared, undefined specialisation of `gmk::isGmkValidViewUnbound<T>`

- **Rule.** Accepted as a temporary, commented device: `template <> bool isGmkValidViewUnbound<GmkRoutedEnemy>(const AGmkBase &);` is declared without a definition. It is removed as soon as the `GmkRoutedEnemy` instance matches.
- **Why.** One template body matches the `GmkEnemy`, `GmkMob` and `GmkRoutedMob` instances, but defining the template also emits the `GmkRoutedEnemy` instance (0x71005e0d5c), which does not match. The unmatched instance stays a target listed by `check` (nothing is hidden), and the three matched instances share the single original body.
- **Scope.** Not a licence for other templates, unless one shared body matches and the excluded instance stays listed.
- **Evidence.** Commit `3c1d94104`.

### 52. The `s64 / 1000` of the movie and ssd code

- **Rule.** Members of `nn::TimeSpan`: `unknown001` (microseconds), `unknown002` (milliseconds), a shared multiply `unknown003` if it matches for both. The comment gives the role, the forms tried and the addresses. Only matching users go in; no general divide helper elsewhere.
- **Why.** The movie and ssd code divides an `s64` by `1000` or `1000000`, which the game computes with a split 32-bit reciprocal multiply instead of `smulh`, always on the result of `nn::os::ConvertToTimeSpan`. nnheaders has no getters, so no SDK name may be used (AGENTS.md).
- **Scope.** `include/nn` is a reserved area: the members are written by its contributor, not as part of a match.
- **Evidence.** 11 XC2 sites; the same in Torna and XC1DE; about 44 sites in XC1DE's SDK module, where a plain `/1000` gives `smulh` too.

### 53. `FixedObjectAllocator<FileHandleTh, 640>::allocate`

- **Rule.** Refused; nothing lands. Reopen only with a natural form or a body seen in a sibling build.
- **Why.** The function is byte-identical only with the object addressed as a byte index into the storage (`reinterpret_cast<T *>(unknown00 + i * sizeof(T))`) and the loop bound read through a raw byte offset of `this` (`*reinterpret_cast<const u32 *>(reinterpret_cast<const u8 *>(this) + ...)`). The cause is the loop strength reduction register choice of clang 3.9. Raw byte offsets of `this` are forbidden (CONTRIBUTING.md), and the form is chosen for the register allocation, not shown by an access.
- **Evidence.** The byte-index storage access alone gives 112 instructions against 107.

### 54. Resource-blob casts in the dr resource parsers

- **Rule.** `reinterpret_cast<const T *>(data + offset)` on model and resource blobs is accepted, extending decision 38 to the dr resource blob parsers.
- **Why.** The symbols fix a `const u8 *` blob parameter and typed callees, so the original adds byte offsets to the blob and casts; no cast-free form exists.
- **Scope.** Only a resource blob plus a header offset read from that blob; `reinterpret_cast` stays refused everywhere else (no casts of `this`, no punning of game objects).
- **Evidence.** `DrResMdoSeamWrkPosMpf::setupInstMpf` (three `unknown08` assignments), outside the two files that decision 38 names. The same form is already on `main` in `DrResMdoSeamWrkMpf::changeMemCall`, `DrResMdoSeamWrkPosInst::changeMemEtcInstPos` and `DrMdoCtlMpfAuto::changeMemAutoMpf`. The same kind of blob read (a sprite resource read at byte offsets taken from its own header) is used by `minigame::tora::minigame::decode_4bpp_sprt(u32, int)` (`a6baa6c6e`).

### 55. The FixStr reverse search

- **Rule.** Accepted as a documented exception confined to one `FixStr` helper (`unknownNNN`, with a comment holding the evidence and the forms tried): a base computed through an integer round trip (`reinterpret_cast<const char *>(reinterpret_cast<size_t>(c_str()) - 1)`), with `c_str()` and `length()` accessors and a `do { } while (--i != 0)` loop behind `length() != 0`.
- **Why.** The inlined `FixStr` reverse search keeps `mData - 1` hoisted. Only that base reproduces it (loop strength reduction; about 600 natural forms were tried). The helper matches 17 functions byte for byte across four libraries and the search loops of nine more, with no contradicting case.
- **Scope.** Not a precedent: integer round trips stay refused everywhere else (decision 53). The nine `ui::UIUtil` users wait for the contributor of `ui`.
- **Evidence.** About 33 game functions: `PathUtil`, `GfMenuMapInfo`, `ui::UIUtil::make*FileName`, `normalizeFileName`, `makeFullPath`...; commit `1576fa595`.

### 56. Assert-free container templates for `skt`

- **Rule.** An assert-free copy of the needed container templates, local to `skt` (its own header under the skt area, used only by skt), with a comment citing the missing asserts in those game functions (addresses) as evidence.
- **Why.** `skt::CommandManager::create`, `recvBinary`, `recvCommand`, `updateCallback`, `removePort` and `PortInfo::destroy` use the `mm::mtl` container templates without the asserts that every other copy in the game has (the skt library was built against an older container version).
- **Scope.** Not shared with any other area: `include/mm_mtl` stays the single implementation elsewhere.
- **Form.** A header local to `skt` holds a `FixedVector` with the members skt uses, without the `push_back`, `erase` and `assign` asserts. The singleton is a full specialisation of `mm::mtl::PtrSingleton<skt::CommandManager>` without the `get() == 0` assert, in `include/skt/command_manager.h`, not a copy in another namespace: the game's symbols for the singleton (vtable, `sys()::s_instance`, destructors) are `mm::mtl::PtrSingleton<skt::CommandManager>`, which a separate namespace would rename. The members the copy calls keep their game symbols (`mm::mtl::copy`).
- **Evidence.** Matched: the `CommandManager` constructor, `create`, `recvCommand`, `recvBinary`, `updateCallback`, `PortInfo::destroy`. `removePort` matches only while `mm::mtl::copy<PortInfo>` is instantiated, and that function (84 instructions against 85, the loop exit test, like `copy<InputObj>`; see [lessons](lessons.md), "Loop strength reduction (LSR)") does not match, so both stay unwritten. `parseCommand` stays at 59 to 61 instructions against 72.

### 57. The party-map save helper (0x71003558e8) and its callers

- **Rule.** Accepted: the single-use locals `f32 driverDeg = rot * mm::RAD_TO_DEG; f32 bladeDeg = ...;`, both kept in the symmetrical form (the game cannot tell it from a blade-only one), with the evidence in a comment at the helper.
- **Why.** The helper (and with it `GfGameUtilSaveData::setupGameSaveData`, 476 instructions, and `getSaveData(SDataGame &)`) matches only with these locals. At first sight they only change register allocation, which P2 refuses (decision 9), but the IR and the register allocation are identical with and without the locals. Only `AArch64A57FPLoadBalancing` differs: under `-g` a named variable leaves a `DBG_VALUE` between the `fmul` and its store, so the chain keeps `s0` (the game has s0, s0, s1, s1, s0, s1). This is the same kind of evidence as decision 44 (a variable visible under `-g`), so P2 does not apply.
- **Scope.** These locals on that evidence; it does not make register-allocation-only locals acceptable in general.
- **Evidence.** An exhaustive search found no other form: 83 hand-written forms, two permuter runs (1311 candidates, 158 matching sources, all with a variable bound to the product) and about 170 more forms elsewhere. Commit `ade36824f`.

### 58. Members named after their game type

- **Rule.** A member with no accessor and no string naming it, whose type is a class or struct the game names and which is the only member of that type in its class, is `m_` plus the class name without namespace, without leading underscores (`m__x` has a double underscore, reserved by C++) and without a leading `SData` or `Gf` (before an upper-case letter, a digit or `_`), first letter lowercased unless the whole name is upper case (`SDataIdea` gives `m_idea`, `GfBladeCreateInfo` gives `m_bladeCreateInfo`, `IDColiTreeTop` gives `m_iDColiTreeTop`, `_wkSeamReadCall` gives `m_wkSeamReadCall`, `CS` gives `m_CS`, `GF_OBJ_HANDLE` gives `m_GF_OBJ_HANDLE`, like the uppercase prefix of the accessor rule). A game accessor or a string name comes first; `unknownXX` stays when neither applies and the type does not qualify. The text is in AGENTS.md.
- **Why.** The type name is a game name (it is in a mangled symbol of the game or of Torna or Xenoblade DE) and the derivation is written down, like the BDAT ids. Most members will never get an accessor or a string, so without the derivation they stay `unknownXX` while their type is known. The name is a derivation, not the original name.
- **Scope.** Excluded, the member stays `unknownXX`: template types and instantiations (`FixedVector<...>`, `IntrusivePtr<...>`, `PtrSingleton<...>`), the `mm` math types (`Vec3`, `Quat`, `Mat44`, `Col4`), the base and SDK types, types whose own name is inferred (`unknownNNN`; the class that declares the member may have an inferred name), and any class with two or more members of the same type (`T`, pointers and references to `T` of any depth, `const T`, a typedef of `T` and arrays of any of these count as one type, static data members included). Reserved areas are not renamed (P5); the proposals are reported to their contributor.
- **Evidence.** `SDataDriver::unknown00` and `SDataBlade::unknown0c` (now `m_idea`) are `SDataIdea`, the only member of that type in their class; the accessors `DataObjDriver::getIdea()` and `DataObjBlade::getIdea()` return their address, so the accessor rule gives `m_idea` first and the type rule gives the same name. 2183 members outside the reserved areas follow the type rule (commits `refactor(gf)`, `refactor(gmk)`, `refactor(event)`, `refactor(layer)`, `refactor(ml)`); a member of type `ml::_wkSeamReadCall` is `m_wkSeamReadCall`, not `m__wkSeamReadCall`.

### 59. Embedded public libraries: the library's own macros, attributes and gotos

- **Rule.** Where the game embeds a public third-party library and its functions only match with a construct of that library's own source, the construct is written as the library writes it, in that library's files only, and nowhere else:
  - utf8.h (public domain): `utf8_weak` (`__attribute__((weak))`) and `utf8_restrict` (`__restrict__`) in `include/utf8.h`; the repeated blocks of `src/libs/monolib_mm/source/util/utf8.cpp` (the library repeats its UTF-8 encoder in `utf8chr`, `utf8rchr` and `utf8catcodepoint`, its lower-casing test in three functions and its codepoint scan in `utf8cspn`, `utf8pbrk` and `utf8spn`).
  - FastLZ 0.1.0 (MIT licence): the `goto literal` and `goto match` statements of `util/fastlz_level.inl`, and the `FASTLZ_EXPECT_CONDITIONAL` and `FASTLZ_UNEXPECT_CONDITIONAL` macros (`__builtin_expect`, which the library enables for GNU C compilers) of `util/fastlz.cpp`.
  - zlib 1.2.8 (zlib licence): the gotos (`goto inf_leave`, `goto dolen`, `goto dodist`) and the repeated blocks of `zlib/inflate.cpp` and `zlib/inffast.cpp`.

  The names, macros and constants keep the library's own spelling, and each file starts with a provenance comment (project, licence, revision proven by the binary). `tools/quality_gate.py` exempts exactly these and no more: the `#define utf8_weak` line of `include/utf8.h` (`UTF8_WEAK`), the gotos of `util/fastlz_level.inl`, `zlib/inflate.cpp` and `zlib/inffast.cpp` (`EMBEDDED_GOTO`), and the duplicate-block rules for `zlib/inflate.cpp`, `zlib/inffast.cpp` and `util/utf8.cpp` (`EMBEDDED_DUPLICATES`). dlmalloc 2.8 keeps the exception it already has in CONTRIBUTING (the `volatile` store of `init_mparams`).
- **Why.** The binary contains the library as its authors wrote it, so the library's own constructs are original source, not constructs added to steer the compiler, like the `volatile` store of dlmalloc's `init_mparams` (CONTRIBUTING). Nothing else of these files is exempt, and no other file may use them: the same `goto` or macro in a game function stays refused.
- **Scope.** Only the libraries above and only the constructs their public source contains. A new library, or a construct the library's source does not have, needs its own decision.
- **Evidence.** utf8.h (early 2017 revision, 26 functions at 0x7100758bd4-0x71007597e8): without `utf8_weak` clang inlines `utf8str` into `utf8chr` and `utf8size` into `utf8dup` where the game calls them (weak definitions are not inlined); with it all 26 functions match, and `utf8ncat` and `utf8ncpy` only get the game's load and store order with `utf8_restrict` on destination and source. FastLZ (0.1.0, the library's fastlz.c of 19 June 2007; `fastlz_compress`, `fastlz1_compress` 270 instructions, `fastlz2_compress` 355, `fastlz_decompress` 366 with both decompressors inlined, `fastlz_compress_level`): the blocks of `fastlz_decompress` are laid out as in the game only with `__builtin_expect` in the library's two macros (363 instructions and a different order without). zlib 1.2.8 (Nintendo SDK build, `zlibVersion()` returns `1.2.8.f-NINTENDO-SDK-v1`; 31 functions and 2 local statics at 0x71009a5e4c-0x71009a9cb8, one root source per C file because the game links one object per C file): all match written as the library's own source, with the tables byte for byte.

### Everything else

Paragraphs of the first review that rulings 1 to 9 already answer (`seqWaitTalkEnd`, `loadStart`, `GfComBehaviorMob`, `initMpfMapParts`, `readMpfModelCheck`, `playAuto`, `VoicePlayer`, `EffectLodManager`, `WorldMap` destructor and `getFloor`, `HanaParts`, `setupAddBooster`, `LinkJump`, three `initialize`, `EvTheater`, `ProcException::wkRender`, `createLookIK`, `shadowRender`, `DrMdoNomAfterImage`, `ItemList2`, `MissionList`, `gevChangeScenarioFlag`, `LvUp`, `Launch`...) follow those rulings: restore any that is not on `main` yet.

## Open requests for reserved areas

Changes that no decision above makes and that wait for the contributor of the area. None blocks a match outside the reserved areas.

- `anm::JobQueue::getJobCount()` (decision 22).
- `DevPadNx` in `include/nn/hid.h` and `EventData::unknown0c_f32` (decision 37).
- `nn::TimeSpan` members for the reciprocal-multiply divisions (decision 52).
- `ui::UIUtil::make*FileName`: nine functions that match with the helper of decision 55 and wait for the contributor of `ui`.
- `wnd::GlobalWind::update`: `WindWorld::updateGlobalWind` (0x710098a710) repeats `GlobalWind::update` (0x7100988d40). Defining `update` in the class body of `wnd_wind.h` (the game emits it with the vtable, with no direct call) and calling it makes both match (26 and 29 instructions).
- `ui::EventData()` zeroing order: the game zeroes the members in descending order (`unknown14`, `unknown10`, `unknown0c`, `unknown08`, `unknown00`); `GfMenuObjDropItem::open` matches fully with a constructor that assigns in that order.
- `eflib` `SendParam` constructor: the game's inlined constructor stores `unknowna3 = 1` after `unknowna2 = 0` (seen in `GmkJump`, `GmkCollection` and `GmkWarp` `validateIconPos`, 0x7100613680, 0x7100608108, 0x71006148a0). Moving the assignment in `include/eflib/effect_send_param.h` fixes that part of those functions.
- `ui::UIListInfoBase::getSize` signedness: the game compares the event index with the list size as signed integers (`GfMenuObjMercenaryForm::UnitListener::reciveEvent`, `cmp w20, w0; b.ge` at 0x7100492a54 and 0x7100492aec), while the reserved header declares `u32`. The matching form casts it, and the same cast is already used in `GfMenuCharDataAdapter`, `GfMenuArtsAdapter`, `GfMenuFieldSkillAdapter::ListConverter::getFieldSkill`, `GfMenuObjBladeCreate`, `GfMenuObjCommonJog`, `GfMenuObjInn` and `GfMenuObjOption`. By P1 the likely cause is the return type of `getSize`; the question is whether it is `int`.
- A `void *` or typed view of `EventData`'s 0x08 slot would remove the `reinterpret_cast` of `event.unknown08_u64` in `GfMenuObjBalloon::SelMoneyListener::reciveEvent` (commit `7106fde12`) and `GfMenuObjQuestReward::RewardListener::reciveEvent`. Low priority.
