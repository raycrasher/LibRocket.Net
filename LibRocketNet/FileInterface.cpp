#include "stdafx.h"
#include <gcroot.h>
#include "Rocket/Core/FileInterface.h"

#include "LibRocketNet.h"
#include "FileInterface.h"
#include "Util.h"



namespace LibRocketNet {

	typedef Rocket::Core::FileHandle RFileHandle;

	class InternalFileInterface : public Rocket::Core::FileInterface {

	public:

		gcroot<LibRocketNet::FileInterface^> _netInterface;

		virtual RFileHandle Open(const Rocket::Core::String& path) {
			return (RFileHandle)_netInterface->Open(Util::ToNetString(path)).ToPointer();
		}

		virtual void Close(RFileHandle file) override {
			_netInterface->Close(IntPtr((void *)file));
		}

		virtual size_t Read(void* buffer, size_t size, RFileHandle file) override {
			return _netInterface->Read(buffer, size, IntPtr((void *)file));
		}
		
		virtual bool Seek(RFileHandle file, long offset, int origin) override {
			return _netInterface->Seek(IntPtr((void *)file), offset, origin);
		}

		virtual size_t Tell(RFileHandle file) override {
			return _netInterface->Tell(IntPtr((void *)file));
		}

		virtual size_t Length(RFileHandle file) override {
			_netInterface->_methodUnused = false;
			auto retval = _netInterface->Length(IntPtr((void *)file));
			if (_netInterface->_methodUnused) return Rocket::Core::FileInterface::Length(file);
			return retval;
		}

		virtual void Release() override {
			_netInterface->_methodUnused = false;
			_netInterface->Release();
			if (_netInterface->_methodUnused) Rocket::Core::FileInterface::Release();
		}


	};

	void FileInterface::SetCore(){
		Rocket::Core::SetFileInterface(_nativeInterface);
	}

	FileInterface::FileInterface()
	{
		_nativeInterface = new InternalFileInterface();
		_nativeInterface->_netInterface = this;
	}

	FileInterface::~FileInterface() {
		delete _nativeInterface;
	}
}