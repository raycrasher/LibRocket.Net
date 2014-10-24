#include "stdafx.h"
#include "Util.h"
#include "Element.h"
#include "ElementCollection.h"


#define CHECK_NULL_ELEM(_Def) if(!element) if(LibRocket::ThrowIfElementDestroyed) throw gcnew InvalidOperationException("Element already disposed."); else return _Def;
#define CHECK_NULL_ELEM_VOID() if(!element) if(LibRocket::ThrowIfElementDestroyed) throw gcnew InvalidOperationException("Element already disposed."); else return;

#define ELEMENT_ATTRIBUTE_NAME "___LIBROCKETNET_ELEMENT_GCROOT___"

namespace LibRocketNet {

RectangleF Element::Size::get(){
	CHECK_NULL_ELEM(RectangleF());
	auto box = element->GetBox();
	return RectangleF::FromLTRB(box.LEFT, box.TOP, box.RIGHT, box.BOTTOM);
}


Vector2f Element::RelativeOffset::get(){
	CHECK_NULL_ELEM(Vector2f());
	auto p=element->GetRelativeOffset();
	return Vector2f(p.x,p.y);
}

Vector2f Element::AbsoluteOffset::get(){
	CHECK_NULL_ELEM(Vector2f());
	auto p=element->GetAbsoluteOffset();
	return Vector2f(p.x,p.y);
}

Vector2f Element::AbsolutePosition::get(){
	CHECK_NULL_ELEM(Vector2f());
	return Vector2f(element->GetAbsoluteLeft(), element->GetAbsoluteTop());
}


void Element::SetAttribute(String^ attribute, int value) {
	CHECK_NULL_ELEM_VOID();
	element->SetAttribute(Util::ToRocketString(attribute), value);
}

void Element::SetAttribute(String^ attribute, float value) {
	CHECK_NULL_ELEM_VOID();
	element->SetAttribute(Util::ToRocketString(attribute), value);
}

void Element::SetAttribute(String^ attribute, String^ value) {
	CHECK_NULL_ELEM_VOID();
	element->SetAttribute(Util::ToRocketString(attribute), Util::ToRocketString(value));
}

Element::Element(RocketElement* elem){
	if(!elem) throw gcnew ArgumentNullException("Attempted to create a LibRocket element with a null raw pointer");
	auto root = Util::GetGcRoot(elem, ELEMENT_ATTRIBUTE_NAME);
	if(root) throw gcnew ArgumentException("Attempted to create a LibRocket element with a raw pointer with an existing Tag");
	element=elem;
	auto r=new gcroot<Element ^>();
	*r=this;
	SetGcRoot(elem,r);
	elem->AddReference();
	_children = gcnew ElementCollection(this);
}

Element::~Element(){
	element->RemoveReference();
	element=NULL;
	
}

bool Element::IsPseudoClassSet(String^ pseudoclass)
{
	CHECK_NULL_ELEM(false);
	return element->IsPseudoClassSet(Util::ToRocketString(pseudoclass));
}

Element^ Element::Create(RocketElement* elem){
	if(!elem) return nullptr;
	auto root=GetGcRoot(elem);
	if(!root){
		return gcnew Element(elem);
	} else {
		return *root;
	}
}

template<class _Handler, class _Args>
void AddHandler(Action<_Args^>^ invoker, Rocket::Core::Element *elem, const char *eventName) {
	auto handler = new _Handler();
	handler->Invoker = invoker;
	elem->AddEventListener(eventName, handler);
}


void Element::InitHandlers(){
	CHECK_NULL_ELEM_VOID();

	AddHandler<RocketEventListener<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventShow), element, "show");

	AddHandler<RocketEventListener<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventShow), element, "show");
	AddHandler<RocketEventListener<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventHide), element, "hide");
	AddHandler<RocketEventListener<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventResize), element, "resize");
	AddHandler<RocketEventListener<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventScroll), element, "scroll");
	AddHandler<RocketEventListener<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventFocus), element, "focus");
	AddHandler<RocketEventListener<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventBlur), element, "blur");

	AddHandler<RocketEventListener<KeyboardEventArgs>, KeyboardEventArgs>(gcnew System::Action<KeyboardEventArgs^>(this, &Element::InvokeEventKeyDown), element, "keydown");
	AddHandler<RocketEventListener<KeyboardEventArgs>, KeyboardEventArgs>(gcnew System::Action<KeyboardEventArgs^>(this, &Element::InvokeEventKeyUp), element, "keyup");

	AddHandler<RocketEventListener<TextInputEventArgs>, TextInputEventArgs>(gcnew System::Action<TextInputEventArgs^>(this, &Element::InvokeEventTextInput), element, "textinput");


	AddHandler<RocketEventListener<MouseEventArgs>, MouseEventArgs>(gcnew System::Action<MouseEventArgs^>(this, &Element::InvokeEventClick), element, "click");
	AddHandler<RocketEventListener<MouseEventArgs>, MouseEventArgs>(gcnew System::Action<MouseEventArgs^>(this, &Element::InvokeEventDoubleClick), element, "dblclick");
	AddHandler<RocketEventListener<MouseEventArgs>, MouseEventArgs>(gcnew System::Action<MouseEventArgs^>(this, &Element::InvokeEventMouseOver), element, "mouseover");
	AddHandler<RocketEventListener<MouseEventArgs>, MouseEventArgs>(gcnew System::Action<MouseEventArgs^>(this, &Element::InvokeEventMouseOut), element, "mouseout");
	AddHandler<RocketEventListener<MouseEventArgs>, MouseEventArgs>(gcnew System::Action<MouseEventArgs^>(this, &Element::InvokeEventMouseMove), element, "mousemove");
	AddHandler<RocketEventListener<MouseEventArgs>, MouseEventArgs>(gcnew System::Action<MouseEventArgs^>(this, &Element::InvokeEventMouseUp), element, "mouseup");
	AddHandler<RocketEventListener<MouseEventArgs>, MouseEventArgs>(gcnew System::Action<MouseEventArgs^>(this, &Element::InvokeEventMouseDown), element, "mousedown");
	AddHandler<RocketEventListener<MouseEventArgs>, MouseEventArgs>(gcnew System::Action<MouseEventArgs^>(this, &Element::InvokeEventMouseScroll), element, "mousescroll");

	AddHandler<RocketEventListener<DragEventArgs>, DragEventArgs>(gcnew System::Action<DragEventArgs^>(this, &Element::InvokeEventDragStart), element, "dragstart");
	AddHandler<RocketEventListener<DragEventArgs>, DragEventArgs>(gcnew System::Action<DragEventArgs^>(this, &Element::InvokeEventDragEnd), element, "dragend");
	AddHandler<RocketEventListener<DragEventArgs>, DragEventArgs>(gcnew System::Action<DragEventArgs^>(this, &Element::InvokeEventDrag), element, "drag");

	AddHandler<RocketEventListener<FormSubmitEventArgs>, FormSubmitEventArgs>(gcnew System::Action<FormSubmitEventArgs^>(this, &Element::InvokeEventFormSubmit), element, "submit");

	AddHandler<RocketEventListener<FormControlChangeEventArgs>, FormControlChangeEventArgs>(gcnew System::Action<FormControlChangeEventArgs^>(this, &Element::InvokeEventFormControlChange), element, "change");

	AddHandler<RocketEventListener<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventLoad), element, "load");
	AddHandler<RocketEventListener<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventUnload), element, "unload");

	AddHandler<RocketEventListener<HandleEventArgs>, HandleEventArgs>(gcnew System::Action<HandleEventArgs^>(this, &Element::InvokeEventHandleDrag), element, "handledrag");

	AddHandler<RocketEventListener<DataGridAddColumnEventArgs>, DataGridAddColumnEventArgs>(gcnew System::Action<DataGridAddColumnEventArgs^>(this, &Element::InvokeEventColumnAdd), element, "columnadd");
	AddHandler<RocketEventListener<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventRowUpdate), element, "rowupdate");
	AddHandler<RocketEventListener<DataGridRowEventArgs>, DataGridRowEventArgs>(gcnew System::Action<DataGridRowEventArgs^>(this, &Element::InvokeEventRowAdd), element, "rowadd");
	AddHandler<RocketEventListener<DataGridRowEventArgs>, DataGridRowEventArgs>(gcnew System::Action<DataGridRowEventArgs^>(this, &Element::InvokeEventRowRemove), element, "rowremove");

	AddHandler<RocketEventListener<TabChangeEventArgs>, TabChangeEventArgs>(gcnew System::Action<TabChangeEventArgs^>(this, &Element::InvokeEventTabChange), element, "tabchange");
}

}
