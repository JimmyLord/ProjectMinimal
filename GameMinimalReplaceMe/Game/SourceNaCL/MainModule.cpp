#include "GamePCH.h"

#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/gles2/gl2ext_ppapi.h"
#include "../SourceCommon/Core/GameMinimalReplaceMe.h"
#include "../../Framework/MyFramework/SourceNaCL/MainInstance.h"

// The Module class.  The browser calls the CreateInstance() method to create
// an instance of your NaCl module on the web page.  The browser creates a new
// instance for each <embed> tag with type="application/x-nacl".
class MainModule : public pp::Module
{
public:
    MainModule() : pp::Module()
    {
        g_pGameCore = MyNew GameMinimalReplaceMe();
    }

    virtual ~MainModule()
    {
        glTerminatePPAPI();
    }

    // Called by the browser when the module is first loaded and ready to run.
    // This is called once per module, not once per instance of the module on
    // the page.
    virtual bool Init()
    {
        return glInitializePPAPI( get_browser_interface() ) == GL_TRUE;
    }

    // Create and return a game instance object.
    // @param[in] instance The browser-side instance.
    // @return the plugin-side instance.
    virtual pp::Instance* CreateInstance(PP_Instance instance)
    {
        return MyNew MainInstance(instance);
    }
};

namespace pp
{
    // Factory function called by the browser when the module is first loaded.
    // The browser keeps a singleton of this module.  It calls the
    // CreateInstance() method on the object you return to make instances.  There
    // is one instance per <embed> tag on the page.  This is the main binding
    // point for your NaCl module with the browser.
    Module* CreateModule()
    {
        return MyNew MainModule();
    }
} // namespace pp
