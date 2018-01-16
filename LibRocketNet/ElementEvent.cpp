#include "stdafx.h"
#include "Rocket/Core/String.h"
#include "ElementEvent.h"
#include "Element.h"
#include "Rocket/Core/Event.h"
#include "Util.h"

namespace LibRocketNet {
	ElementEventArgs::ElementEventArgs(Rocket::Core::Event *evt)
	{
		eventPtr = evt;
		Phase = (EventPhase)eventPtr->GetPhase();
		Type = Util::ToNetString(eventPtr->GetType());
		CurrentElement = Element::Create(eventPtr->GetCurrentElement());
		TargetElement = Element::Create(eventPtr->GetTargetElement());
	}

	void ElementEventArgs::StopPropagation(){
		eventPtr->StopPropagation();
	}

	//////////////////////////////////////////////////////

	KeyboardEventArgs::KeyboardEventArgs(Rocket::Core::Event *evt) : ElementEventArgs(evt)
	{
		Key = (KeyIdentifiers)eventPtr->GetParameter<int>("key_identifier", 0);
		ControlKeyPressed = eventPtr->GetParameter<bool>("ctrl_key", 0);
		ShiftKeyPressed = eventPtr->GetParameter<bool>("shift_key", false);
		MetaKeyPressed = eventPtr->GetParameter<bool>("meta_key", false);
		AltKeyPressed = eventPtr->GetParameter<bool>("alt_key", false);
		CapsLockKeyPressed = eventPtr->GetParameter<bool>("caps_lock_key", false);
		NumLockKeyPressed = eventPtr->GetParameter<bool>("num_lock_key", false);
		ScrollLockKeyPressed = eventPtr->GetParameter<bool>("scroll_lock_key", false);
	}

	//////////////////////////////////////////////////////

	TextInputEventArgs::TextInputEventArgs(Rocket::Core::Event *evt) : ElementEventArgs(evt){
		Data = evt->GetParameter<int>("data", 0);
	}


	//////////////////////////////////////////////////////

	MouseEventArgs::MouseEventArgs(Rocket::Core::Event *evt) : ElementEventArgs(evt){
		X = evt->GetParameter<int>("mouse_x", 0);
		Y = evt->GetParameter<int>("mouse_y", 0);
		Button = evt->GetParameter<int>("button", 0);
		WheelDelta = evt->GetParameter<int>("wheel_delta", 0);
	}

	//////////////////////////////////////////////////////

	DragEventArgs::DragEventArgs(Rocket::Core::Event *evt) : ElementEventArgs(evt){
		X = evt->GetParameter<int>("mouse_x", 0);
		Y = evt->GetParameter<int>("mouse_y", 0);
		DragElement = Element::Create(evt->GetParameter<Rocket::Core::Element *>("drag_element", 0));
	}

	//////////////////////////////////////////////////////

	String^ FormSubmitEventArgs::GetField(String^ name){
		auto s = eventPtr->GetParameter<Rocket::Core::String>(Util::ToRocketString(name), "");
		if (s.Length() <= 0) return nullptr;
		return Util::ToNetString(s);
	}


	//////////////////////////////////////////////////////

	FormControlChangeEventArgs::FormControlChangeEventArgs(Rocket::Core::Event *evt) : ElementEventArgs(evt){
		Value = Util::ToNetString(evt->GetParameter<Rocket::Core::String>("value", ""));
	}


	//////////////////////////////////////////////////////

	HandleEventArgs::HandleEventArgs(Rocket::Core::Event *evt) : ElementEventArgs(evt){
		X = evt->GetParameter<int>("handle_x", 0);
		Y = evt->GetParameter<int>("handle_y", 0);
	}


	//////////////////////////////////////////////////////

	DataGridAddColumnEventArgs::DataGridAddColumnEventArgs(Rocket::Core::Event *evt) : ElementEventArgs(evt){
		Index = evt->GetParameter<int>("index", 0);
	}

	//////////////////////////////////////////////////////

	DataGridRowEventArgs::DataGridRowEventArgs(Rocket::Core::Event *evt) : ElementEventArgs(evt){
		bool add = true;
		auto t = evt->GetType();
		if (t == "rowremove") add = false;

		FirstRowIndex = evt->GetParameter<int>(add ? "first_row_added" : "first_row_removed", 0);
		RowCount = evt->GetParameter<int>(add ? "num_rows_added" : "num_rows_removed", 0);
	}


	//////////////////////////////////////////////////////

	TabChangeEventArgs::TabChangeEventArgs(Rocket::Core::Event *evt) : ElementEventArgs(evt){
		TabIndex = evt->GetParameter<int>("tab_index", 0);
	}

	
}