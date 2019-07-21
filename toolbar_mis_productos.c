#ifndef TOOLBAR_MIS_PRODUCTOS_C
#define TOOLBAR_MIS_PRODUCTOS_C

//*************************************************** toolBoton_mis_productos_nuevo_clicked_cb *************************************
G_MODULE_EXPORT void toolBoton_mis_productos_nuevo_clicked_cb(G_GNUC_UNUSED GtkWidget *button, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	abrirProductosWindows(0);
}

//*************************************************** toolBoton_mis_productos_editar_clicked_cb *************************************
G_MODULE_EXPORT void toolBoton_mis_productos_editar_clicked_cb(G_GNUC_UNUSED GtkWidget *button, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	GtkTreeIter 		iter;
	GtkTreeView 		*treeview 	= GTK_TREE_VIEW(WidgetGlobales->treeview_mis_productos);
	GtkTreeModel 		*model 		= gtk_tree_view_get_model(treeview);
	GtkTreeSelection 	*selection 	= gtk_tree_view_get_selection(treeview);

	if (gtk_tree_selection_get_selected(selection, NULL, &iter))
	{
		GValue vpos 		= {0, };
		gtk_tree_model_get_value(model, &iter, COLUMN_MIS_PRODUCTOS_ID, &vpos);
		unsigned int numPosTreeview = g_value_get_uint(&vpos);
		printf("Editar producto=%u\n", numPosTreeview);
		g_value_unset(&vpos);

		abrirProductosWindows(numPosTreeview);
	}	
}

//*************************************************** toolBoton_mis_productos_eliminar_clicked_cb *************************************
G_MODULE_EXPORT void toolBoton_mis_productos_eliminar_clicked_cb(G_GNUC_UNUSED GtkWidget *button, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("toolBoton_mis_productos_eliminar_clicked_cb\n");
}

//*************************************************** toolBoton_mis_productos_chat_clicked_cb *************************************
G_MODULE_EXPORT void toolBoton_mis_productos_chat_clicked_cb(G_GNUC_UNUSED GtkWidget *button, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("toolBoton_mis_productos_chat_clicked_cb\n");
}

#endif
