#include "Precompiled.h"
#include <windows.h>

struct __declspec(uuid("2d41a5cf-e276-48d2-933f-063dba343322")) __declspec(novtable)
IApplication : IUnknown
{
    virtual HRESULT __stdcall Start() = 0;
};

class Application : public IApplication
{
	long m_references = 1;
	
	wchar_t* m_applicationName;
	
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
	
	// IUnknown interface implementation
    unsigned long __stdcall AddRef() noexcept
    {
        return InterlockedIncrement(&m_references);
    }

    unsigned long __stdcall Release() noexcept
    {
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
	IApplication* app;
	
	CreateObject(__uuidof(IApplication), (void**)&app);
	
	app->Start();
	
	IApplication* app2 = app;
	
	app->Release();
}