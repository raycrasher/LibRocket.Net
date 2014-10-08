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

Rectangle Element::Size::get(){
	CHECK_NULL_ELEM(Rectangle());
	auto box = element->GetBox();
	return Rectangle::FromLTRB(box.LEFT, box.TOP, box.RIGHT, box.BOTTOM);
}


PointF Element::RelativeOffset::get(){
	CHECK_NULL_ELEM(PointF());
	auto p=element->GetRelativeOffset();
	return PointF(p.x,p.y);
}

PointF Element::AbsoluteOffset::get(){
	CHECK_NULL_ELEM(PointF());
	auto p=element->GetAbsoluteOffset();
	return PointF(p.x,p.y);
}

PointF Element::AbsolutePosition::get(){
	CHECK_NULL_ELEM(PointF());
	return PointF(element->GetAbsoluteLeft(), element->GetAbsoluteTop());
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


	ELEMENT_HANDLE_EVENT(MouseEventHandler,Click, "mouse_click");
	ELEMENT_HANDLE_EVENT(MouseEventHandler,DoubleClick, "mouse_dblclick");
	ELEMENT_HANDLE_EVENT(MouseEventHandler,MouseOver, "mouse_hover");
	ELEMENT_HANDLE_EVENT(MouseEventHandler,MouseOut, "mouse_out");
	ELEMENT_HANDLE_EVENT(MouseEventHandler,MouseMove, "mouse_move");
	ELEMENT_HANDLE_EVENT(MouseEventHandler,MouseUp, "mouse_up");
	ELEMENT_HANDLE_EVENT(MouseEventHandler,MouseDown, "mouse_down");
	ELEMENT_HANDLE_EVENT(MouseEventHandler,MouseScroll, "mouse_wheeldelta");

	ELEMENT_HANDLE_EVENT(DragEventHandler,DragStart, "drag_start");
	ELEMENT_HANDLE_EVENT(DragEventHandler,DragEnd, "drag_end");
	ELEMENT_HANDLE_EVENT(DragEventHandler,Drag, "drag");

	ELEMENT_HANDLE_EVENT(FormSubmitEventHandler,FormSubmit, "form_submit");

	ELEMENT_HANDLE_EVENT(FormControlChangeEventHandler,FormControlChange, "form_change");

	ELEMENT_HANDLE_EVENT(ElementEventHandler,Load, "load");
	ELEMENT_HANDLE_EVENT(ElementEventHandler,Unload, "unload");

	ELEMENT_HANDLE_EVENT(HandleEventHandler,HandleDrag,"handle_drag");

	ELEMENT_HANDLE_EVENT(DataGridAddColumnEventHandler,ColumnAdd,"column_add");
	ELEMENT_HANDLE_EVENT(ElementEventHandler,RowUpdate,"row_update");
	ELEMENT_HANDLE_EVENT(DataGridRowEventHandler,RowAdd,"row_add");
	ELEMENT_HANDLE_EVENT(DataGridRowEventHandler,RowRemove,"row_remove");

	ELEMENT_HANDLE_EVENT(TabChangeEventHandler,TabChange,"tab_change");
}

}
