#pragma once

using namespace System;
using namespace System::Collections;
using namespace NosebleedStudios::Utilities;

#include "LibRocketNet.h"

namespace LibRocketNet {

ref class Element;

public ref class ElementCollection: ReadOnlyListCpp<Element^>
{
private:
	Element^ _element;


	ref class ElementEnumerator : Generic::IEnumerator<Element^> {
		property Element^ CurrentGeneric { 
            virtual Element^ get() sealed = Generic::IEnumerator<Element^>::Current::get;
        };

		Element^ _elem;
		Element^ _current;
		bool _isLast;

	public:
		

		ElementEnumerator(Element^ element);

		virtual ~ElementEnumerator(){}

		property Object^ Current { 
			virtual Object^ get() { return _current; }
		};

		virtual bool MoveNext();

		virtual void Reset();
	};

internal:
	ElementCollection(Element^);

public:

	property Element^ First { Element^ get(); }
	property Element^ Last { Element^ get(); }

	virtual property int Count { int get() override; }

protected:

	virtual Element^ GetItemByIndex(int index) override;
	virtual Generic::IEnumerator<Element^>^ GetEnumeratorImpl() override;
};

}