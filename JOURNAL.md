# Development Journal (Strive RISC-V / Arduino Toolchain)
**Date:** 2025-12-29  
**Author:** (your name)  
**Project/Module:** Compiler + SDK setup (Strive Series / RISC‑V)

## Objective
Set up and validate a working development environment for Strive Series RISC‑V boards, including:
- A RISC‑V compilation toolchain (GCC/binutils)
- A debugging/programming toolchain (OpenOCD + GDB workflow)
- Board support package (BSP) + example programs (build + upload/debug targets)

## Background / Context
This repository contains an Arduino-style package tree under `Arduino15/` (similar to what the Arduino IDE uses). Within it, the Strive platform provides:
- Hardware core + libraries (e.g., CAN library docs and examples)
- A Strive SDK (`strive-sdk`) with a Makefile-driven workflow for building, flashing, and debugging
- A bundled RISC‑V GCC toolchain and related utilities

## What is in the repo (evidence)
- **SDK README:** `Arduino15/packages/strive/hardware/riscv/1.0.0/strive-sdk/README.md`  
  Describes the SDK contents and mentions benchmarking targets (Dhrystone/CoreMark).
- **SDK build/debug automation:** `Arduino15/packages/strive/hardware/riscv/1.0.0/strive-sdk/Makefile`  
  Provides targets such as `tools`, `software`, `upload`, and debug helpers.
- **Toolchain already present:** `Arduino15/packages/strive/tools/riscv32-unknown-elf-gcc/1.0.0/...`  
  Indicates a prepackaged cross toolchain is tracked in git (the “compiler”).

## Work performed today
### 1) Reviewed SDK workflow
The `strive-sdk/Makefile` defines a standard flow:
- **Install tools:** `make tools` (build/install compiler + OpenOCD into a local `toolchain/` directory)
- **Build software:** `make software PROGRAM=<name> BOARD=<board>`
- **Flash:** `make upload PROGRAM=<name> BOARD=<board>`
- **Debug:** `make run_debug` (OpenOCD + GDB)

Key defaults noted in the Makefile:
- `DEFAULT_BOARD := freedom-e300-hifive1`
- `DEFAULT_PROGRAM := demo_gpio`

Captured Makefile help output (for traceability):

```text
tools:
  Install compilation & debugging tools.

software [PROGRAM=demo_gpio BOARD=freedom-e300-hifive1]:
  Build a software program to load with the debugger.

upload [PROGRAM=demo_gpio BOARD=freedom-e300-hifive1]:
  Launch OpenOCD to flash your program to the on-board Flash.

run_debug [PROGRAM=demo_gpio BOARD=freedom-e300-hifive1]:
  Launch OpenOCD & GDB to load or debug running programs.

run_openocd [BOARD=freedom-e300-hifive1]:
run_gdb     [PROGRAM=demo_gpio BOARD=freedom-e300-hifive1]:

dasm:
  Generates disassembly output via objdump.
```

### 2) Confirmed toolchain/debug artifacts are tracked
The repo tracks a large `Arduino15/` subtree including `riscv32-unknown-elf-gcc` and OpenOCD-related content, which supports local builds without separately installing a compiler on the host machine.

## Observations
- The SDK README lists required Ubuntu packages for building the toolchain from source; however, this repo also contains a prepackaged toolchain under `Arduino15/packages/strive/tools/...`, which may reduce setup time if it’s used directly.
- The Makefile includes a `dasm` target that runs `objdump -D` on the compiled ELF; this is useful for verifying code generation and for documentation.

## Issues / Risks
- The `Arduino15/` tree is very large; committing toolchains can make cloning and CI slower. If this is for coursework, it may be acceptable; for long-term development, consider tracking only source + scripts and downloading toolchains during setup.
- The SDK README in this repo appears partially incomplete (some command blocks are blank), so the Makefile is the most reliable “source of truth” for actual commands/targets.

## Next steps
- Run the SDK help and a dry-run build:
  - `make -C Arduino15/packages/strive/hardware/riscv/1.0.0/strive-sdk help`
  - `make -C Arduino15/packages/strive/hardware/riscv/1.0.0/strive-sdk software PROGRAM=demo_gpio BOARD=freedom-e300-hifive1`
- If hardware is available: attempt `upload` and/or `run_debug` and capture screenshots/logs for the journal.
- Incorporate PPT requirements (format, rubric, screenshots, expected sections) once the PPT is provided.

## References
- `Arduino15/packages/strive/hardware/riscv/1.0.0/strive-sdk/README.md`
- `Arduino15/packages/strive/hardware/riscv/1.0.0/strive-sdk/Makefile`

