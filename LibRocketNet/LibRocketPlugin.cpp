#include "stdafx.h"
#include <gcroot.h>
#include "LibRocketPlugin.h"
#include "Rocket/Core/Element.h"
#include "Element.h"

namespace LibRocketNet {

void LibRocketPlugin::OnElementDestroy(RocketElement *elem) 
{
	auto r=GetGcRoot(elem);
	if(!r) return;
	auto root= (gcroot<Element^>*) r;
	auto e=(*root);
	delete root;
	//e->Dispose();
}
}