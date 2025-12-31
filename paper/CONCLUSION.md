## Conclusion (Editable Draft)

This work presented a hardware–software co-designed approach for securing embedded programming and execution under physical-access threat models. The architecture gates **both normal execution and debug access** on a device-resident authorization decision, using protected key storage and a verification datapath that is not exposed through ordinary memory transactions. Authorization is invoked through an ISA-visible primitive that is integrated into the toolchain, enabling reproducible builds and inspectable binaries.

The evaluation demonstrated end-to-end feasibility using collected evidence: successful compilation and image generation with the custom instruction, key match evidence preceding debug enablement, an operational host workflow supporting compilation/inspection/connection/programming, and fail-stop behavior consistent with a **halt-on-failure** policy when authorization is not satisfied. These results indicate that instruction-triggered, key-gated control is a practical foundation for restricting unauthorized reflashing and invasive debugging in embedded systems.

