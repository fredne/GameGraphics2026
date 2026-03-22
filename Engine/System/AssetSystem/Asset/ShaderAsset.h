#pragma once
#include "Asset.h"
#include <Shader/Shader.h>

namespace F
{
    struct ShaderAssetParam : AssetParam
    {
        std::wstring vsFile;
        std::wstring psFile;
    };

    class ShaderAsset : public Asset<Shader>
    {
    private:

    public:
        ShaderAsset(const ShaderAssetParam& param);
        Shader* Load(const std::wstring& path) override;
        void Create(const std::wstring& path) override;

    };

}

