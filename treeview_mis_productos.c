
#ifndef TREEVIEW_MIS_PRODUCTOS_C
#define TREEVIEW_MIS_PRODUCTOS_C


static void recargarTreeview_mis_productos()
{
	GtkTreeIter iter;
	GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(WidgetGlobales->treeview_mis_productos));
	
	gtk_list_store_clear(GTK_LIST_STORE(model));

	//Liberar GSList
	g_slist_free_full(lista_productos, (GDestroyNotify)liberarMemoria_lista_productos);
	lista_productos = NULL;


	FILE *fichero = fopen(BD_PRODUCTOS_DAT, "rb");

	if (fichero)
	{
		fseek(fichero, 0L, SEEK_SET);
		REGBD_PRODUCTO registro;
		memset(&registro, 0, sizeof(REGBD_PRODUCTO));

		fseek(fichero, (long int)(sizeof(REGBD_PRODUCTO)), SEEK_SET);
		char msm[1024];

		while(fread(&registro, sizeof(REGBD_PRODUCTO), 1,fichero))
		{
		
			if (!registro.activo) continue;

			REGBD_PRODUCTO *registro2lista = (REGBD_PRODUCTO*)malloc(sizeof(REGBD_PRODUCTO));
			memcpy(registro2lista, &registro, sizeof(REGBD_PRODUCTO));
			lista_productos = g_slist_prepend(lista_productos, registro2lista);

			memset(msm, '\0', sizeof(char)*1024);

			for (int i=0;i<16;i++)
			{
				if (registro.flag_categoria & BITSET[i])
				{
					strcat(msm, str_sector[i]);
				}
			}

			gtk_list_store_append(GTK_LIST_STORE(model), &iter);
			gtk_list_store_set (GTK_LIST_STORE(model), &iter, 
						COLUMN_MIS_PRODUCTOS_ID,  				registro.idProducto,
						COLUMN_MIS_PRODUCTOS_NOMBRE_PRODUCTO,	registro.nombre,
						COLUMN_MIS_PRODUCTOS_FABRICANTE,		registro.fabricante,
						COLUMN_MIS_PRODUCTOS_CATEGORIA,			msm,
						COLUMN_MIS_PRODUCTOS_STOCK,   			registro.disponibilidad, 
						COLUMN_MIS_PRODUCTOS_PRECIO,  			registro.precio, 
						COLUMN_MIS_PRODUCTOS_UNIDAD,			str_unidades[registro.codUnidad],
						COLUMN_MIS_PRODUCTOS_PRESENTACION,		str_presentacion[registro.codPresentacion],
						COLUMN_MIS_PRODUCTOS_VISITAS,			0,
						-1);	

			memset(&registro, 0, sizeof(REGBD_PRODUCTO));
		} 
	
		fclose(fichero);

		lista_productos = g_slist_reverse(lista_productos);
	}	
}


//******************************************* create_items_model_mis_productos ****************************************
static GtkTreeModel* create_items_model_mis_productos()
{
	GtkListStore *model;

	model = gtk_list_store_new(NUM_MIS_PRODUCTOS_COLUMNS, 
														G_TYPE_UINT,			//	COLUMN_MIS_PRODUCTOS_ID,
														G_TYPE_STRING,			//	COLUMN_MIS_PRODUCTOS_NOMBRE_PRODUCTO,
														G_TYPE_STRING,			//	COLUMN_MIS_PRODUCTOS_FABRICANTE,
														G_TYPE_STRING,			//  COLUMN_MIS_PRODUCTOS_CATEGORIA,
														G_TYPE_INT,				//	COLUMN_MIS_PRODUCTOS_STOCK,
														G_TYPE_ULONG,			//	COLUMN_MIS_PRODUCTOS_PRECIO,
														G_TYPE_STRING,			//	COLUMN_MIS_PRODUCTOS_UNIDAD,
														G_TYPE_STRING,			//	COLUMN_MIS_PRODUCTOS_PRESENTACION,
														G_TYPE_INT);			//	COLUMN_MIS_PRODUCTOS_VISITAS,
 
	return GTK_TREE_MODEL(model);
}

//********************************************** add_columns_mis_productos *********************************************
static void add_columns_mis_productos(GtkTreeView *treeview)
{

	GtkCellRenderer 	*renderer;
	GtkTreeViewColumn 	*colummnaTreeView;

	// Columna Id Torneo COLUMN_MIS_PRODUCTOS_ID
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, "xalign", (gfloat)0.5, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_MIS_PRODUCTOS_ID));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", COLUMN_MIS_PRODUCTOS_ID, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_MIS_PRODUCTOS_ID);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Nombre  COLUMN_MIS_PRODUCTOS_NOMBRE_PRODUCTO 
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_MIS_PRODUCTOS_NOMBRE_PRODUCTO));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Producto", renderer, "text", COLUMN_MIS_PRODUCTOS_NOMBRE_PRODUCTO, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_MIS_PRODUCTOS_NOMBRE_PRODUCTO);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		


	// Columna Nombre  COLUMN_MIS_PRODUCTOS_FABRICANTE 
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_MIS_PRODUCTOS_FABRICANTE));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Fabricante", renderer, "text", COLUMN_MIS_PRODUCTOS_FABRICANTE, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_MIS_PRODUCTOS_FABRICANTE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Nombre  COLUMN_MIS_PRODUCTOS_CATEGORIA 
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_MIS_PRODUCTOS_CATEGORIA));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Categoía", renderer, "text", COLUMN_MIS_PRODUCTOS_CATEGORIA, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_MIS_PRODUCTOS_CATEGORIA);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Stock  COLUMN_MIS_PRODUCTOS_STOCK
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_MIS_PRODUCTOS_STOCK));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Stock", renderer, "text", COLUMN_MIS_PRODUCTOS_STOCK, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_MIS_PRODUCTOS_STOCK);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Stock  COLUMN_MIS_PRODUCTOS_PRECIO
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_MIS_PRODUCTOS_PRECIO));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Precio", renderer, "text", COLUMN_MIS_PRODUCTOS_PRECIO, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_MIS_PRODUCTOS_PRECIO);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Nombre  COLUMN_MIS_PRODUCTOS_UNIDAD 
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_MIS_PRODUCTOS_UNIDAD));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Unidad", renderer, "text", COLUMN_MIS_PRODUCTOS_UNIDAD, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_MIS_PRODUCTOS_UNIDAD);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Nombre  COLUMN_MIS_PRODUCTOS_PRESENTACION 
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_MIS_PRODUCTOS_PRESENTACION));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Presentación", renderer, "text", COLUMN_MIS_PRODUCTOS_PRESENTACION, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_MIS_PRODUCTOS_PRESENTACION);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Visitas  COLUMN_MIS_PRODUCTOS_VISITAS
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_MIS_PRODUCTOS_VISITAS));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Visitas", renderer, "text", COLUMN_MIS_PRODUCTOS_VISITAS, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_MIS_PRODUCTOS_VISITAS);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

}

#endif

