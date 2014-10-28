#include "Stdafx.h"
#include <gcroot.h>
#include <vcclr.h>
#include "Rocket/Core/Element.h"
#include "Util.h"

#include "Element.h"

namespace LibRocketNet {
namespace Util {

	

	gcroot<Element^>* GetGcRoot(Rocket::Core::Element* elem, const char *attribName){
		if (!elem) throw gcnew ArgumentNullException();
		return (gcroot<Element^>*) elem->GetAttribute<void *>(attribName, NULL);
	}

	void SetGcRoot(Rocket::Core::Element* elem, gcroot<Element^>* r, const char *attribName){
		if (!elem || !r) throw gcnew ArgumentNullException();
		elem->SetAttribute(attribName, (void *)r);
	}

	String^ ToNetString(const Rocket::Core::String& s) {
		return gcnew String(s.CString());
	}

	Rocket::Core::String ToRocketString(String^ str) {
		array<Byte>^ encodedBytes = System::Text::Encoding::UTF8->GetBytes(str);
		pin_ptr<Byte> pinnedBytes = &encodedBytes[0];
		Rocket::Core::String s(reinterpret_cast<char*>(pinnedBytes));
		return s;
	}

}
}