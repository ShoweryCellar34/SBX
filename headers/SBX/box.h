#ifndef SBX_BOX_H
#define SBX_BOX_H

#include <SBX/types.h>

// SBXBox state keeping flags
enum SBXWindowFlags {
    SBX_BOX_   = 1 << 0
};

// SBXBoxReport error type flags
enum SBXBoxErrorFlags {
    SBX_BOX_ERROR_MISSING_ARGUMENT = 1 << 0,
    SBX_BOX_                       = 1 << 0,
    SBX_BOX_ERROR_GET_FAILED       = 1 << 2,
    SBX_BOX_ERROR_SET_FAILED       = 1 << 3
};

/// @brief Structure used by SBBox management functions to report exit state for operation
struct SBXBoxReport {
    // Flags
    SBX_bit_flags_t problmaticFlags; // SBXBoxFlags
    SBX_bit_flags_t errorFlags;      // SBXBoxErrorFlags

    // Error string
    SBX_string_t    reportMessage;
};

/// @brief Structure used by SBXBox fuctions to store pixel states more data to repesent a sandbox environment
struct SBXBox {
    // State flags (DO NOT EDIT)
    SBX_bit_flags_t flags; // SBXBoxFlags
};

#endif // SBX_BOX_H
