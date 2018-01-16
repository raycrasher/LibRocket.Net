#pragma once
using namespace System;
using namespace System::Collections;

#include <gcroot.h>

#include "LibRocketNet.h"
#include "ElementEvent.h"
#include "Rectangle.h"
#include "Box.h"
#include "Util.h"
#include "Color.h"

#define ELEMENT_ATTRIBUTE_NAME "___LIBROCKETNET_ELEMENT_GCROOT___"

using namespace LibRocketNet::Util;

namespace LibRocketNet {

ref class Context;
ref class ElementCollection;
ref class ElementDocument;



public ref class Element
{
protected:
	Element(Rocket::Core::Element* elem);

public:
	Element(String^ tagName);
	Element(String^ instancer, String^ tagName);
	Element(Element^ parent, String^ tagName);
	Element(Element^ parent, String^ instancer, String^ tagName);

	virtual ~Element();

	property RectangleF Size {	RectangleF get();	}
	property Vector2f RelativeOffset {	Vector2f get();	}
	property Vector2f AbsoluteOffset {	Vector2f get();	}
	property Vector2f AbsolutePosition { Vector2f get();	}

	Element^ Clone();

	void SetClass(String^ className, bool activate);
	void SetClass(String^ className) { SetClass(className, true); }

	bool IsClassSet(String^ className);
	
	property String^ ClassNames { String^ get(); void set(String^ s); }

	String^ GetAddress(bool includePseudoClasses);
	String^ GetAddress() {  return GetAddress(false); }

	void SetOffset(Vector2f offset, Element^ offsetParent, bool offsetFixed);
	void SetOffset(Vector2f offset, Element^ offsetParent) { SetOffset(offset, offsetParent, false); }

	property Box::Area ClientArea { Box::Area get(); void set(Box::Area r); }

	void SetContentBox(Vector2f contentOffset, Vector2f contentBox);
	void SetBox(Box^ box);
	void AddBox(Box^ box);

	Box^ GetBox(int index);
	Box^ GetBox() { return GetBox(0); }

	property int NumBoxes {	int get();	}

	virtual property float Baseline {	virtual float get();	}

	virtual bool GetIntrinsicDimensions(Vector2f% point);
	virtual bool IsPointWithinElement(Vector2f point);

	property bool IsVisible { bool get();	}

	float GetPropertyFloat(String^ str);
	int GetPropertyInt(String^ str);
	Color GetPropertyColor(String^ str);
	String^ GetPropertyString(String^ str);

	void SetProperty(String^ propertyName, String^ value);
	void SetProperty(String^ propertyName, int value);
	void SetProperty(String^ propertyName, float value);

	void RemoveProperty(String^ propertyName);

	Element^ GetElementById(String^ id);
	/// Get all descendant elements with the given tag.
	/// @param[out] elements Resulting elements.
	/// @param[in] tag Tag to search for.
	array<Element^>^ GetElementsByTagName(String^ tag);
	/// Get all descendant elements with the given class set on them.
	/// @param[out] elements Resulting elements.
	/// @param[in] tag Tag to search for.
	array<Element^>^ GetElementsByClassName(String^ class_name);

	// float ResolveProperty(String^ propertyName, float baseValue);
	// 
	// 
	// // void GetBorderWidthProperties (String^% top, String^% bottom, String^% left, String^% right);
	// // void GetMarginProperties (String^% top, String^% bottom, String^% left, String^% right);
	// // void GetPaddingProperties (String^% top, String^% bottom, String^% left, String^% right);
	// // void GetDimensionProperties (String^% width, String^% height);
	// // void GetLocalDimensionProperties (String^% width, String^% height);
	// 
	// property Vector2i OverflowProperty { Vector2i get(); }
	// property int PositionProperty { int get(); }
	// property int FloatProperty { int get(); }
	// property int DisplayProperty { int get(); }
	// property int WhitespaceProperty { int get(); }
	// 
	// property String^ LineHeightProperty { String^ get(); }
	// property String^ VerticalAlignProperty { String^ get(); }
	// 
	// property int TextAlignProperty { int get(); }
	// property int TextTransformProperty { int get(); }


	bool IsPseudoClassSet(String^ pseudoclass);
	void SetPseudoClass(String^ pseudoClass, bool activate);
	void SetPseudoClass(String^ pseudoClass) { SetPseudoClass(pseudoClass, true); }
	bool ArePseudoClassesSet(Generic::IEnumerable<String^ > ^ classes);
	property Generic::IEnumerable<String^ > ^ ActivePseudoClasses { Generic::IEnumerable<String^ > ^ get(); }

	void SetAttribute(String^ attribute, int value);
	void SetAttribute(String^ attribute, float value);
	void SetAttribute(String^ attribute, String^ value);

	int GetAttributeInt(String^ attribute, int defaultVal);
	float GetAttributeFloat(String^ attribute, float defaultVal);
	String^ GetAttributeString(String^ attribute, String^ defaultVal);
	IntPtr GetAttributePtr(String^ attribute, IntPtr defaultVal);

	bool HasAttribute(String^ name);
	void RemoveAttribute(String^ name);

	void SetAttributes(Generic::Dictionary<String^, Object^> attributes);

	property Element^ FocusLeafNode { Element^ get(); }
	property Context^ Context { LibRocketNet::Context^ get(); }
	property String^ TagName { String^ get(); }
	property String^ Id { String^ get(); void set(String^ id); }

	property float AbsoluteLeft { float get(); }
	property float AbsoluteTop { float get(); }
	property RectangleF ClientRect { RectangleF get(); }
	
	property Element^ OffsetParent { Element^ get(); }

	property RectangleF Offset { RectangleF get(); }

	property float ScrollLeft { float get(); void set(float s); }
	property float ScrollTop { float get(); void set(float s); }

	property Vector2f ScrollSize { Vector2f get(); }

	property ElementDocument^ OwnerDocument { ElementDocument^ get(); }
	
	property String^ InnerRml { String^ get(); void set(String^ s); }

	property ElementCollection^ Children { ElementCollection^ get() { return _children; } } 

	property Element^ PreviousSibling { Element^ get(); }
	property Element^ NextSibling { Element^ get(); }
	property Element^ ParentNode { Element^ get(); }

	property Object^ Tag;

	bool FocusElement() { return element->Focus(); }
	void BlurElement() { element->Blur();  }
	void ClickElement() { element->Click(); }

	void AppendChild(Element^ elem);
	void InsertBefore(Element^ elem, Element^ adjacentElement);
	void ScrollIntoView();

	void RemoveChild(Element^ elem);
	void ReplaceChild(Element^ elem, Element^ replacedElem);

internal:
	
	template<class _Handler, class _Args>
	void AddHandler(Action<_Args^>^ invoker, Rocket::Core::Element *elem, const char *eventName) {
		auto handler = new _Handler();
		handler->Invoker = invoker;
		elem->AddEventListener(eventName, handler);
	}

#define DEFINE_EVENT(name, rmlName, netEventArgs)																													\
internal:																																							\
	EventHandler < netEventArgs^ >^ _elementHandlers_##name;																										\
	void InvokeEvent##name(netEventArgs^ args) { _elementHandlers_##name(this, args); }																				\
public:																																								\
	event EventHandler < netEventArgs^ >^ name {																													\
		void add(EventHandler < netEventArgs^ >^ handler) {																											\
			if (_elementHandlers_##name == nullptr) {																												\
				_elementHandlers_##name = handler;																													\
				AddHandler<RocketEvent<netEventArgs>, netEventArgs > (gcnew System::Action<netEventArgs^>(this, &Element::InvokeEvent##name), element, #rmlName);	\
			}																																						\
			else {																																					\
				_elementHandlers_##name->Combine(handler);																											\
			}																																						\
		}																																							\
		void remove(EventHandler < netEventArgs^ >^ handler) {																										\
			if (_elementHandlers_##name != nullptr) {																												\
				_elementHandlers_##name -= handler;																													\
			}																																						\
		}																																							\
	}

DEFINE_EVENT(Show, "show", ElementEventArgs)
DEFINE_EVENT(Hide, "hide", ElementEventArgs)
DEFINE_EVENT(Resize, "resize", ElementEventArgs)
DEFINE_EVENT(Scroll, "scroll", ElementEventArgs)
DEFINE_EVENT(Focus, "focus", ElementEventArgs)
DEFINE_EVENT(Blur, "blur", ElementEventArgs)

DEFINE_EVENT(KeyDown, "keydown", KeyboardEventArgs)
DEFINE_EVENT(KeyUp, "keyup", KeyboardEventArgs)

DEFINE_EVENT(TextInput, "textinput", TextInputEventArgs)

DEFINE_EVENT(Click, "click", MouseEventArgs)
DEFINE_EVENT(DoubleClick, "dblclick", MouseEventArgs)
DEFINE_EVENT(MouseOver, "mouseover", MouseEventArgs)
DEFINE_EVENT(MouseOut, "mouseout", MouseEventArgs)
DEFINE_EVENT(MouseMove, "mousemove", MouseEventArgs)
DEFINE_EVENT(MouseUp, "mouseup", MouseEventArgs)
DEFINE_EVENT(MouseDown, "mousedown", MouseEventArgs)
DEFINE_EVENT(MouseScroll, "mousescroll", MouseEventArgs)

DEFINE_EVENT(DragStart, "dragstart", DragEventArgs)
DEFINE_EVENT(DragEnd, "dragend", DragEventArgs)
DEFINE_EVENT(Drag, "drag", DragEventArgs)

DEFINE_EVENT(FormSubmit, "formsubmit", FormSubmitEventArgs)

DEFINE_EVENT(FormControlChange, "formcontrolchange", FormControlChangeEventArgs)

DEFINE_EVENT(Load, "load", ElementEventArgs)
DEFINE_EVENT(Unload, "unload", ElementEventArgs)

DEFINE_EVENT(HandleDrag, "handledrag", HandleEventArgs)

DEFINE_EVENT(ColumnAdd, "columnadd", DataGridAddColumnEventArgs)
DEFINE_EVENT(RowUpdate, "rowupdate", ElementEventArgs)
DEFINE_EVENT(RowAdd, "rowadd", DataGridRowEventArgs)
DEFINE_EVENT(RowRemove, "rowremove", DataGridRowEventArgs)

DEFINE_EVENT(TabChange, "tabchange", TabChangeEventArgs)

internal:
	Rocket::Core::Element *element;
	
	static Element^ Create(Rocket::Core::Element* element);

private:

	void Construct(Rocket::Core::Element *elem);
	

	ElementCollection^ _children;

	//void GeneralEventHandler(Object^ sender, ElementEventArgs^ args);
};

}


