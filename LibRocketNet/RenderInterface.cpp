#include "stdafx.h"
#include "Rocket/Core/RenderInterface.h"
#include "LibRocketNet.h"
#include "RenderInterface.h"
#include <gcroot.h>


namespace LibRocketNet {


	typedef Rocket::Core::TextureHandle RTextureHandle;
	typedef Rocket::Core::CompiledGeometryHandle RCompiledGeometryHandle;

	class InternalRenderInterface : public Rocket::Core::RenderInterface {
	public:
		gcroot<LibRocketNet::RenderInterface^> Interface;

		virtual void RenderGeometry(RVertex* vertices, int num_vertices, int* indices, int num_indices, RTextureHandle texture, const RVector2f& translation) {
			Interface->RenderGeometry((Vertex *)vertices, num_vertices, indices, num_indices, (TextureHandle) (void *)texture, Vector2f(translation.x,translation.y));
		}

		virtual RCompiledGeometryHandle CompileGeometry(RVertex* vertices, int num_vertices, int* indices, int num_indices, RTextureHandle texture) {
			return Interface->CompileGeometry((Vertex *)vertices, num_vertices, indices, num_indices, (TextureHandle) (void *)texture).ToInt32;
		}

		virtual void RenderCompiledGeometry(RCompiledGeometryHandle geometry, const RVector2f& translation) {
			return Interface->CompileGeometry((CompiledGeometryHandle)(void *) geometry, new Vector2f(translation));
		}
		virtual void ReleaseCompiledGeometry(CompiledGeometryHandle geometry);
		virtual void EnableScissorRegion(bool enable);
		virtual void SetScissorRegion(int x, int y, int width, int height);
		virtual bool LoadTexture(TextureHandle& texture_handle, RVector2i& texture_dimensions, const RocketString& source);
		virtual bool GenerateTexture(TextureHandle& texture_handle, const unsigned char* source, const RVector2i& source_dimensions);
		virtual void ReleaseTexture(TextureHandle texture);
		virtual float GetHorizontalTexelOffset();
		virtual float GetVerticalTexelOffset();
		virtual float GetPixelsPerInch();
		virtual void Release();
	};

RenderInterface::RenderInterface(){

}

}