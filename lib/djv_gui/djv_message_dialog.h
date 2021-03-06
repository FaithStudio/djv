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

//! \file djv_message_dialog.h

#ifndef DJV_MESSAGE_DIALOG_H
#define DJV_MESSAGE_DIALOG_H

#include <djv_dialog.h>

namespace djv
{

class Label;
class Push_Button;

//------------------------------------------------------------------------------
//! \class Abstract_Message_Dialog
//!
//! This class provides the base functionality for message dialogs.
//------------------------------------------------------------------------------

class DJV_GUI_EXPORT Abstract_Message_Dialog : public Dialog
{
public:

    //! Constructor.

    Abstract_Message_Dialog(const String & title = String());

    //! Destructor.

    virtual ~Abstract_Message_Dialog() = 0;

    virtual void dirty();

    virtual const V2i & size_min() const;

private:

    V2i _size_min;
};

//------------------------------------------------------------------------------
//! \class Message_Dialog
//!
//! This class provides a message dialog.
//------------------------------------------------------------------------------

class DJV_GUI_EXPORT Message_Dialog : public Abstract_Message_Dialog
{
public:

    //! Constructor.

    Message_Dialog(const String & label = String());

    //! Destructor.

    virtual ~Message_Dialog();

    //! Set the label.

    void label(const String &);

    //! Get the label.

    const String & label() const;

    virtual void show();

    //! Show the global dialog.

    static void dialog(const String &);

    //! Show the global dialog.

    static void dialog();

private:

    DJV_CALLBACK(Message_Dialog, close_callback, bool);

    Label *       _label;
    Push_Button * _close_widget;
};

} // djv

#endif // DJV_MESSAGE_DIALOG_H
