#pragma once

using namespace System;
using namespace System;
using namespace System::Collections::Generic;

#include "LibRocketNet.h"

namespace LibRocketNet {

ref class Element;

public ref class ElementCollection: IReadOnlyList<Element^>
{
private:
	Element^ _element;


	ref class ElementEnumerator : System::Collections::Generic::IEnumerator<Element^> {
		property Element^ CurrentGeneric { 
			virtual Element^ get() sealed = System::Collections::Generic::IEnumerator<Element^>::Current::get;
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


	virtual System::Collections::IEnumerator^ EnumerableGetEnumerator() = System::Collections::IEnumerable::GetEnumerator
	{
		return GetEnumerator();
	}

public:

	property Element^ First { Element^ get(); }
	property Element^ Last { Element^ get(); }

	virtual property int Count { int get(); }



	virtual System::Collections::Generic::IEnumerator<Element^>^ GetEnumerator(){
		return gcnew ElementEnumerator(_element);
	}

	property Element^ default[int] {
		virtual Element^ get(int index){
			return GetItemByIndex(index);
		}
	}

protected:

	Element^ GetItemByIndex(int index);
};

}