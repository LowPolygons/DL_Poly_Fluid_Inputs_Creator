#ifndef INPUT_VERIFIER

#define INPUT_VERIFIER

#include "../../parameters/Inputs.h"

class InputVerifier {
  public:
    InputVerifier(ConfigInputs _inputs) {
      inputs = _inputs;
    }
    //Overseeing the validation; this will do the error handling
    auto ConductValidation() -> void;

    //Molecule Validator stuff
    auto ValidateMolecule() -> bool;
    //Confirm that the vectors aren't parallel
    auto ValidateVectors() -> bool;
    //validate that only one type of bounding validation is present
    auto ValidateBounding() -> bool;
  private:
    ConfigInputs inputs;
};

#endif
