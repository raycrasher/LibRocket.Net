#pragma once

using namespace System;

namespace LibRocketNet {

	public ref class FileInterface abstract
	{
	internal:
		IntPtr _fileInterfacePtr;
		bool _methodUnused;
	protected:
		FileInterface();
	public:
		virtual ~FileInterface();

		virtual IntPtr Open(String^ filename) abstract;
		virtual void Close(IntPtr filehandle) abstract;
		virtual size_t Read(void *buffer, size_t size, IntPtr filehandle) abstract;
		virtual bool Seek(IntPtr filehandle, long offset, int origin) abstract;
		virtual size_t Tell(IntPtr filehandle) abstract;
		virtual size_t Length(IntPtr filehandle) { _methodUnused = true; }
	};

}