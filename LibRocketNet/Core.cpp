#include "stdafx.h"

#include "Rocket/Core.h"
#include "Rocket/Core/String.h"

#include "Core.h"
#include "Util.h"
#include "SystemInterface.h"
#include "RenderInterface.h"

namespace LibRocketNet{

	bool Core::Initialize() {
		_contexts = gcnew List<Context^>();
		return Rocket::Core::Initialise();
	}

	void Core::Shutdown() {
		Rocket::Core::Shutdown();
		_contexts->Clear();
		_contexts = nullptr;

	}

	String^ Core::Version::get(){
		auto v = Rocket::Core::GetVersion();
		return Util::ToNetString(v);
	}

}