#ifndef VISOR_FOTO_WINDOW
#define VISOR_FOTO_WINDOW

G_MODULE_EXPORT gboolean visorFotoWindows_key_press_event(G_GNUC_UNUSED GtkWidget *widget, GdkEvent *event, VISOR_FOTO_WINDOWS *data)
{

//	printf("key: %x\n", ((GdkEventKey*)event)->keyval);

	switch (((GdkEventKey*)event)->keyval)
	{
		case 0xff1b: // GDK_KEY_Escape:
		{
			gtk_widget_destroy(data->visorFotoWindows);

		} break;
	}

	return FALSE;
}

G_MODULE_EXPORT void visorFotoWindows_destroy(G_GNUC_UNUSED GtkWidget *widget, VISOR_FOTO_WINDOWS *data)
{
	g_slice_free(VISOR_FOTO_WINDOWS, data);
	data = NULL;
}

G_MODULE_EXPORT void visorFotoWindows_boton_cerrar_clicked_cb(G_GNUC_UNUSED GtkButton *widget, VISOR_FOTO_WINDOWS *data)
{
	printf("visorFotoWindows_boton_cerrar_clicked_cb\n");

	gtk_widget_destroy(data->visorFotoWindows);
}

void abrirVisor(char *rutaFoto, GtkWidget *ventana)
{

	GtkBuilder		*builder;
	GError 			*error		= NULL;
	VISOR_FOTO_WINDOWS 	*visorData;

	builder = gtk_builder_new();

	if( !gtk_builder_add_from_file(builder,"VisorFotoWindows.ui", &error) )
	{
		g_warning("%s", error->message);
		printf("abrirProductosWindows::VisorFotoWindows.ui -[%s]\n",error->message);

		mostrarMensaje("Error","Qué vergonzoso, no he podido dibujar la ventana de visor de fotos","");

		g_error_free(error);
		error = NULL;
		return;
	}

	visorData = g_slice_new(VISOR_FOTO_WINDOWS);


	GWVF(visorFotoWindows);
	GWVF(visorFotoWindows_foto);
	GWVF(visorFotoWindows_foto_viewport_scroll);

	gtk_image_set_from_file(GTK_IMAGE(visorData->visorFotoWindows_foto), rutaFoto);

	gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(visorData->visorFotoWindows_foto_viewport_scroll), (gint)alto_pantalla*0.8);
	gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(visorData->visorFotoWindows_foto_viewport_scroll),  (gint)ancho_pantalla*0.8);

	/* Connect signals */
	gtk_builder_connect_signals(builder, visorData);

	/* Destroy builder, since we don't need it anymore */
	g_object_unref(G_OBJECT(builder));


	

	gtk_window_set_transient_for(GTK_WINDOW(visorData->visorFotoWindows), GTK_WINDOW(ventana));
	gtk_window_resize(GTK_WINDOW(visorData->visorFotoWindows), (ancho_pantalla*2)/3, (alto_pantalla*2)/3);
	gtk_window_set_modal(GTK_WINDOW(visorData->visorFotoWindows), TRUE);

	apply_css(GTK_WIDGET(visorData->visorFotoWindows), provider);

	gtk_widget_show(visorData->visorFotoWindows);
	

}

#endif
