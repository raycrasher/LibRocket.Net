#include "stdafx.h"
#include "Util.h"
#include "Element.h"
#include "ElementCollection.h"
#include "Context.h"
#include "Rectangle.h"
#include "ElementDocument.h"
#include "Core.h"

#define CHECK_NULL_ELEM(_Def) if(!element) if(LibRocket::ThrowIfElementDestroyed) throw gcnew InvalidOperationException("Element already disposed."); else return _Def;
#define CHECK_NULL_ELEM_VOID() if(!element) if(LibRocket::ThrowIfElementDestroyed) throw gcnew InvalidOperationException("Element already disposed."); else return;



using namespace LibRocketNet::Util;

namespace LibRocketNet {


Element::Element( String^ tagName ) {
	auto s = ToRocketString(tagName);
	Construct(Rocket::Core::Factory::InstanceElement(NULL, s, s, Rocket::Core::XMLAttributes()));
}

Element::Element(Element^ parent, String^ tagName){
	if (parent == nullptr || parent->element == NULL) throw gcnew ArgumentNullException("parent");
	auto s = ToRocketString(tagName);
	Construct(Rocket::Core::Factory::InstanceElement(parent->element, s, s, Rocket::Core::XMLAttributes()));
}

Element::Element(Element^ parent, String^ instancer, String^ tagName){
	if (parent == nullptr || parent->element == NULL) throw gcnew ArgumentNullException("parent");
	auto s = ToRocketString(tagName);
	auto i = ToRocketString(instancer);
	Construct(Rocket::Core::Factory::InstanceElement(parent->element, i, s, Rocket::Core::XMLAttributes()));
}

Element::Element(String^ instancer, String^ tagName){
	auto s = ToRocketString(tagName);
	auto i = ToRocketString(instancer);
	Construct(Rocket::Core::Factory::InstanceElement(NULL, i, s, Rocket::Core::XMLAttributes()));
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


int Element::GetAttributeInt(String^ attribute, int defaultVal) {
	return element->GetAttribute(ToRocketString(attribute), defaultVal);
}

float Element::GetAttributeFloat(String^ attribute, float defaultVal) {
	return element->GetAttribute(ToRocketString(attribute), defaultVal);
}

String^ Element::GetAttributeString(String^ attribute, String^ defaultVal) {
	return ToNetString( element->GetAttribute(ToRocketString(attribute), ToRocketString( defaultVal)) );
}

IntPtr Element::GetAttributePtr(String^ attribute, IntPtr defaultVal) {
	return IntPtr(element->GetAttribute(ToRocketString(attribute), (void *)NULL));
}

bool Element::HasAttribute(String^ name) {
	return element->HasAttribute(ToRocketString(name));
}

void Element::SetAttributes(Generic::Dictionary<String^, Object^> attributes) {

	Rocket::Core::ElementAttributes attr;

	for each (auto v in attributes)
	{
		Object^ value = v.Value;
		if (value->GetType() == float::typeid) {
			float f = (float)value;
			attr.Set(ToRocketString(v.Key), f);
		}
		else if (value->GetType() == int::typeid) {
			int i = (int)value;
			attr.Set(ToRocketString(v.Key), i);
		}
		else if (value->GetType() == String::typeid) {
			attr.Set(ToRocketString(v.Key), ToRocketString((String^)value));
		}
		else if (value->GetType() == IntPtr::typeid) {
			attr.Set(ToRocketString(v.Key), ((IntPtr)value).ToPointer());
		} 
		else throw gcnew ArgumentException("One of the attributes specified cannot be set.");
	}

	element->SetAttributes(&attr);
}

void Element::RemoveAttribute(String^ name){
	element->RemoveAttribute(ToRocketString(name));
}

Element^ Element::FocusLeafNode::get() {
	return Create(element->GetFocusLeafNode());
}

Context^ Element::Context::get(){
	return LibRocketNet::Core::_contexts[IntPtr((void *)element->GetContext())];
}

String^ Element::TagName::get() { return ToNetString(element->GetTagName()); }
String^ Element::Id::get() { return ToNetString(element->GetId()); }
void Element::Id::set(String^ str) { element->SetId(ToRocketString(str)); }

float Element::AbsoluteLeft::get(){ return element->GetAbsoluteLeft(); }

float Element::AbsoluteTop::get(){ return element->GetAbsoluteTop(); }

RectangleF Element::ClientRect::get(){
	return RectangleF(element->GetClientLeft(), element->GetClientTop(), element->GetClientWidth(), element->GetClientHeight());
}

Element^ Element::OffsetParent::get(){
	return Create(element->GetOffsetParent());
}

RectangleF Element::Offset::get() {
	return RectangleF(element->GetOffsetLeft(), element->GetOffsetTop(), element->GetOffsetWidth(), element->GetOffsetHeight());
}

float Element::ScrollLeft::get(){
	return element->GetScrollLeft();
}

void Element::ScrollLeft::set(float scroll){
	element->SetScrollLeft(scroll);
}


float Element::ScrollTop::get(){
	return element->GetScrollTop();
}

void Element::ScrollTop::set(float scroll){
	element->SetScrollTop(scroll);
}

Vector2f Element::ScrollSize::get(){
	return Vector2f(element->GetScrollWidth(), element->GetScrollHeight());
}

ElementDocument^ Element::OwnerDocument::get(){
	return ElementDocument::Create(element->GetOwnerDocument());
}

String^ Element::InnerRml::get() {
	return ToNetString(element->GetInnerRML());
} 

void Element::InnerRml::set(String^ s){
	element->SetInnerRML(ToRocketString(s));
}

Element^ Element::PreviousSibling::get(){
	return Create(element->GetPreviousSibling());
}

Element^ Element::NextSibling::get(){
	return Create(element->GetNextSibling());
}

Element^ Element::ParentNode::get(){
	return Create(element->GetParentNode());
}









Box::Area Element::ClientArea::get(){
	return (Box::Area) element->GetClientArea();
}  

void Element::ClientArea::set(Box::Area a){
	element->SetClientArea((Rocket::Core::Box::Area) a);
}

void Element::SetContentBox(Vector2f contentOffset, Vector2f contentBox){
	element->SetContentBox(contentOffset, contentBox);
}

void Element::SetBox(Box^ box) {
	element->SetBox(*box->box);
}

void Element::AddBox(Box^ box) {
	element->AddBox(*box->box);
}

Box^ Element::GetBox(int index){
	return gcnew Box(element->GetBox(index));
}

int Element::NumBoxes::get() { return element->GetNumBoxes(); }

float Element::Baseline::get(){ return element->GetBaseline(); }

bool Element::GetIntrinsicDimensions(Vector2f% point){
	Rocket::Core::Vector2f p;
	bool ret = element->GetIntrinsicDimensions(p);
	point = Vector2f( p );
	return ret;
}

bool Element::IsPointWithinElement(Vector2f point) {
	return element->IsPointWithinElement(point);
}

bool Element::IsVisible::get() { return element->IsVisible(); }

bool Element::IsPseudoClassSet(String^ pseudoclass)
{
	CHECK_NULL_ELEM(false);
	return element->IsPseudoClassSet(Util::ToRocketString(pseudoclass));
}

void Element::SetPseudoClass(String^ pseudoClass, bool activate) {
	element->SetPseudoClass(ToRocketString(pseudoClass), activate);
}

bool Element::ArePseudoClassesSet(Generic::IEnumerable<String^ > ^ classes){
	Rocket::Core::PseudoClassList psl;

	for each (auto c in classes)
		psl.insert(ToRocketString(c));	

	return element->ArePseudoClassesSet(psl);
}

Generic::IEnumerable<String^ > ^ Element::ActivePseudoClasses::get(){
	auto l = gcnew Generic::List<String^>();

	for each (auto c in element->GetActivePseudoClasses())
	{
		l->Add(ToNetString(c));
	}
	return l;
}









void Element::Construct(Rocket::Core::Element *elem){
	if (!elem) throw gcnew ArgumentNullException("Attempted to create a LibRocket element with a null raw pointer");
	auto root = Util::GetGcRoot(elem, ELEMENT_ATTRIBUTE_NAME);
	if (root) throw gcnew ArgumentException("Attempted to create a LibRocket element with a raw pointer with an existing Tag");
	element = elem;
	auto r = new gcroot<Element ^>();
	*r = this;
	SetGcRoot(elem, r, ELEMENT_ATTRIBUTE_NAME);
	elem->AddReference();
	InitHandlers();
	_children = gcnew ElementCollection(this);
}

Element::Element(Rocket::Core::Element* elem){
	Construct(elem);
}

Element::~Element(){
	element->RemoveReference();
	element=NULL;
	
}



Element^ Element::Create(Rocket::Core::Element* elem){
	if(!elem) return nullptr;
	auto root = GetGcRoot(elem, ELEMENT_ATTRIBUTE_NAME);
	if(!root){
		return gcnew Element(elem);
	} else {
		return *root;
	}
}

Element^ Element::Clone() {
	return Create(element->Clone());
}

void Element::SetClass(String^ className, bool activate) {
	CHECK_NULL_ELEM_VOID();
	element->SetClass(Util::ToRocketString(className), activate);
}

bool Element::IsClassSet(String^ className) {
	CHECK_NULL_ELEM(false);
	return element->IsClassSet(Util::ToRocketString(className));
}

String^ Element::ClassNames::get(){
	CHECK_NULL_ELEM(nullptr);
	return Util::ToNetString(element->GetClassNames());
} 

void Element::ClassNames::set(String^ s) {
	CHECK_NULL_ELEM_VOID();
	element->SetClassNames( Util::ToRocketString(s) );
}

String^ Element::GetAddress(bool includePseudoClasses) {
	CHECK_NULL_ELEM(nullptr);
	return ToNetString(element->GetAddress(includePseudoClasses));
}

void Element::SetOffset(Vector2f offset, Element^ offsetParent, bool offsetFixed) {
	CHECK_NULL_ELEM_VOID();
	element->SetOffset(offset, offsetParent->element, offsetFixed);
}

void Element::SetProperty(String^ propertyName, String^ value) {
	element->SetProperty(ToRocketString(propertyName), ToRocketString(value));
}

void Element::SetProperty(String^ propertyName, int value) {
	element->SetProperty(ToRocketString(propertyName), Rocket::Core::Property(value, Rocket::Core::Property::NUMBER));
}

void Element::SetProperty(String^ propertyName, float value) {
	element->SetProperty(ToRocketString(propertyName), Rocket::Core::Property(value, Rocket::Core::Property::NUMBER));
}


void Element::RemoveProperty(String^ propertyName) {
	element->RemoveProperty(ToRocketString(propertyName));
}

/*
float Element::ResolveProperty(String^ propertyName, float baseValue) {
	return element->ResolveProperty(ToRocketString(propertyName), baseValue);
}

Vector2i Element::OverflowProperty::get() { 
	Vector2i v;
	element->GetOverflow( &v.X, &v.Y );
	return v;
}

int Element::PositionProperty::get() { return element->GetPosition(); }
int Element::FloatProperty::get() { return element->GetFloat(); }
int Element::DisplayProperty::get() { return element->GetDisplay(); }
int Element::WhitespaceProperty::get() { return element->GetWhitespace(); }

*/

float Element::GetPropertyFloat(String^ str) {
	return element->GetProperty<float>(ToRocketString(str));
}

int Element::GetPropertyInt(String^ str) {
	return element->GetProperty<int>(ToRocketString(str));
}

Color Element::GetPropertyColor(String^ str) {
	return Color(element->GetProperty<Rocket::Core::Colourb>(ToRocketString(str)));
}

String^ Element::GetPropertyString(String^ str) {
	return ToNetString(element->GetProperty<Rocket::Core::String>(ToRocketString(str)));
}

Element^ Element::GetElementById(String^ id) {
	return Create(element->GetElementById(ToRocketString(id)));
}

array<Element^>^ Element::GetElementsByTagName(String^ tag) {
	Rocket::Core::ElementList list;
	element->GetElementsByTagName(list, ToRocketString(tag));
	auto arr = gcnew array<Element^>(list.size());
	for (unsigned i = 0; i < list.size(); i++)
	{
		arr[i] = Create(list[i]);
	}
	return arr;
}

array<Element^>^ Element::GetElementsByClassName(String^ class_name) {
	Rocket::Core::ElementList list;
	element->GetElementsByClassName(list, ToRocketString(class_name));
	auto arr = gcnew array<Element^>(list.size());
	for (unsigned i = 0; i < list.size(); i++)
	{
		arr[i] = Create(list[i]);
	}
	return arr;
}

template<class _Handler, class _Args>
void AddHandler(Action<_Args^>^ invoker, Rocket::Core::Element *elem, const char *eventName) {
	auto handler = new _Handler();
	handler->Invoker = invoker;
	elem->AddEventListener(eventName, handler);
}


void Element::InitHandlers(){
	CHECK_NULL_ELEM_VOID();

	AddHandler<RocketEvent<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventShow), element, "show");

	AddHandler<RocketEvent<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventShow), element, "show");
	AddHandler<RocketEvent<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventHide), element, "hide");
	AddHandler<RocketEvent<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventResize), element, "resize");
	AddHandler<RocketEvent<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventScroll), element, "scroll");
	AddHandler<RocketEvent<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventFocus), element, "focus");
	AddHandler<RocketEvent<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventBlur), element, "blur");

	AddHandler<RocketEvent<KeyboardEventArgs>, KeyboardEventArgs>(gcnew System::Action<KeyboardEventArgs^>(this, &Element::InvokeEventKeyDown), element, "keydown");
	AddHandler<RocketEvent<KeyboardEventArgs>, KeyboardEventArgs>(gcnew System::Action<KeyboardEventArgs^>(this, &Element::InvokeEventKeyUp), element, "keyup");

	AddHandler<RocketEvent<TextInputEventArgs>, TextInputEventArgs>(gcnew System::Action<TextInputEventArgs^>(this, &Element::InvokeEventTextInput), element, "textinput");


	AddHandler<RocketEvent<MouseEventArgs>, MouseEventArgs>(gcnew System::Action<MouseEventArgs^>(this, &Element::InvokeEventClick), element, "click");
	AddHandler<RocketEvent<MouseEventArgs>, MouseEventArgs>(gcnew System::Action<MouseEventArgs^>(this, &Element::InvokeEventDoubleClick), element, "dblclick");
	AddHandler<RocketEvent<MouseEventArgs>, MouseEventArgs>(gcnew System::Action<MouseEventArgs^>(this, &Element::InvokeEventMouseOver), element, "mouseover");
	AddHandler<RocketEvent<MouseEventArgs>, MouseEventArgs>(gcnew System::Action<MouseEventArgs^>(this, &Element::InvokeEventMouseOut), element, "mouseout");
	AddHandler<RocketEvent<MouseEventArgs>, MouseEventArgs>(gcnew System::Action<MouseEventArgs^>(this, &Element::InvokeEventMouseMove), element, "mousemove");
	AddHandler<RocketEvent<MouseEventArgs>, MouseEventArgs>(gcnew System::Action<MouseEventArgs^>(this, &Element::InvokeEventMouseUp), element, "mouseup");
	AddHandler<RocketEvent<MouseEventArgs>, MouseEventArgs>(gcnew System::Action<MouseEventArgs^>(this, &Element::InvokeEventMouseDown), element, "mousedown");
	AddHandler<RocketEvent<MouseEventArgs>, MouseEventArgs>(gcnew System::Action<MouseEventArgs^>(this, &Element::InvokeEventMouseScroll), element, "mousescroll");

	AddHandler<RocketEvent<DragEventArgs>, DragEventArgs>(gcnew System::Action<DragEventArgs^>(this, &Element::InvokeEventDragStart), element, "dragstart");
	AddHandler<RocketEvent<DragEventArgs>, DragEventArgs>(gcnew System::Action<DragEventArgs^>(this, &Element::InvokeEventDragEnd), element, "dragend");
	AddHandler<RocketEvent<DragEventArgs>, DragEventArgs>(gcnew System::Action<DragEventArgs^>(this, &Element::InvokeEventDrag), element, "drag");

	AddHandler<RocketEvent<FormSubmitEventArgs>, FormSubmitEventArgs>(gcnew System::Action<FormSubmitEventArgs^>(this, &Element::InvokeEventFormSubmit), element, "submit");

	AddHandler<RocketEvent<FormControlChangeEventArgs>, FormControlChangeEventArgs>(gcnew System::Action<FormControlChangeEventArgs^>(this, &Element::InvokeEventFormControlChange), element, "change");

	AddHandler<RocketEvent<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventLoad), element, "load");
	AddHandler<RocketEvent<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventUnload), element, "unload");

	AddHandler<RocketEvent<HandleEventArgs>, HandleEventArgs>(gcnew System::Action<HandleEventArgs^>(this, &Element::InvokeEventHandleDrag), element, "handledrag");

	AddHandler<RocketEvent<DataGridAddColumnEventArgs>, DataGridAddColumnEventArgs>(gcnew System::Action<DataGridAddColumnEventArgs^>(this, &Element::InvokeEventColumnAdd), element, "columnadd");
	AddHandler<RocketEvent<ElementEventArgs>, ElementEventArgs>(gcnew System::Action<ElementEventArgs^>(this, &Element::InvokeEventRowUpdate), element, "rowupdate");
	AddHandler<RocketEvent<DataGridRowEventArgs>, DataGridRowEventArgs>(gcnew System::Action<DataGridRowEventArgs^>(this, &Element::InvokeEventRowAdd), element, "rowadd");
	AddHandler<RocketEvent<DataGridRowEventArgs>, DataGridRowEventArgs>(gcnew System::Action<DataGridRowEventArgs^>(this, &Element::InvokeEventRowRemove), element, "rowremove");

	AddHandler<RocketEvent<TabChangeEventArgs>, TabChangeEventArgs>(gcnew System::Action<TabChangeEventArgs^>(this, &Element::InvokeEventTabChange), element, "tabchange");
}

}
