#ifndef SBX_TEXTURE_H
#define SBX_TEXTURE_H

// Project headers
#include <SBX/types.h>

// Dependency headers
#include <PR/texture.h>

/// @brief Structure used by SBXTexture fuctions to store texture handle, associated SBXWindow, and more data to represent a texture
struct SBXTexture {
    // State keeping
    SBX_bool_t     initialized;

    // Handles
    SBX_window_t*     associatedWindow;
    prTextureData* textureHandle;
};

#endif // SBX_TEXTURE_H
