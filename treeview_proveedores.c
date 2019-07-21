
#ifndef TREEVIEW_PROVEEDORES_C
#define TREEVIEW_PROVEEDORES_C


//******************************************* create_items_model_proveedores ****************************************
static GtkTreeModel* create_items_model_proveedores()
{
	GtkListStore *model;

	model = gtk_list_store_new(NUM_PROVEEDORES_COLUMNS, 
														G_TYPE_INT, 			// COLUMN_PROVEEDORES_ID
														G_TYPE_STRING,			// COLUMN_PROVEEDORES_NOMBRE_PRODUCTO
														GDK_TYPE_PIXBUF,		// COLUMN_PROVEEDORES_REPUTACION_GENERAL
														GDK_TYPE_PIXBUF,		// COLUMN_PROVEEDORES_REPUTACION_LOCAL
														G_TYPE_STRING,			// COLUMN_PROVEEDORES_NOMBRE_EMPRESA
														G_TYPE_STRING,			// COLUMN_PROVEEDORES_CATEGORIA
														G_TYPE_INT, 			// COLUMN_PROVEEDORES_STOCK COLUMN_PROVEEDORES_PRECIO
														G_TYPE_INT, 			// COLUMN_PROVEEDORES_PRECIO
														G_TYPE_STRING,			// COLUMN_PROVEEDORES_ESTADO
														G_TYPE_STRING,			// COLUMN_PROVEEDORES_MUNICIPIO
														G_TYPE_STRING);			// COLUMN_PROVEEDORES_DIRECCION
 
	return GTK_TREE_MODEL(model);
}

//********************************************** add_columns_proveedores *********************************************
static void add_columns_proveedores(GtkTreeView *treeview)
{
	GtkCellRenderer 	*renderer;
	GtkTreeViewColumn 	*colummnaTreeView;

	// Columna Id Torneo COLUMN_PROVEEDORES_ID
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, "xalign", (gfloat)0.5, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_PROVEEDORES_ID));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", COLUMN_PROVEEDORES_ID, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_PROVEEDORES_ID);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Id Torneo COLUMN_PROVEEDORES_NOMBRE_PRODUCTO
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, "xalign", (gfloat)0.5, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_PROVEEDORES_NOMBRE_PRODUCTO));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Producto", renderer, "text", COLUMN_PROVEEDORES_NOMBRE_PRODUCTO, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_PROVEEDORES_NOMBRE_PRODUCTO);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		


	//Imagen ON OFF COLUMN_PROVEEDORES_REPUTACION_GENERAL
	renderer = gtk_cell_renderer_pixbuf_new();
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Reputación de la Comunidad", renderer, "pixbuf", COLUMN_PROVEEDORES_REPUTACION_GENERAL, NULL);
	g_object_set(colummnaTreeView, "expand", FALSE, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	//Imagen ON OFF COLUMN_PROVEEDORES_REPUTACION_LOCAL
	renderer = gtk_cell_renderer_pixbuf_new();
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Reputación Local", renderer, "pixbuf", COLUMN_PROVEEDORES_REPUTACION_LOCAL, NULL);
	g_object_set(colummnaTreeView, "expand", FALSE, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Nombre  COLUMN_PROVEEDORES_NOMBRE_EMPRESA 
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_PROVEEDORES_NOMBRE_EMPRESA));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Empresa", renderer, "text", COLUMN_PROVEEDORES_NOMBRE_EMPRESA, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_PROVEEDORES_NOMBRE_EMPRESA);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Categoria  COLUMN_PROVEEDORES_CATEGORIA
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_PROVEEDORES_CATEGORIA));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Categoría", renderer, "text", COLUMN_PROVEEDORES_CATEGORIA, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_PROVEEDORES_CATEGORIA);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Stock  COLUMN_PROVEEDORES_STOCK
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_PROVEEDORES_STOCK));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Stock", renderer, "text", COLUMN_PROVEEDORES_STOCK, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_PROVEEDORES_STOCK);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Stock  COLUMN_PROVEEDORES_PRECIO
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_PROVEEDORES_PRECIO));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Precio", renderer, "text", COLUMN_PROVEEDORES_PRECIO, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_PROVEEDORES_PRECIO);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Visitas  COLUMN_PROVEEDORES_ESTADO
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_PROVEEDORES_ESTADO));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Estado", renderer, "text", COLUMN_PROVEEDORES_ESTADO, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_PROVEEDORES_ESTADO);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Visitas  COLUMN_PROVEEDORES_MUNICIPIO
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_PROVEEDORES_MUNICIPIO));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Municipio", renderer, "text", COLUMN_PROVEEDORES_MUNICIPIO, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_PROVEEDORES_MUNICIPIO);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Visitas  COLUMN_PROVEEDORES_DIRECCION
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_PROVEEDORES_DIRECCION));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Dirección", renderer, "text", COLUMN_PROVEEDORES_DIRECCION, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_PROVEEDORES_DIRECCION);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		


}

#endif

