// Component.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Component.h"
#pragma comment(lib, "runtimeobject")

using namespace ABI::Component;

namespace ABI {
	namespace Component {
		class Application : public IApplication {
			long m_references = 1;

		public:

			Application()
			{
				Trace(L"Application construct\n");
			}

			~Application()
			{
				Trace(L"Application destruct\n");
			}

			virtual HRESULT STDMETHODCALLTYPE Start(void) {
				Trace(L"Start the application\n");
				return S_OK;
			}

			// IInspectable interface implementation
			HRESULT STDMETHODCALLTYPE GetIids(ULONG *iidCount,
				IID ** iids) noexcept {
				*iidCount = 0;

				*iids = static_cast<GUID *>(CoTaskMemAlloc(sizeof(GUID) * 1));

				(*iids)[0] = __uuidof(IApplication);

				*iidCount = 1;

				return S_OK;
			}

			HRESULT STDMETHODCALLTYPE  GetRuntimeClassName(HSTRING *className) noexcept {

				LPCWSTR text = L"Application.Name";

				WindowsCreateString(text, lstrlen(text), className);

				return S_OK;
			}

			HRESULT STDMETHODCALLTYPE GetTrustLevel(TrustLevel *trustLevel) noexcept {

				*trustLevel = BaseTrust;

				return S_OK;
			}

			// IUnknown interface implementation
			unsigned long __stdcall AddRef() noexcept
			{
				Trace(L"ApplicationReference + 1\n");

				return InterlockedIncrement(&m_references);
			}

			unsigned long __stdcall Release() noexcept
			{
				Trace(L"ApplicationReference - 1\n");

				unsigned long const count = InterlockedDecrement(&m_references);

				if (0 == count)
				{
					delete this;
				}

				return count;
			}

			HRESULT __stdcall QueryInterface(GUID const & id,
				void ** object) noexcept
			{
				if (id == __uuidof(IApplication) ||
					id == __uuidof(IInspectable) ||
					id == __uuidof(IUnknown))
				{
					*object = static_cast<IApplication *>(this);
				}
				else
				{
					*object = nullptr;
					return E_NOINTERFACE;
				}

				static_cast<IUnknown *>(*object)->AddRef();

				return S_OK;
			}
		};

		class ApplicationFactory : public IActivationFactory
		{
			long m_references = 1;

		public:

			// IInspectable interface implementation
			HRESULT STDMETHODCALLTYPE GetIids(ULONG *iidCount,
				IID ** iids) noexcept {
				*iidCount = 0;

				*iids = static_cast<GUID *>(CoTaskMemAlloc(sizeof(GUID) * 1));

				(*iids)[0] = __uuidof(IActivationFactory);

				*iidCount = 1;

				return S_OK;
			}

			HRESULT STDMETHODCALLTYPE  GetRuntimeClassName(HSTRING *className) noexcept {

				LPCWSTR text = L"ApplicationFactory";

				WindowsCreateString(text, lstrlen(text), className);

				return S_OK;
			}

			HRESULT STDMETHODCALLTYPE GetTrustLevel(TrustLevel *trustLevel) noexcept {

				*trustLevel = BaseTrust;

				return S_OK;
			}

			// IUnknown interface implementation
			unsigned long __stdcall AddRef() noexcept
			{
				Trace(L"ApplicationFactoryReference + 1\n");

				return InterlockedIncrement(&m_references);
			}

			unsigned long __stdcall Release() noexcept
			{
				Trace(L"ApplicationFactoryReference - 1\n");

				unsigned long const count = InterlockedDecrement(&m_references);

				if (0 == count)
				{
					delete this;
				}

				return count;
			}

			HRESULT __stdcall QueryInterface(GUID const & id,
				void ** object) noexcept
			{
				if (id == __uuidof(IActivationFactory) ||
					id == __uuidof(IInspectable) ||
					id == __uuidof(IUnknown))
				{
					*object = static_cast<IActivationFactory *>(this);
				}
				else
				{
					*object = nullptr;
					return E_NOINTERFACE;
				}

				static_cast<IUnknown *>(*object)->AddRef();

				return S_OK;
			}


			HRESULT __stdcall ActivateInstance(IInspectable ** instance) noexcept
			{
				*instance = static_cast<ABI::Component::IApplication *>(new (std::nothrow) Application);

				return *instance ? S_OK : E_OUTOFMEMORY;
			}
		};
	} /*Component*/
}

HRESULT WINAPI DllGetActivationFactory(
	_In_  HSTRING            activatableClassId,
	_Out_ IActivationFactory **factory
	)
{
	Trace(L"DllGetActivationFactory");

	*factory = new ABI::Component::ApplicationFactory();

	return S_OK;
}


