#pragma once

#include "LibRocketNet.h"
#include "Vector2.h"
#include "Constants.h"

using namespace System;

typedef Rocket::Core::Context RocketContext;

namespace LibRocketNet {

ref class RenderInterface;
ref class ElementDocument;
ref class Element;

public ref class Context
{
internal:
	Context(Rocket::Core::Context * ctx);

public:
	
	virtual ~Context();

	property String^ Name { String^ get(); }
	property Vector2i Dimensions { Vector2i get(); void set(Vector2i d); }
	bool Update();
	bool Render();

	ElementDocument^ CreateDocument(String^ tag);
	ElementDocument^ CreateDocument() { return CreateDocument("body"); }

	ElementDocument^ LoadDocument(String^ documentPath);
	ElementDocument^ LoadDocumentFromMemory(String^ str);

	void UnloadDocument(ElementDocument^ document);
	void UnloadAllDocuments();

	void AddMouseCursor(ElementDocument ^ cursorDocument);
	ElementDocument^ LoadMouseCursor(String^ documentPath);
	void UnloadMouseCursor(String^ cursorName);
	void UnloadAllMouseCursors();
	void ShowMouseCursor(bool show);
	bool SetMouseCursor(String^ cursor);
	
	ElementDocument^ GetDocument(String^ id);
	ElementDocument^ GetDocument(int index);

	property int NumDocuments {int get(); }
	property Element^ HoverElement{ Element^ get(); }
	property Element^ FocusElement{ Element^ get(); }
	property Element^ RootElement{ Element^ get(); }

	void PullDocumentToFront(ElementDocument^ document);
	void PushDocumentToBack(ElementDocument^ document);

	bool ProcessKeyDown(KeyIdentifiers key, KeyModifier modifiers);
	bool ProcessKeyUp(KeyIdentifiers key, KeyModifier modifiers);
	bool ProcessTextInput(unsigned short int word);
	void ProcessMouseMove(int x, int y, KeyModifier keyModifierState);
	void ProcessMouseButtonDown(int buttonIndex, KeyModifier keyModifierState);
	void ProcessMouseButtonUp(int buttonIndex, KeyModifier keyModifierState);
	void ProcessMouseWheel(int wheelDelta, KeyModifier keyModifierState);

	property RenderInterface^ RenderInterface { LibRocketNet::RenderInterface^ get(); }
	bool GetActiveClipRegion(Vector2i% origin, Vector2i% dimensions);
	void SetActiveClipRegion(Vector2i origin, Vector2i dimensions);

internal:
	Rocket::Core::Context * ContextPtr;
	LibRocketNet::RenderInterface ^ _renderInterface;
};


}