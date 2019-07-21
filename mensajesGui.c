
#ifndef MENSAJES_GUI_C
#define MENSAJES_GUI_C


void mostrarMensaje(const char *msmTitulo, const char *msm, const char *entrada_user)
{
	GtkWidget *dialog;

	dialog = gtk_message_dialog_new (GTK_WINDOW(WidgetGlobales->AppWindowProductos),
		                               GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
		                               GTK_MESSAGE_INFO,
		                               GTK_BUTTONS_OK,
		                               "%s %s",msmTitulo,entrada_user);
	gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG (dialog), "%s",msm);
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);

}

#endif
