#include "stdafx.h"
#include <gcroot.h>
#include "Rocket/Core.h"
#include "Util.h"
#include "Element.h"
#include "ElementCollection.h"


#define CHECK_NULL_ELEM(_Def) if(!element) if(LibRocket::ThrowIfElementDestroyed) throw gcnew InvalidOperationException("Element already disposed."); else return _Def;
#define CHECK_NULL_ELEM_VOID() if(!element) if(LibRocket::ThrowIfElementDestroyed) throw gcnew InvalidOperationException("Element already disposed."); else return;

#define ELEMENT_ATTRIBUTE_NAME "___LIBROCKETNET_GCROOT___"

namespace LibRocketNet {

gcroot<Element^>* GetGcRoot(RocketElement* elem){
	if(!elem) throw gcnew ArgumentNullException();
	return (gcroot<Element^>*) elem->GetAttribute<void *>(ELEMENT_ATTRIBUTE_NAME,NULL);
}

void SetGcRoot(RocketElement* elem, gcroot<Element^>* r){
	if(!elem || !r) throw gcnew ArgumentNullException();
	elem->SetAttribute(ELEMENT_ATTRIBUTE_NAME,(void *)r);
}

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
	auto root=GetGcRoot(elem);
	if(root) throw gcnew ArgumentException("Attempted to create a LibRocket element with a raw pointer with an existing Tag");
	element=elem;
	auto r=new gcroot<Element ^>();
	*r=this;
	SetGcRoot(elem,r);
	_children = gcnew ElementCollection(this);
}

Element::~Element(){
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



void Element::InitHandlers(){
	CHECK_NULL_ELEM_VOID();

	ELEMENT_HANDLE_EVENT(ElementEventHandler, Show, "show");
	ELEMENT_HANDLE_EVENT(ElementEventHandler, Hide, "hide");
	ELEMENT_HANDLE_EVENT(ElementEventHandler, Resize, "resize");
	ELEMENT_HANDLE_EVENT(ElementEventHandler, Scroll, "scroll");
	ELEMENT_HANDLE_EVENT(ElementEventHandler, Focus, "focus");
	ELEMENT_HANDLE_EVENT(ElementEventHandler, Blur, "blur");

	ELEMENT_HANDLE_EVENT(KeyboardEventHandler,KeyDown, "keydown");
	ELEMENT_HANDLE_EVENT(KeyboardEventHandler,KeyUp, "keyup");

	ELEMENT_HANDLE_EVENT(TextInputEventHandler,TextInput, "textinput");


	ELEMENT_HANDLE_EVENT(MouseEventHandler,Click, "click");
	ELEMENT_HANDLE_EVENT(MouseEventHandler,DoubleClick, "dblclick");
	ELEMENT_HANDLE_EVENT(MouseEventHandler,MouseOver, "mouseover");
	ELEMENT_HANDLE_EVENT(MouseEventHandler,MouseOut, "mouseout");
	ELEMENT_HANDLE_EVENT(MouseEventHandler,MouseMove, "mousemove");
	ELEMENT_HANDLE_EVENT(MouseEventHandler,MouseUp, "mouseup");
	ELEMENT_HANDLE_EVENT(MouseEventHandler,MouseDown, "mousedown");
	ELEMENT_HANDLE_EVENT(MouseEventHandler,MouseScroll, "mousescroll");

	ELEMENT_HANDLE_EVENT(DragEventHandler,DragStart, "dragstart");
	ELEMENT_HANDLE_EVENT(DragEventHandler,DragEnd, "dragend");
	ELEMENT_HANDLE_EVENT(DragEventHandler,Drag, "drag");

	ELEMENT_HANDLE_EVENT(FormSubmitEventHandler,FormSubmit, "submit");

	ELEMENT_HANDLE_EVENT(FormControlChangeEventHandler,FormControlChange, "change");

	ELEMENT_HANDLE_EVENT(ElementEventHandler,Load, "load");
	ELEMENT_HANDLE_EVENT(ElementEventHandler,Unload, "unload");

	ELEMENT_HANDLE_EVENT(HandleEventHandler,HandleDrag,"handledrag");

	ELEMENT_HANDLE_EVENT(DataGridAddColumnEventHandler,ColumnAdd,"columnadd");
	ELEMENT_HANDLE_EVENT(ElementEventHandler,RowUpdate,"rowupdate");
	ELEMENT_HANDLE_EVENT(DataGridRowEventHandler,RowAdd,"rowadd");
	ELEMENT_HANDLE_EVENT(DataGridRowEventHandler,RowRemove,"rowremove");

	ELEMENT_HANDLE_EVENT(TabChangeEventHandler,TabChange,"tabchange");
}

}
