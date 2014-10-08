#pragma once
using namespace System;
using namespace System::Drawing;
using namespace System::Collections;

#include <gcroot.h>

#include "LibRocketNet.h"
#include "ElementEvent.h"

namespace LibRocketNet {

gcroot<Element^>* GetGcRoot(RocketElement* elem);
void SetGcRoot(RocketElement* elem, gcroot<Element^>* r);

ref class Context;
ref class ElementCollection;
ref class ElementDocument;

public ref class Element
{
protected:
	Element(RocketElement* elem);

public:
	virtual ~Element();

	property Rectangle Size {	Rectangle get();	}
	property PointF RelativeOffset {	PointF get();	}
	property PointF AbsoluteOffset {	PointF get();	}
	property PointF AbsolutePosition {	PointF get();	}

	Element^ Clone();

	void SetClass(String^ className, bool activate);
	void SetClass(String^ className) { SetClass(className, true); }

	void IsClassSet(String^ className);
	
	property String^ ClassNames { String^ get(); void set(String^ s); }

	String^ GetAddress(bool includePseudoClasses);
	String^ GetAddress() {  return GetAddress(false); }

	void SetOffset(PointF offset, Element^ offsetParent, bool offsetFixed);
	void SetOffset(PointF offset, Element^ offsetParent) { SetOffset(offset, offsetParent, false); }

	property Rectangle ClientArea { Rectangle get(); void set(Rectangle r); }

	void SetContentBox(PointF contentOffset, PointF contentBox);
	void SetBox(Rectangle box);
	void AddBox(Rectangle box);

	Rectangle GetBox(int index);
	Rectangle GetBox() { return GetBox(0); }

	property int NumBoxes {	int get();	}

	virtual property float Baseline {	virtual float get();	}

	virtual bool GetIntrinsicDimensions(PointF% point);
	virtual bool IsPointWithinElement(PointF point);

	property bool IsVisible { bool get();	}


	void SetProperty(String^ propertyName, int value);
	void SetProperty(String^ propertyName, float value);
	void SetProperty(String^ propertyName, String^ value);

	void RemoveProperty(String^ propertyName);
	float ResolveProperty(String^ propertyName);


	void GetBorderWidthProperties (String^% top, String^% bottom, String^% left, String^% right);
	void GetMarginProperties (String^% top, String^% bottom, String^% left, String^% right);
	void GetPaddingProperties (String^% top, String^% bottom, String^% left, String^% right);
	void GetDimensionProperties (String^% width, String^% height);
	void GetLocalDimensionProperties (String^% width, String^% height);

	property Point OverflowProperty { Point get(); }
	property int PositionProperty { int get(); }
	property int FloatProperty { int get(); }
	property int DisplayProperty { int get(); }
	property int WhitespaceProperty { int get(); }

	property String^ LineHeightProperty { String^ get(); }
	property String^ VerticalAlignProperty { String^ get(); }

	property int TextAlignProperty { int get(); }
	property int TextTransformProperty { int get(); }


	bool IsPseudoClassSet(String^ pseudoclass);
	void SetPseudoClass(String^ pseudoClass, bool activate);
	void SetPseudoClass(String^ pseudoClass) { SetPseudoClass(pseudoClass, true); }
	bool ArePseudoClassesSet(Generic::IEnumerable<String^>^ classes);
	property Generic::IEnumerable<String^>^ ActivePseudoClasses { Generic::IEnumerable<String^>^ get(); }

	void SetAttribute(String^ attribute, int value);
	void SetAttribute(String^ attribute, float value);
	void SetAttribute(String^ attribute, String^ value);

	int GetAttribute(String^ attribute, int defaultVal);
	float GetAttribute(String^ attribute, float defaultVal);
	String^ GetAttribute(String^ attribute, String^ defaultVal);

	bool HasAttribute(String^ name);
	bool RemoveAttribute(String^ name);

	void SetAttributes(Generic::KeyValuePair<String^, Object^> attributes);
	Generic::KeyValuePair<String^, Object^> GetAttributes();

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

	property PointF ScrollSize { PointF get(); }

	property ElementDocument^ OwnerDocument { ElementDocument^ get(); }
	
	property String^ InnerRml { String^ get(); void set(String^ s); }

	property ElementCollection^ Children { ElementCollection^ get() { return _children; } } 

	property Element^ PreviousSibling { Element^ get(); }
	property Element^ NextSibling { Element^ get(); }
	property Element^ ParentNode { Element^ get(); }

	bool FocusElement();
	void BlurElement();
	void ClickElement();

	// events

#define ELEMENT_DEFINE_EVENT(args, name) \
	private: \
	EventHandler< args ^ >^ _event##name; \
	public:\
	event EventHandler < args ^>^ name {                \
		void add(EventHandler< args ^>^e) { _event##name = static_cast<EventHandler< args ^ >^> (Delegate::Combine(_event##name, e)); }				\
		void remove(EventHandler< args ^>^e) { _event##name = static_cast<EventHandler< args ^ >^> (Delegate::Remove(_event##name, e)); }			\
		void raise(Object^ s, args ^ e) { if(_event##name != nullptr) _event##name->Invoke(s, e); } \
	}   

#define ELEMENT_HANDLE_EVENT(__handler, evt, str) \
{ \
	auto handler=new __handler(); \
	handler->Handlers = this->_event##evt;   \
	element->AddEventListener(str, handler); \
}


	ELEMENT_DEFINE_EVENT(ElementEventArgs,Show);
	ELEMENT_DEFINE_EVENT(ElementEventArgs,Hide);
	ELEMENT_DEFINE_EVENT(ElementEventArgs,Resize);
	ELEMENT_DEFINE_EVENT(ElementEventArgs,Scroll);
	ELEMENT_DEFINE_EVENT(ElementEventArgs,Focus);
	ELEMENT_DEFINE_EVENT(ElementEventArgs,Blur);

	ELEMENT_DEFINE_EVENT(KeyboardEventArgs,KeyDown);
	ELEMENT_DEFINE_EVENT(KeyboardEventArgs,KeyUp);

	ELEMENT_DEFINE_EVENT(TextInputEventArgs,TextInput);


	ELEMENT_DEFINE_EVENT(MouseEventArgs,Click);
	ELEMENT_DEFINE_EVENT(MouseEventArgs,DoubleClick);
	ELEMENT_DEFINE_EVENT(MouseEventArgs,MouseOver);
	ELEMENT_DEFINE_EVENT(MouseEventArgs,MouseOut);
	ELEMENT_DEFINE_EVENT(MouseEventArgs,MouseMove);
	ELEMENT_DEFINE_EVENT(MouseEventArgs,MouseUp);
	ELEMENT_DEFINE_EVENT(MouseEventArgs,MouseDown);
	ELEMENT_DEFINE_EVENT(MouseEventArgs,MouseScroll);

	ELEMENT_DEFINE_EVENT(DragEventArgs,DragStart);
	ELEMENT_DEFINE_EVENT(DragEventArgs,DragEnd);
	ELEMENT_DEFINE_EVENT(DragEventArgs,Drag);

	ELEMENT_DEFINE_EVENT(FormSubmitEventArgs,FormSubmit);

	ELEMENT_DEFINE_EVENT(FormControlChangeEventArgs,FormControlChange);

	ELEMENT_DEFINE_EVENT(ElementEventArgs,Load);
	ELEMENT_DEFINE_EVENT(ElementEventArgs,Unload);

	ELEMENT_DEFINE_EVENT(HandleEventArgs,HandleDrag);

	ELEMENT_DEFINE_EVENT(DataGridAddColumnEventArgs,ColumnAdd);
	ELEMENT_DEFINE_EVENT(ElementEventArgs,RowUpdate);
	ELEMENT_DEFINE_EVENT(DataGridRowEventArgs,RowAdd);
	ELEMENT_DEFINE_EVENT(DataGridRowEventArgs,RowRemove);

	ELEMENT_DEFINE_EVENT(TabChangeEventArgs,TabChange);



internal:
	RocketElement *element;
	//void InvokeEvent(RocketString& str, ElementEventArgs^ args);
	static Element^ Create(RocketElement* element);

private:
	void InitHandlers();
	ElementCollection^ _children;

	//void GeneralEventHandler(Object^ sender, ElementEventArgs^ args);
};

}


