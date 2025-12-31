## Results and Evaluation (Editable Draft)

This is a markdown version of the Results section you can edit quickly, then port to LaTeX/IEEE if needed. Figure filenames refer to the extracted images in `../figures/`.

### Evidence Artifacts and Experimental Workflow
Evaluation is presented at two levels:
- **Toolchain-level validation**: custom instruction support through compile/assemble/link and ELF→HEX generation.
- **System-level validation**: execution + debug are gated by authorization; failure triggers a fail-stop halt.

### Toolchain Validation
- Evidence: `../figures/compiler_design__image11.PNG`  
  Shows a test program invoking the custom instruction via inline assembly and the console reporting:
  - “Compilation successful!”
  - “Generate hex from elf successful!”

### Firmware Inspection (HEX Viewer)
- Evidence: `../figures/compiler_design__image12.png`  
  Shows the hex viewer output for the generated image.

### Authorization and Debug Enablement (Key Match)
- Evidence (key exchange/match): `../figures/compiler_design__image13.png`  
  Shows log lines indicating successful key reception and “Same key received successfully!”
- Evidence (debug enabled after match): `../figures/compiler_design__image14.PNG`  
  Shows the “Debugger is enabled now.” message, consistent with debug gating on successful match.

### Connection and Programming Workflow
- Evidence (connected state): `../figures/compiler_design__image17.PNG`  
  Shows “Connected Successfully!” in the UI.
- Evidence (programming log): `../figures/compiler_design__image18.PNG`  
  Shows a `load_image ... firmware.elf` entry and subsequent programming interactions.

### Fail-Stop Enforcement (Halt-on-Failure)
- Evidence: `../figures/compiler_design__image16.png`  
  Shows “Processor Halted,” consistent with halt-on-failure policy.

### Summary Table
| Requirement | Evidence |
|---|---|
| Custom instruction compiles/emits | `compiler_design__image11.PNG` |
| ELF→HEX generation succeeds | `compiler_design__image11.PNG` |
| Hex inspection supported | `compiler_design__image12.png` |
| Key exchange/match visible | `compiler_design__image13.png` |
| Debug enabled only after match | `compiler_design__image14.PNG` |
| Device connection workflow supported | `compiler_design__image17.PNG` |
| Programming log shows image load | `compiler_design__image18.PNG` |
| Halt-on-failure evidence | `compiler_design__image16.png` |

