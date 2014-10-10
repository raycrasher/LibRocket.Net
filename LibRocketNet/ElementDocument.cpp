#include "stdafx.h"
#include "ElementDocument.h"
#include "Rocket/Core/Element.h"
#include "Rocket/Core/ElementDocument.h"
#include "Util.h"


namespace LibRocketNet {

	ElementDocument::ElementDocument(Rocket::Core::ElementDocument* doc) : Element(doc) {
		DocumentPtr = doc;

	}

	ElementDocument^ ElementDocument::Create(Rocket::Core::ElementDocument* doc) 
	{
		if (!doc) return nullptr;
		auto root = GetGcRoot(doc);
		if (!root){
			return gcnew ElementDocument(doc);
		}
		else {
			Element^ elem = *root;
			if (Util::IsInstance<ElementDocument^>(elem)) return dynamic_cast<ElementDocument^>(elem);
			else return gcnew ElementDocument(doc);
		}
	}
}