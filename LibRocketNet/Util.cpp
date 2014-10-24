#include "Stdafx.h"
#include <gcroot.h>
#include "Rocket/Core/Element.h"
#include "Util.h"

#include "Element.h"

namespace LibRocketNet {
namespace Util {

	

	gcroot<Element^>* GetGcRoot(RocketElement* elem, const char *attribName){
		if (!elem) throw gcnew ArgumentNullException();
		return (gcroot<Element^>*) elem->GetAttribute<void *>(attribName, NULL);
	}

	void SetGcRoot(RocketElement* elem, gcroot<Element^>* r, const char *attribName){
		if (!elem || !r) throw gcnew ArgumentNullException();
		elem->SetAttribute(attribName, (void *)r);
	}

}
}