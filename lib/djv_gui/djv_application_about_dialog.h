//------------------------------------------------------------------------------
// Copyright (c) 2004-2012 Darby Johnston
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions, and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions, and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the names of the copyright holders nor the names of any
//   contributors may be used to endorse or promote products derived from this
//   software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//------------------------------------------------------------------------------

//! \file djv_application_about_dialog.h

#ifndef DJV_APPLICATION_ABOUT_DIALOG_H
#define DJV_APPLICATION_ABOUT_DIALOG_H

#include <djv_dialog.h>

class Fl_Image;

namespace djv
{

class Push_Button;

//------------------------------------------------------------------------------
//! \class Application_About_Dialog
//!
//! This class provides a dialog for displaying application about information.
//------------------------------------------------------------------------------

class DJV_GUI_EXPORT Application_About_Dialog : public Dialog
{
public:

    //! Constructor.

    Application_About_Dialog();

    //! Destructor.

    virtual ~Application_About_Dialog();

    void show();

    //! Get the global dialog.

    static Application_About_Dialog * global();

private:

    DJV_CALLBACK(Application_About_Dialog, close_callback, bool);

    std::auto_ptr<Fl_Image> _image;
    Push_Button *           _close_widget;
};

} // djv

#endif // DJV_APPLICATION_ABOUT_DIALOG_H

