## Discussion (Editable Draft)

### Interpretation of results
The collected evidence supports three core properties of the design:  
1) the authorization primitive is supported end-to-end by the build pipeline (compile/link/image generation),  
2) debug enablement is released only after an explicit authorization event (key match), and  
3) the failure policy is fail-stop (halt-on-failure), keeping both execution and debug disabled.

### Security rationale and expected resistance
The architecture targets unauthorized reflashing and invasive debugging under physical access. Storing the reference key in protected non-volatile storage that is not exposed through the normal system bus reduces the feasibility of key extraction via ordinary load/store operations. Expressing authorization as an ISA-visible trigger also improves auditability: the authorization event can be located in compiled artifacts and integrated into reproducible engineering workflows.

### Fail-stop enforcement (halt-on-failure)
The halt-on-failure policy provides a conservative security posture. It prevents the system from progressing into partially initialized states after failed authorization and reduces opportunities for iterative probing within a single boot session. It also simplifies system reasoning by making the failure state absorbing until reset.

### Trusted computing base considerations
Because the authorization trigger is emitted by the toolchain, the toolchain and programming workflow become security-relevant artifacts. In practice, this motivates controlled toolchain distribution and recording build provenance (toolchain version, policy) as part of the audit trail.

### Operationalization: provisioning and policy
Security depends on correct provisioning of the reference key (or derived verifier) into protected storage and consistent host-side binding policy. Centralized binding records and log tracking support accountability and incident investigation. For non-laboratory deployment, the binding model must be paired with explicit lifecycle procedures (enrollment, administrative recovery, decommissioning).

---

## Future Work (Editable Draft)

### Cryptographic protocol refinement
Formalize the authorization exchange as a nonce-based challenge–response protocol and bind authorization tokens to device-unique identity to strengthen replay resistance and interoperability with established attestation/secure-boot ecosystems.

### Key lifecycle management
Add key rotation and endpoint revocation (epochs, revocation lists, recovery procedures) to handle host compromise and credential expiration.

### Anti-replay and attempt limiting across resets
Persist attempt counters in protected state, apply exponential backoff, and require fresh device nonces to raise the cost of reset-based brute force and replay.

### Formal methods and assurance
Apply formal verification to the Authenticator FSM to prove that unauthorized paths never assert `exec_enable` or `debug_enable`, and that failure states are absorbing under the specified policy.

### Overhead characterization
Quantify verification latency (boot-time impact), hardware area/power of the compare path, and any code-size impact introduced by toolchain integration.

### Policy generalization
Extend the authorization primitive to gate additional privileged operations (firmware update mode, privileged peripheral configuration, secure memory access), generalizing the mechanism into a platform authorization framework.

