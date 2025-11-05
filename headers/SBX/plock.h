#ifndef SBX_PLOCK_H
#define SBX_PLOCK_H

// Project headers
#include <SBX/types.h>

/// @brief Structure used by SBXPlock functions to report exit state for operation
struct SBXPlockReport {
    // Flags
    SBX_bit_flags_t errorFlags; // SBXPlockErrorFlags

    // Error string
    SBX_string_t    reportMessage;
};

/// @brief Structure used by SBXPlock functions to store pixel settings, types, and more to represent a pixel type
struct SBXPlock {
    SBX_color_t color;
};

/// @brief Allocates memory for a SBXPlock object and then sets values according to the provided settings, on error the address pointed to by the SBX_plock_t** will be set to NULL
/// @param plock A pointer to a SBX_plock_t pointer to set to the allocated SBXPlock pointer, cannot be NULL
/// @return A SBXPlockReport struct that reports the return state of the creation function, this can be an error, or a success.
///         Possible errors include: SBX_PLOCK_ERROR_MISSING_ARGUMENT, SBX_PLOCK_ERROR_MEMORY_FAILURE
SBX_plock_report_t SBXPlockCreate(SBX_plock_t** plock, SBX_color_t color);

/// @brief Deallocates a SBXPlock objects memory
/// @param plock A SBX_plock_t pointer to the desired SBXplock to be destroyed, cannot be NULL
/// @return A SBXPlockReport struct that reports the return state of the destruction function, this can be an error, or a success.
///         Possible errors include: SBX_PLOCK_ERROR_MISSING_ARGUMENT
SBX_plock_report_t SBXPlockDestroy(SBX_plock_t* plock);

#endif // SBX_PLOCK_H
