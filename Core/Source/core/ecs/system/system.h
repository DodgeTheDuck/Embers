#pragma once

namespace Core::System {

    class System {
    public:
        virtual void Init() = 0;
        virtual void Tick(Ref<entt::registry> registry, double dt) = 0;
        virtual void PreRender(Ref<entt::registry> registry, double dt) = 0;
        virtual void RenderPass(Ref<entt::registry> registry, double dt, uint32_t passIndex) = 0;
        virtual void Gui(Ref<entt::registry> registry, double dt) = 0;
        virtual void PostRender(Ref<entt::registry> registry, double dt) = 0;
    };


}