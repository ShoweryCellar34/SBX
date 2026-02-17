#ifndef SBX_PLOCK_H
#define SBX_PLOCK_H

// Project headers
#include <SBX/types.h>
#include <SBX/report.h>

struct SBXPlockType {
    SBX_color_t color;
};

struct SBXPlock {
    SBX_plock_type_id_t     type;

    SBX_plock_temperature_t temperature;
};

struct SBXPlockArray {
    SBX_plock_t*      plocks;

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
