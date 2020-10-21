// borland_register.h : Include file for standard system include files,
// or project specific include files.

#ifndef BORLAND_REGISTER_H
#define BORLAND_REGISTER_H

#include "asmjit/asmjit.h"

namespace borland_register
{
	class translator {
	public:
		void* cdecl_to_register(void* func, int argc);
		void* register_to_cdecl(void* func, int argc);
	private:
		asmjit::JitRuntime runtime_;
	};
}

#endif