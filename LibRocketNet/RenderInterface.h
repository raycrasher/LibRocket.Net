#pragma once

#include "Vertex.h"

using namespace System;
using namespace System::Drawing;


namespace Rocket {
	namespace Core {
		class RenderInterface;
	}
}

namespace LibRocketNet {



typedef IntPtr TextureHandle;
typedef IntPtr CompiledGeometryHandle;

ref class Context;

public ref class RenderInterface abstract
{
public:
	RenderInterface();
	virtual ~RenderInterface();

	virtual void RenderGeometry(Vertex * vertices, int num_vertices, int * indices, int num_indices, IntPtr texture, Vector2f translation) abstract;
	virtual CompiledGeometryHandle CompileGeometry(Vertex* vertices, int num_vertices, int* indices, int num_indices, TextureHandle texture);
	virtual void RenderCompiledGeometry(CompiledGeometryHandle geometry, Vector2f translation);
	virtual void ReleaseCompiledGeometry(CompiledGeometryHandle geometry);
	virtual void EnableScissorRegion(bool enable) abstract;
	virtual void SetScissorRegion(int x, int y, int width, int height) abstract;
	virtual bool LoadTexture(TextureHandle% texture_handle, Vector2i% texture_dimensions, String^ source);
	virtual bool GenerateTexture(TextureHandle% texture_handle, Byte* source, Vector2i% source_dimensions);
	virtual void ReleaseTexture(TextureHandle texture);
	virtual float GetHorizontalTexelOffset();
	virtual float GetVerticalTexelOffset();
	virtual float GetPixelsPerInch();
	virtual void Release();
	property Context^ Context { LibRocketNet::Context^ get(); }

internal:
	System::IntPtr Interface;
};




}