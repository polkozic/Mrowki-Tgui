/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2022 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/FileDialogIconLoader.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(TGUI_SYSTEM_WINDOWS) && !defined(TGUI_SYSTEM_LINUX)
    // This struct is used to be able to use make_shared while still keeping the constructor protected.
    struct MakeSharedFileDialogIconLoader : public FileDialogIconLoader {};

    std::shared_ptr<FileDialogIconLoader> FileDialogIconLoader::createInstance()
    {
        // Platform-specific implementations are found in other files. This implementation is only used on platforms
        // where loading the system icons is not (yet) supported.
        return std::make_shared<MakeSharedFileDialogIconLoader>();
    }
#endif

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool FileDialogIconLoader::update()
    {
        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool FileDialogIconLoader::supportsSystemIcons() const
    {
        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool FileDialogIconLoader::hasGenericIcons() const
    {
        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Texture FileDialogIconLoader::getGenericFileIcon(const Filesystem::FileInfo&)
    {
        return {};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void FileDialogIconLoader::requestFileIcons(const std::vector<Filesystem::FileInfo>&)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<Texture> FileDialogIconLoader::retrieveFileIcons()
    {
        return {};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
