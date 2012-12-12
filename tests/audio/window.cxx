//#define DJV_DEBUG

#include "audio.h"

#include <djv_ui/layout_row.h>

namespace audio {

Window::Window(const String & in) :
  _play(false),
  _frame(0),
  _idle_init(false),
  _idle_frame(0)
{
  DJV_DEBUG(string::Format("Window::Window(%%)").arg(int64_t(this)));

  // Initialize.
  
  try { _movie.init(in); }
  catch (Error in) { application()->error(in); }
  
  _widget = new djv_ui::image::View;
  _play_widget = new djv_ui::Tool_Button("playback_forward");
  _play_widget->type(djv_ui::tool_button::TOGGLE);
  _slider = new djv_ui::Int_Slider;
  
  djv_ui::Layout_V * layout = new djv_ui::Layout_V(this);
  layout->margin(0);
  layout->spacing(0);
  layout->add(_widget);
  layout->stretch(_widget);
  djv_ui::Layout_H * layout_h = new djv_ui::Layout_H(layout);
  layout_h->margin(0);
  layout_h->add(_play_widget);
  layout_h->add(_slider);
  layout_h->stretch(_slider);

  _slider->range(0, static_cast<int>(_movie.info_time().list.size()) - 1);
  
  dirty();
  size(_movie.info().size + V2i(0, size_min().y));

  frame_update();
  play_update();

  _play_widget->signal.set(this, play_callback);
  _slider->signal.set(this, frame_callback);
  close_signal.set(this, close_callback);
  
  show();
}

void Window::play(bool in)
{
  DJV_DEBUG("Window::play");
  DJV_DEBUG_PRINT("in = " << in);
  
  _play = in;
  
  play_update();
}

void Window::play_callback(bool in)
{
  play(in);
}

void Window::play_update()
{
  DJV_DEBUG(string::Format("Window::play_update(%%)").arg(int64_t(this)));
  DJV_DEBUG_PRINT("play = " << _play);
  
  callbacks(false);
  
  _play_widget->set(_play);
  
  if (_play)
  {
    _audio = std::auto_ptr<Audio>(new Audio);
    try
    {
      _audio->init(_movie.info_audio(), &_audio_buffer);
    }
    catch (Error in)
    {
      _audio.reset();
      application()->error(in);
    }

    _idle_init = false;
    
    application()->idle_add(this);
  }
  else
  {
    _audio.reset();
    _audio_buffer.clear();
    
    application()->idle_del(this);
  }
  
  callbacks(true);
}

void Window::frame_callback(int in)
{
  play(false);

  _frame = in;
  
  frame_update();
}

void Window::frame_update()
{
  DJV_DEBUG(string::Format("Window::frame_update(%%)").arg(int64_t(this)));
  DJV_DEBUG_PRINT("frame = " << _frame);
  
  callbacks(false);
  
  _slider->set(_frame);
  
  _widget->set(_movie.image(_frame));
  _widget->redraw();

  callbacks(true);
}

void Window::idle()
{
  DJV_DEBUG(string::Format("Window::idle(%%)").arg(int64_t(this)));
  
  if (_audio.get())
  {
    int size = _audio_buffer.size();
    DJV_DEBUG_PRINT("audio size = " << size);
    
    if (! size)
    {
      // Reset audio.
      
      _audio->stop();
      _audio_buffer.clear();
      _movie.audio_seek(_frame);
      _idle_init = false;
    }

    // Fill audio buffer.

    const int min = _audio_buffer.min();
    do
    {
      int16_t * p = _audio_buffer.push();
      if (! p) break;
      _movie.audio(p, _audio_buffer.chunk() / _movie.info_audio().channel);
    }
    while (++size < min)
      ;
  }
  
  if (! _idle_init)
  {
    DJV_DEBUG_PRINT("init");
    
    if (_audio.get()) _audio->start();
    _idle_timer.start();
    _idle_frame = 0;
    _idle_init = true;
  }
  else
  {
    _idle_timer.check();
  }
  
  const double time = _audio.get() ? _audio->time() : _idle_timer.seconds();
  DJV_DEBUG_PRINT("time = " << time);
  if (time > 0.0)
  {
    const int64_t absolute_frame = math::floor(time *
      djv_image::time::speed_to_float(_movie.info_time().speed)
    );
    int inc = absolute_frame - _idle_frame;
    _idle_frame = absolute_frame;
    DJV_DEBUG_PRINT("absolute frame = " << absolute_frame);
    DJV_DEBUG_PRINT("inc = " << inc);
    
    if (inc)
    {
      _frame += inc;
      if (_frame >= static_cast<int>(_movie.info_time().list.size()))
      {
        _frame = 0;
        
        if (_audio.get()) _audio->stop();
        _audio_buffer.clear();
    
        _idle_init = false;
      }
  
      frame_update();
    }
  }
}

void Window::close_callback(bool)
{
  application()->window_del(this);
}

}
