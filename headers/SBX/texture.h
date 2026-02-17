#ifndef SBX_TEXTURE_H
#define SBX_TEXTURE_H

// Project headers
#include <SBX/types.h>

// Dependency headers
#include <PR/texture.h>

struct SBXTexture {
    SBX_bool_t     initialized;

    SBX_window_t*     associatedWindow;
    prTextureData* textureHandle;
};

#endif // SBX_TEXTURE_H
