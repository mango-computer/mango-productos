
#ifndef TOOLBAR_ENCONTRADOS_C
#define TOOLBAR_ENCONTRADOS_C

//*************************************************** toolBoton_encontrados_ver_clicked_cb *************************************
G_MODULE_EXPORT void toolBoton_encontrados_ver_clicked_cb(G_GNUC_UNUSED GtkWidget *button, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("toolBoton_encontrados_ver_clicked_cb\n");

	GtkTreeIter 		iter;
	GtkTreeView 		*treeview 	= GTK_TREE_VIEW(WidgetGlobales->treeview_encontrados);
	GtkTreeModel 		*model 		= gtk_tree_view_get_model(treeview);
	GtkTreeSelection 	*selection 	= gtk_tree_view_get_selection(treeview);

	if (gtk_tree_selection_get_selected(selection, NULL, &iter))
	{
		GValue vpos 		= {0, };
		gtk_tree_model_get_value(model, &iter, COLUMN_ENCONTRADOS_AUTO, &vpos);
		int numPosTreeview = g_value_get_int(&vpos);
		g_value_unset(&vpos);
		printf("Encontrado: %d\n",numPosTreeview);
		abrir_encontradoProducto(numPosTreeview);
	}	
}

//*************************************************** toolBoton_encontrados_grabar_clicked_cb *************************************
G_MODULE_EXPORT void toolBoton_encontrados_grabar_clicked_cb(G_GNUC_UNUSED GtkWidget *button, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("toolBoton_encontrados_grabar_clicked_cb\n");
}

//*************************************************** toolBoton_encontrados_bloquear_clicked_cb *************************************
G_MODULE_EXPORT void toolBoton_encontrados_bloquear_clicked_cb(G_GNUC_UNUSED GtkWidget *button, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("toolBoton_encontrados_bloquear_clicked_cb\n");
}


//*************************************************** toolBoton_encontrados_chat_clicked_cb *************************************
G_MODULE_EXPORT void toolBoton_encontrados_chat_clicked_cb(G_GNUC_UNUSED GtkWidget *button, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("toolBoton_encontrados_chat_clicked_cb\n");
}

#endif
