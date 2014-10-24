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

		gcroot<LibRocketNet::RenderInterface^> _netInterface;

		

		virtual void RenderGeometry(RVertex* vertices, int num_vertices, int* indices, int num_indices, RTextureHandle texture, const RVector2f& translation)  override {
			_netInterface->RenderGeometry((Vertex *)vertices, num_vertices, indices, num_indices, (TextureHandle)(void *)texture, Vector2f(translation.x, translation.y));
		}

		virtual RCompiledGeometryHandle CompileGeometry(RVertex* vertices, int num_vertices, int* indices, int num_indices, RTextureHandle texture) override  {
			_netInterface->_methodUnused = false;
			RCompiledGeometryHandle result = (RCompiledGeometryHandle)_netInterface->CompileGeometry((Vertex *)vertices, num_vertices, indices, num_indices, (TextureHandle)(void *)texture).ToPointer();
			if (_netInterface->_methodUnused)
				return Rocket::Core::RenderInterface::CompileGeometry(vertices, num_vertices, indices, num_indices, texture);
			else return result;
		}

		virtual void RenderCompiledGeometry(RCompiledGeometryHandle geometry, const RVector2f& translation)  override {
			_netInterface->_methodUnused = false;
			_netInterface->RenderCompiledGeometry((CompiledGeometryHandle)(void *)geometry, Vector2f(translation));
			if (_netInterface->_methodUnused)
				Rocket::Core::RenderInterface::RenderCompiledGeometry(geometry, translation);
		}

		virtual void ReleaseCompiledGeometry(RCompiledGeometryHandle geometry)  override {
			_netInterface->_methodUnused = false;
			_netInterface->ReleaseCompiledGeometry((CompiledGeometryHandle)(void *)geometry);
			if (_netInterface->_methodUnused)
				Rocket::Core::RenderInterface::ReleaseCompiledGeometry(geometry);
		}

		virtual void EnableScissorRegion(bool enable)  override {
			_netInterface->EnableScissorRegion(enable);
		}

		virtual void SetScissorRegion(int x, int y, int width, int height)  override {
			_netInterface->SetScissorRegion(x, y, width, height);
		}

		virtual bool LoadTexture(RTextureHandle& texture_handle, RVector2i& texture_dimensions, const RocketString& source) {
			_netInterface->_methodUnused = false;
			TextureHandle handle = TextureHandle::Zero;
			Vector2i dimensions;
			
			bool result = _netInterface->LoadTexture(handle, dimensions, Util::ToNetString(source));

			if (_netInterface->_methodUnused) return Rocket::Core::RenderInterface::LoadTexture(texture_handle, texture_dimensions, source);

			texture_handle=(RTextureHandle) handle.ToPointer();
			texture_dimensions.x=dimensions.X;
			texture_dimensions.y=dimensions.Y;

			return result;
		}

		virtual bool GenerateTexture(RTextureHandle& texture_handle, const unsigned char* source, const RVector2i& source_dimensions)  override {
			_netInterface->_methodUnused = false;
			TextureHandle handle = TextureHandle::Zero;

			bool result = _netInterface->GenerateTexture(handle, (System::Byte *) source, Vector2i(source_dimensions));
			if (_netInterface->_methodUnused)
				return Rocket::Core::RenderInterface::GenerateTexture(texture_handle, source, source_dimensions);

			texture_handle = (RTextureHandle)handle.ToPointer();
			return result;
		}


		virtual void ReleaseTexture(RTextureHandle texture) override {
			_netInterface->_methodUnused = false;
			_netInterface->ReleaseTexture((TextureHandle)(void*)texture);
			if (_netInterface->_methodUnused)
				Rocket::Core::RenderInterface::ReleaseTexture(texture);
		}

		virtual float GetHorizontalTexelOffset()  override {
			_netInterface->_methodUnused = false;
			auto result = _netInterface->GetHorizontalTexelOffset();
			if (_netInterface->_methodUnused)
				return Rocket::Core::RenderInterface::GetHorizontalTexelOffset();
			else 
				return result;
		}

		virtual float GetVerticalTexelOffset()  override {
			_netInterface->_methodUnused = false;
			auto result = _netInterface->GetVerticalTexelOffset();
			if (_netInterface->_methodUnused)
				return Rocket::Core::RenderInterface::GetVerticalTexelOffset();
			else 
				return result;
		}

		virtual float GetPixelsPerInch()  override {
			_netInterface->_methodUnused = false;
			auto result = _netInterface->GetPixelsPerInch();
			if (_netInterface->_methodUnused)
				return Rocket::Core::RenderInterface::GetPixelsPerInch();
			return result;
		}

		virtual void Release()  override {
			_netInterface->_methodUnused = false;
			_netInterface->Release();
			if (_netInterface->_methodUnused)
				Rocket::Core::RenderInterface::Release();
		}
	};

RenderInterface::RenderInterface(){

	_nativeInterface = new InternalRenderInterface();
	_nativeInterface->_netInterface = this;
}

RenderInterface::~RenderInterface(){
	delete _nativeInterface;
}

Context^ RenderInterface::Context::get(){
	return _context;
}

}