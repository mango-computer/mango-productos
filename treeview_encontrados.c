
#ifndef TREEVIEW_ENCONTRADOS_C
#define TREEVIEW_ENCONTRADOS_C

//**************************************
static void recargarTreeview_encontrados()
{
	if (!vg_index_seguimiento) return;

	GtkTreeIter iter;
	GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(WidgetGlobales->treeview_encontrados));
	gtk_list_store_clear(GTK_LIST_STORE(model));

	int i=0;

	for (GSList *iterador2=gslista_encontrados[vg_index_seguimiento];iterador2;iterador2=iterador2->next)
	{
		REGBD_ENCONTRADO *regnuevo = (REGBD_ENCONTRADO*)iterador2->data;

		gtk_list_store_append(GTK_LIST_STORE(model), &iter);
		gtk_list_store_set (GTK_LIST_STORE(model), &iter, 
									COLUMN_ENCONTRADOS_AUTO,				++i,
									COLUMN_ENCONTRADOS_IMAGEN_ARCHIVADO,	NULL,
									COLUMN_ENCONTRADOS_NOMBRE_PRODUCTO,		regnuevo->nombre,	
									COLUMN_ENCONTRADOS_CATEGORIA,			NULL,
									COLUMN_ENCONTRADOS_STOCK,				regnuevo->disponibilidad,
									COLUMN_ENCONTRADOS_PRECIO,				regnuevo->precio,
									COLUMN_ENCONTRADOS_ESTADO,				estadosVenezuela[regnuevo->codEstado],
									COLUMN_ENCONTRADOS_MUNICIPIO,			getStrMinicipio(regnuevo->codEstado, regnuevo->codMunicipio),
									COLUMN_ENCONTRADOS_DIRECCION,			regnuevo->direccion_empresa,
									COLUMN_ENCONTRADOS_TELEFONO_EMPRESA,	regnuevo->telefono,
									COLUMN_ENCONTRADOS_NOMBRE_EMPRESA,		regnuevo->nombre_empresa,
									COLUMN_ENCONTRADOS_REPUTACION,			0,
									-1);
	}

}


//******************************************* create_items_model_encontrados ****************************************
static GtkTreeModel* create_items_model_encontrados()
{
	GtkListStore *model;
//	GtkTreeIter iter;

	model = gtk_list_store_new(NUM_ENCONTRADOS_COLUMNS, 
											G_TYPE_INT, 			// COLUMN_ENCONTRADOS_AUTO
											GDK_TYPE_PIXBUF,		// COLUMN_ENCONTRADOS_IMAGEN_ARCHIVADO
											G_TYPE_STRING, 			// COLUMN_ENCONTRADOS_NOMBRE_PRODUCTO
											G_TYPE_STRING, 			// COLUMN_ENCONTRADOS_CATEGORIA
											G_TYPE_INT, 			// COLUMN_ENCONTRADOS_STOCK
											G_TYPE_INT, 			// COLUMN_ENCONTRADOS_PRECIO
											G_TYPE_STRING,			// COLUMN_ENCONTRADOS_ESTADO
											G_TYPE_STRING,			// COLUMN_ENCONTRADOS_MUNICIPIO
											G_TYPE_STRING,			// COLUMN_ENCONTRADOS_DIRECCION
											G_TYPE_STRING,			// COLUMN_ENCONTRADOS_TELEFONO_EMPRESA
											G_TYPE_STRING,			// COLUMN_ENCONTRADOS_NOMBRE_EMPRESA
											GDK_TYPE_PIXBUF);		// COLUMN_ENCONTRADOS_REPUTACION

 
	return GTK_TREE_MODEL(model);
}

//********************************************** add_columns_encontrados *********************************************
static void add_columns_encontrados(GtkTreeView *treeview)
{

	GtkCellRenderer 	*renderer;
	GtkTreeViewColumn 	*colummnaTreeView;

	// Columna Nombre  COLUMN_ENCONTRADOS_AUTO 
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_ENCONTRADOS_AUTO));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Id", renderer, "text", COLUMN_ENCONTRADOS_AUTO, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_ENCONTRADOS_AUTO);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		


	//Imagen ON OFF COLUMN_ENCONTRADOS_IMAGEN_ARCHIVADO
	renderer = gtk_cell_renderer_pixbuf_new();
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("", renderer, "pixbuf", COLUMN_ENCONTRADOS_IMAGEN_ARCHIVADO, NULL);
	g_object_set(colummnaTreeView, "expand", FALSE, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Nombre  COLUMN_ENCONTRADOS_NOMBRE_PRODUCTO 
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_ENCONTRADOS_NOMBRE_PRODUCTO));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Nombre", renderer, "text", COLUMN_ENCONTRADOS_NOMBRE_PRODUCTO, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_ENCONTRADOS_NOMBRE_PRODUCTO);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Categoria  COLUMN_ENCONTRADOS_CATEGORIA
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_ENCONTRADOS_CATEGORIA));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Categoría", renderer, "text", COLUMN_ENCONTRADOS_CATEGORIA, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_ENCONTRADOS_CATEGORIA);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Cantidad  COLUMN_ENCONTRADOS_STOCK
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_ENCONTRADOS_STOCK));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Stock", renderer, "text", COLUMN_ENCONTRADOS_STOCK, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_ENCONTRADOS_STOCK);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Cantidad  COLUMN_ENCONTRADOS_PRECIO
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_ENCONTRADOS_PRECIO));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Precio", renderer, "text", COLUMN_ENCONTRADOS_PRECIO, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_ENCONTRADOS_PRECIO);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Estado  COLUMN_ENCONTRADOS_ESTADO
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_ENCONTRADOS_ESTADO));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Estado", renderer, "text", COLUMN_ENCONTRADOS_ESTADO, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_ENCONTRADOS_ESTADO);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Estado  COLUMN_ENCONTRADOS_MUNICIPIO
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_ENCONTRADOS_MUNICIPIO));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Municipio", renderer, "text", COLUMN_ENCONTRADOS_MUNICIPIO, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_ENCONTRADOS_MUNICIPIO);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Estado  COLUMN_ENCONTRADOS_DIRECCION
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_ENCONTRADOS_DIRECCION));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Dirección", renderer, "text", COLUMN_ENCONTRADOS_DIRECCION, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_ENCONTRADOS_DIRECCION);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		


	// Columna Estado  COLUMN_ENCONTRADOS_TELEFONO_EMPRESA
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_ENCONTRADOS_TELEFONO_EMPRESA));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Teléfono", renderer, "text", COLUMN_ENCONTRADOS_TELEFONO_EMPRESA, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_ENCONTRADOS_TELEFONO_EMPRESA);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Empresa  COLUMN_ENCONTRADOS_NOMBRE_EMPRESA
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_ENCONTRADOS_NOMBRE_EMPRESA));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Empresa", renderer, "text", COLUMN_ENCONTRADOS_NOMBRE_EMPRESA, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_ENCONTRADOS_NOMBRE_EMPRESA);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	//Imagen Reputacion COLUMN_ENCONTRADOS_REPUTACION
	renderer = gtk_cell_renderer_pixbuf_new();
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Reputación", renderer, "pixbuf", COLUMN_ENCONTRADOS_REPUTACION, NULL);
	g_object_set(colummnaTreeView, "expand", FALSE, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		


}

#endif

