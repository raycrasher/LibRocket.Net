#include "stdafx.h"
#include <gcroot.h>
#include "ElementCollection.h"
#include "Element.h"
#include "Rocket/Core.h"


namespace LibRocketNet {

#define NULL_PTR_MSG "Element contains a null raw element pointer."

ElementCollection::ElementCollection(Element^element)
{
	if(element==nullptr) throw gcnew ArgumentNullException();
	if(element->element == NULL) throw gcnew InvalidOperationException(NULL_PTR_MSG);
	_element=element;
}

Element^ ElementCollection::ElementEnumerator::CurrentGeneric::get(){
	return _current;
};

Generic::IEnumerator<Element^>^ ElementCollection::GetEnumeratorImpl(){
	return gcnew ElementEnumerator(_element);
}

Element^ ElementCollection::GetItemByIndex(int index){
	if(index>=Count) throw gcnew IndexOutOfRangeException();
	if(_element->element == NULL) throw gcnew InvalidOperationException(NULL_PTR_MSG);
	return Element::Create(_element->element->GetChild(index));
}

int ElementCollection::Count::get() {
	if(_element->element == NULL) throw gcnew InvalidOperationException(NULL_PTR_MSG);
	return _element->element->GetNumChildren();
}

Element^ ElementCollection::First::get() {
	if(_element->element == NULL) throw gcnew InvalidOperationException(NULL_PTR_MSG);
	return Element::Create(_element->element->GetFirstChild());
}

Element^ ElementCollection::Last::get() {
	if(_element->element == NULL) throw gcnew InvalidOperationException(NULL_PTR_MSG);
	return Element::Create(_element->element->GetLastChild());
}


/////////////////////////////////////////////////
// enumerator

ElementCollection::ElementEnumerator::ElementEnumerator(Element^ elem){
	if(elem==nullptr) throw gcnew ArgumentNullException();
	if(elem->element == NULL) throw gcnew InvalidOperationException(NULL_PTR_MSG);
	
	_elem=elem;
	_isLast=false;
	_current=nullptr;
}

bool ElementCollection::ElementEnumerator::MoveNext() {
	if(_elem->element == NULL) throw gcnew InvalidOperationException(NULL_PTR_MSG);
	if(_current==nullptr ) {
		if(_isLast) return false;
		else Reset();
	}
	
	_current = Element::Create(_current->element->GetNextSibling());
	if(_current==nullptr) {
		_isLast=true;
		return false;
	}
	return true;
}

void ElementCollection::ElementEnumerator::Reset(){
	if(_elem->element == NULL) throw gcnew InvalidOperationException(NULL_PTR_MSG);
	_current = Element::Create(_elem->element->GetChild(0));
}

}


