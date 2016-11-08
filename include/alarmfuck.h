#ifndef ORG_WALRUS_ALARMFUCK_ALARMFUCK_H
#define ORG_WALRUS_ALARMFUCK_ALARMFUCK_H

#include "common.h"
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <glibmm/dispatcher.h>
#include <canberra-gtk.h>

class AlarmFuck : public Gtk::Window
{

public:
    AlarmFuck();

private:
    //Signal handlers:
    void on_button_clicked();
    bool on_window_delete(GdkEventAny*);

    //Member widgets:
    Gtk::Box vBox;
    Gtk::Button m_button;
    Gtk::Label questionField, commentField;
    Gtk::Entry answerField;

    // canberra-related
    ca_context* canberraContext;
    ca_proplist* canberraProps;

    // thread flags - see comment in alarmfuck.cc on why they're not atomic
    static bool loopFinished;
    static bool stopPlayback;
    // thread tasks
    static void playback_looper(ca_context* canCon, ca_proplist* canProp);
    static void canberra_callback(ca_context *, uint32_t, int, void *);

    // file-tree
    std::string baseDir;
    bool hasHostages;
    bool decompress_hostage_archive();
    void free_hostages(const std::string&);
    void error_to_user(const std::string&, const std::string&);
    void error_to_user(const AfSystemException& error);
    void error_to_user(const std::string&);
    bool erase_file(std::string);

    // rands
    gint32 randNo1, randNo2;
};

#endif // ORG_WALRUS_ALARMFUCK_ALARMFUCK_H
