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

		gcroot<LibRocketNet::RenderInterface^> _netInterface;

		InternalRenderInterface() {
		}

		virtual void RenderGeometry(RVertex* vertices, int num_vertices, int* indices, int num_indices, RTextureHandle texture, const Rocket::Core::Vector2f& translation)  override {
			array<Vertex>^ vtxArray = gcnew array<Vertex>(num_vertices);
			array<int>^ idxArray = gcnew array<int>(num_indices);
			{
				pin_ptr<Vertex> pinnedVtxArray = &vtxArray[0];
				const int vtxSizeInBytes = num_vertices * sizeof(Vertex);
				memcpy_s(pinnedVtxArray, vtxSizeInBytes, vertices, vtxSizeInBytes);

				pin_ptr<int> pinnedIdxArray = &idxArray[0];
				const int idxSizeInBytes = num_indices * sizeof(int);
				memcpy_s(pinnedIdxArray, idxSizeInBytes, indices, idxSizeInBytes);
			}

			_netInterface->RenderGeometry(vtxArray, idxArray, (TextureHandle)(void *)texture, Vector2f(translation));
		}

		virtual RCompiledGeometryHandle CompileGeometry(RVertex* vertices, int num_vertices, int* indices, int num_indices, RTextureHandle texture) override  {
			_netInterface->_methodUnused = false;

			array<Vertex>^ vtxArray = gcnew array<Vertex>(num_vertices);
			array<int>^ idxArray = gcnew array<int>(num_indices);
			{
				pin_ptr<Vertex> pinnedVtxArray = &vtxArray[0];
				const int vtxSizeInBytes = num_vertices * sizeof(Vertex);
				memcpy_s(pinnedVtxArray, vtxSizeInBytes, vertices, vtxSizeInBytes);
				
				pin_ptr<int> pinnedIdxArray = &idxArray[0];
				const int idxSizeInBytes = num_indices * sizeof(int);
				memcpy_s(pinnedIdxArray, idxSizeInBytes, indices, idxSizeInBytes);
			}

			RCompiledGeometryHandle result = (RCompiledGeometryHandle)_netInterface->CompileGeometry(vtxArray, idxArray, (TextureHandle)(void *)texture).ToPointer();
			if (_netInterface->_methodUnused)
				return Rocket::Core::RenderInterface::CompileGeometry(vertices, num_vertices, indices, num_indices, texture);
			else return result;
		}

		virtual void RenderCompiledGeometry(RCompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation)  override {
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

		virtual bool LoadTexture(RTextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source) {
			_netInterface->_methodUnused = false;
			TextureHandle handle = TextureHandle::Zero;
			Vector2i dimensions;
			
			bool result = _netInterface->LoadTexture(handle, dimensions, Util::ToNetString(source));

			if (_netInterface->_methodUnused) return Rocket::Core::RenderInterface::LoadTexture(texture_handle, texture_dimensions, source);

			texture_handle=(RTextureHandle) handle.ToPointer();
			texture_dimensions = dimensions;

			return result;
		}

		virtual bool GenerateTexture(RTextureHandle& texture_handle, const unsigned char* source, const Rocket::Core::Vector2i& source_dimensions)  override {
			_netInterface->_methodUnused = false;
			TextureHandle handle = TextureHandle::Zero;
			auto sizeBytes = source_dimensions.x * source_dimensions.y * 4;
			array<unsigned char>^ bytes = gcnew array<unsigned char>(sizeBytes);
			{
				pin_ptr<unsigned char> pinnedBytes = &bytes[0];
				memcpy_s(pinnedBytes, sizeBytes, source, sizeBytes);
			}

			bool result = _netInterface->GenerateTexture(handle, bytes, Vector2i(source_dimensions));
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

void RenderInterface::SetCore(){
	Rocket::Core::SetRenderInterface(_nativeInterface);
}

}