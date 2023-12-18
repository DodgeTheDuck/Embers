#include "stdafx.h"
#include "fbo.h"

namespace Core {

    void Fbo::GenerateFramebuffer() {
        if (_fbo != 0) {
            Error::Exit(L"Framebuffer already generated");
        }
        glGenFramebuffers(1, &_fbo);
    }

    void Fbo::AttachTexture(const uint32_t textureId, const uint32_t attachmentIndex) {
        if (_fbo == 0) {
            Error::Exit(L"Trying to attach texture to invalid framebuffer");
        }
        glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachmentIndex, GL_TEXTURE_2D, textureId, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Fbo::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    }

    void Fbo::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}