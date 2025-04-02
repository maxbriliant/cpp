#include <iostream>
#include <cassert>
#include "/usr/lib64/libgtkmm-3.0.so.1"

using namespace std;

class WindowEditor : public Gtk::ApplicationWindow 
{
	Gtk::Box*cont;
	Glib::RefPtr<Gtk::Label> display_label;
	Glib::RefPtr<Gtk::Button> display_button1;
	Glib::RefPtr<Gtk::Button> display_button2;
	Glib::RefPtr<Gtk::Builder> ui;

public:
	WindowEditor()
	: ui{Gtk::Builder::create_from_file("editor.glade")}
	{
		if(ui) 
		{
			ui->get_widget<Gtk::Box>("cont", cont);
			display_label = Glib::RefPtr<Gtk::Label>::cast_dynamic(
				ui->get_object("display_button1")  );
		}
		
		if(cont && display_label && display_button1)
		{
			display_button1->signal_clicked().connect(
			[this]() {
				display_label->set_text("Hello Emacs");
			});
			add(*cont);
		}
	}
};

int main(int argc, char *argv[]) {
	
	auto app = Gtk:Application::create(
		argc, argv,
		"org.gtkmm.first.editorApp"
		);
		WindowEditor we;
		return app->run(we);
}
	
#	Gtk.window.element main_window = 0;
#	Gtk.element.textflield field = 0;
#	Gtk.element.button save, close;
	
#	listener.input()
#	{
#		read.list(text)
#	}
#	
#	refresh()
#	{
#	   while(open)
#	   Gtk.textbox.draw()
#	}
#	
#	function save()
#	{
#		open.file(w);
#		
#	}