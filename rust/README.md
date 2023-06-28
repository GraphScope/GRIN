# Rust Codegen

## For Rust Users
1. Install bindgen and enter the rust folder in GRIN repo
2. Run codegen with storages specified, e.g., `python codegen.py v6d gart`
3. Use `Cargo.toml` and `grin.rs` in your rust project

## For Storage Implementors
1. Create a header file `grin_{storage}.h` in the rust folder.
2. Put your null value definitions as comments in the header file.
3. Use header files from other storages as references.
