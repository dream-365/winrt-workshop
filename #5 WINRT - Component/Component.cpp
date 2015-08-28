// Component.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Component.h"

using namespace ABI::Component;

namespace ABI {
	namespace Component {
		class Application : IApplication {
			virtual HRESULT STDMETHODCALLTYPE Start(void) {
				return S_OK;
			}
		};
	} /*Component*/
}



