#include "stdafx.h"
#include "Context.h"
#include "Util.h"
#include "Rocket/Core/Context.h"

namespace LibRocketNet {

	Context::Context(Rocket::Core::Context * ctx) {
		ContextPtr = ctx;
		ContextPtr->AddReference();
	}

	Context::~Context() {
		ContextPtr->RemoveReference();
	}

	String^ Context::Name::get() {
		return Util::ToNetString(ContextPtr->GetName());
	}

	Vector2i Context::Dimensions::get() {
		return Vector2i(ContextPtr->GetDimensions());
	}

	void Context::Dimensions::set(Vector2i d){
		ContextPtr->SetDimensions(Rocket::Core::Vector2i(d.X, d.Y));
	}

	bool Context::Update() {
		ContextPtr->Update();
	}

	bool Context::Render() {
		ContextPtr->Render();
	}

	ElementDocument^ Context::CreateDocument(String^ tag) {
		auto docPtr = ContextPtr->CreateDocument(Util::ToRocketString(tag));
		if (!docPtr) return nullptr;
		return gcnew ElementDocument(docPtr);
	}

	ElementDocument^ Context::LoadDocument(String^ documentPath) {
		auto docPtr = ContextPtr->LoadDocument(Util::ToRocketString(documentPath));
		if (!docPtr) return nullptr;
		return gcnew ElementDocument(docPtr);
	}

	ElementDocument^ Context::LoadDocumentFromMemory(String^ str) {
		auto docPtr = ContextPtr->LoadDocumentFromMemory(Util::ToRocketString(str));
		if (!docPtr) return nullptr;
		return gcnew ElementDocument(docPtr);
	}

	void Context::UnloadDocument(ElementDocument^ document) {
		ContextPtr->UnloadDocument(document->DocumentPtr);
	}

	void Context::UnloadAllDocuments() {
		ContextPtr->UnloadAllDocuments();
	}

	void Context::AddMouseCursor(ElementDocument ^ cursorDocument) {
		ContextPtr->AddMouseCursor(cursorDocument->DocumentPtr);
	}

	ElementDocument^ Context::LoadMouseCursor(String^ documentPath) {
		auto docPtr = ContextPtr->LoadMouseCursor(Util::ToRocketString(documentPath));
		if (!docPtr) return nullptr;
		return ElementDocument::Create(docPtr);
	}


	void Context::UnloadMouseCursor(String^ cursorName) {
		ContextPtr->UnloadMouseCursor(Util::ToRocketString(cursorName));
	}

	void Context::UnloadAllMouseCursors() {
		ContextPtr->UnloadAllMouseCursors(); 
	}

	void Context::ShowMouseCursor(bool show) {
		ContextPtr->ShowMouseCursor(show);
	}

	bool Context::SetMouseCursor(String^ cursor) {
		return ContextPtr->SetMouseCursor(Util::ToRocketString(cursor));
	}

	ElementDocument^ GetDocument(String^ id) {
		
	}

	ElementDocument^ GetDocument(int index);

	int Context::NumDocuments::get() {
		return ContextPtr->GetNumDocuments();
	}

	property Element^ HoverElement{ Element^ get(); }
	property Element^ FocusElement{ Element^ get(); }
	property Element^ RootElement{ Element^ get(); }

	void PullDocumentToFront(ElementDocument^ document);
	void PushDocumentToBack(ElementDocument^ document);

	bool ProcessKeyDown(KeyIdentifiers key, KeyModifier modifiers);
	bool ProcessKeyUp(KeyIdentifiers key, KeyModifier modifiers);
	bool ProcessTextInput(unsigned short int word);
	void ProcessMouseMove(int x, int y, int keyModifierState);
	void ProcessMouseButtonDown(int buttonIndex, int keyModifierState);
	void ProcessMouseButtonUp(int buttonIndex, int keyModifierState);
	void ProcessMouseWheel(int wheelDelta, int keyModifierState);

	property RenderInterface^ RenderInterface { LibRocketNet::RenderInterface^ get(); }
	bool GetActiveClipRegion(Vector2i% origin, Vector2i% dimensions);
	bool SetActiveClipRegion(Vector2i origin, Vector2i dimensions);
}