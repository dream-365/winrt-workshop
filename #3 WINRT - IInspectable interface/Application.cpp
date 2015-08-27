#include "Precompiled.h"
#include <windows.h>
#include <winstring.h>
#include <wrl.h>
#include <iostream>
#include <string>
using namespace std;

#pragma comment(lib, "runtimeobject")

using namespace Microsoft::WRL;

struct __declspec(uuid("2d41a5cf-e276-48d2-933f-063dba343322")) __declspec(novtable)
IApplication : IInspectable
{
    virtual HRESULT __stdcall Start() = 0;
};

class Application : public IApplication
{
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

    HRESULT __stdcall Start() noexcept
    {
        Trace(L"Application Start...\n");
        return S_OK;
    }
	
	// IInspectable interface implementation
	HRESULT GetIids(ULONG *iidCount,
					IID ** iids ) noexcept {
		*iidCount = 0;
		
		*iids = static_cast<GUID *>(CoTaskMemAlloc(sizeof(GUID) * 1));
		
		(*iids)[0] = __uuidof(IApplication); 
		
		*iidCount = 1;
						
		return S_OK;
	}
	
	HRESULT GetRuntimeClassName(HSTRING *className) noexcept {
		
		LPCWSTR text = L"Application.Name";
				
		WindowsCreateString(text, lstrlen(text), className);
		
		return E_NOTIMPL;
	}
	
	HRESULT GetTrustLevel(TrustLevel *trustLevel) noexcept {
		
		*trustLevel = BaseTrust;
		
		return S_OK;
	}

	// IUnknown interface implementation
    unsigned long __stdcall AddRef() noexcept
    {
		Trace(L"Reference + 1\n");
		
        return InterlockedIncrement(&m_references);
    }

    unsigned long __stdcall Release() noexcept
    {
		Trace(L"Reference - 1\n");
		
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

HRESULT CreateObject(GUID const & id, void ** obj) noexcept
{
	   if (id == __uuidof(IApplication))
        {
            *obj = static_cast<IApplication*>(new (std::nothrow) Application);
        }
        else
        {
            *obj = nullptr;
			
            return E_NOINTERFACE;
        }
	
	return S_OK;
}

int main()
{
	ComPtr<IApplication> app;
	
	CreateObject(__uuidof(IApplication), (void**)app.GetAddressOf());
	
	ComPtr<IInspectable> obj;
	
	app->QueryInterface(__uuidof(IInspectable), (void**)obj.GetAddressOf());
	
	ULONG idCount;
	
	IID* iids; 
	
	HSTRING className;
	
	obj->GetIids(&idCount, &iids);
	
	obj->GetRuntimeClassName(&className);
	
	cout << "id count: " << idCount << endl;
	
	UINT32 strlen;
	
	PCWSTR text = WindowsGetStringRawBuffer(className, &strlen);
	
	wcout << "string length: " << strlen << endl;
	wcout << "class name: " << text << endl;
}