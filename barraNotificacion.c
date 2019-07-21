#ifndef BARRA_NOTIFICACION_C
#define BARRA_NOTIFICACION_C


static gboolean cb_timeout_update_barra_notificacion(G_GNUC_UNUSED gpointer data_out )
{

//	printf("cb_timeout_update_barra_notificacion\n");
//*
	WIDGET_GLOBALES *data = (WIDGET_GLOBALES*)data_out;

	//Actualizar label reputacion local
	char *markup = g_markup_printf_escaped("<span color=\"#3579c6\" weight=\"bold\" size=\"large\">%d</span>", vg_reputacion);
	gtk_label_set_markup(GTK_LABEL(data->label_notificacion_reputacion), markup);
	g_free(markup);
	markup = NULL;

	int conectado = FALSO; 

	G_LOCK(vg_saludo_servidor_on);
	{
		conectado = vg_saludo_servidor_on;
	}
	G_UNLOCK(vg_saludo_servidor_on);

	if (conectado)
	{
		gtk_image_set_from_icon_name(GTK_IMAGE(data->imagen_notificacion_conexion), "gtk-connect", GTK_ICON_SIZE_SMALL_TOOLBAR);

	} else {

		gtk_image_set_from_icon_name(GTK_IMAGE(data->imagen_notificacion_conexion), "gtk-disconnect", GTK_ICON_SIZE_SMALL_TOOLBAR);
	}

	G_LOCK(vg_servidorLocal_vivo);
	{
		conectado = vg_servidorLocal_vivo;
	}
	G_UNLOCK(vg_servidorLocal_vivo);


	if (conectado)
	{
		gtk_image_set_from_icon_name(GTK_IMAGE(data->imagen_notificacion_servidor_local), "gtk-apply", GTK_ICON_SIZE_SMALL_TOOLBAR);

	} else {

		gtk_image_set_from_icon_name(GTK_IMAGE(data->imagen_notificacion_servidor_local), "gtk-cancel", GTK_ICON_SIZE_SMALL_TOOLBAR);
	}


//*/

	return VERDADERO;
}


#endif
