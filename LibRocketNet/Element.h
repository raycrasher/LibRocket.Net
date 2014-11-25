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

	bool FocusElement() { return element->Focus(); }
	void BlurElement() { element->Blur();  }
	void ClickElement() { element->Click(); }

public:
	
	event EventHandler < ElementEventArgs^ >^ Show;
	event EventHandler < ElementEventArgs^ >^ Hide;
	event EventHandler < ElementEventArgs^ >^ Resize;
	event EventHandler < ElementEventArgs^ >^ Scroll;
	event EventHandler < ElementEventArgs^ >^ Focus;
	event EventHandler < ElementEventArgs^ >^ Blur;

	event EventHandler < KeyboardEventArgs^ > ^ KeyDown;
	event EventHandler < KeyboardEventArgs^ > ^ KeyUp;

	event EventHandler < TextInputEventArgs^ > ^ TextInput;


	event EventHandler < MouseEventArgs^ > ^ Click;
	event EventHandler < MouseEventArgs^ > ^ DoubleClick;
	event EventHandler < MouseEventArgs^ > ^ MouseOver;
	event EventHandler < MouseEventArgs^ > ^ MouseOut;
	event EventHandler < MouseEventArgs^ > ^ MouseMove;
	event EventHandler < MouseEventArgs^ > ^ MouseUp;
	event EventHandler < MouseEventArgs^ > ^ MouseDown;
	event EventHandler < MouseEventArgs^ > ^ MouseScroll;

	event EventHandler < DragEventArgs^ > ^ DragStart;
	event EventHandler < DragEventArgs^ > ^ DragEnd;
	event EventHandler < DragEventArgs^ > ^ Drag;

	event EventHandler < FormSubmitEventArgs^ > ^ FormSubmit;

	event EventHandler < FormControlChangeEventArgs^ > ^ FormControlChange;

	event EventHandler < ElementEventArgs^ > ^ Load;
	event EventHandler < ElementEventArgs^ > ^ Unload;

	event EventHandler < HandleEventArgs^ > ^ HandleDrag;

	event EventHandler < DataGridAddColumnEventArgs^ > ^ ColumnAdd;
	event EventHandler < ElementEventArgs^ > ^ RowUpdate;
	event EventHandler < DataGridRowEventArgs^ > ^ RowAdd;
	event EventHandler < DataGridRowEventArgs^ > ^ RowRemove;

	event EventHandler < TabChangeEventArgs^ > ^ TabChange;



internal:
	Rocket::Core::Element *element;
	
	static Element^ Create(Rocket::Core::Element* element);

	// event invokers

	void InvokeEventShow(ElementEventArgs^ args) { Show(this, args); }
	void InvokeEventHide(ElementEventArgs^ args) { Hide(this, args); }
	void InvokeEventResize(ElementEventArgs^ args) { Resize(this, args); }
	void InvokeEventScroll(ElementEventArgs^ args) { Scroll(this, args); }
	void InvokeEventFocus(ElementEventArgs^ args) { Focus(this, args); }
	void InvokeEventBlur(ElementEventArgs^ args) { Blur(this, args); }

	void InvokeEventKeyDown(KeyboardEventArgs^ args) { KeyDown(this, args); }
	void InvokeEventKeyUp(KeyboardEventArgs^ args) { KeyUp(this, args); }

	void InvokeEventTextInput(TextInputEventArgs^ args) { TextInput(this, args); }


	void InvokeEventClick(MouseEventArgs^ args) { Click(this, args); }
	void InvokeEventDoubleClick(MouseEventArgs^ args) { DoubleClick(this, args); }
	void InvokeEventMouseOver(MouseEventArgs^ args) { MouseOver(this, args); }
	void InvokeEventMouseOut(MouseEventArgs^ args) { MouseOut(this, args); }
	void InvokeEventMouseMove(MouseEventArgs^ args) { MouseMove(this, args); }
	void InvokeEventMouseUp(MouseEventArgs^ args) { MouseUp(this, args); }
	void InvokeEventMouseDown(MouseEventArgs^ args) { MouseDown(this, args); }
	void InvokeEventMouseScroll(MouseEventArgs^ args) { MouseScroll(this, args); }

	void InvokeEventDragStart(DragEventArgs^ args) { DragStart(this, args); }
	void InvokeEventDragEnd(DragEventArgs^ args) { DragEnd(this, args); }
	void InvokeEventDrag(DragEventArgs^ args) { Drag(this, args); }

	void InvokeEventFormSubmit(FormSubmitEventArgs^ args) { FormSubmit(this, args); }

	void InvokeEventFormControlChange(FormControlChangeEventArgs^ args) { FormControlChange(this, args); }

	void InvokeEventLoad(ElementEventArgs^ args) { Load(this, args); }
	void InvokeEventUnload(ElementEventArgs^ args) { Unload(this, args); }

	void InvokeEventHandleDrag(HandleEventArgs^ args) { HandleDrag(this, args); }

	void InvokeEventColumnAdd(DataGridAddColumnEventArgs^ args) { ColumnAdd(this, args); }
	void InvokeEventRowUpdate(ElementEventArgs^ args) { RowUpdate(this, args); }
	void InvokeEventRowAdd(DataGridRowEventArgs^ args) { RowAdd(this, args); }
	void InvokeEventRowRemove(DataGridRowEventArgs^ args) { RowRemove(this, args); }

	void InvokeEventTabChange(TabChangeEventArgs^ args) { TabChange(this, args); }

private:

	void Construct(Rocket::Core::Element *elem);
	void InitHandlers();

	ElementCollection^ _children;

	//void GeneralEventHandler(Object^ sender, ElementEventArgs^ args);
};

}


