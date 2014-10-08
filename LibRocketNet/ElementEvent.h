#pragma once

#include <gcroot.h>
#include "Element.h"
#include "Constants.h"

namespace LibRocketNet {

public enum class EventPhase { Unknown, Capture, Target, Bubble };

ref class Element;


public ref class ElementEventArgs: public EventArgs
{
internal:
	ElementEventArgs(RocketEvent *evt);
	RocketEvent * eventPtr;
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
	KeyboardEventArgs(RocketEvent *evt);
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
	TextInputEventArgs(RocketEvent *evt);
public:
	long Data;
};

//////////////////////////////////////////////////////

public ref class MouseEventArgs: public ElementEventArgs {
internal:
	MouseEventArgs(RocketEvent *evt);
public:
	float X;
	float Y;
	int Button;
	int WheelDelta;
};


//////////////////////////////////////////////////////

public ref class DragEventArgs: public ElementEventArgs {
internal:
	DragEventArgs(RocketEvent *evt);
public:
	float X;
	float Y;
	Element^ DragElement;
	
};

//////////////////////////////////////////////////////

public ref class FormSubmitEventArgs: public ElementEventArgs {
internal:
	FormSubmitEventArgs(RocketEvent *evt) : ElementEventArgs(evt) {}
public:
	String^ GetField(String^ field);
};

//////////////////////////////////////////////////////

public ref class FormControlChangeEventArgs: public ElementEventArgs {
internal:
	FormControlChangeEventArgs(RocketEvent *evt);
public:
	String^ Value;
};

//////////////////////////////////////////////////////

public ref class HandleEventArgs: public ElementEventArgs {
internal:
	HandleEventArgs(RocketEvent *evt);
public:
	float X, Y;
};

//////////////////////////////////////////////////////

public ref class DataGridAddColumnEventArgs: public ElementEventArgs {
internal:
	DataGridAddColumnEventArgs(RocketEvent *evt);
public:
	int Index;
};

//////////////////////////////////////////////////////

public ref class DataGridRowEventArgs: public ElementEventArgs {
internal:
	DataGridRowEventArgs(RocketEvent *evt);
public:
	int FirstRowIndex, RowCount;
};

//////////////////////////////////////////////////////

public ref class TabChangeEventArgs: public ElementEventArgs {
internal:
	TabChangeEventArgs(RocketEvent *evt);
public:
	int TabIndex;
};







//////////////////////////////////////////////////////////////////////

#define ELEMENT_ADD_HANDLER_DECLARATION(Handler, Args)   \
class Handler : public Rocket::Core::EventListener		\
{       \
public:   \
	gcroot<EventHandler<Args^>^> Handlers;    \
	virtual void ProcessEvent(RocketEvent &evt); \
	virtual void OnDetach(RocketElement* element) { delete this; } \
};   \


ELEMENT_ADD_HANDLER_DECLARATION(ElementEventHandler,ElementEventArgs);
ELEMENT_ADD_HANDLER_DECLARATION(KeyboardEventHandler,KeyboardEventArgs);
ELEMENT_ADD_HANDLER_DECLARATION(TextInputEventHandler,TextInputEventArgs);
ELEMENT_ADD_HANDLER_DECLARATION(MouseEventHandler,MouseEventArgs);
ELEMENT_ADD_HANDLER_DECLARATION(DragEventHandler,DragEventArgs);
ELEMENT_ADD_HANDLER_DECLARATION(FormSubmitEventHandler,FormSubmitEventArgs);
ELEMENT_ADD_HANDLER_DECLARATION(FormControlChangeEventHandler,FormControlChangeEventArgs);
ELEMENT_ADD_HANDLER_DECLARATION(HandleEventHandler,HandleEventArgs);
ELEMENT_ADD_HANDLER_DECLARATION(DataGridAddColumnEventHandler,DataGridAddColumnEventArgs);
ELEMENT_ADD_HANDLER_DECLARATION(DataGridRowEventHandler,DataGridRowEventArgs);
ELEMENT_ADD_HANDLER_DECLARATION(TabChangeEventHandler,TabChangeEventArgs);


#undef ELEMENT_ADD_HANDLER_DECLARATION


////////////////////////////////////////////////////////////////////
// add handlers


}