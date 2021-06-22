#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

char QUOTE[2048];

static void
get_fortune (GtkLabel *label)
{
        FILE *fp;
        size_t size = sizeof(QUOTE);
        memset(QUOTE, 0, size);
        fp = popen("fortune", "r");
        if (fp != NULL) {
        fread(QUOTE, 1, size, fp);
        gtk_label_set_text(label, QUOTE);
        } else {
                gtk_label_set_text(label, "Please install fortune-mod");
        }
        /* close */
        pclose(fp);
}

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
        GtkWidget *window, *label, *box, *button;

        window = gtk_application_window_new (app);
        gtk_window_set_title (GTK_WINDOW (window), "Fortune");
        gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

        box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 16);

        label = gtk_label_new("");
        get_fortune(GTK_LABEL(label));

        button = gtk_button_new_with_label("New Quote");
        g_signal_connect_swapped(button, "clicked", G_CALLBACK(get_fortune), GTK_LABEL(label));

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

        app = gtk_application_new ("com.gmail.trainraider7.fortune_mod_gtk", G_APPLICATION_FLAGS_NONE);
        g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
        status = g_application_run (G_APPLICATION (app), argc, argv);
        g_object_unref (app);

        return status;
}