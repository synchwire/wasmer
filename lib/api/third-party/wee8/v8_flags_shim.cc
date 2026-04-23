// Minimal shim over v8::V8::SetFlagsFromString. This file is compiled
// and linked only when the `v8` feature is enabled.
//
// The wasm-c-api surface that wasmer links against (`wasm_engine_new`,
// `wasm_module_new`, ...) does not expose V8 command-line flags.
// V8 requires flags to be set before any engine is constructed
// because V8::Initialize — which runs the first time wasm_engine_new
// is called — freezes most flag values. This shim gives the embedder
// a C entry point to push flags through.
//
// Typical use case: iOS builds must initialize with "--jitless" so
// V8 never requests RWX pages (Apple does not grant the JIT
// entitlement to non-browser apps). The shim is generic, though —
// any documented V8 flag string is accepted.

#include <cstddef>
// Use the umbrella header so this compiles against both the old wee8
// 11.8 archive (monolithic v8.h) and the newer 13.x archives where
// v8::V8 lives in v8-initialization.h.
#include "v8.h"

extern "C" void wasmer_v8_set_flags_from_string(const char* flags,
                                                std::size_t len) {
  v8::V8::SetFlagsFromString(flags, len);
}
