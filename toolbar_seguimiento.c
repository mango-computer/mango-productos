#ifndef TOOLBAR_SEGUIMIENTO_C
#define TOOLBAR_SEGUIMIENTO_C


//*************************************************** toolBoton_seguimiento_buscar_clicked_cb *************************************
G_MODULE_EXPORT void toolBoton_seguimiento_buscar_clicked_cb(G_GNUC_UNUSED GtkButton *widget, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("toolBoton_seguimiento_buscar_clicked_cb\n");

	GtkTreeIter 		iter;
	GtkTreeView 		*treeview 	= GTK_TREE_VIEW(WidgetGlobales->treeview_seguimiento);
	GtkTreeModel 		*model 		= gtk_tree_view_get_model(treeview);
	GtkTreeSelection 	*selection 	= gtk_tree_view_get_selection(treeview);

	if (gtk_tree_selection_get_selected(selection, NULL, &iter))
	{
		GValue vpos 		= {0, };
		gtk_tree_model_get_value(model, &iter, COLUMN_SEGUIMIENTO_ID, &vpos);
		unsigned int numPosTreeview = g_value_get_uint(&vpos);
//		printf("Activar busqueda de =%u\n", numPosTreeview);
		g_value_unset(&vpos);

		//Lanzar hilo de busqueda
		pthread_t hilo_busqueda; 
		REGBD_NECESIDAD *reg;
		REGBD_NECESIDAD *copia_reg;

		for (GSList *iterador=lista_necesidad;iterador;iterador=iterador->next)
		{
			reg = (REGBD_NECESIDAD*)iterador->data;

			if (reg->idNecesidad==numPosTreeview)
			{
				if (!reg->busqueda)
				{
					reg->busqueda = VERDADERO;
					copia_reg = (REGBD_NECESIDAD*) malloc(sizeof(REGBD_NECESIDAD));
					memcpy(copia_reg, reg, sizeof(REGBD_NECESIDAD));

				} else { //Detener Busqueda

					reg->busqueda = FALSO;
					G_LOCK(vg_llave_busqueda_stop);
					{
						vg_llave_busqueda_stop = numPosTreeview;
					}
					G_UNLOCK(vg_llave_busqueda_stop);
				}

				grabarRegistroNecesidad(reg);

				//actualizar imagen en el treeview
				gtk_list_store_set (GTK_LIST_STORE(model), &iter, COLUMN_SEGUIMIENTO_BUSQUEDA,	(reg->busqueda?pixBusqueda:NULL), -1);	
				break;
			}		
		}

		if (copia_reg)
		{
			GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(WidgetGlobales->treeview_encontrados));
			gtk_list_store_clear(GTK_LIST_STORE(model));

			int s = pthread_create(&hilo_busqueda, NULL, thread_func_bucle_busqueda, (void*)copia_reg); 
			if (s != 0)
			{
				printf("****** Error al crear el hilo_busqueda\n");
				exit(-1);
			}
/*
			s = pthread_join(hilo_busqueda, NULL); 
			if (s != 0)
			{
				printf("****** Error en join hilo hilo_hijo_server_local\n");
				exit(-1);
			}
//*/
		}
	}	
}


//*************************************************** toolBoton_seguimiento_nuevo_clicked_cb *************************************
G_MODULE_EXPORT void toolBoton_seguimiento_nuevo_clicked_cb(G_GNUC_UNUSED GtkWidget *button, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("toolBoton_seguimiento_nuevo_clicked_cb\n");
	abrirNecesidadWindow(0);
}

//*************************************************** toolBoton_seguimiento_editar_clicked_cb *************************************
G_MODULE_EXPORT void toolBoton_seguimiento_editar_clicked_cb(G_GNUC_UNUSED GtkWidget *button, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("toolBoton_seguimiento_editar_clicked_cb\n");

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

//*************************************************** toolBoton_seguimiento_eliminar_clicked_cb *************************************
G_MODULE_EXPORT void toolBoton_seguimiento_eliminar_clicked_cb(G_GNUC_UNUSED GtkWidget *button, G_GNUC_UNUSED APPWINDOW_DATA *data)
{
	printf("toolBoton_seguimiento_eliminar_clicked_cb\n");
}

#endif
