#ifndef SBX_PLOCK_H
#define SBX_PLOCK_H

// Project headers
#include <SBX/types.h>
#include <SBX/report.h>

/// @brief Structure used by SBXPlockType fuctions to store color, physics type, and more data to represent a plock type
struct SBXPlockType {
    SBX_color_t color;
};

/// @brief Structure used by SBXPlock functions to store plock type, temperature, and more data to represent a plock
struct SBXPlock {
    /// @brief The plock type, this will map to a SBXPlockType object
    SBX_plock_type_id_t     type;

    /// @brief The temperature of the plock
    SBX_plock_temperature_t temperature;
};

/// @brief Structure used by SBXPlockArray functions to store plocks to represent a plock array
struct SBXPlockArray {
    /// @brief Pointer to an array of plocks
    SBX_plock_t*      plocks;

    /// @brief The count of plocks in the array (not bytes)
    SBX_plock_count_t count;
};

SBX_report_t SBXPlockArrayGetSize(SBX_plock_array_t* plockArray, SBX_plock_count_t* count);

SBX_report_t SBXPlockArraySetSize(SBX_plock_array_t* plockArray, SBX_plock_count_t count);

struct SBXPlockIDMatrix {
    SBX_plock_id_t*                  plockIDs;

    SBX_plock_id_matrix_dimensions_t width, 
                                     height;
};

SBX_report_t SBXPlockIDMatrixGetSize(SBX_plock_id_matrix_t* plockIDMatrix,
                                     SBX_plock_id_matrix_dimensions_t* width, SBX_plock_id_matrix_dimensions_t* height);

SBX_report_t SBXPlockIDMatrixSetSize(SBX_plock_id_matrix_t* plockIDMatrix,
                                     SBX_plock_id_matrix_dimensions_t width, SBX_plock_id_matrix_dimensions_t height);

#endif // SBX_PLOCK_H
