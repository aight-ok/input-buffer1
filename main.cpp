#include <Geode/Geode.hpp>
#include "InputBufferCore.hpp"

using namespace geode::prelude;

// v0.2.0 intentionally contains no gameplay hook yet. The iOS 2.208
// PlayerObject/GameManager signatures and safe-state checks must be verified
// against the exact Geode 5.11.2 bindings before forwarding real inputs.
$on_mod(Loaded) {
    log::info("[Input Buffer] v0.2.0 loaded; gameplay buffering is not enabled yet.");
}

$on_mod(Enable) {
    log::info("[Input Buffer] Enabled (core only; no inputs intercepted).");
}
