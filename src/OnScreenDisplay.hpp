#ifndef ONSCREENDISPLAY_HPP_INCLUDED
#define ONSCREENDISPLAY_HPP_INCLUDED

#include <gtk/gtk.h>
#include <thread>
#include <functional>

#include <gtkmm.h>

using namespace std;

class OnScreenDisplay
{
public:
	OnScreenDisplay()
	{
		gtk_init(nullptr, nullptr);

//		GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//		g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
//		gtk_widget_show(window);

		GtkBuilder* builder;
		try{
			builder = gtk_builder_new_from_file("../res/osd.glade");
		}catch(Glib::Error& e){
			cErr<<"Failed to load osd.glade: "<<e.what()<<endl;
		}

		GObject* obj = gtk_builder_get_object(builder, "rootwid");
		gtk_widget_show((GtkWidget*)obj);


		m_thdGtk = new thread(gtk_main);

	}

	void Display();
	void Hide();


private:
	thread* m_thdGtk;



};

#endif // ONSCREENDISPLAY_HPP_INCLUDED
