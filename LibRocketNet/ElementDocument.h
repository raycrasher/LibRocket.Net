#pragma once

#include "LibRocketNet.h"
#include "Element.h"

using namespace System;

namespace LibRocketNet {

	ref class Context;

	public ref class ElementDocument : public Element
	{
	protected:
		ElementDocument(Rocket::Core::ElementDocument * doc);
	internal:
		Rocket::Core::ElementDocument* DocumentPtr;

		static ElementDocument^ Create(Rocket::Core::ElementDocument* doc);
	public:

		enum class FocusFlags
		{
			None = 0,
			Focus = (1 << 1),
			Modal = (1 << 2)
		};

		virtual ~ElementDocument(){}

		property LibRocketNet::Context^ Context { LibRocketNet::Context^ get(); }
		property String^ Title { String^ get(); void set(String^ s); }

		property String^ SourceUrl { String^ get(); }

		void PullToFront();
		void PushToBack();

		void Show(FocusFlags focus);
		void Show() { Show(FocusFlags::Focus); }
		void Hide();
		void Close();

		Element^ CreateElement(String^ name);
		Element^ CreateTextNode(String^ text);

		property bool IsModal { bool get(); }
		
		void UpdateLayout();
		void UpdatePosition();
		
	};

}