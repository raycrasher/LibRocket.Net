#include "stdafx.h"
#include "Rocket/Core/RenderInterface.h"
#include "LibRocketNet.h"
#include "RenderInterface.h"
#include <gcroot.h>
#include "Util.h"


namespace LibRocketNet {


	typedef Rocket::Core::TextureHandle RTextureHandle;
	typedef Rocket::Core::CompiledGeometryHandle RCompiledGeometryHandle;

	class InternalRenderInterface : public Rocket::Core::RenderInterface {
	public:

		InternalRenderInterface(){
			
		}

		gcroot<LibRocketNet::RenderInterface^> Interface;

		

		virtual void RenderGeometry(RVertex* vertices, int num_vertices, int* indices, int num_indices, RTextureHandle texture, const RVector2f& translation)  override {
			Interface->RenderGeometry((Vertex *)vertices, num_vertices, indices, num_indices, (TextureHandle) (void *)texture, Vector2f(translation.x,translation.y));
		}

		virtual RCompiledGeometryHandle CompileGeometry(RVertex* vertices, int num_vertices, int* indices, int num_indices, RTextureHandle texture) override  {
			Interface->_methodUnused=false;
			bool result = Interface->CompileGeometry((Vertex *)vertices, num_vertices, indices, num_indices, (TextureHandle) (void *)texture).ToInt32;
			if(Interface->_methodUnused)
				return Rocket::Core::RenderInterface::CompileGeometry(vertices, num_vertices, indices, num_indices, texture);
			else return result;
		}

		virtual void RenderCompiledGeometry(RCompiledGeometryHandle geometry, const RVector2f& translation)  override {
			Interface->_methodUnused=false;
				Interface->RenderCompiledGeometry((CompiledGeometryHandle)(void *) geometry, Vector2f(translation));
			if(Interface->_methodUnused)
				Rocket::Core::RenderInterface::RenderCompiledGeometry(geometry, translation);
		}

		virtual void ReleaseCompiledGeometry(RCompiledGeometryHandle geometry)  override {
			Interface->_methodUnused=false;
				Interface->ReleaseCompiledGeometry((CompiledGeometryHandle)(void *) geometry);
			if(Interface->_methodUnused)
				Rocket::Core::RenderInterface::ReleaseCompiledGeometry(geometry);
		}

		virtual void EnableScissorRegion(bool enable)  override {
			Interface->EnableScissorRegion(enable);
		}

		virtual void SetScissorRegion(int x, int y, int width, int height)  override {
			Interface->SetScissorRegion(x,y,width,height);
		}

		virtual bool LoadTexture(RTextureHandle& texture_handle, RVector2i& texture_dimensions, const RocketString& source)  override {
			Interface->_methodUnused=false;
			TextureHandle handle = TextureHandle::Zero;
			Vector2i dimensions;
			
			bool result = Interface->LoadTexture(handle, dimensions, Util::ToNetString(source));

			if(Interface->_methodUnused) return Rocket::Core::RenderInterface::LoadTexture(texture_handle, texture_dimensions, source);

			texture_handle=handle.ToPointer;
			texture_dimensions.x=dimensions.X;
			texture_dimensions.y=dimensions.Y;

			return result;
		}

		virtual bool GenerateTexture(RTextureHandle& texture_handle, const unsigned char* source, const RVector2i& source_dimensions)  override {
			Interface->_methodUnused=false;
			TextureHandle handle = TextureHandle::Zero;

			bool result=Interface->GenerateTexture(handle, (System::Byte *) source, Vector2i(source_dimensions));
			if(Interface->_methodUnused)
				return Rocket::Core::RenderInterface::GenerateTexture(texture_handle, source, source_dimensions);

			texture_handle = handle.ToPointer;
			return result;
		}


		virtual void ReleaseTexture(RTextureHandle texture) override {
			Interface->_methodUnused=false;
			Interface->ReleaseTexture((TextureHandle)(void*)texture);
			if(Interface->_methodUnused)
				Rocket::Core::RenderInterface::ReleaseTexture(texture);
		}

		virtual float GetHorizontalTexelOffset()  override {
			Interface->_methodUnused=false;
			auto result= Interface->GetHorizontalTexelOffset();
			if(Interface->_methodUnused)
				return Rocket::Core::RenderInterface::GetHorizontalTexelOffset();
			else 
				return result;
		}

		virtual float GetVerticalTexelOffset()  override {
			Interface->_methodUnused=false;
			auto result = Interface->GetVerticalTexelOffset();
			if(Interface->_methodUnused)
				return Rocket::Core::RenderInterface::GetVerticalTexelOffset();
			else 
				return result;
		}

		virtual float GetPixelsPerInch()  override {
			Interface->_methodUnused=false;
			auto result=Interface->GetPixelsPerInch();
			if(Interface->_methodUnused)
				return Rocket::Core::RenderInterface::GetPixelsPerInch();
			return result;
		}

		virtual void Release()  override {
			Interface->_methodUnused=false;
			Interface->Release();
			if(Interface->_methodUnused)
				Rocket::Core::RenderInterface::Release();
		}
	};

RenderInterface::RenderInterface(){
	Interface= (IntPtr) new InternalRenderInterface();
}

RenderInterface::~RenderInterface(){
	InternalRenderInterface * ptr = Interface.ToPointer;
	delete ptr;
}

Context^ RenderInterface::Context::get(){
	return _context;
}

}