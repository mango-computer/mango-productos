
#ifndef TREEVIEW_SEGUIMIENTO_C
#define TREEVIEW_SEGUIMIENTO_C


G_MODULE_EXPORT gboolean treeview_seguimiento_button_release_event_cb
			(G_GNUC_UNUSED GtkWidget* widget,  GdkEvent *evento, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	GdkEventButton *event = (GdkEventButton*)evento;

	if ((event->button==1) && (event->type == GDK_BUTTON_RELEASE)) //GDK_BUTTON_PRESS
	{
		GtkTreeSelection *selection	= gtk_tree_view_get_selection(GTK_TREE_VIEW(WidgetGlobales->treeview_seguimiento));

		if (gtk_tree_selection_get_selected(selection, NULL, NULL))
		{
			GtkTreePath *path;
            if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(WidgetGlobales->treeview_seguimiento), (gint) event->x, (gint) event->y, &path, NULL, NULL, NULL))
            {
                GtkTreeIter iter;
				GtkTreeModel *model_treeview = gtk_tree_view_get_model(GTK_TREE_VIEW(WidgetGlobales->treeview_seguimiento));
               
                gtk_tree_model_get_iter (GTK_TREE_MODEL(model_treeview), &iter, path);

				GValue vidSeguimiento = {0, };
				gtk_tree_model_get_value(model_treeview, &iter, COLUMN_SEGUIMIENTO_ID, &vidSeguimiento);
				vg_index_seguimiento = g_value_get_uint(&vidSeguimiento);
				g_value_unset(&vidSeguimiento);

				if (vg_index_seguimiento>0)
				{
					recargarTreeview_encontrados();
				}

	            gtk_tree_path_free(path);
  			}  
		} 
	}

	return FALSE;
}

static void recargarTreeview_seguimiento()
{
	GtkTreeIter iter;
	GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(WidgetGlobales->treeview_seguimiento));
	
	gtk_list_store_clear(GTK_LIST_STORE(model));

	//Liberar GSList
	g_slist_free_full(lista_necesidad, (GDestroyNotify)liberarMemoria_lista_necesidad);
	lista_necesidad = NULL;


	FILE *fichero = fopen(BD_NECESIDAD_DAT, "rb");

	if (fichero)
	{
		fseek(fichero, 0L, SEEK_SET);
		REGBD_NECESIDAD registro;
		memset(&registro, 0, sizeof(REGBD_NECESIDAD));

		fseek(fichero, (long int)(sizeof(REGBD_NECESIDAD)), SEEK_SET);
		char msm[1024];

		while(fread(&registro, sizeof(REGBD_NECESIDAD), 1,fichero))
		{

			if (!registro.activo) continue;

			REGBD_NECESIDAD *registro2lista = (REGBD_NECESIDAD*)malloc(sizeof(REGBD_NECESIDAD));
			memcpy(registro2lista, &registro, sizeof(REGBD_NECESIDAD));
			lista_necesidad = g_slist_prepend(lista_necesidad, registro2lista);

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
						COLUMN_SEGUIMIENTO_ID,  				registro.idNecesidad,
						COLUMN_SEGUIMIENTO_BUSQUEDA,			(registro.busqueda?pixBusqueda:NULL),
						COLUMN_SEGUIMIENTO_NOMBRE_PRODUCTO,		registro.nombre,
						COLUMN_SEGUIMIENTO_FABRICANTE,			registro.fabricante,
						COLUMN_SEGUIMIENTO_CATEGORIA,   		msm, 
						COLUMN_SEGUIMIENTO_PRECIO,  			registro.precio, 
						COLUMN_SEGUIMIENTO_UNIDAD,				str_unidades[registro.codUnidad],
						COLUMN_SEGUIMIENTO_CANTIDAD_REQUERIDA,	registro.disponibilidad, 
						COLUMN_SEGUIMIENTO_PRESENTACION,		str_presentacion[registro.codPresentacion],
						COLUMN_SEGUIMIENTO_ESTADO,				estadosVenezuela[registro.codEstado],
						COLUMN_SEGUIMIENTO_MUNICIPIO,			getStrMinicipio(registro.codEstado, registro.codMunicipio),
						-1);	

			memset(&registro, 0, sizeof(REGBD_NECESIDAD));
		} 
	
		fclose(fichero);

		lista_necesidad = g_slist_reverse(lista_necesidad);
	
	}	
}


//******************************************* create_items_model_seguimiento ****************************************
static GtkTreeModel* create_items_model_seguimiento()
{
	GtkListStore *model;
//	GtkTreeIter iter;

	model = gtk_list_store_new(NUM_SEGUIMIENTO_COLUMNS,
						G_TYPE_UINT, 		//COLUMN_SEGUIMIENTO_ID,
						GDK_TYPE_PIXBUF,	//COLUMN_SEGUIMIENTO_BUSQUEDA
						G_TYPE_STRING,		//COLUMN_SEGUIMIENTO_NOMBRE_PRODUCTO,
						G_TYPE_STRING,		//COLUMN_SEGUIMIENTO_FABRICANTE,
						G_TYPE_STRING,		//COLUMN_SEGUIMIENTO_CATEGORIA,
						G_TYPE_ULONG,		//COLUMN_SEGUIMIENTO_PRECIO,
						G_TYPE_STRING,		//COLUMN_SEGUIMIENTO_UNIDAD,
						G_TYPE_INT,			//COLUMN_SEGUIMIENTO_CANTIDAD_REQUERIDA,
						G_TYPE_STRING,		//COLUMN_SEGUIMIENTO_PRESENTACION,
						G_TYPE_STRING,		//COLUMN_SEGUIMIENTO_ESTADO,
						G_TYPE_STRING);		//COLUMN_SEGUIMIENTO_MUNICIPIO;
						 	

 
	return GTK_TREE_MODEL(model);
}

//********************************************** add_columns_seguimiento *********************************************
static void add_columns_seguimiento(GtkTreeView *treeview)
{

	GtkCellRenderer 	*renderer;
	GtkTreeViewColumn 	*colummnaTreeView;

	// Columna Id Torneo COLUMN_SEGUIMIENTO_ID
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, "xalign", (gfloat)0.5, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_SEGUIMIENTO_ID));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", COLUMN_SEGUIMIENTO_ID, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_SEGUIMIENTO_ID);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Busqueda 
	renderer = gtk_cell_renderer_pixbuf_new();
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Buscando", renderer, "pixbuf", COLUMN_SEGUIMIENTO_BUSQUEDA, NULL);
	g_object_set(colummnaTreeView, "expand", FALSE, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

//*
	// Columna Nombre  COLUMN_SEGUIMIENTO_NOMBRE_PRODUCTO
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_SEGUIMIENTO_NOMBRE_PRODUCTO));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Nombre", renderer, "text", COLUMN_SEGUIMIENTO_NOMBRE_PRODUCTO, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_SEGUIMIENTO_NOMBRE_PRODUCTO);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Nombre  COLUMN_SEGUIMIENTO_FABRICANTE
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_SEGUIMIENTO_FABRICANTE));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Fabricante", renderer, "text", COLUMN_SEGUIMIENTO_FABRICANTE, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_SEGUIMIENTO_FABRICANTE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Categoria  COLUMN_SEGUIMIENTO_CATEGORIA
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_SEGUIMIENTO_CATEGORIA));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Categoría", renderer, "text", COLUMN_SEGUIMIENTO_CATEGORIA, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_SEGUIMIENTO_CATEGORIA);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Categoria  COLUMN_SEGUIMIENTO_UNIDAD
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_SEGUIMIENTO_UNIDAD));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Unidad", renderer, "text", COLUMN_SEGUIMIENTO_UNIDAD, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_SEGUIMIENTO_UNIDAD);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Cantidad  COLUMN_SEGUIMIENTO_PRECIO
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_SEGUIMIENTO_PRECIO));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Precio", renderer, "text", COLUMN_SEGUIMIENTO_PRECIO, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_SEGUIMIENTO_PRECIO);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		


	// Columna Cantidad  COLUMN_SEGUIMIENTO_CANTIDAD_REQUERIDA
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_SEGUIMIENTO_CANTIDAD_REQUERIDA));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Unidades Requeridas", renderer, "text", COLUMN_SEGUIMIENTO_CANTIDAD_REQUERIDA, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_SEGUIMIENTO_CANTIDAD_REQUERIDA);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna COLUMN_SEGUIMIENTO_PRESENTACION
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_SEGUIMIENTO_PRESENTACION));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Presentación", renderer, "text", COLUMN_SEGUIMIENTO_PRESENTACION, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_SEGUIMIENTO_PRESENTACION);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna Estado  COLUMN_SEGUIMIENTO_ESTADO
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_SEGUIMIENTO_ESTADO));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Estado", renderer, "text", COLUMN_SEGUIMIENTO_ESTADO, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_SEGUIMIENTO_ESTADO);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

	// Columna COLUMN_SEGUIMIENTO_MUNICIPIO
	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", FALSE, NULL);
	g_object_set_data(G_OBJECT(renderer), "column", GINT_TO_POINTER(COLUMN_SEGUIMIENTO_MUNICIPIO));
	colummnaTreeView = gtk_tree_view_column_new_with_attributes("Municipio", renderer, "text", COLUMN_SEGUIMIENTO_MUNICIPIO, NULL);
	gtk_tree_view_column_set_resizable(colummnaTreeView, TRUE);
	gtk_tree_view_column_set_alignment(colummnaTreeView, (gfloat)0.5);
	gtk_tree_view_column_set_sort_column_id(colummnaTreeView, COLUMN_SEGUIMIENTO_MUNICIPIO);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), colummnaTreeView);		

//*/
}

#endif

