#pragma once

#include "Constants.h"

using namespace System;


namespace LibRocketNet {

public enum class EventPhase { Unknown, Capture, Target, Bubble };

ref class Element;


public ref class ElementEventArgs: public EventArgs
{
internal:
	ElementEventArgs(Rocket::Core::Event* evt);
	Rocket::Core::Event* eventPtr;
public:

	
	EventPhase Phase;
	Element^ CurrentElement;
	Element^ TargetElement;
	String^ Type;

	void StopPropagation();

internal:

};


//////////////////////////////////////////////////////

public ref class KeyboardEventArgs: public ElementEventArgs {
internal:
	KeyboardEventArgs(Rocket::Core::Event *evt);
public:
	KeyIdentifiers Key;
	bool ControlKeyPressed;
	bool ShiftKeyPressed;
	bool AltKeyPressed;
	bool MetaKeyPressed;
	bool CapsLockKeyPressed;
	bool NumLockKeyPressed;
	bool ScrollLockKeyPressed;
};

//////////////////////////////////////////////////////

public ref class TextInputEventArgs: public ElementEventArgs {
internal:
	TextInputEventArgs(Rocket::Core::Event *evt);
public:
	long Data;
};

//////////////////////////////////////////////////////

public ref class MouseEventArgs: public ElementEventArgs {
internal:
	MouseEventArgs(Rocket::Core::Event *evt);
public:
	int X;
	int Y;
	int Button;
	int WheelDelta;
};


//////////////////////////////////////////////////////

public ref class DragEventArgs: public ElementEventArgs {
internal:
	DragEventArgs(Rocket::Core::Event *evt);
public:
	int X;
	int Y;
	Element^ DragElement;
	
};

//////////////////////////////////////////////////////

public ref class FormSubmitEventArgs: public ElementEventArgs {
internal:
	FormSubmitEventArgs(Rocket::Core::Event *evt) : ElementEventArgs(evt) {}
public:
	String^ GetField(String^ field);
};

//////////////////////////////////////////////////////

public ref class FormControlChangeEventArgs: public ElementEventArgs {
internal:
	FormControlChangeEventArgs(Rocket::Core::Event *evt);
public:
	String^ Value;
};

//////////////////////////////////////////////////////

public ref class HandleEventArgs: public ElementEventArgs {
internal:
	HandleEventArgs(Rocket::Core::Event *evt);
public:
	int X, Y;
};

//////////////////////////////////////////////////////

public ref class DataGridAddColumnEventArgs: public ElementEventArgs {
internal:
	DataGridAddColumnEventArgs(Rocket::Core::Event *evt);
public:
	int Index;
};

//////////////////////////////////////////////////////

public ref class DataGridRowEventArgs: public ElementEventArgs {
internal:
	DataGridRowEventArgs(Rocket::Core::Event *evt);
public:
	int FirstRowIndex, RowCount;
};

//////////////////////////////////////////////////////

public ref class TabChangeEventArgs: public ElementEventArgs {
internal:
	TabChangeEventArgs(Rocket::Core::Event *evt);
public:
	int TabIndex;
};

//////////////////////////////////////////////////////////////////////

public ref class ScriptEventArgs : public ElementEventArgs {
internal:
	ScriptEventArgs(Rocket::Core::Event *evt);
public:
	String^ Script;
};




//////////////////////////////////////////////////////////////////////

template<class Args>
class RocketEvent : public Rocket::Core::EventListener {

public:
	gcroot<Action<Args^>^> Invoker;
	virtual void ProcessEvent(Rocket::Core::Event &evt) {
		Action<Args^>^ invoker = Invoker;
		invoker(gcnew Args(&evt));
	}
	virtual void OnDetach(Rocket::Core::Element *elem) { delete this; }
};



}