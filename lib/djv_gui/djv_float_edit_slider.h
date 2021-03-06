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

//! \file djv_float_edit_slider.h

#ifndef DJV_FLOAT_EDIT_SLIDER_H
#define DJV_FLOAT_EDIT_SLIDER_H

#include <djv_abstract_value_widget.h>

namespace djv
{

class Float_Slider;
class Horizontal_Layout;
class Label;
class Text_Display;
class Text_Edit;
class Tool_Button;

//------------------------------------------------------------------------------
//! \class Float_Edit_Slider
//!
//! This class provides a floating-point edit widget with a slider.
//------------------------------------------------------------------------------

class DJV_GUI_EXPORT Float_Edit_Slider :
    public Widget,
    public Abstract_Float_Input
{
public:

    //! Constructor.

    Float_Edit_Slider(
        double min = 0.0,
        double max = 1.0,
        const String & label = String());

    //! Destructor.

    virtual ~Float_Edit_Slider();

    //! Set whether rhe default is valid.

    virtual void is_default_valid(bool);

    //! Get whether the default is valid.

    bool is_default_valid() const;

    //! Set the value range.

    virtual void range(double min, double max);

    //! Set the slider range.

    virtual void slider_range(double min, double max);

    //! This signal is emitted when the value is changed.

    Signal<double> signal;

    //! Set the label widget.

    void label(Widget *);

    //! Get the label widget.

    Widget * label() const;

    virtual Layout_Item * label_align();

    virtual void text_font(Fl_Font);

    virtual void text_color(Fl_Color);

    virtual Fl_Font text_font() const;

    virtual Fl_Color text_color() const;

    virtual int handle(int);

    virtual Layout_Item * group_align();

private:

    void value_callback();
    void range_callback();
    DJV_CALLBACK(Float_Edit_Slider, widget_callback, const String &);
    DJV_CALLBACK(Float_Edit_Slider, inc_callback, bool);
    DJV_CALLBACK(Float_Edit_Slider, dec_callback, bool);
    DJV_CALLBACK(Float_Edit_Slider, slider_callback, double);
    DJV_CALLBACK(Float_Edit_Slider, default_callback, bool);

    void value_update();
    void range_update();

    Text_Edit *         _widget;
    Float_Slider *      _slider;
    Widget *            _label;
    Tool_Button *       _default_widget;
    Horizontal_Layout * _layout;
};

} // djv

#endif // DJV_FLOAT_EDIT_SLIDER_H

