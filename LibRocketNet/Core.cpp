#include "stdafx.h"

#include "Rocket/Core.h"
#include "Rocket/Core/String.h"
#include "Rocket/Debugger.h"

#include "Core.h"
#include "Util.h"
#include "SystemInterface.h"
#include "RenderInterface.h"
#include "FileInterface.h"
#include "Context.h"

using namespace System;
using namespace LibRocketNet::Util;

namespace LibRocketNet {

	bool Core::Initialize() {
		_contexts = gcnew Dictionary<IntPtr,Context^>();
		return Rocket::Core::Initialise();
	}

	void Core::Shutdown() {
		Rocket::Core::Shutdown();
		_contexts->Clear();
		_contexts = nullptr;

	}

	String^ Core::Version::get(){
		auto v = Rocket::Core::GetVersion();
		return Util::ToNetString(v);
	}

	SystemInterface^ Core::SystemInterface::get(){
		return _systemInterface;
	} 

	void Core::SystemInterface::set(LibRocketNet::SystemInterface^ s) {
		s->SetCore();
		_systemInterface = s;
	}


	RenderInterface^ Core::RenderInterface::get() {
		return _renderInterface;
	}

	void Core::RenderInterface::set(LibRocketNet::RenderInterface^ r) {
		r->SetCore();
		_renderInterface = r;
	}

	FileInterface^ Core::FileInterface::get() {
		return _fileInterface;
	}

	void Core::FileInterface::set(LibRocketNet::FileInterface^ f) {
		f->SetCore();
		_fileInterface = f;
	}

	Context^ Core::CreateContext(String^ name, Vector2i dimensions, LibRocketNet::RenderInterface^ renderInterface) {

		auto rPtr = (_renderInterface == nullptr ? NULL : _renderInterface->_nativeInterface);
		IntPtr ctxPtr = IntPtr(Rocket::Core::CreateContext(Util::ToRocketString(name), Rocket::Core::Vector2i(dimensions.X, dimensions.Y), (Rocket::Core::RenderInterface*) rPtr));
		auto ctx = gcnew Context((Rocket::Core::Context *) ctxPtr.ToPointer());
		ctx->_renderInterface = renderInterface;
		_contexts[ctxPtr] = ctx;
		return ctx;
	}

	Context^ Core::GetContext(String^ name) {
		auto ptr = Rocket::Core::GetContext(Util::ToRocketString(name));
		if (!ptr) return nullptr;
		return _contexts[IntPtr(ptr)];
	}


	Context^ Core::GetContext(int index) {
		auto ptr = Rocket::Core::GetContext(index);
		if (!ptr) return nullptr;
		return _contexts[IntPtr(ptr)];
	}

	int Core::NumContexts::get(){
		return Rocket::Core::GetNumContexts();
	}

	void Core::ReleaseCompiledGeometries() {
		Rocket::Core::ReleaseCompiledGeometries();
	}
	void Core::ReleaseTextures() {
		Rocket::Core::ReleaseTextures();
	}

	bool Core::LoadFontFace(String^ font){
		return Rocket::Core::FontDatabase::LoadFontFace(ToRocketString(font));
	}

	bool Core::LoadFontFace(String^ file_name, String^ family, FontStyle style, FontWeight weight) {
		return Rocket::Core::FontDatabase::LoadFontFace(ToRocketString(file_name), ToRocketString(family), (Rocket::Core::Font::Style) style, (Rocket::Core::Font::Weight) weight);
	}

	bool Core::LoadFontFace(array<Byte>^ data){
		pin_ptr<Byte> ptr = &data[0];
		return Rocket::Core::FontDatabase::LoadFontFace(ptr, data->Length);
	}

	bool Core::LoadFontFace(array<Byte>^ data, String^ family, FontStyle style, FontWeight weight) {
		pin_ptr<Byte> ptr = &data[0];
		return Rocket::Core::FontDatabase::LoadFontFace(ptr, data->Length, ToRocketString(family), (Rocket::Core::Font::Style) style, (Rocket::Core::Font::Weight) weight);
	}

	void Core::InitDebugger(Context^ context){
		Rocket::Debugger::Initialise(context->ContextPtr);
	}

	bool Core::DebugMode::get(){
		return Rocket::Debugger::IsVisible();
	}

	void Core::DebugMode::set(bool v){
		Rocket::Debugger::SetVisible(v);
	}
}