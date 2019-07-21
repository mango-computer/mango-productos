
#ifndef MENUBAR_C
#define MENUBAR_C

//***********************************Menu Seguimiento**********************************************************

//***********************************item_seguimiento_nuevo_activate_cb**********************************************************
G_MODULE_EXPORT void item_seguimiento_nuevo_activate_cb(G_GNUC_UNUSED GtkImageMenuItem *item, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("item_seguimiento_nuevo_activate_cb\n");
	abrirNecesidadWindow(0);
}

//***********************************item_seguimiento_editar_activate_cb**********************************************************
G_MODULE_EXPORT void item_seguimiento_editar_activate_cb(G_GNUC_UNUSED GtkImageMenuItem *item, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("item_seguimiento_editar_activate_cb\n");

	GtkTreeIter 		iter;
	GtkTreeView 		*treeview 	= GTK_TREE_VIEW(WidgetGlobales->treeview_seguimiento);
	GtkTreeModel 		*model 		= gtk_tree_view_get_model(treeview);
	GtkTreeSelection 	*selection 	= gtk_tree_view_get_selection(treeview);

	if (gtk_tree_selection_get_selected(selection, NULL, &iter))
	{
		GValue vpos 		= {0, };
		gtk_tree_model_get_value(model, &iter, COLUMN_SEGUIMIENTO_ID, &vpos);
		unsigned int numPosTreeview = g_value_get_uint(&vpos);
		printf("Editar seguimiento=%u\n", numPosTreeview);
		g_value_unset(&vpos);

		abrirNecesidadWindow(numPosTreeview);
	}	
}

//***********************************item_seguimiento_eliminar_activate_cb**********************************************************
G_MODULE_EXPORT void item_seguimiento_eliminar_activate_cb(G_GNUC_UNUSED GtkImageMenuItem *item, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("item_seguimiento_eliminar_activate_cb\n");
}

//***********************************Menu Encontrados**********************************************************

//***********************************item_encontrados_ver_activate_cb**********************************************************
G_MODULE_EXPORT void item_encontrados_ver_activate_cb(G_GNUC_UNUSED GtkImageMenuItem *item, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("item_encontrados_ver_activate_cb\n");
}

//***********************************item_encontrados_grabar_activate_cb**********************************************************
G_MODULE_EXPORT void item_encontrados_grabar_activate_cb(G_GNUC_UNUSED GtkImageMenuItem *item, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("item_encontrados_grabar_activate_cb\n");
}

//***********************************item_encontrados_bloquear_resultado_activate_cb**********************************************************
G_MODULE_EXPORT void item_encontrados_bloquear_resultado_activate_cb(G_GNUC_UNUSED GtkImageMenuItem *item, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("item_encontrados_bloquear_resultado_activate_cb\n");
}

//***********************************Menu Mis Productos**********************************************************

//***********************************item_mis_productos_nuevo_activate_cb**********************************************************
G_MODULE_EXPORT void item_mis_productos_nuevo_activate_cb(G_GNUC_UNUSED GtkImageMenuItem *item, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("item_mis_productos_nuevo_activate_cb\n");

	abrirProductosWindows(0);
}

//***********************************item_mis_productos_editar_activate_cb**********************************************************
G_MODULE_EXPORT void item_mis_productos_editar_activate_cb(G_GNUC_UNUSED GtkImageMenuItem *item, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("item_mis_productos_editar_activate_cb\n");
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

//***********************************item_mis_productos_eliminar_activate_cb**********************************************************
G_MODULE_EXPORT void item_mis_productos_eliminar_activate_cb(G_GNUC_UNUSED GtkImageMenuItem *item, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("item_mis_productos_eliminar_activate_cb\n");
}

//***********************************Menu Mantenimiento**********************************************************

//***********************************item_mantenimiento_perfil_activate_cb**********************************************************
G_MODULE_EXPORT void item_mantenimiento_perfil_activate_cb(G_GNUC_UNUSED GtkImageMenuItem *item, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("item_mantenimiento_perfil_activate_cb\n");
}

//***********************************item_mantenimiento_red_activate_cb**********************************************************
G_MODULE_EXPORT void item_mantenimiento_red_activate_cb(G_GNUC_UNUSED GtkImageMenuItem *item, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("item_mantenimiento_red_activate_cb\n");
}


//***********************************Menu Ayuda**********************************************************

//***********************************item_ayuda_activate_cb**********************************************************
G_MODULE_EXPORT void item_ayuda_activate_cb(G_GNUC_UNUSED GtkImageMenuItem *item, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("item_ayuda_activate_cb\n");
}

//***********************************menubar_about_activate**********************************************************
G_MODULE_EXPORT void item_about_activate_cb(G_GNUC_UNUSED GtkImageMenuItem *item, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	mostrarAboutWindow();
}


#endif
