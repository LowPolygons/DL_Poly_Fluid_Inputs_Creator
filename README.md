# Inputs For Fluids
This read me is a constant WIP, and serves more as a guide for both users and developer(s)

## [USERS] 
### USE 
There are key things to consider before creating a fluid:
- The different molecules in the fluids
- The concentrations of each molecule in the fluid

These will be randomly (uniform) distributed among the solution area

To create a Molecule, navigate to the `parameters/molecules` and create the necessary molecules. Examples are provided 
For more general control over the inputs, navigate to `parameters` and modify the Inputs header to suit your needs

## [DEVS] 
### TODO
- Redo the file structure to be more generalised
- Resolve Inline TODOs (colon, space, f, w, to grep search in nvim)

### Naming Conventions

Variables: standardCamelCase

Classes: FullCamelCase

File Names: 
    -> Class related: FullCamelCase
    -> other: standardCamelCase

Enums: CAPSLOCK_SNAKE_CASE

Structs: FullCamelCase

Methods: standardCamelCase
    -> Getters: FullCamelCase, match variable name, in implementation file, try make a getter be all on one line, at the top
