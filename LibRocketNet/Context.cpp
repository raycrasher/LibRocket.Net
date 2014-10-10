#include "stdafx.h"

#include "Rocket/Core/Context.h"

#include "Context.h"
#include "Util.h"
#include "Element.h"
#include "ElementDocument.h"

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
		return ElementDocument::Create(docPtr);
	}

	ElementDocument^ Context::LoadDocument(String^ documentPath) {
		auto docPtr = ContextPtr->LoadDocument(Util::ToRocketString(documentPath));
		if (!docPtr) return nullptr;
		return ElementDocument::Create(docPtr);
	}

	ElementDocument^ Context::LoadDocumentFromMemory(String^ str) {
		auto docPtr = ContextPtr->LoadDocumentFromMemory(Util::ToRocketString(str));
		if (!docPtr) return nullptr;
		return ElementDocument::Create(docPtr);
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

	ElementDocument^ Context::GetDocument(String^ id) {
		return ElementDocument::Create(ContextPtr->GetDocument(Util::ToRocketString(id)));
	}

	ElementDocument^ Context::GetDocument(int index) {
		return ElementDocument::Create(ContextPtr->GetDocument(index));
	}

	int Context::NumDocuments::get() {
		return ContextPtr->GetNumDocuments();
	}

	Element^ Context::HoverElement::get() {
		return Element::Create(ContextPtr->GetHoverElement());
	}

	Element^ Context::FocusElement::get(){
		return Element::Create(ContextPtr->GetFocusElement());
	}

	Element^ Context::RootElement::get(){
		return Element::Create(ContextPtr->GetRootElement());
	}

	void Context::PullDocumentToFront(ElementDocument^ document) {
		ContextPtr->PullDocumentToFront(document->DocumentPtr);
	}

	void Context::PushDocumentToBack(ElementDocument^ document) {
		ContextPtr->PushDocumentToBack(document->DocumentPtr);
	}

	bool Context::ProcessKeyDown(KeyIdentifiers key, KeyModifier modifiers) {
		ContextPtr->ProcessKeyDown((Rocket::Core::Input::KeyIdentifier)key, (int)modifiers);
	}

	bool Context::ProcessKeyUp(KeyIdentifiers key, KeyModifier modifiers){
		ContextPtr->ProcessKeyUp((Rocket::Core::Input::KeyIdentifier)key, (int)modifiers);
	}

	bool Context::ProcessTextInput(unsigned short int word) {
		ContextPtr->ProcessTextInput(word);
	}

	void Context::ProcessMouseMove(int x, int y, KeyModifier keyModifierState) {
		ContextPtr->ProcessMouseMove(x, y, (int)keyModifierState);
	}

	void Context::ProcessMouseButtonDown(int buttonIndex, KeyModifier keyModifierState) {
		ContextPtr->ProcessMouseButtonDown(buttonIndex, (int)keyModifierState);
	}

	void Context::ProcessMouseButtonUp(int buttonIndex, KeyModifier keyModifierState) {
		ContextPtr->ProcessMouseButtonUp(buttonIndex, (int)keyModifierState);
	}

	void Context::ProcessMouseWheel(int wheelDelta, KeyModifier keyModifierState) {
		ContextPtr->ProcessMouseWheel(wheelDelta, (int)keyModifierState);
	}

	RenderInterface^ Context::RenderInterface::get() {
		return _renderInterface;
	}

	bool Context::GetActiveClipRegion(Vector2i% origin, Vector2i% dimensions) {
		RVector2i o;
		RVector2i d;
		ContextPtr->GetActiveClipRegion(o, d);
		origin = Vector2i(o.x,o.y);
		dimensions = Vector2i(d.x, d.y);
	}

	bool Context::SetActiveClipRegion(Vector2i origin, Vector2i dimensions) {
		ContextPtr->SetActiveClipRegion(RVector2i(origin.X, origin.Y), RVector2i(dimensions.X, dimensions.Y));
	}
}