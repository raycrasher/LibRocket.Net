#pragma once

#include "Vertex.h"

using namespace System;


namespace Rocket {
	namespace Core {
		class RenderInterface;
	}
}

namespace LibRocketNet {

typedef IntPtr TextureHandle;
typedef IntPtr CompiledGeometryHandle;

ref class Context;

class InternalRenderInterface;

public ref class RenderInterface abstract
{
internal:
	bool _methodUnused;

	void SetCore();
protected:
	RenderInterface();
public:
	virtual ~RenderInterface();

public protected:

	virtual void RenderGeometry(Vertex *vertices, int numVertices, int* indices, int numIndices, IntPtr texture, Vector2f translation) abstract;
	virtual CompiledGeometryHandle CompileGeometry(Vertex *vertices, int numVertices, int* indices, int numIndices, TextureHandle texture) { _methodUnused = true; return IntPtr::Zero; }
	virtual void RenderCompiledGeometry(CompiledGeometryHandle geometry, Vector2f translation) {	_methodUnused=true;	}
	virtual void ReleaseCompiledGeometry(CompiledGeometryHandle geometry) {	_methodUnused=true;	}
	virtual void EnableScissorRegion(bool enable) abstract;
	virtual void SetScissorRegion(int x, int y, int width, int height) abstract;
	virtual bool LoadTexture(TextureHandle% texture_handle, Vector2i% texture_dimensions, String^ source) { _methodUnused = true;	return false; }
	virtual bool GenerateTexture(TextureHandle% texture_handle, const unsigned char *source, Vector2i source_dimensions) { _methodUnused = true;	return false; }
	virtual void ReleaseTexture(TextureHandle texture) {	_methodUnused=true;	}
	virtual float GetHorizontalTexelOffset() { _methodUnused = true; return 0; }
	virtual float GetVerticalTexelOffset() { _methodUnused = true;	return 0; }
	virtual float GetPixelsPerInch() { _methodUnused = true; return 0; }
	virtual void Release() {	_methodUnused=true;	}

	property Context^ Context { LibRocketNet::Context^ get(); }

internal:
	InternalRenderInterface* _nativeInterface;

	LibRocketNet::Context^ _context;

};




}