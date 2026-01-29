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
- Debug and programming interfaces allow invasive control
- Need device-local authorization before execution/debug

## Slide 4 - Problem Statement
- Debug/program access can be enabled without on-device checks
- Key material may be exposed via normal memory paths
- Host-side policies can be bypassed after reflashing
- Authorization must be bound to a device-visible execution point
- Goal: enforce authorization inside the device execution model

## Slide 5 - Objectives
- Add a minimal ISA extension (kc) for authorization
- Store keys in protected NVM (not memory-mapped)
- Enforce fail-stop FSM gating of execution/debug
- Integrate into compiler/toolchain for enforceability
- Maintain compatibility with standard build workflows

## Slide 6 - Key Contributions
- ISA-level authorization trigger (kc)
- Protected key storage + constant-time comparator
- Security FSM: LOCKED -> VERIFY -> AUTHORIZED / HALT
- Toolchain + host workflow integration
- End-to-end prototype with evidence artifacts

## Slide 7 - System Overview (Concept)
- Host toolchain + UART protocol
- Device security logic (protected NVM + comparator + FSM)
- Debug and execution gated on-device
- Host database and audit logs for traceability
- [Insert architecture overview figure: figures/fig_arch_flow.png]

## Slide 8 - Authorization Flow (Diagram)
- Start sequence
- Key fragment checks
- kc event verifies token
- AUTHORIZED enables execution/debug
- HALT on mismatch
- Match output drives FSM transition
- [Insert flowchart diagram from Chapter 4]

## Slide 9 - Methodology Summary
- Key derivation: host + device identifiers + nonce
- UART message sequence: Start -> Key-1..Key-3 -> Enable -> End
- kc instruction binds authorization to execution context
- Fail-stop on any mismatch
- Reference key stored in protected NVM

## Slide 10 - Implementation: ISA and Toolchain
- kc opcode recognized in decode stage
- Preserved through compile -> link -> ELF->HEX
- Disassembly shows kc for audit
- BootROM places kc early in boot
- Assembler and disassembler updated for opcode

## Slide 11 - Implementation: Device Logic
- Protected NVM (not in load/store path)
- Constant-time comparator (no key leakage)
- FSM drives exec_enable, debug_enable, halt_cpu
- Only a match bit is exposed to control logic

## Slide 12 - Host Workflow
- Compile and inspect HEX
- Send authorization sequence via UART
- Enable programming only after match
- Logs: device ID, toolchain version, match result
- Audit log supports traceability and accountability

## Slide 13 - Experimental Setup
- Customized toolchain
- Host application for compile/authorize/program
- Device with protected key + FSM
- Evidence from logs and screenshots
- Functional validation (not micro-architectural benchmarks)

## Slide 14 - Results: Toolchain Validation
- kc present in build artifacts
- Successful ELF->HEX generation
- C/assembly invocation preserved in output
- [Insert screenshot: figures/fig_compile.png]

## Slide 15 - Results: Firmware Inspection
- Hex viewer confirms expected image contents
- Operator can verify kc location
- [Insert screenshot: figures/fig_hex.png]

## Slide 16 - Results: Authorization and Debug Enable
- Key match required before debug enable
- Debug gate released only after match
- [Insert screenshots: figures/fig_keymatch.png, figures/fig_debugenabled.png]

## Slide 17 - Results: Fail-Stop on Mismatch
- Invalid key triggers HALT
- Device remains halted until reset
- Prevents iterative probing in one session
- [Insert screenshot: figures/fig_halted.png]

## Slide 18 - Results: Programming Workflow
- Device connection and image load under authorization
- Programming occurs only after authorization
- [Insert screenshots: figures/fig_connected.png, figures/fig_loadimage.png]

## Slide 19 - Results Summary
- kc preserved in binaries
- Authorization required before debug
- Programming occurs only after authorization
- Fail-stop behavior verified
- Evidence supports device-local enforcement

## Slide 20 - Conclusion
- Device-local authorization closes post-boot gap
- Minimal ISA extension + protected storage is practical
- Toolchain integration enables auditability
- Enforcement is device-resident and deterministic

## Slide 21 - Future Work
- Measure area/power/latency overheads
- Key rotation and revocation policies
- Stronger fault/side-channel evaluation
- Larger-scale deployment studies
- Formal verification of FSM and toolchain tests

## Slide 22 - Q and A
- Thank you
