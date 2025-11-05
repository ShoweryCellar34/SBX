#ifndef SBX_BOX_H
#define SBX_BOX_H

// Project headers
#include <SBX/types.h>

/// @brief Structure used by SBXBox functions to report exit state for operation
struct SBXBoxReport {
    /// @brief This variable contains the bit flag for the error that was raised
    SBX_bit_flags_t errorFlags; // SBXBoxErrorFlags or SBXCommonErrorFlags

    /// @brief This variable contains an error message to go with the error
    SBX_string_t    reportMessage;
};

/// @brief Structure used by SBXBox fuctions to store pixels, states, and more data to represent a sandbox environment
struct SBXBox {
    // State keeping
    SBX_bool_t           initialized;

    // Plocks
    SBX_plock_id_t*      plocks;
    SBX_box_dimensions_t width,
                         height;
};

#endif // SBX_BOX_H
