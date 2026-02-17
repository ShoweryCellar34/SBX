#ifndef SBX_BOX_H
#define SBX_BOX_H

// Project headers
#include <SBX/plock.h>
#include <SBX/types.h>
#include <SBX/report.h>

/// @brief Structure used by SBXBox* functions to store dimensions and plocks required to represent a box
struct SBXBox {
    /// @brief SBX_bool_t object used to keep initialization state
    SBX_bool_t            initialized;

    /// @brief SBX_box_dimensions_t object used to keep box width
    SBX_box_dimensions_t  width;
    /// @brief SBX_box_dimensions_t object used to keep box height
    SBX_box_dimensions_t  height;

    /// @brief SBX_plock_array_t object used to store all the plocks associated with 
    SBX_plock_array_t     plockArray;
    SBX_plock_id_matrix_t plockIDMatrix;
};

SBX_report_t SBXBoxCreate(SBX_box_t** box);

SBX_report_t SBXBoxDestroy(SBX_box_t* box);

SBX_report_t SBXBoxInit(SBX_box_t* box,
                        SBX_box_dimensions_t width,
                        SBX_box_dimensions_t height);

SBX_report_t SBXBoxDeinit(SBX_box_t* box);

SBX_report_t SBXBoxGetSize(SBX_box_t* box, SBX_box_dimensions_t* width, SBX_box_dimensions_t* height);

SBX_report_t SBXBoxSetSize(SBX_box_t* box, SBX_box_dimensions_t width, SBX_box_dimensions_t height);

#endif // SBX_BOX_H
