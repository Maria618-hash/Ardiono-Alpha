## Discussion (Editable Draft)

### Security implications of key-gated execution and debug
The results support an end-to-end workflow where **both normal execution and debug capability** are released only after a successful authorization event (key match). This directly targets a common embedded risk: once an attacker can reflash firmware or enable invasive debugging, higher-level checks can often be bypassed. Keeping the reference key in protected non-volatile storage that is **not exposed on the normal system bus** reduces the chance that untrusted firmware can read/exfiltrate the key via standard load/store operations.

### Fail-stop policy trade-offs (halt on failure)
The selected policy is **fail-stop**: on authorization failure the processor halts, and both execution and debug remain disabled. This improves security by preventing repeated online attempts within a single boot session and by avoiding ambiguous “partially enabled” states. The cost is availability: provisioning mistakes or benign communication faults can halt the device until reset and correct authorization are provided. In practice this motivates careful provisioning and recovery procedures.

### Toolchain as part of the trusted computing base
Because the authorization primitive is integrated into the compilation workflow (rather than applied via post-build patching), it is easier to deploy consistently and to audit. However, it also expands the trusted computing base to include toolchain and host workflow aspects: build provenance and tool distribution become security-relevant.

### Operational considerations: provisioning, binding, and auditability
Security relies on correct provisioning of the reference key (or derived verifier) and a consistent host-to-key binding policy. Centralized binding records and “last log entry” tracking improve accountability and incident investigation. For production use, the model should be paired with lifecycle policy: enrollment, rotation, revocation, and administrative processes for compromised hosts.

### Scope and assumptions
This architecture mitigates unauthorized programming and debug activation under physical-access threat models, assuming the protected key storage and compare path are not software-readable. It raises the cost of reflashing and invasive debugging by enforcing device-side authorization gates, but does not claim to prevent all advanced physical attacks.

---

## Future Work (Editable Draft)

### Key lifecycle management (rotation and revocation)
Add support for key rotation and host revocation. Real deployments must handle compromised hosts and expired credentials.

### Stronger cryptographic binding and attestation
Adopt a standard challenge–response protocol and bind authorization to device-unique identity. Add optional remote attestation to report measured boot state and firmware identity to a verifier.

### Hardening against replay and online guessing
In addition to fail-stop, incorporate monotonic counters, backoff timers, and attempt-limiting stored in protected state to resist repeated reset-based guessing. Use nonces/challenges to prevent replay.

### Formal verification of the Authenticator FSM
Formally verify that unauthorized paths cannot assert `exec_enable` or `debug_enable` and that failure always leads to the HALT state.

### Micro-architectural evaluation and overhead measurement
Quantify performance/area/power impact of the custom instruction and compare datapath; measure worst-case verification latency and boot-time overhead.

### Broader policy controls beyond debug
Extend the same authorization primitive to gate additional sensitive operations (firmware update mode, privileged peripherals, secure memory regions) using the same hardware substrate.

