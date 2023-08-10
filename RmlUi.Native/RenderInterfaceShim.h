#pragma once
#include <RmlUi/Core/RenderInterface.h>

#include "DllUtils.h"

typedef void (*ManagedRenderGeometry)(void* vertices, int num_vertices, int* indices, int num_indices,
                                      uintptr_t texture, float translation_x, float translation_y);
typedef uintptr_t (*ManagedCompileGeometry)(void* vertices, int num_vertices, int* indices, int num_indices,
                                            uintptr_t texture);
typedef void (*ManagedRenderCompiledGeometry)(uintptr_t geometry, float translation_x, float translation_y);
typedef void (*ManagedReleaseCompiledGeometry)(uintptr_t geometry);
typedef void (*ManagedEnableScissorRegion)(bool enable);
typedef void (*ManagedSetScissorRegion)(int x, int y, int width, int height);
typedef bool (*ManagedLoadTexture)(uintptr_t texture_handle, int width, int height, const char* source);
typedef bool (*ManagedGenerateTexture)(uintptr_t texture_handle, const uint8_t* source, int width, int height);
typedef void (*ManagedReleaseTexture)(uintptr_t texture);
typedef void (*ManagedSetTransform)(const void* matrix44f);

class RenderInterfaceShim final : public Rml::RenderInterface
{
public:
    RenderInterfaceShim(const ManagedRenderGeometry render_geometry, const ManagedCompileGeometry compile_geometry,
                        const ManagedRenderCompiledGeometry render_compiled_geometry,
                        const ManagedReleaseCompiledGeometry release_compiled_geometry,
                        const ManagedEnableScissorRegion enable_scissor_region,
                        const ManagedSetScissorRegion set_scissor_region,
                        const ManagedLoadTexture load_texture, const ManagedGenerateTexture generate_texture,
                        const ManagedReleaseTexture release_texture, const ManagedSetTransform set_transform)
    {
        this->render_geometry = render_geometry;
        this->compile_geometry = compile_geometry;
        this->render_compiled_geometry = render_compiled_geometry;
        this->release_compiled_geometry = release_compiled_geometry;
        this->enable_scissor_region = enable_scissor_region;
        this->set_scissor_region = set_scissor_region;
        this->load_texture = load_texture;
        this->generate_texture = generate_texture;
        this->release_texture = release_texture;
        this->set_transform = set_transform;
    }

    void RenderGeometry(Rml::Vertex* vertices, const int num_vertices, int* indices, const int num_indices,
                        const Rml::TextureHandle texture, const Rml::Vector2f& translation) override
    {
        render_geometry(vertices, num_vertices, indices, num_indices, texture, translation.x, translation.y);
    }

    Rml::CompiledGeometryHandle CompileGeometry(Rml::Vertex* vertices, const int num_vertices, int* indices,
                                                const int num_indices,
                                                const Rml::TextureHandle texture) override
    {
        return compile_geometry(vertices, num_vertices, indices, num_indices, texture);
    }

    void RenderCompiledGeometry(const Rml::CompiledGeometryHandle geometry, const Rml::Vector2f& translation) override
    {
        render_compiled_geometry(geometry, translation.x, translation.y);
    }

    void ReleaseCompiledGeometry(const Rml::CompiledGeometryHandle geometry) override
    {
        release_compiled_geometry(geometry);
    }

    void EnableScissorRegion(const bool enable) override
    {
        enable_scissor_region(enable);
    }

    void SetScissorRegion(const int x, const int y, const int width, const int height) override
    {
        set_scissor_region(x, y, width, height);
    }

    bool LoadTexture(Rml::TextureHandle& texture_handle, Rml::Vector2i& texture_dimensions,
                     const Rml::String& source) override
    {
        return load_texture(texture_handle, texture_dimensions.x, texture_dimensions.y, source.c_str());
    }

    bool GenerateTexture(Rml::TextureHandle& texture_handle, const Rml::byte* source,
                         const Rml::Vector2i& source_dimensions) override
    {
        return generate_texture(texture_handle, source, source_dimensions.x, source_dimensions.y);
    }

    void ReleaseTexture(const Rml::TextureHandle texture) override
    {
        release_texture(texture);
    }

    void SetTransform(const Rml::Matrix4f* transform) override
    {
        set_transform(transform);
    }

private:
    ManagedRenderGeometry render_geometry;
    ManagedCompileGeometry compile_geometry;
    ManagedRenderCompiledGeometry render_compiled_geometry;
    ManagedReleaseCompiledGeometry release_compiled_geometry;
    ManagedEnableScissorRegion enable_scissor_region;
    ManagedSetScissorRegion set_scissor_region;
    ManagedLoadTexture load_texture;
    ManagedGenerateTexture generate_texture;
    ManagedReleaseTexture release_texture;
    ManagedSetTransform set_transform;
};

extern "C" {
inline DllExport RenderInterfaceShim* RenderInterfaceShimAlloc(const ManagedRenderGeometry render_geometry,
                                                               const ManagedCompileGeometry compile_geometry,
                                                               const ManagedRenderCompiledGeometry
                                                               render_compiled_geometry,
                                                               const ManagedReleaseCompiledGeometry
                                                               release_compiled_geometry,
                                                               const ManagedEnableScissorRegion enable_scissor_region,
                                                               const ManagedSetScissorRegion set_scissor_region,
                                                               const ManagedLoadTexture load_texture,
                                                               const ManagedGenerateTexture generate_texture,
                                                               const ManagedReleaseTexture release_texture,
                                                               const ManagedSetTransform set_transform)
{
    return new RenderInterfaceShim(render_geometry, compile_geometry, render_compiled_geometry,
                                   release_compiled_geometry, enable_scissor_region, set_scissor_region, load_texture,
                                   generate_texture, release_texture, set_transform);
}

inline DllExport void RenderInterfaceShimFree(const RenderInterfaceShim* instance)
{
    delete instance;
}
}
