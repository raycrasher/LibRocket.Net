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
public:
	
	virtual ~RenderInterface();
protected:
	RenderInterface();
public protected:
	
	virtual void RenderGeometry(Vertex * vertices, int num_vertices, int * indices, int num_indices, IntPtr texture, Vector2f translation) abstract;
	virtual CompiledGeometryHandle CompileGeometry(Vertex* vertices, int num_vertices, int* indices, int num_indices, TextureHandle texture) { _methodUnused = true; return IntPtr::Zero; }
	virtual void RenderCompiledGeometry(CompiledGeometryHandle geometry, Vector2f translation) {	_methodUnused=true;	}
	virtual void ReleaseCompiledGeometry(CompiledGeometryHandle geometry) {	_methodUnused=true;	}
	virtual void EnableScissorRegion(bool enable) abstract;
	virtual void SetScissorRegion(int x, int y, int width, int height) abstract;
	virtual bool LoadTexture(TextureHandle% texture_handle, Vector2i% texture_dimensions, String^ source) { _methodUnused = true;	return false; }
	virtual bool GenerateTexture(TextureHandle% texture_handle, Byte* source, Vector2i source_dimensions) { _methodUnused = true;	return false; }
	virtual void ReleaseTexture(TextureHandle texture) {	_methodUnused=true;	}
	virtual float GetHorizontalTexelOffset() { _methodUnused = true; return 0; }
	virtual float GetVerticalTexelOffset() { _methodUnused = true;	return 0; }
	virtual float GetPixelsPerInch() { _methodUnused = true; return 0; }
	virtual void Release() {	_methodUnused=true;	}

	property Context^ Context { LibRocketNet::Context^ get(); }

	generic<typename T> where T:value class
	static array<T>^ CopyVertices(Vertex *vtx, int numVertices) {
		if (sizeof(T) != sizeof(Vertex))
			throw gcnew ArgumentException(
				String::Format(
					"Unable to copy vertices to type - sizes are not equal: {0} = {1}, {2} = {3}", 
					T::typeid->Name, sizeof(T), Vertex::typeid->Name, sizeof(Vertex)));

		auto arr = gcnew array<T>(numVertices);

		pin_ptr<T> ptr = &arr[0];

		void *p = ptr;
		memcpy(p, vtx, sizeof(T)* numVertices);
		return arr;
	}

	generic<typename T> where T:value class
		static array<T>^ CopyVertices(Vertex *vtx, array<T>^ arr, int numVertices) {
		if (sizeof(T) != sizeof(Vertex))
			throw gcnew ArgumentException(
			String::Format(
			"Unable to copy vertices to type - sizes are not equal: {0} = {1}, {2} = {3}",
			T::typeid->Name, sizeof(T), Vertex::typeid->Name, sizeof(Vertex)));

		if (arr->Length < numVertices)
			throw gcnew ArgumentException("CopyVertices: Vertex array not large enough.");

		pin_ptr<T> ptr = &arr[0];

		void *p = ptr;
		memcpy(p, vtx, sizeof(T)* numVertices);
		return arr;
	}

internal:
	InternalRenderInterface* _nativeInterface;

	LibRocketNet::Context^ _context;
};




}