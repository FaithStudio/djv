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

//! \file djv_ppm_save_widget.cpp

#include <djv_ppm_save_widget.h>

#include <djv_group_box.h>
#include <djv_label.h>
#include <djv_radio_button_group.h>
#include <djv_row_layout.h>
#include <djv_style.h>

namespace djv_ppm
{

//------------------------------------------------------------------------------
// djv_image_save_widget
//------------------------------------------------------------------------------

extern "C" {

DJV_PLUGIN_EXPORT Plugin * djv_image_save_widget()
{
    return new Save_Widget;
}

}

//------------------------------------------------------------------------------
// Save_Widget
//------------------------------------------------------------------------------

namespace
{

const String
    label_type_group = "File Type",
    label_data_group = "File Data";

} // namespace

Save_Widget::Save_Widget() :
    _plugin     (0),
    _type       (TYPE_AUTO),
    _data       (DATA_BINARY),
    _type_widget(0),
    _data_widget(0)
{
    // Create widgets.

    Group_Box * type_group = new Group_Box(label_type_group);

    _type_widget = new Radio_Button_Group(label_type());

    Group_Box * data_group =
        new Group_Box(label_data_group);

    _data_widget = new Radio_Button_Group(label_data());

    // Layout.

    Vertical_Layout * layout = new Vertical_Layout(this);
    layout->margin(Style::global()->margin_large());
    layout->spacing(Style::global()->spacing_large());

    layout->add(type_group);
    type_group->layout()->add(_type_widget);

    layout->add(data_group);
    data_group->layout()->add(_data_widget);

    layout->add_stretch();

    // Initialize.

    plugin_update();
    widget_update();

    // Callbacks.

    _type_widget->signal.set(this, type_callback);
    _data_widget->signal.set(this, data_callback);
}

Save_Widget::~Save_Widget()
{}

Plugin * Save_Widget::copy() const
{
    return new Save_Widget;
}

String Save_Widget::name() const
{
    return djv_ppm::name;
}

void Save_Widget::set(Image_Io_Base * in)
{
    _plugin = in;

    widget_update();
}

void Save_Widget::type_callback(int in)
{
    if (! _plugin)
    {
        return;
    }

    _type = static_cast<TYPE>(in);

    plugin_update();

    signal.emit(_plugin);
}

void Save_Widget::data_callback(int in)
{
    if (! _plugin)
    {
        return;
    }

    _data = static_cast<DATA>(in);

    plugin_update();

    signal.emit(_plugin);
}

void Save_Widget::plugin_update()
{
    callbacks(false);

    if (_plugin)
    {
        String tmp;
        tmp << _type;
        _plugin->option(_plugin->options()[Save::TYPE_OPTION], &tmp);
        tmp << _data;
        _plugin->option(_plugin->options()[Save::DATA_OPTION], &tmp);
    }

    callbacks(true);
}

void Save_Widget::widget_update()
{
    callbacks(false);

    try
    {
        if (_plugin)
        {
            String tmp;
            tmp = _plugin->option(_plugin->options()[Save::TYPE_OPTION]);
            tmp >> _type;
            tmp = _plugin->option(_plugin->options()[Save::DATA_OPTION]);
            tmp >> _data;
        }
    }
    catch (String) {}

    _type_widget->set(_type);
    _data_widget->set(_data);

    callbacks(true);
}

} // djv_ppm


