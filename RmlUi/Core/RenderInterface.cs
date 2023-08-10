using System.Runtime.InteropServices;

namespace RmlUi.Core;

public abstract partial class RenderInterface : IDisposable
{
    private nint _ptr;

    public RenderInterface()
    {
        _ptr = RenderInterfaceAlloc(RenderGeometry);
    }

    public abstract void RenderGeometry(Span<Vertex> vertices, int numVertices, Span<int> indices,
        int numIndices, nint texture, float translationX, float translationY);

    private void ReleaseUnmanagedResources()
    {
        RenderInterfaceFree(_ptr);
        _ptr = IntPtr.Zero;
    }

    public void Dispose()
    {
        ReleaseUnmanagedResources();
        GC.SuppressFinalize(this);
    }

    ~RenderInterface()
    {
        ReleaseUnmanagedResources();
    }

    private delegate void ManagedRenderGeometry(Span<Vertex> vertices, int numVertices, Span<int> indices,
        int numIndices, nint texture, float translationX, float translationY);

    [LibraryImport("RmlUi.Native.dll", EntryPoint = "RenderInterfaceAlloc")]
    private static partial nint RenderInterfaceAlloc(ManagedRenderGeometry renderGeometry);

    [LibraryImport("RmlUi.Native.dll", EntryPoint = "RenderInterfaceFree")]
    private static partial void RenderInterfaceFree(nint ptr);
}