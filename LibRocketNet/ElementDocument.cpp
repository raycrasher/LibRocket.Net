#include "stdafx.h"
#include "ElementDocument.h"
#include "Rocket/Core/Element.h"
#include "Rocket/Core/ElementDocument.h"
#include "Util.h"
#include "Context.h"

using namespace System;
using namespace LibRocketNet::Util;

namespace LibRocketNet {

	ElementDocument::ElementDocument(Rocket::Core::ElementDocument* doc) : Element(doc) {
		DocumentPtr = doc;

	}

	ElementDocument^ ElementDocument::Create(Rocket::Core::ElementDocument* doc) 
	{
		if (!doc) return nullptr;
		auto root = Util::GetGcRoot(doc, "");
		if (!root){
			return gcnew ElementDocument(doc);
		}
		else {
			Element^ elem = *root;
			if (Util::IsInstance<ElementDocument^>(elem)) return dynamic_cast<ElementDocument^>(elem);
			else return gcnew ElementDocument(doc);
		}
	}

	LibRocketNet::Context^ ElementDocument::Context::get(){
		return LibRocketNet::Context::Contexts[IntPtr((void *)DocumentPtr->GetContext())];
	}

	String^ ElementDocument::Title::get(){
		return ToNetString(DocumentPtr->GetTitle());
	} 

	void ElementDocument::Title::set(String^ s) {
		DocumentPtr->SetTitle(ToRocketString(s));
	}

	String^ ElementDocument::SourceUrl::get() {
		return ToNetString(DocumentPtr->GetSourceURL());
	}

	void ElementDocument::PullToFront() {
		DocumentPtr->PullToFront();
	}

	void ElementDocument::PushToBack() {
		DocumentPtr->PushToBack();
	}

	void ElementDocument::Show(FocusFlags focus) {
		DocumentPtr->Show((int)focus);
	}

	
	void ElementDocument::Hide() {
		DocumentPtr->Hide();
	}

	void ElementDocument::Close(){
		DocumentPtr->Close();
	}

	Element^ ElementDocument::CreateElement(String^ name) {
		return Element::Create(DocumentPtr->CreateElement(ToRocketString(name)));
	}

	Element^ ElementDocument::CreateTextNode(String^ text) {
		return Element::Create(DocumentPtr->CreateTextNode(ToRocketString(text)));
	}

	bool ElementDocument::IsModal::get(){
		return DocumentPtr->IsModal();
	}

	void ElementDocument::UpdateLayout() {
		DocumentPtr->UpdateLayout();
	}

	void ElementDocument::UpdatePosition() {
		DocumentPtr->UpdatePosition();
	}
}