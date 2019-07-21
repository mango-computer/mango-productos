
#ifndef APPWINDOW_C
#define APPWINDOW_C

G_MODULE_EXPORT void salir(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED APPWINDOW_DATA *data)
{

//*
	char msm[MAXDATASIZE];
	char respuesta[MAXDATASIZE];
	memset(msm,'\0',sizeof(char)*MAXDATASIZE);
	memset(respuesta,'\0',sizeof(char)*MAXDATASIZE);

	int descript = servidor_abrir_conexion();

	if (descript)
	{
		char msm[MAXDATASIZE];
		char respuesta[MAXDATASIZE];
		memset(respuesta,'\0',sizeof(char)*MAXDATASIZE);

		memset(msm,'\0',sizeof(char)*MAXDATASIZE);
		sprintf(msm,"120 chao %u", vg_identificador); 

		if (servidor_send(descript, msm, respuesta))
		{
			if (!strncmp(respuesta,"121 chao ok",11)) //el servidor acepto el saludo 
			{
				printf("S->C: [%s]\n", respuesta);
				memset(msm,'\0',sizeof(char)*MAXDATASIZE);
				strcpy(msm,"100 salir");

				memset(respuesta,'\0',sizeof(char)*MAXDATASIZE);
				if (servidor_send(descript, msm, respuesta))
				{
					if (!strncmp(respuesta,"100 salir",8)) //el servidor acepto el saludo 
					{
						servidor_send(descript, msm, respuesta);
					}
				}
			}
		}

		close(descript);
	}
//*/
	gtk_main_quit();
}


//************************************** AppWindowProductos_key_press_event_cb ****************************************************
G_MODULE_EXPORT gboolean AppWindowProductos_key_press_event_cb(G_GNUC_UNUSED GtkWidget *widget, GdkEvent *event, APPWINDOW_DATA *data)
{

//printf("Key=%X\n",((GdkEventKey*)event)->keyval);

	switch (((GdkEventKey*)event)->keyval)
	{
		case 0xFF1B: // GDK_KEY_Escape:
		{
			GtkWidget *dialog;
			dialog = gtk_message_dialog_new (GTK_WINDOW(GTK_WINDOW(WidgetGlobales->AppWindowProductos)),
						                       GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
						                       GTK_MESSAGE_QUESTION,
						                       GTK_BUTTONS_YES_NO,
						                       "¿Desea cerrar la aplicación?");
		
			gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog),
					"Presione 'no' para cancelar y mantenerse en la aplicación\nPresione 'si' para salir de la aplicación");

			gint res = gtk_dialog_run(GTK_DIALOG (dialog));
			gtk_widget_destroy(dialog);
	
			if (res == GTK_RESPONSE_YES)
			{
				salir(NULL, data);
			}

		} break;

	}

	return FALSE;
}

#endif

