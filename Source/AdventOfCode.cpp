
#include "Generated/GeneratedDefinitions.h"

// EDIT HERE! These lines will change what is executed
#define CHALLENGE_TYPE CChallenge_N
#define IS_FIRST_PART true



int main()
{
    CHALLENGE_TYPE challenge;
    EErrorCode errorCode = challenge.SetUp(IS_FIRST_PART);

    if (errorCode == EErrorCode::Success)
    {
        errorCode = challenge.Run();
    }

    challenge.CleanUp();
    return static_cast<int>(errorCode);
}
