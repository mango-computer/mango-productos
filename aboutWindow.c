
#ifndef ABOUT_WINDOW_C
#define ABOUT_WINDOW_C


void mostrarAboutWindow()
{

	const gchar *authors[] = {
		"José Andrés Morales <comprasmangocomputer@gmail.com>",
		"",
		"Zorelys Manaure",
		"Paola Morales",
		"Camila Morales",
		NULL
	};

	const gchar *documentors[] = {
		"José Andrés Morales",
		"Zorelys Manaure",
		"Paola Morales",
		NULL
	};

	GdkPixbuf *pix = gdk_pixbuf_new_from_file("mango-icono.ico", NULL);

	gtk_show_about_dialog (GTK_WINDOW(WidgetGlobales->AppWindowProductos),
                         "program-name", TITULO_APLICACION,
                         "version", "1.0",
                         "copyright", "Mango Productos 2017-2018, Mango Computer - comprasmangocomputer@gmail.com",
                         "license-type", GTK_LICENSE_LGPL_2_1,
                         "website", "mailto:comprasmangocomputer@gmail.com",
                         "comments", "",
                         "authors", authors,
                         "documenters", documentors,
                         "logo", pix,
                         "title", TITULO_APLICACION,
                         NULL);

	g_object_unref(pix);

}


#endif
