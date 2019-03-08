[Goback to Readme](./readme.md)

## Computer Architecture


### RISC vs CISC
- RISC(reduced instruction set)
  - it want to execture a simple instructions in a single cpu clock cycle
  - its code size is usually large

- CISC
  - it want to use instruction as few as possible to accomplish complex task
  - its code size is uaually small.
  - A instruction will go through several clock cycles

### Pipeline

5 Stages Pipeline:
- Fetch
- Decode
- Execute
- Memory Operation
- WriteBack

R10K Pipeline Stages:
- Fetch
- Dispatch
- Issue (Issue the instructions to functional unit and execute)
- Execute 
- Complete
- Retire 


### Hazards

- Control hanzard and data hanzard
- 