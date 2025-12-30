# Development Journal — STRIVE Compiler Binding
**Date:** 2025-12-29  
**Author:** (your name)  
**Topic:** STRIVE compiler binding (PC ↔ microcontroller) using key verification + custom RISC‑V instruction + custom compiler

## Objective (from PPT)
Bind a specific PC to a microcontroller such that **only a registered user** is able to **program** it.

## Justification / Threat model (from PPT)
If an attacker erases the existing firmware on a PCB and installs malicious firmware, it can compromise the mission and it may be hard to attribute who programmed the device.

**Proposed mitigation:** introduce a mechanism so the microcontroller will not execute (and/or will not enable debug/programming) unless the firmware was compiled/authorized by **our own secure compiler**.

## Proposed solution overview (from PPT)
### Novel key sharing mechanism
- **Debug unit accessibility is controlled via key verification**
- **Processor is locked to a specific PC** for execution/programming
- **Unauthorized code execution is blocked** using a **custom instruction**
- This is supported end-to-end by a **NECOP Secure Compiler** (compiler/toolchain changes)

## Architecture notes (from PPT)
- The flash memory that stores keys is **not connected to the system bus**.
- Keys are accessible only through a **compare unit** triggered by a **custom instruction**.
- Debug is enabled only if the **Authenticator** allows it.
- The Authenticator needs the **last key** in order to access the flash memory.

## Compiler binding flow (from PPT)
High-level intent captured from the slides:
- A custom key is stored/managed in flash (via the secure mechanism).
- A custom instruction embeds or checks an **immediate value (imm)** and participates in the compare/authentication path.
- A key such as **Key‑1 / Key‑2 / Key‑3** is used in a staged/sequence manner (slides show a “Start → Key‑2 → Key‑3 → Enable → End” style flow).

*(Note: the PPT is diagram-based here; once you tell me your exact state machine/sequence, I can rewrite this section with precise steps.)*

## Key binding (from PPT)
### Key generation
- A **26‑bit** key is generated dynamically.
- Components mentioned: **Timestamp**, **Machine ID**, **UUID**, **Random selection**.

### Database management
- A **centralized database** stores key bindings.
- Purpose: enable tracking of secure execution and maintain integrity.

### Log tracking
- The system can retrieve the **last log entry** for security/auditing purposes.

## Custom RISC‑V instruction (from PPT)
### Instruction details
`kc` is added as a **first-class instruction** in the RISC‑V ISA so it can be used from C/assembly and supported by **GCC + binutils**.

From the PPT table:
- **Name**: `kc`
- **Syntax**: `kc rd imm20`
- **Format**: I‑Type
- **Encoding**: `imm[20 bits]`, `rd[5]` (as shown in slides)

## Toolchain work (from PPT)
### Testing custom GCC
- Windows executable screenshot (PPT) indicates a built/custom compiler tool was produced.
- “Addition of instruction” slide indicates `kc` support was validated at the tool level.

### Testing code with custom GCC
- PPT includes a slide showing code/output validation with the custom GCC.

## GUI / Application (from PPT)
The PPT shows a GUI and lists application workflow screens:
- **Application features** (overview)
- **Code compiling**
- **Hex viewer**
- **Key matching**
- **Updated hex**
- **Connect button**
- **Program button**

## Current repo evidence (local workspace)
In this workspace, the tracked tree includes a RISC‑V SDK and toolchain artifacts under `Arduino15/`, including `riscv32-unknown-elf-gcc` content and a Makefile-driven build/debug workflow in `strive-sdk`.

## References
- PPT source: `compiler_design.pptx` from repo `Maria618-hash/compiler`

