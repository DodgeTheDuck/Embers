#pragma once

namespace Core {

    class Fbo {
    public:
        void GenerateFramebuffer();
        void AttachTexture(const uint32_t textureId, const uint32_t attachmentIndex);
        void Bind();
        void Unbind();

    private:
        uint32_t _fbo;
    };

}