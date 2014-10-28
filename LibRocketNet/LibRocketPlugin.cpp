#include "stdafx.h"
#include <gcroot.h>
#include "LibRocketPlugin.h"
#include "Rocket/Core/Element.h"
#include "Element.h"
#include "Util.h"

namespace LibRocketNet {

void LibRocketPlugin::OnElementDestroy(Rocket::Core::Element *elem) 
{
	auto r = Util::GetGcRoot(elem, ELEMENT_ATTRIBUTE_NAME);
	if(!r) return;
	auto root= (gcroot<Element^>*) r;
	auto e=(*root);
	delete root;
	//e->Dispose();
}
}