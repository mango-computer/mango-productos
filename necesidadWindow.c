
#ifndef NECESIDAD_WINDOW_C
#define NECESIDAD_WINDOW_C



G_MODULE_EXPORT void NecesidadWindow_combobox_estado_changed_cb(G_GNUC_UNUSED GtkComboBox *widget, NECESIDAD_WINDOWS *data)
{
	//Obtener Sistema de Juego
	gint id_;
	g_object_get(G_OBJECT(data->NecesidadWindow_combobox_estado), "active", &id_, NULL);
	
	llenarComboMunicipios(id_, 0, data);

}


G_MODULE_EXPORT void NecesidadWindow_boton_select_sector_clicked_cb(G_GNUC_UNUSED GtkButton *widget, NECESIDAD_WINDOWS *data)
{
	abrirSelectWindow(data->NecesidadWindow_boton_select_sector_entry);
}


G_MODULE_EXPORT void NecesidadWindow_button_aceptar_clicked(G_GNUC_UNUSED GtkButton *widget, NECESIDAD_WINDOWS *data)
{
	int esNuevo = FALSO;

	REGBD_NECESIDAD *registro = (REGBD_NECESIDAD *) malloc(sizeof(REGBD_NECESIDAD));
	memset(registro,0,sizeof(REGBD_NECESIDAD));

	if (data->idNecesidad)
	{
		registro->idNecesidad = data->idNecesidad;

	} else {

		registro->idNecesidad = getSiguenteIdNecesidadLibre();//getSiguenteidNecesidadLibre();
		esNuevo = VERDADERO;
	}

	//Flag Sector
	registro->flag_categoria = flagGlobal_temporal;

	//Nombre
	strncpy(registro->nombre, gtk_entry_get_text(GTK_ENTRY(data->NecesidadWindow_entry_nombres)), 
		gtk_entry_get_text_length(GTK_ENTRY(data->NecesidadWindow_entry_nombres)));

	//Descripcion
	strncpy(registro->descripcion, gtk_entry_get_text(GTK_ENTRY(data->NecesidadWindow_entry_descripcion)), 
		gtk_entry_get_text_length(GTK_ENTRY(data->NecesidadWindow_entry_descripcion)));

	//Fabricacion
	strncpy(registro->fabricante, gtk_entry_get_text(GTK_ENTRY(data->NecesidadWindow_entry_fabricante)), 
		gtk_entry_get_text_length(GTK_ENTRY(data->NecesidadWindow_entry_fabricante)));

	//Precio
	char strPrecio[MAX_CAMPOS_PRODUCTO];
	strncpy(strPrecio, gtk_entry_get_text(GTK_ENTRY(data->NecesidadWindow_entry_precio)), 
		gtk_entry_get_text_length(GTK_ENTRY(data->NecesidadWindow_entry_precio)));

	registro->precio = strtoul(strPrecio, NULL, 10); 

	//Cantidad Disponible
	registro->disponibilidad = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(data->NecesidadWindow_spin_stock));

	//Cod Unidad
	int codUnidad = 0;
	g_object_get(G_OBJECT(data->NecesidadWindow_comboboxtext_unidad), "active",&codUnidad, NULL); 
	registro->codUnidad = codUnidad;

	//Cod Presentacion
	int codPresentacion = 0;
	g_object_get(G_OBJECT(data->NecesidadWindow_comboboxtext_presentacion), "active",&codPresentacion, NULL); 
	
	registro->codPresentacion = codPresentacion;

	//Fabricado
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->NecesidadWindow_check_fabricacion_propia)))
	{
		registro->fabricacion = VERDADERO;

	} else {

		registro->fabricacion = FALSO;
	}

	//Nuevo
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->NecesidadWindow_check_nuevo)))
	{
		registro->nuevo = VERDADERO;

	} else {

		registro->nuevo = FALSO;
	}

	//Transporte
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->NecesidadWindow_check_transporte)))
	{
		registro->transporte = VERDADERO;

	} else {

		registro->transporte = FALSO;
	}


	int codEstado = 0;
	g_object_get(G_OBJECT(data->NecesidadWindow_combobox_estado), "active",&codEstado, NULL); 
	registro->codEstado 	= codEstado;

	int codMunicipio = 0;
	g_object_get(G_OBJECT(data->NecesidadWindow_combobox_municipio), "active",&codMunicipio, NULL); 
	registro->codMunicipio 	= codMunicipio;

	printf("ID=%u\n", 				registro->idNecesidad);
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

	printf("codEstado=%d\n",		registro->codEstado);
	printf("codMinicipio=%d\n",		registro->codMunicipio);

	grabarIdNecesidadLibre(registro->idNecesidad);
	registro->activo = VERDADERO;

	grabarRegistroNecesidad(registro);


	if (esNuevo)
	{
		//Agregar al treeview
		GtkTreeIter   iter;
		GtkTreeModel  *model = NULL;

		REGBD_NECESIDAD *registro2lista = (REGBD_NECESIDAD*)malloc(sizeof(REGBD_NECESIDAD));
		memcpy(registro2lista, registro, sizeof(REGBD_NECESIDAD));
		lista_necesidad = g_slist_append(lista_necesidad, registro2lista);

		model = gtk_tree_view_get_model(GTK_TREE_VIEW(WidgetGlobales->treeview_seguimiento));

		gtk_list_store_append(GTK_LIST_STORE(model), &iter);
		gtk_list_store_set (GTK_LIST_STORE(model), &iter, 
					COLUMN_SEGUIMIENTO_ID,  				registro->idNecesidad,
					COLUMN_SEGUIMIENTO_BUSQUEDA,			NULL,
					COLUMN_SEGUIMIENTO_NOMBRE_PRODUCTO,		registro->nombre,
					COLUMN_SEGUIMIENTO_FABRICANTE,			registro->fabricante,
					COLUMN_SEGUIMIENTO_CATEGORIA,   		gtk_entry_get_text(GTK_ENTRY(data->NecesidadWindow_boton_select_sector_entry)), 
					COLUMN_SEGUIMIENTO_PRECIO,  			registro->precio, 
					COLUMN_SEGUIMIENTO_UNIDAD,				str_unidades[registro->codUnidad],
					COLUMN_SEGUIMIENTO_CANTIDAD_REQUERIDA,	registro->disponibilidad, 
					COLUMN_SEGUIMIENTO_PRESENTACION,		str_presentacion[registro->codPresentacion],
					COLUMN_SEGUIMIENTO_ESTADO,				estadosVenezuela[registro->codEstado],
					COLUMN_SEGUIMIENTO_MUNICIPIO,			getStrMinicipio(registro->codEstado, registro->codMunicipio),
					-1);	
	} else {

		recargarTreeview_seguimiento();
	}

	free(registro);
	registro = NULL;

	gtk_widget_destroy(data->NecesidadWindow);

}


//**************************************************************************************************************************************
G_MODULE_EXPORT void NecesidadWindow_button_cerrar_clicked(G_GNUC_UNUSED GtkButton *widget, NECESIDAD_WINDOWS *data)
{
	gtk_widget_destroy(data->NecesidadWindow);
}

G_MODULE_EXPORT gboolean NecesidadWindow_key_press_event(G_GNUC_UNUSED GtkWidget *widget, GdkEvent *event, NECESIDAD_WINDOWS *data)
{

//	printf("key: %x\n", ((GdkEventKey*)event)->keyval);

	switch (((GdkEventKey*)event)->keyval)
	{
		case 0xff1b: // GDK_KEY_Escape:
		{
			gtk_widget_destroy(data->NecesidadWindow);

		} break;
	}

	return FALSE;
}

G_MODULE_EXPORT void NecesidadWindow_destroy(G_GNUC_UNUSED GtkWidget *widget, NECESIDAD_WINDOWS *data)
{
	g_slice_free(NECESIDAD_WINDOWS, data);
	data = NULL;
	flagGlobal_temporal = 0;
}


G_MODULE_EXPORT void NecesidadWindow_boton_imprimir_ficha_clicked(G_GNUC_UNUSED GtkButton *widget, NECESIDAD_WINDOWS *data)
{
	//Precio
	char strPrecio[MAX_CAMPOS_PRODUCTO];
	strncpy(strPrecio, gtk_entry_get_text(GTK_ENTRY(data->NecesidadWindow_entry_precio)), 
		gtk_entry_get_text_length(GTK_ENTRY(data->NecesidadWindow_entry_precio)));

	unsigned long int precio = strtoul(strPrecio, NULL, 10); 

	printf("precio=%lu\n", precio);
}

G_MODULE_EXPORT void NecesidadWindow_entry_precio_insert_text_cb(G_GNUC_UNUSED GtkEditable *editable, G_GNUC_UNUSED gchar *new_text, G_GNUC_UNUSED gint new_text_length,
		G_GNUC_UNUSED gpointer position, G_GNUC_UNUSED NECESIDAD_WINDOWS *user_data)
{
//	printf("%s len:%d b:%d\n",new_text,new_text_length, g_ascii_isdigit(new_text[0]));

//printf("Caracter: [%c][%d]\n", new_text[0], (int)new_text[0]);

	if (new_text_length>1)
	{
		//Caracter no permitido
		 g_signal_stop_emission_by_name (editable, "insert_text");

//	} else if ( (new_text[0]==62) || (new_text[0]==60) ) {

		//No hacer nada

	} else if (!(g_ascii_isdigit(new_text[0]))) {

		//Caracter no permitido
		 g_signal_stop_emission_by_name (editable, "insert_text");
	}


/*
	gchar *result = g_utf8_strup (new_text, new_text_length);
	g_signal_handlers_block_by_func (editable, (gpointer) NecesidadWindow_entry_precio_insert_text_cb, user_data);
	gtk_editable_insert_text (editable, result, new_text_length, position);
	g_signal_handlers_unblock_by_func (editable, (gpointer) NecesidadWindow_entry_precio_insert_text_cb, user_data);
	g_signal_stop_emission_by_name (editable, "insert_text");
	g_free (result);
//*/

}

void abrirNecesidadWindow(unsigned int idNecesidad)
{
//*
	GtkBuilder		*builder;
	GError 			*error		= NULL;
	NECESIDAD_WINDOWS 	*NecesidadData;

	builder = gtk_builder_new();

	if( !gtk_builder_add_from_file(builder,"NecesidadWindows.ui", &error) )
	{
		g_warning("%s", error->message);
		printf("abrirProductosWindows::NecesidadWindows.ui -[%s]\n",error->message);

		mostrarMensaje("Error","Qué vergonzoso, no he podido dibujar la ventana de necesidades","");

		g_error_free(error);
		error = NULL;
		return;
	}

	NecesidadData = g_slice_new(NECESIDAD_WINDOWS);
	memset(NecesidadData,0, sizeof(NECESIDAD_WINDOWS));

	NecesidadData->idNecesidad = idNecesidad;

	GWN(NecesidadWindow);

	GWN(NecesidadWindow_boton_select_sector_entry);

	GWN(NecesidadWindow_entry_nombres);
	GWN(NecesidadWindow_entry_descripcion);
	GWN(NecesidadWindow_entry_precio);
	GWN(NecesidadWindow_entry_fabricante);
	GWN(NecesidadWindow_spin_stock);
	GWN(NecesidadWindow_comboboxtext_unidad);
	GWN(NecesidadWindow_comboboxtext_presentacion);
	GWN(NecesidadWindow_check_nuevo);
	GWN(NecesidadWindow_check_transporte);
	GWN(NecesidadWindow_check_fabricacion_propia);
	GWN(NecesidadWindow_combobox_municipio);
	GWN(NecesidadWindow_combobox_estado);
	

	//Unidades
	for (int i=0;str_unidades[i];i++)
	{
		gtk_combo_box_text_append_text((GtkComboBoxText*)NecesidadData->NecesidadWindow_comboboxtext_unidad, str_unidades[i]);
	}

	//Presentacion
	for (int i=0;str_presentacion[i];i++)
	{
		gtk_combo_box_text_append_text((GtkComboBoxText*)NecesidadData->NecesidadWindow_comboboxtext_presentacion, str_presentacion[i]);
	}

	//Estados
	for (int i=0;estadosVenezuela[i];i++)
	{
		gtk_combo_box_text_append_text((GtkComboBoxText*)NecesidadData->NecesidadWindow_combobox_estado, estadosVenezuela[i]);
	}

	if (NecesidadData->idNecesidad)
	{
		REGBD_NECESIDAD registro;
		memset(&registro, 0, sizeof(REGBD_NECESIDAD));

		cargarRegistroNecesidad(NecesidadData->idNecesidad, &registro);

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

		gtk_entry_set_text(GTK_ENTRY(NecesidadData->NecesidadWindow_boton_select_sector_entry), msm);

		//Nombre
		gtk_entry_set_text(GTK_ENTRY(NecesidadData->NecesidadWindow_entry_nombres), (const gchar*)registro.nombre);
		
		//Descripcion
		gtk_entry_set_text(GTK_ENTRY(NecesidadData->NecesidadWindow_entry_descripcion), (const gchar*)registro.descripcion);
	
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(NecesidadData->NecesidadWindow_spin_stock),  
				(gdouble) registro.disponibilidad);

		//Check Fabricacion
		if (registro.fabricacion)
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(NecesidadData->NecesidadWindow_check_fabricacion_propia), TRUE); 
		}

		//Check Nuevo
		if (!registro.nuevo)
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(NecesidadData->NecesidadWindow_check_nuevo), FALSE); 
		}

		//Check Transporte
		if (registro.transporte)
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(NecesidadData->NecesidadWindow_check_transporte), TRUE); 
		}

		//Precio
		char str_precio[10];
		memset(str_precio, '\0', sizeof(char)*10);
		sprintf(str_precio, "%lu", registro.precio);
		gtk_entry_set_text(GTK_ENTRY(NecesidadData->NecesidadWindow_entry_precio), (const gchar*)str_precio);

		//Fabricante
		gtk_entry_set_text(GTK_ENTRY(NecesidadData->NecesidadWindow_entry_fabricante), (const gchar*)registro.fabricante);

		//Combobox
		g_object_set(G_OBJECT(NecesidadData->NecesidadWindow_comboboxtext_unidad), 			"active", registro.codUnidad, NULL);
		g_object_set(G_OBJECT(NecesidadData->NecesidadWindow_comboboxtext_presentacion), 	"active", registro.codPresentacion, NULL);
		g_object_set(G_OBJECT(NecesidadData->NecesidadWindow_combobox_estado), 				"active", registro.codEstado, NULL);

		llenarComboMunicipios(registro.codEstado, registro.codMunicipio, NecesidadData);
 
	} else { //Nuevo Registro

		flagGlobal_temporal=0;

		//Combobox
		g_object_set(G_OBJECT(NecesidadData->NecesidadWindow_comboboxtext_unidad), 			"active", 0, NULL);
		g_object_set(G_OBJECT(NecesidadData->NecesidadWindow_comboboxtext_presentacion), 	"active", 0, NULL);
		g_object_set(G_OBJECT(NecesidadData->NecesidadWindow_combobox_estado), 				"active", 0, NULL);

		gtk_widget_set_sensitive(GTK_WIDGET(NecesidadData->NecesidadWindow_combobox_municipio), FALSE);

	}


	// Connect signals 
	gtk_builder_connect_signals(builder, NecesidadData);
//	g_signal_connect (NecesidadData->ex_total, "notify::expanded", G_CALLBACK(ex_total_expanded_cb), NecesidadData);

	g_object_unref(G_OBJECT(builder));

	gtk_window_set_transient_for(GTK_WINDOW(NecesidadData->NecesidadWindow), GTK_WINDOW(WidgetGlobales->AppWindowProductos));
	gtk_window_resize(GTK_WINDOW(NecesidadData->NecesidadWindow), (ancho_pantalla*2)/3, (alto_pantalla*2)/3);
	gtk_window_set_modal(GTK_WINDOW(NecesidadData->NecesidadWindow), TRUE);

	apply_css(GTK_WIDGET(NecesidadData->NecesidadWindow), provider);
	gtk_widget_show(NecesidadData->NecesidadWindow);

//*/
}

#endif
