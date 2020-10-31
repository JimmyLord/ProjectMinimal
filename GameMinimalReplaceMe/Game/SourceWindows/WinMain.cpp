//
// Copyright (c) 2012-2016 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "GamePCH.h"

#include <delayimp.h>

#include "../../../Framework/MyFramework/SourceWindows/MYFWWinMain.h"
#include "../../../Framework/MyFramework/SourceWindows/Screenshot.h"

#define SCREEN_WIDTH    400
#define SCREEN_HEIGHT   600

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#if MYFW_USE_MEMORY_TRACKER
    MyMemory_MarkAllExistingAllocationsAsStatic();
#endif

    GameCore* pGameCore = new GameMinimalReplaceMe;

    int result = MYFWWinMain( pGameCore, SCREEN_WIDTH, SCREEN_HEIGHT );

    delete pGameCore;

    return result;
}

FARPROC WINAPI delayHook(unsigned dliNotify, PDelayLoadInfo pdli)
{
    switch( dliNotify )
    {
    case dliNotePreLoadLibrary:
        if( strcmp( pdli->szDll, "pthreadVC2.dll" ) == 0 )
        {
#if _WIN64
            return (FARPROC)LoadLibrary( "pthreadVC2-x64.dll" );
#else
            return (FARPROC)LoadLibrary( "pthreadVC2-x86.dll" );
#endif
        }
        break;

    default:
        return 0;
    }

    return 0;
}

#if WINVER >= 0x0602
const PfnDliHook __pfnDliNotifyHook2 = delayHook;
#else
PfnDliHook __pfnDliNotifyHook2 = delayHook;
#endif

