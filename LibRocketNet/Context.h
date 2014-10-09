#pragma once

#include "LibRocketNet.h"
#include "Vector2.h"
#include "ElementDocument.h"
#include "Constants.h"

using namespace System;

ROCKET_FORWARD_DECLARE(class Context);
typedef Rocket::Core::Context RocketContext;

namespace LibRocketNet {

ref class RenderInterface;

public ref class Context
{
public:
	Context();
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
	bool SetMouseCursor(bool show);
	
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
	void ProcessMouseMove(int x, int y, int keyModifierState);
	void ProcessMouseButtonDown(int buttonIndex, int keyModifierState);
	void ProcessMouseButtonUp(int buttonIndex, int keyModifierState);
	void ProcessMouseWheel(int wheelDelta, int keyModifierState);

	property RenderInterface^ RenderInterface { LibRocketNet::RenderInterface^ get(); }
	bool GetActiveClipRegion(Vector2i% origin, Vector2i% dimensions);
	bool SetActiveClipRegion(Vector2i origin, Vector2i dimensions);

internal:
	RocketContext *_context;

};


}