#!/bin/sh
clang \
    -Ofast \
    -flto \
    -Wl,--lto-O3 \
    -nostdlib \
    -Wl,--no-entry \
    -Wl,--export-all \
    -Wl,--allow-undefined \
    --target=wasm32-unknown-unknown-wasm \
    -o game.wasm \
    game.c
