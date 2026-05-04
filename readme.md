# Project to apply on MIT, Ternary Virtualization Machine

# readme in construcion...

- this project is in early stages of development. 

# how to run
- clone the project and navigate to ternary_os/ directory
- run `make` in ternary_os/ to build the project

# how to test assembler and VM
- create a test file with .w extension, example in [docs/](./docs/code_example.md)
- after create a file with .w extension, run `assembler.exe <input_file.w> <output_file.bin>` to assemble the code
- then run `ternary_os <output_file.bin>` to execute the code in the virtual machine