

#ifndef PRODUCTO_WINDOW_C
#define PRODUCTO_WINDOW_C

/*
G_MODULE_EXPORT void ex_total_expanded_cb(GObject *object, GParamSpec *param_spec, PRODUCTOS_WINDOWS *data)
{
	printf("click\n");

	GtkExpander *expander;

	expander = GTK_EXPANDER(object);

	if (gtk_expander_get_expanded(expander))
	{
printf("show\n");
		gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(data->ProductoWindow_scroll_sector),300);;

	} else {

printf("hide\n");
		gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(data->ProductoWindow_scroll_sector), -1);;
	}

}
//*/

G_MODULE_EXPORT void ProductoWindow_button_cerrar_clicked(G_GNUC_UNUSED GtkButton *widget, PRODUCTOS_WINDOWS *data)
{
	gtk_widget_destroy(data->ProductoWindow);
}


G_MODULE_EXPORT gboolean ProductoWindow_key_press_event(G_GNUC_UNUSED GtkWidget *widget, GdkEvent *event, PRODUCTOS_WINDOWS *data)
{

//	printf("key: %x\n", ((GdkEventKey*)event)->keyval);

	switch (((GdkEventKey*)event)->keyval)
	{
		case 0xff1b: // GDK_KEY_Escape:
		{
			gtk_widget_destroy(data->ProductoWindow);

		} break;
	}

	return FALSE;
}


G_MODULE_EXPORT void ProductoWindow_drag_data_received(
			G_GNUC_UNUSED GtkWidget 			*widget,
            GdkDragContext   					*context,
            G_GNUC_UNUSED gint              	x,
            G_GNUC_UNUSED gint              	y,
            GtkSelectionData 					*data,
            G_GNUC_UNUSED guint             	info,
            guint             					time,
            PRODUCTOS_WINDOWS      				*datax)
{

	gchar **list 	= NULL;
	guchar *txt 	= NULL;

	txt = gtk_selection_data_get_text(data);
	if (!txt)
	{
		gtk_drag_finish (context, TRUE, TRUE, time);
 		return;
	}

	if (txt[0]=='f' && txt[1]=='i' && txt[2]=='l' && txt[3]=='e' && txt[4]==':' && txt[5]=='/' && txt[6]=='/') //Es un archivo
	{
		list = g_uri_list_extract_uris((const gchar *)txt);
	}	

	g_free(txt);
	txt = NULL;

	if (list)
	{
		char *archivo = g_filename_from_uri(list[0], NULL, NULL);
		if (archivo)
		{
			printf("archivo=%s\n",archivo);
			subirFoto(archivo, datax);
			g_free(archivo);
			archivo = NULL;
		}
		g_strfreev(list);
		list = NULL;
	}
}

G_MODULE_EXPORT void ProductoWindow_boton_select_sector_clicked_cb(G_GNUC_UNUSED GtkButton *widget, PRODUCTOS_WINDOWS *data)
{
	abrirSelectWindow(data->ProductoWindow_boton_select_sector_entry);
}

G_MODULE_EXPORT void ProductoWindow_button_aceptar_clicked(G_GNUC_UNUSED GtkButton *widget, PRODUCTOS_WINDOWS *data)
{
	char strRutaArchivo[LARGO_STR_RUTAS];
	int esNuevo = FALSO;

	REGBD_PRODUCTO *registro = (REGBD_PRODUCTO *) malloc(sizeof(REGBD_PRODUCTO));
	memset(registro,0,sizeof(REGBD_PRODUCTO));

	if (data->idProducto)
	{
		registro->idProducto = data->idProducto;

	} else {

		registro->idProducto = getSiguenteIdProductoLibre();
		esNuevo = VERDADERO;
	}

	//Flag Sector
	registro->flag_categoria = flagGlobal_temporal;

	//Nombre
	strncpy(registro->nombre, gtk_entry_get_text(GTK_ENTRY(data->ProductoWindow_entry_nombres)), 
		gtk_entry_get_text_length(GTK_ENTRY(data->ProductoWindow_entry_nombres)));

	//Descripcion
	strncpy(registro->descripcion, gtk_entry_get_text(GTK_ENTRY(data->ProductoWindow_entry_descripcion)), 
		gtk_entry_get_text_length(GTK_ENTRY(data->ProductoWindow_entry_descripcion)));

	//Fabricacion
	strncpy(registro->fabricante, gtk_entry_get_text(GTK_ENTRY(data->ProductoWindow_entry_fabricante)), 
		gtk_entry_get_text_length(GTK_ENTRY(data->ProductoWindow_entry_fabricante)));

	//Precio
	char strPrecio[MAX_CAMPOS_PRODUCTO];
	strncpy(strPrecio, gtk_entry_get_text(GTK_ENTRY(data->ProductoWindow_entry_precio)), 
		gtk_entry_get_text_length(GTK_ENTRY(data->ProductoWindow_entry_precio)));

	registro->precio = strtoul(strPrecio, NULL, 10); 

	//Cantidad Disponible
	registro->disponibilidad = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(data->ProductoWindow_spin_stock));

	//Cod Unidad
	int codUnidad = 0;
	g_object_get(G_OBJECT(data->ProductoWindow_comboboxtext_unidad), "active",&codUnidad, NULL); 
	registro->codUnidad = codUnidad;

	//Cod Presentacion
	int codPresentacion = 0;
	g_object_get(G_OBJECT(data->ProductoWindow_comboboxtext_presentacion), "active",&codPresentacion, NULL); 
	
	registro->codPresentacion = codPresentacion;

	//Fabricado
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->ProductoWindow_check_fabricacion_propia)))
	{
		registro->fabricacion = VERDADERO;

	} else {

		registro->fabricacion = FALSO;
	}

	//Nuevo
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->ProductoWindow_check_nuevo)))
	{
		registro->nuevo = VERDADERO;

	} else {

		registro->nuevo = FALSO;
	}

	//Transporte
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->ProductoWindow_check_transporte)))
	{
		registro->transporte = VERDADERO;

	} else {

		registro->transporte = FALSO;
	}

	//Fotos
	registro->flag_fotos ^= registro->flag_fotos;


	if (data->foto1_on)
	{
		registro->flag_fotos |= 1;
		strncpy(registro->descripcionFoto1, gtk_entry_get_text(GTK_ENTRY(data->ProductoWindow_entry_imagen1)), 
			gtk_entry_get_text_length(GTK_ENTRY(data->ProductoWindow_entry_imagen1)));


		GdkPixbuf *pix = gdk_pixbuf_new_from_file((const gchar*)data->foto1, NULL);
		if (pix)
		{
			memset(strRutaArchivo, '\0',sizeof(char)*LARGO_STR_RUTAS);
			sprintf(strRutaArchivo,"bd/productos/%u-1.png",registro->idProducto);
			gdk_pixbuf_save(pix, strRutaArchivo, "png", NULL, NULL);		
			g_object_unref(pix);
		} 		
	}	

	if (data->foto2_on)
	{
		registro->flag_fotos |= (1<<1);
		strncpy(registro->descripcionFoto2, gtk_entry_get_text(GTK_ENTRY(data->ProductoWindow_entry_imagen2)), 
			gtk_entry_get_text_length(GTK_ENTRY(data->ProductoWindow_entry_imagen2)));

		GdkPixbuf *pix = gdk_pixbuf_new_from_file((const gchar*)data->foto2, NULL);
		if (pix)
		{
			memset(strRutaArchivo, '\0',sizeof(char)*LARGO_STR_RUTAS);
			sprintf(strRutaArchivo,"bd/productos/%u-2.png",registro->idProducto);
			gdk_pixbuf_save(pix, strRutaArchivo, "png", NULL, NULL);		
			g_object_unref(pix);
		} 		
	}	

	if (data->foto3_on)
	{
		registro->flag_fotos |= (1<<2);
		strncpy(registro->descripcionFoto3, gtk_entry_get_text(GTK_ENTRY(data->ProductoWindow_entry_imagen3)), 
			gtk_entry_get_text_length(GTK_ENTRY(data->ProductoWindow_entry_imagen3)));

		GdkPixbuf *pix = gdk_pixbuf_new_from_file((const gchar*)data->foto3, NULL);
		if (pix)
		{
			memset(strRutaArchivo, '\0',sizeof(char)*LARGO_STR_RUTAS);
			sprintf(strRutaArchivo,"bd/productos/%u-3.png",registro->idProducto);
			gdk_pixbuf_save(pix, strRutaArchivo, "png", NULL, NULL);		
			g_object_unref(pix);
		} 		
	}	

	if (data->foto4_on)
	{
		registro->flag_fotos |= (1<<3);
		strncpy(registro->descripcionFoto4, gtk_entry_get_text(GTK_ENTRY(data->ProductoWindow_entry_imagen4)), 
			gtk_entry_get_text_length(GTK_ENTRY(data->ProductoWindow_entry_imagen4)));

		GdkPixbuf *pix = gdk_pixbuf_new_from_file((const gchar*)data->foto4, NULL);
		if (pix)
		{
			memset(strRutaArchivo, '\0',sizeof(char)*LARGO_STR_RUTAS);
			sprintf(strRutaArchivo,"bd/productos/%u-4.png",registro->idProducto);
			gdk_pixbuf_save(pix, strRutaArchivo, "png", NULL, NULL);		
			g_object_unref(pix);
		} 		
	}

	printf("ID=%u\n", registro->idProducto);
	printf("Sector=%llu\n", 		registro->flag_categoria);
	printf("Nombre=%s\n", 			registro->nombre);
	printf("Descripcion=%s\n", 		registro->descripcion);
	printf("fabricante=%s\n", 		registro->fabricante);

	printf("Precio=%ld\n", 			registro->precio);
	printf("Stock=%d\n", 			registro->disponibilidad);
	printf("Unidad=%d\n", 			registro->codUnidad);
	printf("Presentacion=%d\n",		registro->codPresentacion);


	printf("Nuevo=%d\n", 			registro->nuevo);
	printf("Fabricacion=%d\n",		registro->fabricacion);
	printf("Transporte=%d\n",		registro->transporte);

	printf("FlagFotos=%d\n", 		registro->flag_fotos);

	printf("descripcion foto 1=%s\n", 	registro->descripcionFoto1);
	printf("descripcion foto 2=%s\n", 	registro->descripcionFoto2);
	printf("descripcion foto 3=%s\n", 	registro->descripcionFoto3);
	printf("descripcion foto 4=%s\n", 	registro->descripcionFoto4);

	grabarIdProductoLibre(registro->idProducto);
	registro->activo = VERDADERO;

	grabarRegistroProducto(registro);

	if (esNuevo)
	{
		//Agregar al treeview
		GtkTreeIter   iter;
		GtkTreeModel  *model = NULL;

		model = gtk_tree_view_get_model(GTK_TREE_VIEW(WidgetGlobales->treeview_mis_productos));

		gtk_list_store_append(GTK_LIST_STORE(model), &iter);
		gtk_list_store_set (GTK_LIST_STORE(model), &iter, 
					COLUMN_MIS_PRODUCTOS_ID,  				registro->idProducto,
					COLUMN_MIS_PRODUCTOS_NOMBRE_PRODUCTO,	registro->nombre,
					COLUMN_MIS_PRODUCTOS_FABRICANTE,		registro->fabricante,
					COLUMN_MIS_PRODUCTOS_CATEGORIA,   		gtk_entry_get_text(GTK_ENTRY(data->ProductoWindow_boton_select_sector_entry)), 
					COLUMN_MIS_PRODUCTOS_STOCK,   			registro->disponibilidad, 
					COLUMN_MIS_PRODUCTOS_PRECIO,  			registro->precio, 
					COLUMN_MIS_PRODUCTOS_UNIDAD,			str_unidades[registro->codUnidad],
					COLUMN_MIS_PRODUCTOS_PRESENTACION,		str_presentacion[registro->codPresentacion],
					COLUMN_MIS_PRODUCTOS_VISITAS,			0,
					-1);	
	} else {

		recargarTreeview_mis_productos();
	}

	free(registro);
	registro = NULL;
	gtk_widget_destroy(data->ProductoWindow);

}

void subirFoto(char *filename, PRODUCTOS_WINDOWS *data)
{
//	printf("filename=%s\n", filename);

	GdkPixbuf *fotoBuff = gdk_pixbuf_new_from_file_at_scale( (const char*)filename, 180,180,FALSE, NULL);
	if (fotoBuff)
	{

		//gtk_image_set_from_file(GTK_IMAGE(data->ProductoWindow_imagen_subir_archivo), filename);
		gtk_image_set_from_pixbuf(GTK_IMAGE(data->ProductoWindow_imagen_subir_archivo), fotoBuff);

		switch(data->fotoSeleccionada)
		{
			case 1:
			{
				memset(data->foto1,'\0',sizeof(char)*LARGO_STR_RUTAS);
				strcpy(data->foto1,filename);
				gtk_image_set_from_pixbuf(GTK_IMAGE(data->ProductoWindow_imagen1), fotoBuff);
				gtk_widget_set_sensitive (data->ProductoWindow_entry_imagen1, VERDADERO);
				data->foto1_on = VERDADERO;

			} break;

			case 2:
			{
				memset(data->foto2,'\0',sizeof(char)*LARGO_STR_RUTAS);
				strcpy(data->foto2,filename);
				gtk_image_set_from_pixbuf(GTK_IMAGE(data->ProductoWindow_imagen2), fotoBuff);
				gtk_widget_set_sensitive (data->ProductoWindow_entry_imagen2, VERDADERO);
				data->foto2_on = VERDADERO;

			} break;

			case 3:
			{
				memset(data->foto3,'\0',sizeof(char)*LARGO_STR_RUTAS);
				strcpy(data->foto3,filename);
				gtk_image_set_from_pixbuf(GTK_IMAGE(data->ProductoWindow_imagen3), fotoBuff);
				gtk_widget_set_sensitive (data->ProductoWindow_entry_imagen3, VERDADERO);
				data->foto3_on = VERDADERO;

			} break;

			case 4:
			{
				memset(data->foto4,'\0',sizeof(char)*LARGO_STR_RUTAS);
				strcpy(data->foto4,filename);
				gtk_image_set_from_pixbuf(GTK_IMAGE(data->ProductoWindow_imagen4), fotoBuff);
				gtk_widget_set_sensitive (data->ProductoWindow_entry_imagen4, VERDADERO);
				data->foto4_on = VERDADERO;

			} break;

		};
		g_object_unref(fotoBuff);
	}
}


G_MODULE_EXPORT void ProductoWindow_boton_subir_archivo_add_clicked_cb(G_GNUC_UNUSED GtkButton *widget, PRODUCTOS_WINDOWS *data)
{
	printf("add foto\n");

	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	GtkFileFilter *filtro 		= gtk_file_filter_new();

	gtk_file_filter_add_pattern(filtro, "*.png");
	gtk_file_filter_add_pattern(filtro, "*.jpg");
	gtk_file_filter_add_pattern(filtro, "*.bmp");
	gtk_file_filter_add_pattern(filtro, "*.tiff");
	gtk_file_filter_add_pattern(filtro, "*.gif");

	gint res;
	dialog = gtk_file_chooser_dialog_new ("Cargar foto...",
		                                  GTK_WINDOW(WidgetGlobales->AppWindowProductos),
		                                  action,
		                                  "_Cancel",
		                                  GTK_RESPONSE_CANCEL,
		                                  "_Cargar",
		                                  GTK_RESPONSE_ACCEPT,
		                                  NULL);

	
	GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
	gtk_file_chooser_set_filter(chooser, filtro);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		char *filename;
		filename = gtk_file_chooser_get_filename (chooser);

		printf("filename=%s\n", filename);

		subirFoto(filename, data);

		g_free (filename);
		filename = NULL;
	}

	gtk_widget_destroy (dialog);

}

G_MODULE_EXPORT void ProductoWindow_boton_subir_archivo_del_clicked_cb(G_GNUC_UNUSED GtkButton *widget, PRODUCTOS_WINDOWS *data)
{
	printf("del foto\n");

	switch(data->fotoSeleccionada)
	{
		case 1:
		{
			memset(data->foto1,'\0',sizeof(char)*LARGO_STR_RUTAS);
			strcpy(data->foto1,RUTA_IMAGEN_SUBIR);
			gtk_image_set_from_file(GTK_IMAGE(data->ProductoWindow_imagen_subir_archivo), data->foto1);

			gtk_image_set_from_file(GTK_IMAGE(data->ProductoWindow_imagen1), data->foto1);
			gtk_entry_set_text(GTK_ENTRY(data->ProductoWindow_entry_imagen1),"");
			gtk_widget_set_sensitive (data->ProductoWindow_entry_imagen1, FALSO);
			data->foto1_on = FALSO;

		} break;

		case 2:
		{
			memset(data->foto2,'\0',sizeof(char)*LARGO_STR_RUTAS);
			strcpy(data->foto2,RUTA_IMAGEN_SUBIR);
			gtk_image_set_from_file(GTK_IMAGE(data->ProductoWindow_imagen_subir_archivo), data->foto2);

			gtk_image_set_from_file(GTK_IMAGE(data->ProductoWindow_imagen2), data->foto2);
			gtk_entry_set_text(GTK_ENTRY(data->ProductoWindow_entry_imagen2),"");
			gtk_widget_set_sensitive (data->ProductoWindow_entry_imagen2, FALSO);
			data->foto2_on = FALSO;

		} break;

		case 3:
		{
			memset(data->foto3,'\0',sizeof(char)*LARGO_STR_RUTAS);
			strcpy(data->foto3,RUTA_IMAGEN_SUBIR);
			gtk_image_set_from_file(GTK_IMAGE(data->ProductoWindow_imagen_subir_archivo), data->foto3);

			gtk_image_set_from_file(GTK_IMAGE(data->ProductoWindow_imagen3), data->foto3);
			gtk_entry_set_text(GTK_ENTRY(data->ProductoWindow_entry_imagen3),"");
			gtk_widget_set_sensitive (data->ProductoWindow_entry_imagen3, FALSO);
			data->foto3_on = FALSO;

		} break;

		case 4:
		{
			memset(data->foto4,'\0',sizeof(char)*LARGO_STR_RUTAS);
			strcpy(data->foto4,RUTA_IMAGEN_SUBIR);
			gtk_image_set_from_file(GTK_IMAGE(data->ProductoWindow_imagen_subir_archivo), data->foto4);

			gtk_image_set_from_file(GTK_IMAGE(data->ProductoWindow_imagen4), data->foto4);
			gtk_entry_set_text(GTK_ENTRY(data->ProductoWindow_entry_imagen4),"");
			gtk_widget_set_sensitive (data->ProductoWindow_entry_imagen4, FALSO);
			data->foto4_on = FALSO;

		} break;
	}
}

G_MODULE_EXPORT gboolean ProductoWindow_eventbox_imagen_subir_archivo_button_press_event_cb(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED GdkEvent *event, 
	 PRODUCTOS_WINDOWS *data)
{
	ProductoWindow_boton_subir_archivo_open_clicked_cb(NULL, data);

	return VERDADERO;
}

G_MODULE_EXPORT void ProductoWindow_boton_subir_archivo_open_clicked_cb(G_GNUC_UNUSED GtkButton *widget, PRODUCTOS_WINDOWS *data)
{
	printf("open foto=%d \n", data->fotoSeleccionada);

	switch(data->fotoSeleccionada)
	{
		case 1:
		{
			abrirVisor(data->foto1, data->ProductoWindow);

		} break;

		case 2:
		{
			abrirVisor(data->foto2, data->ProductoWindow);

		} break;

		case 3:
		{
			abrirVisor(data->foto3, data->ProductoWindow);

		} break;

		case 4:
		{
			abrirVisor(data->foto4, data->ProductoWindow);

		} break;
	}
}

G_MODULE_EXPORT gboolean ProductoWindow_eventbox_imagen1_button_press_event_cb(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED GdkEvent *event, 
	 PRODUCTOS_WINDOWS *data)
{

	gtk_label_set_text (GTK_LABEL( data->ProductoWindow_imagen_subir_archivo_label ), (const gchar*)titulo_label_foto[0]); 

	GdkPixbuf *fotoBuff = gdk_pixbuf_new_from_file_at_scale( (const char*)data->foto1, 180,180,FALSE, NULL);
	if (fotoBuff)
	{
		gtk_image_set_from_pixbuf(GTK_IMAGE(data->ProductoWindow_imagen_subir_archivo), fotoBuff);
		g_object_unref(fotoBuff);
	}

	data->fotoSeleccionada=1;

	printf("Click 1\n");

	return VERDADERO;
}

G_MODULE_EXPORT gboolean ProductoWindow_eventbox_imagen2_button_press_event_cb(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED GdkEvent *event, 
	PRODUCTOS_WINDOWS *data)
{

	gtk_label_set_text (GTK_LABEL( data->ProductoWindow_imagen_subir_archivo_label ), (const gchar*)titulo_label_foto[1]); 

	GdkPixbuf *fotoBuff = gdk_pixbuf_new_from_file_at_scale( (const char*)data->foto2, 180,180,FALSE, NULL);
	if (fotoBuff)
	{
		gtk_image_set_from_pixbuf(GTK_IMAGE(data->ProductoWindow_imagen_subir_archivo), fotoBuff);
		g_object_unref(fotoBuff);
	}

	data->fotoSeleccionada=2;


	printf("Click 2\n");

	return VERDADERO;
}

G_MODULE_EXPORT gboolean ProductoWindow_eventbox_imagen3_button_press_event_cb(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED GdkEvent *event, 
	PRODUCTOS_WINDOWS *data)
{

	gtk_label_set_text (GTK_LABEL( data->ProductoWindow_imagen_subir_archivo_label ), (const gchar*)titulo_label_foto[2]); 

	GdkPixbuf *fotoBuff = gdk_pixbuf_new_from_file_at_scale( (const char*)data->foto3, 180,180,FALSE, NULL);
	if (fotoBuff)
	{
		gtk_image_set_from_pixbuf(GTK_IMAGE(data->ProductoWindow_imagen_subir_archivo), fotoBuff);
		g_object_unref(fotoBuff);
	}

	data->fotoSeleccionada=3;


	printf("Click 3\n");

	return VERDADERO;
}

G_MODULE_EXPORT gboolean ProductoWindow_eventbox_imagen4_button_press_event_cb(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED GdkEvent *event, 
	PRODUCTOS_WINDOWS *data)
{

	gtk_label_set_text (GTK_LABEL( data->ProductoWindow_imagen_subir_archivo_label ), (const gchar*)titulo_label_foto[3]); 

	GdkPixbuf *fotoBuff = gdk_pixbuf_new_from_file_at_scale( (const char*)data->foto4, 180,180,FALSE, NULL);
	if (fotoBuff)
	{
		gtk_image_set_from_pixbuf(GTK_IMAGE(data->ProductoWindow_imagen_subir_archivo), fotoBuff);
		g_object_unref(fotoBuff);
	}

	data->fotoSeleccionada=4;

	printf("Click 4\n");

	return VERDADERO;
}


G_MODULE_EXPORT void ProductoWindow_entry_precio_insert_text_cb(GtkEditable *editable, G_GNUC_UNUSED gchar *new_text, G_GNUC_UNUSED gint new_text_length,
		G_GNUC_UNUSED gpointer position, G_GNUC_UNUSED PRODUCTOS_WINDOWS *user_data)
{
//	printf("%s len:%d b:%d\n",new_text,new_text_length, g_ascii_isdigit(new_text[0]));


	if ( (new_text_length>1) || !(g_ascii_isdigit(new_text[0])) )
	{
		//Caracter no permitido
		 g_signal_stop_emission_by_name (editable, "insert_text");
	}


/*
	gchar *result = g_utf8_strup (new_text, new_text_length);
	g_signal_handlers_block_by_func (editable, (gpointer) ProductoWindow_entry_precio_insert_text_cb, user_data);
	gtk_editable_insert_text (editable, result, new_text_length, position);
	g_signal_handlers_unblock_by_func (editable, (gpointer) ProductoWindow_entry_precio_insert_text_cb, user_data);
	g_signal_stop_emission_by_name (editable, "insert_text");
	g_free (result);
//*/

}

void abrirProductosWindows(unsigned int idProducto)
{

	GtkBuilder		*builder;
	GError 			*error		= NULL;
	PRODUCTOS_WINDOWS 	*ProductoData;

	builder = gtk_builder_new();

	if( !gtk_builder_add_from_file(builder,"ProductosWindows.ui", &error) )
	{
		g_warning("%s", error->message);
		printf("abrirProductosWindows::ProductosWindows.ui -[%s]\n",error->message);

		mostrarMensaje("Error","Qué vergonzoso, no he podido dibujar la ventana de productos","");

		g_error_free(error);
		error = NULL;
		return;
	}

	ProductoData = g_slice_new(PRODUCTOS_WINDOWS);
	memset(ProductoData,0, sizeof(PRODUCTOS_WINDOWS));

	ProductoData->idProducto = idProducto;

	GWP(ProductoWindow);
	GWP(ProductoWindow_imagen_subir_archivo_label);
	GWP(ProductoWindow_imagen_subir_archivo);
	GWP(ProductoWindow_imagen1);
	GWP(ProductoWindow_imagen2);
	GWP(ProductoWindow_imagen3);
	GWP(ProductoWindow_imagen4);

	GWP(ProductoWindow_entry_imagen1);
	GWP(ProductoWindow_entry_imagen2);
	GWP(ProductoWindow_entry_imagen3);
	GWP(ProductoWindow_entry_imagen4);

	GWP(ProductoWindow_boton_select_sector_entry);

	GWP(ProductoWindow_entry_nombres);
	GWP(ProductoWindow_entry_descripcion);
	GWP(ProductoWindow_entry_precio);
	GWP(ProductoWindow_entry_fabricante);
	GWP(ProductoWindow_spin_stock);
	GWP(ProductoWindow_comboboxtext_unidad);
	GWP(ProductoWindow_comboboxtext_presentacion);
	GWP(ProductoWindow_check_nuevo);
	GWP(ProductoWindow_check_transporte);
	GWP(ProductoWindow_check_fabricacion_propia);
	
	//Drag and Drop
	gtk_drag_dest_add_text_targets(GTK_WIDGET(ProductoData->ProductoWindow));

	//Unidades
	for (int i=0;str_unidades[i];i++)
	{
		gtk_combo_box_text_append_text((GtkComboBoxText*)ProductoData->ProductoWindow_comboboxtext_unidad, str_unidades[i]);
	}

	//Presentacion
	for (int i=0;str_presentacion[i];i++)
	{
		gtk_combo_box_text_append_text((GtkComboBoxText*)ProductoData->ProductoWindow_comboboxtext_presentacion, str_presentacion[i]);
	}

	if (ProductoData->idProducto)
	{
		REGBD_PRODUCTO registro;
		memset(&registro, 0, sizeof(REGBD_PRODUCTO));

		cargarRegistroProducto(ProductoData->idProducto, &registro);

		//Flag Sector
		flagGlobal_temporal = registro.flag_categoria;
		char msm[1024];
		memset(msm, '\0', sizeof(char)*1024);

		for (int i=0;i<16;i++)
		{
			if (flagGlobal_temporal & BITSET[i])
			{
				strcat(msm, str_sector[i]);
			}
		}

		gtk_entry_set_text(GTK_ENTRY(ProductoData->ProductoWindow_boton_select_sector_entry), msm);

		//Nombre
		gtk_entry_set_text(GTK_ENTRY(ProductoData->ProductoWindow_entry_nombres), (const gchar*)registro.nombre);
		
		//Descripcion
		gtk_entry_set_text(GTK_ENTRY(ProductoData->ProductoWindow_entry_descripcion), (const gchar*)registro.descripcion);
	
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(ProductoData->ProductoWindow_spin_stock),  
				(gdouble) registro.disponibilidad);

		//Check Fabricacion
		if (registro.fabricacion)
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ProductoData->ProductoWindow_check_fabricacion_propia), TRUE); 
		}

		//Check Nuevo
		if (!registro.nuevo)
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ProductoData->ProductoWindow_check_nuevo), FALSE); 
		}

		//Check Transporte
		if (registro.transporte)
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ProductoData->ProductoWindow_check_transporte), TRUE); 
		}

		//Precio
		char str_precio[10];
		memset(str_precio, '\0', sizeof(char)*10);
		sprintf(str_precio, "%lu", registro.precio);
		gtk_entry_set_text(GTK_ENTRY(ProductoData->ProductoWindow_entry_precio), (const gchar*)str_precio);

		//Fabricante
		gtk_entry_set_text(GTK_ENTRY(ProductoData->ProductoWindow_entry_fabricante), (const gchar*)registro.fabricante);


		//Fotos
		if (registro.flag_fotos & (1))
		{
			gtk_entry_set_text(GTK_ENTRY(ProductoData->ProductoWindow_entry_imagen1), (const gchar*)registro.descripcionFoto1);

			char strRutaArchivo[LARGO_STR_RUTAS];
			memset(strRutaArchivo, '\0',sizeof(char)*LARGO_STR_RUTAS);
			sprintf(strRutaArchivo,"bd/productos/%u-1.png",registro.idProducto);
			ProductoData->fotoSeleccionada = 1;
			subirFoto(strRutaArchivo,ProductoData);

		} else {

			strcpy(ProductoData->foto1,RUTA_IMAGEN_SUBIR);
			GdkPixbuf *fotoBuff = gdk_pixbuf_new_from_file_at_scale( (const char*)ProductoData->foto1, 180,180,FALSE, NULL);
			if (fotoBuff)
			{
				gtk_image_set_from_pixbuf(GTK_IMAGE(ProductoData->ProductoWindow_imagen1), fotoBuff);
				g_object_unref(fotoBuff);
			}
		}	

		if (registro.flag_fotos & (1<<1))
		{
			gtk_entry_set_text(GTK_ENTRY(ProductoData->ProductoWindow_entry_imagen2), (const gchar*)registro.descripcionFoto2);

			char strRutaArchivo[LARGO_STR_RUTAS];
			memset(strRutaArchivo, '\0',sizeof(char)*LARGO_STR_RUTAS);
			sprintf(strRutaArchivo,"bd/productos/%u-2.png",registro.idProducto);
			ProductoData->fotoSeleccionada = 2;
			subirFoto(strRutaArchivo,ProductoData);

		} else {

			strcpy(ProductoData->foto2,RUTA_IMAGEN_SUBIR);
			GdkPixbuf *fotoBuff = gdk_pixbuf_new_from_file_at_scale( (const char*)ProductoData->foto2, 180,180,FALSE, NULL);
			if (fotoBuff)
			{
				gtk_image_set_from_pixbuf(GTK_IMAGE(ProductoData->ProductoWindow_imagen2), fotoBuff);
				g_object_unref(fotoBuff);
			}
		}	

		if (registro.flag_fotos & (1<<2))
		{
			gtk_entry_set_text(GTK_ENTRY(ProductoData->ProductoWindow_entry_imagen3), (const gchar*)registro.descripcionFoto3);

			char strRutaArchivo[LARGO_STR_RUTAS];
			memset(strRutaArchivo, '\0',sizeof(char)*LARGO_STR_RUTAS);
			sprintf(strRutaArchivo,"bd/productos/%u-3.png",registro.idProducto);
			ProductoData->fotoSeleccionada = 3;
			subirFoto(strRutaArchivo,ProductoData);

		} else {

			strcpy(ProductoData->foto3,RUTA_IMAGEN_SUBIR);
			GdkPixbuf *fotoBuff = gdk_pixbuf_new_from_file_at_scale( (const char*)ProductoData->foto3, 180,180,FALSE, NULL);
			if (fotoBuff)
			{
				gtk_image_set_from_pixbuf(GTK_IMAGE(ProductoData->ProductoWindow_imagen3), fotoBuff);
				g_object_unref(fotoBuff);
			}
		}	
		
		if (registro.flag_fotos & (1<<3))
		{
			gtk_entry_set_text(GTK_ENTRY(ProductoData->ProductoWindow_entry_imagen4), (const gchar*)registro.descripcionFoto4);

			char strRutaArchivo[LARGO_STR_RUTAS];
			memset(strRutaArchivo, '\0',sizeof(char)*LARGO_STR_RUTAS);
			sprintf(strRutaArchivo,"bd/productos/%u-4.png",registro.idProducto);
			ProductoData->fotoSeleccionada = 4;
			subirFoto(strRutaArchivo,ProductoData);

		} else {

			strcpy(ProductoData->foto4,RUTA_IMAGEN_SUBIR);
			GdkPixbuf *fotoBuff = gdk_pixbuf_new_from_file_at_scale( (const char*)ProductoData->foto4, 180,180,FALSE, NULL);
			if (fotoBuff)
			{
				gtk_image_set_from_pixbuf(GTK_IMAGE(ProductoData->ProductoWindow_imagen4), fotoBuff);
				gtk_image_set_from_pixbuf(GTK_IMAGE(ProductoData->ProductoWindow_imagen_subir_archivo), fotoBuff);
				g_object_unref(fotoBuff);
			}
		}	

		//Combobox
		g_object_set(G_OBJECT(ProductoData->ProductoWindow_comboboxtext_unidad), 		"active", registro.codUnidad, NULL);
		g_object_set(G_OBJECT(ProductoData->ProductoWindow_comboboxtext_presentacion), 	"active", registro.codPresentacion, NULL);


 
	} else { //Nuevo Registro

		strcpy(ProductoData->foto1,RUTA_IMAGEN_SUBIR);
		strcpy(ProductoData->foto2,RUTA_IMAGEN_SUBIR);
		strcpy(ProductoData->foto3,RUTA_IMAGEN_SUBIR);
		strcpy(ProductoData->foto4,RUTA_IMAGEN_SUBIR);

		flagGlobal_temporal=0;

		GdkPixbuf *fotoBuff = NULL;

		fotoBuff = gdk_pixbuf_new_from_file_at_scale( (const char*)ProductoData->foto1, 180,180,FALSE, NULL);
		if (fotoBuff)
		{
			gtk_image_set_from_pixbuf(GTK_IMAGE(ProductoData->ProductoWindow_imagen1), fotoBuff);
			//Imagen Panel Cargar
			gtk_image_set_from_pixbuf(GTK_IMAGE(ProductoData->ProductoWindow_imagen_subir_archivo), fotoBuff);

			g_object_unref(fotoBuff);
		}

		fotoBuff = gdk_pixbuf_new_from_file_at_scale( (const char*)ProductoData->foto2, 180,180,FALSE, NULL);
		if (fotoBuff)
		{
			gtk_image_set_from_pixbuf(GTK_IMAGE(ProductoData->ProductoWindow_imagen2), fotoBuff);
			g_object_unref(fotoBuff);
		}

		fotoBuff = gdk_pixbuf_new_from_file_at_scale( (const char*)ProductoData->foto3, 180,180,FALSE, NULL);
		if (fotoBuff)
		{
			gtk_image_set_from_pixbuf(GTK_IMAGE(ProductoData->ProductoWindow_imagen3), fotoBuff);
			g_object_unref(fotoBuff);
		}

		fotoBuff = gdk_pixbuf_new_from_file_at_scale( (const char*)ProductoData->foto4, 180,180,FALSE, NULL);
		if (fotoBuff)
		{
			gtk_image_set_from_pixbuf(GTK_IMAGE(ProductoData->ProductoWindow_imagen4), fotoBuff);
			g_object_unref(fotoBuff);
		}

		//Combobox
		g_object_set(G_OBJECT(ProductoData->ProductoWindow_comboboxtext_unidad), 		"active", 0, NULL);
		g_object_set(G_OBJECT(ProductoData->ProductoWindow_comboboxtext_presentacion), 	"active", 41, NULL);
	}

	ProductoData->fotoSeleccionada=4;

	/* Connect signals */
	gtk_builder_connect_signals(builder, ProductoData);
//	g_signal_connect (ProductoData->ex_total, "notify::expanded", G_CALLBACK(ex_total_expanded_cb), ProductoData);

	/* Destroy builder, since we don't need it anymore */
	g_object_unref(G_OBJECT(builder));

	gtk_window_set_transient_for(GTK_WINDOW(ProductoData->ProductoWindow), GTK_WINDOW(WidgetGlobales->AppWindowProductos));
	gtk_window_resize(GTK_WINDOW(ProductoData->ProductoWindow), (ancho_pantalla*2)/3, (alto_pantalla*2)/3);
	gtk_window_set_modal(GTK_WINDOW(ProductoData->ProductoWindow), TRUE);

	apply_css(GTK_WIDGET(ProductoData->ProductoWindow), provider);

	gtk_widget_show(ProductoData->ProductoWindow);
}

G_MODULE_EXPORT void ProductoWindow_destroy(G_GNUC_UNUSED GtkWidget *widget, PRODUCTOS_WINDOWS *data)
{
	g_slice_free(PRODUCTOS_WINDOWS, data);
	data = NULL;
	flagGlobal_temporal = 0;
}

#endif
