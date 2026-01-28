# Defense Presentation Outline (Copy into PPT/Word)

## Slide 1 - Title
- Title: Device-Local Authorization for Secure Execution and Debug in Embedded Systems
- Student: [Your Name]
- Supervisor: [Supervisor Name]
- Department / University
- Date

## Slide 2 - Agenda
- Motivation and problem
- Objectives and contributions
- Methodology (system model and protocol)
- Implementation
- Experiments and results
- Conclusion and future work

## Slide 3 - Motivation
- Embedded devices face physical-access threats
- Secure boot protects only the initial image
- Post-boot debug/programming remains exposed
- Need device-local authorization before execution/debug

## Slide 4 - Problem Statement
- Debug/program access can be enabled without on-device checks
- Key material may be exposed via normal memory paths
- Host-side policies can be bypassed after reflashing
- Goal: enforce authorization inside the device execution model

## Slide 5 - Objectives
- Add a minimal ISA extension (kc) for authorization
- Store keys in protected NVM (not memory-mapped)
- Enforce fail-stop FSM gating of execution/debug
- Integrate into compiler/toolchain for enforceability

## Slide 6 - Key Contributions
- ISA-level authorization trigger (kc)
- Protected key storage + constant-time comparator
- Security FSM: LOCKED -> VERIFY -> AUTHORIZED / HALT
- Toolchain + host workflow integration

## Slide 7 - System Overview (Concept)
- Host toolchain + UART protocol
- Device security logic (protected NVM + comparator + FSM)
- Debug and execution gated on-device
- [Insert architecture overview figure: figures/fig_arch_flow.png]

## Slide 8 - Authorization Flow (Diagram)
- Start sequence
- Key fragment checks
- kc event verifies token
- AUTHORIZED enables execution/debug
- HALT on mismatch
- [Insert flowchart diagram from Chapter 4]

## Slide 9 - Methodology Summary
- Key derivation: host + device identifiers + nonce
- UART message sequence: Start -> Key-1..Key-3 -> Enable -> End
- kc instruction binds authorization to execution context
- Fail-stop on any mismatch

## Slide 10 - Implementation: ISA and Toolchain
- kc opcode recognized in decode stage
- Preserved through compile -> link -> ELF->HEX
- Disassembly shows kc for audit
- BootROM places kc early in boot

## Slide 11 - Implementation: Device Logic
- Protected NVM (not in load/store path)
- Constant-time comparator (no key leakage)
- FSM drives exec_enable, debug_enable, halt_cpu

## Slide 12 - Host Workflow
- Compile and inspect HEX
- Send authorization sequence via UART
- Enable programming only after match
- Logs: device ID, toolchain version, match result

## Slide 13 - Experimental Setup
- Customized toolchain
- Host application for compile/authorize/program
- Device with protected key + FSM
- Evidence from logs and screenshots

## Slide 14 - Results: Toolchain Validation
- kc present in build artifacts
- Successful ELF->HEX generation
- [Insert screenshot: figures/fig_compile.png]

## Slide 15 - Results: Firmware Inspection
- Hex viewer confirms expected image contents
- [Insert screenshot: figures/fig_hex.png]

## Slide 16 - Results: Authorization and Debug Enable
- Key match required before debug enable
- [Insert screenshots: figures/fig_keymatch.png, figures/fig_debugenabled.png]

## Slide 17 - Results: Fail-Stop on Mismatch
- Invalid key triggers HALT
- Device remains halted until reset
- [Insert screenshot: figures/fig_halted.png]

## Slide 18 - Results: Programming Workflow
- Device connection and image load under authorization
- [Insert screenshots: figures/fig_connected.png, figures/fig_loadimage.png]

## Slide 19 - Results Summary
- kc preserved in binaries
- Authorization required before debug
- Programming occurs only after authorization
- Fail-stop behavior verified

## Slide 20 - Conclusion
- Device-local authorization closes post-boot gap
- Minimal ISA extension + protected storage is practical
- Toolchain integration enables auditability

## Slide 21 - Future Work
- Measure area/power/latency overheads
- Key rotation and revocation policies
- Stronger fault/side-channel evaluation
- Larger-scale deployment studies

## Slide 22 - Q and A
- Thank you
