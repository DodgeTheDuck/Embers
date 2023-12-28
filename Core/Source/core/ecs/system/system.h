#pragma once

#include "dll.h"

namespace Core::System {

    class Extension;

    class ENGINE_API System {
    public:
        virtual void Init() = 0;
        virtual void Tick(Ref<entt::registry> registry, double dt) = 0;
        virtual void PreRender(Ref<entt::registry> registry) = 0;
        virtual void RenderPass(Ref<entt::registry> registry, uint32_t passIndex) = 0;
        virtual void Gui(Ref<entt::registry> registry, double dt) = 0;
        virtual void PostRender(Ref<entt::registry> registry) = 0;
        std::vector<Ref<Extension>> Extensions() { return _extensions; };
    private:
        std::vector<Ref<Extension>> _extensions;
    };


}