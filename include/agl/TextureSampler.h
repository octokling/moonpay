#pragma once

#include "util.h"
#include "detail/Surface.h"
#include "driver/NVNtexture.h"
#include <prim/seadSafeString.h>

namespace agl
{
    class TextureSampler
    {
    public:
        void* unk1;
        TextureData mTextureData;
        char unk2[0x40];
    };
};
