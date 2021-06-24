#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
        GtkLabel * label;
        char * text;
        size_t size;
} labeldata;

static void
get_fortune (labeldata * data)
{       
        GtkLabel *label = data->label;
        char * quote = data->text;
        size_t size = data->size;
        FILE *fp = popen("fortune", "r");
        
        memset(quote, 0, size);
        if (fp != NULL) {
                fread(quote, 1, size, fp);
                gtk_label_set_text(label, quote);
        } else {
                gtk_label_set_text(label, "Please install fortune-mod");
        }

        pclose(fp);
}

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
        GtkWidget *window = gtk_application_window_new (app);
        gtk_window_set_title (GTK_WINDOW (window), "Fortune");
        gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 16);

        GtkWidget *label = gtk_label_new("");
        labeldata * dptr = (labeldata *)user_data;
        dptr->label = GTK_LABEL(label);
        get_fortune(dptr);

        GtkWidget *button = gtk_button_new_with_label("New Quote");
        g_signal_connect_swapped(button, "clicked", G_CALLBACK(get_fortune), dptr);

        gtk_container_add(GTK_CONTAINER(window), box);
        gtk_container_add(GTK_CONTAINER(box), button);
        gtk_container_add(GTK_CONTAINER(box), label);

        gtk_widget_show_all (window);
}

int
main (int    argc,
      char *argv[])
{
        GtkApplication *app;
        int status;

        size_t size = 2048;
        char quote[size];
        memset(quote, 0, size);
        labeldata data = {NULL, quote, size};
        labeldata * dptr = &data;

        app = gtk_application_new ("com.gmail.trainraider7.fortune_mod_gtk", G_APPLICATION_FLAGS_NONE);
        g_signal_connect (app, "activate", G_CALLBACK (activate), (gpointer)dptr);
        status = g_application_run (G_APPLICATION (app), argc, argv);

        g_object_unref (app);

        return status;
}
