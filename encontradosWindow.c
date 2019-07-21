
#ifndef ENCONTRADOS_WINDOW_C
#define ENCONTRADOS_WINDOW_C

G_MODULE_EXPORT gboolean EncontradosWindows_eventbox_imagen1_button_press_event_cb(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED GdkEvent *event, 
	 ENCONTRADOS_WINDOWS *data)
{
	abrirVisor("bd/fotos-bajadas/foto1.png",data->EncontradosWindows);

	printf("Click 1\n");

	return VERDADERO;
}

G_MODULE_EXPORT gboolean EncontradosWindows_eventbox_imagen2_button_press_event_cb(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED GdkEvent *event, 
	 ENCONTRADOS_WINDOWS *data)
{
	abrirVisor("bd/fotos-bajadas/foto2.png",data->EncontradosWindows);

	printf("Click 2\n");

	return VERDADERO;
}

G_MODULE_EXPORT gboolean EncontradosWindows_eventbox_imagen3_button_press_event_cb(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED GdkEvent *event, 
	 ENCONTRADOS_WINDOWS *data)
{
	abrirVisor("bd/fotos-bajadas/foto3.png",data->EncontradosWindows);

	printf("Click 3\n");

	return VERDADERO;
}

G_MODULE_EXPORT gboolean EncontradosWindows_eventbox_imagen4_button_press_event_cb(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED GdkEvent *event, 
	 ENCONTRADOS_WINDOWS *data)
{
	abrirVisor("bd/fotos-bajadas/foto4.png",data->EncontradosWindows);

	printf("Click 4\n");

	return VERDADERO;
}

G_MODULE_EXPORT void EncontradosWindows_button_aceptar_clicked(G_GNUC_UNUSED GtkButton *widget, ENCONTRADOS_WINDOWS *data)
{
	gtk_widget_destroy(data->EncontradosWindows);
}


G_MODULE_EXPORT gboolean EncontradosWindows_key_press_event(G_GNUC_UNUSED GtkWidget *widget, GdkEvent *event, ENCONTRADOS_WINDOWS *data)
{

//	printf("key: %x\n", ((GdkEventKey*)event)->keyval);

	switch (((GdkEventKey*)event)->keyval)
	{
		case 0xff1b: // GDK_KEY_Escape:
		{
			gtk_widget_destroy(data->EncontradosWindows);

		} break;
	}

	return FALSE;
}

void abrir_encontradoProducto(int numAuto)
{

	GtkBuilder		*builder;
	GError 			*error		= NULL;
	ENCONTRADOS_WINDOWS 	*EncontradoData;

	int cargadoIP_proveedor = FALSO;
	int numFoto=0;
	unsigned long int tamanioFoto=0;

	REGBD_NECESIDAD_IP ipProveedor;

	builder = gtk_builder_new();

	if( !gtk_builder_add_from_file(builder,"EncontradosWindows.ui", &error) )
	{
		g_warning("%s", error->message);
		printf("abrirProductosWindows::EncontradosWindows.ui -[%s]\n",error->message);

		mostrarMensaje("Error","Qué vergonzoso, no he podido dibujar la ventana de encontrados ver","");

		g_error_free(error);
		error = NULL;
		return;
	}

	EncontradoData = g_slice_new(ENCONTRADOS_WINDOWS);
	memset(EncontradoData,0, sizeof(ENCONTRADOS_WINDOWS));

	REGBD_ENCONTRADO *registro = (REGBD_ENCONTRADO *)g_slist_nth_data( gslista_encontrados[vg_index_seguimiento], (numAuto-1) );

	if (!registro) 
	{
		printf("registro=NULL\n");
		return;
	}

	GWE(EncontradosWindows);
	GWE(EncontradosWindows_imagen1);
	GWE(EncontradosWindows_imagen2);
	GWE(EncontradosWindows_imagen3);
	GWE(EncontradosWindows_imagen4);

	GWE(EncontradosWindows_entry_imagen1);
	GWE(EncontradosWindows_entry_imagen2);
	GWE(EncontradosWindows_entry_imagen3);
	GWE(EncontradosWindows_entry_imagen4);

	GWE(EncontradosWindows_boton_select_sector_entry);

	GWE(EncontradosWindows_entry_nombres);
	GWE(EncontradosWindows_entry_descripcion);
	GWE(EncontradosWindows_entry_precio);
	GWE(EncontradosWindows_entry_fabricante);
	GWE(EncontradosWindows_spin_stock);
	GWE(EncontradosWindows_comboboxtext_unidad);
	GWE(EncontradosWindows_comboboxtext_presentacion);
	GWE(EncontradosWindows_check_nuevo);
	GWE(EncontradosWindows_check_transporte);
	GWE(EncontradosWindows_check_fabricacion_propia);
	
	//Unidades
	for (int i=0;str_unidades[i];i++)
	{
		gtk_combo_box_text_append_text((GtkComboBoxText*)EncontradoData->EncontradosWindows_comboboxtext_unidad, str_unidades[i]);
	}

	//Presentacion
	for (int i=0;str_presentacion[i];i++)
	{
		gtk_combo_box_text_append_text((GtkComboBoxText*)EncontradoData->EncontradosWindows_comboboxtext_presentacion, str_presentacion[i]);
	}

	//Flag Sector
	flagGlobal_temporal = registro->flag_categoria;
	char msm[1024];
	memset(msm, '\0', sizeof(char)*1024);

	for (int i=0;i<16;i++)
	{
		if (flagGlobal_temporal & BITSET[i])
		{
			strcat(msm, str_sector[i]);
		}
	}

	gtk_entry_set_text(GTK_ENTRY(EncontradoData->EncontradosWindows_boton_select_sector_entry), msm);

	//Nombre
	gtk_entry_set_text(GTK_ENTRY(EncontradoData->EncontradosWindows_entry_nombres), (const gchar*)registro->nombre);
	
	//Descripcion
	gtk_entry_set_text(GTK_ENTRY(EncontradoData->EncontradosWindows_entry_descripcion), (const gchar*)registro->descripcion);

	gtk_spin_button_set_value(GTK_SPIN_BUTTON(EncontradoData->EncontradosWindows_spin_stock),  
			(gdouble) registro->disponibilidad);

	//Check Fabricacion
	if (registro->fabricacion)
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(EncontradoData->EncontradosWindows_check_fabricacion_propia), TRUE); 
	}

	//Check Nuevo
	if (!registro->nuevo)
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(EncontradoData->EncontradosWindows_check_nuevo), FALSE); 
	}

	//Check Transporte
	if (registro->transporte)
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(EncontradoData->EncontradosWindows_check_transporte), TRUE); 
	}

	//Precio
	char str_precio[10];
	memset(str_precio, '\0', sizeof(char)*10);
	sprintf(str_precio, "%lu", registro->precio);
	gtk_entry_set_text(GTK_ENTRY(EncontradoData->EncontradosWindows_entry_precio), (const gchar*)str_precio);

	//Fabricante
	gtk_entry_set_text(GTK_ENTRY(EncontradoData->EncontradosWindows_entry_fabricante), (const gchar*)registro->fabricante);


	//Cargar Fotos
	GdkPixbuf *fotoBuff = gdk_pixbuf_new_from_file_at_scale( (const char*)RUTA_IMAGEN_SUBIR, 180,180,FALSE, NULL);
	if (fotoBuff)
	{
		gtk_image_set_from_pixbuf(GTK_IMAGE(EncontradoData->EncontradosWindows_imagen1), fotoBuff);
		gtk_image_set_from_pixbuf(GTK_IMAGE(EncontradoData->EncontradosWindows_imagen2), fotoBuff);
		gtk_image_set_from_pixbuf(GTK_IMAGE(EncontradoData->EncontradosWindows_imagen3), fotoBuff);
		gtk_image_set_from_pixbuf(GTK_IMAGE(EncontradoData->EncontradosWindows_imagen4), fotoBuff);

		g_object_unref(fotoBuff);
	}


	if (registro->flag_fotos)
	{
		memset(&ipProveedor,0,sizeof(REGBD_NECESIDAD_IP));		
		cargadoIP_proveedor = getIPBD(registro->idProveedor , registro->idNecesidad, &ipProveedor);
	}

//	printf("cargadoIP_proveedor=%d ip=%u port=%hu\n", cargadoIP_proveedor, ipProveedor.ip.s_addr, ipProveedor.puerto);


//	EncontradoData->fotoSeleccionada=1;

	//Fotos
	if (registro->flag_fotos & (1))
	{
		gtk_entry_set_text(GTK_ENTRY(EncontradoData->EncontradosWindows_entry_imagen1), (const gchar*)registro->descripcionFoto1);

		if (cargadoIP_proveedor)
		{
			int f=0;

			if ((f=abrir_conexion_p2p(ipProveedor.ip, ipProveedor.puerto)) != -1)
			{
				printf("Peticion de Foto 1 al proveedor p2p\n");
				int codPeticionFoto=999;
				send(f, &codPeticionFoto, sizeof(int), 0);

				numFoto=1;
				send(f, &numFoto, sizeof(int), 0);
				send(f, &registro->idProductoProveedor, sizeof(unsigned int), 0);

				tamanioFoto=0;
				recv(f, &tamanioFoto, sizeof(unsigned long int), 0);

				if (tamanioFoto>0)
				{
					unsigned char *foto = (unsigned char *)malloc(sizeof(unsigned char)*tamanioFoto); 
					recv(f, foto, sizeof(unsigned char)*tamanioFoto, MSG_WAITALL);

					FILE *ficheroFoto = fopen("bd/fotos-bajadas/foto1.png", "wb+");
	
					if (ficheroFoto)
					{
						fwrite(foto, sizeof(unsigned char)*tamanioFoto,1,ficheroFoto);
						fflush(ficheroFoto);
						fclose(ficheroFoto);	

						GdkPixbuf *fotoBuff1 = gdk_pixbuf_new_from_file_at_scale( (const char*)"bd/fotos-bajadas/foto1.png", 180,180,FALSE, NULL);
						if (fotoBuff1)
						{
							gtk_image_set_from_pixbuf(GTK_IMAGE(EncontradoData->EncontradosWindows_imagen1), fotoBuff1);
						}
						g_object_unref(fotoBuff1);
					}	

					if(foto)
						free(foto);				
				}

				close(f);
			}
		}
	}

//*
	if (registro->flag_fotos & (1<<1))
	{
		gtk_entry_set_text(GTK_ENTRY(EncontradoData->EncontradosWindows_entry_imagen2), (const gchar*)registro->descripcionFoto2);

		if (cargadoIP_proveedor)
		{
			int f=0;

			if ((f=abrir_conexion_p2p(ipProveedor.ip, ipProveedor.puerto)) != -1)
			{
				printf("Peticion de Foto 2 al proveedor p2p\n");
				int codPeticionFoto=999;
				send(f, &codPeticionFoto, sizeof(int), 0);

				numFoto=2;
				send(f, &numFoto, sizeof(int), 0);
				send(f, &registro->idProductoProveedor, sizeof(unsigned int), 0);

				tamanioFoto=0;
				recv(f, &tamanioFoto, sizeof(unsigned long int), 0);

				if (tamanioFoto>0)
				{
					unsigned char *foto = (unsigned char *)malloc(sizeof(unsigned char)*tamanioFoto); 
					recv(f, foto, sizeof(unsigned char)*tamanioFoto, 0);

					FILE *ficheroFoto = fopen("bd/fotos-bajadas/foto2.png", "wb+");
	
					if (ficheroFoto)
					{
						fwrite(foto, sizeof(unsigned char)*tamanioFoto,1,ficheroFoto);
						fflush(ficheroFoto);
						fclose(ficheroFoto);	

						GdkPixbuf *fotoBuff2 = gdk_pixbuf_new_from_file_at_scale( (const char*)"bd/fotos-bajadas/foto2.png", 180,180,FALSE, NULL);
						if (fotoBuff2)
						{
							gtk_image_set_from_pixbuf(GTK_IMAGE(EncontradoData->EncontradosWindows_imagen2), fotoBuff2);
							g_object_unref(fotoBuff2);
						}
					}	

					if(foto)
						free(foto);				
				}

				close(f);
			}
		}
	}	

	if (registro->flag_fotos & (1<<2))
	{
		gtk_entry_set_text(GTK_ENTRY(EncontradoData->EncontradosWindows_entry_imagen3), (const gchar*)registro->descripcionFoto3);

		if (cargadoIP_proveedor)
		{
			int f=0;

			if ((f=abrir_conexion_p2p(ipProveedor.ip, ipProveedor.puerto)) != -1)
			{
				printf("Peticion de Foto 3 al proveedor p2p\n");
				int codPeticionFoto=999;
				send(f, &codPeticionFoto, sizeof(int), 0);

				numFoto=3;
				send(f, &numFoto, sizeof(int), 0);
				send(f, &registro->idProductoProveedor, sizeof(unsigned int), 0);

				tamanioFoto=0;
				recv(f, &tamanioFoto, sizeof(unsigned long int), 0);

				if (tamanioFoto>0)
				{
					unsigned char *foto = (unsigned char *)malloc(sizeof(unsigned char)*tamanioFoto); 
					recv(f, foto, sizeof(unsigned char)*tamanioFoto, 0);

					FILE *ficheroFoto = fopen("bd/fotos-bajadas/foto3.png", "wb+");
	
					if (ficheroFoto)
					{
						fwrite(foto, sizeof(unsigned char)*tamanioFoto,1,ficheroFoto);
						fflush(ficheroFoto);
						fclose(ficheroFoto);	

						GdkPixbuf *fotoBuff3 = gdk_pixbuf_new_from_file_at_scale( (const char*)"bd/fotos-bajadas/foto3.png", 180,180,FALSE, NULL);
						if (fotoBuff3)
						{
							gtk_image_set_from_pixbuf(GTK_IMAGE(EncontradoData->EncontradosWindows_imagen3), fotoBuff3);
							g_object_unref(fotoBuff3);
						}
					}	

					if(foto)
						free(foto);				
				}

				close(f);
			}
		}
	}	
	
	if (registro->flag_fotos & (1<<3))
	{
		gtk_entry_set_text(GTK_ENTRY(EncontradoData->EncontradosWindows_entry_imagen4), (const gchar*)registro->descripcionFoto4);

		if (cargadoIP_proveedor)
		{
			int f=0;

			if ((f=abrir_conexion_p2p(ipProveedor.ip, ipProveedor.puerto)) != -1)
			{
				printf("Peticion de Foto 4 al proveedor p2p\n");
				int codPeticionFoto=999;
				send(f, &codPeticionFoto, sizeof(int), 0);

				int numFoto=4;
				send(f, &numFoto, sizeof(int), 0);
				send(f, &registro->idProductoProveedor, sizeof(unsigned int), 0);

				tamanioFoto=0;
				recv(f, &tamanioFoto, sizeof(unsigned long int), 0);

				if (tamanioFoto>0)
				{
					unsigned char *foto = (unsigned char *)malloc(sizeof(unsigned char)*tamanioFoto); 
					recv(f, foto, sizeof(unsigned char)*tamanioFoto, 0);

					FILE *ficheroFoto = fopen("bd/fotos-bajadas/foto4.png", "wb+");
	
					if (ficheroFoto)
					{
						fwrite(foto, sizeof(unsigned char)*tamanioFoto,1,ficheroFoto);
						fflush(ficheroFoto);
						fclose(ficheroFoto);	

						GdkPixbuf *fotoBuff4 = gdk_pixbuf_new_from_file_at_scale( (const char*)"bd/fotos-bajadas/foto4.png", 180,180,FALSE, NULL);
						if (fotoBuff4)
						{
							gtk_image_set_from_pixbuf(GTK_IMAGE(EncontradoData->EncontradosWindows_imagen4), fotoBuff4);
							g_object_unref(fotoBuff4);
						}
					}	

					if(foto)
						free(foto);				
				}

				close(f);
			}
		}
	}	
//*/

	//Combobox
	g_object_set(G_OBJECT(EncontradoData->EncontradosWindows_comboboxtext_unidad), 			"active", registro->codUnidad, NULL);
	g_object_set(G_OBJECT(EncontradoData->EncontradosWindows_comboboxtext_presentacion), 	"active", registro->codPresentacion, NULL);

	/* Connect signals */
	gtk_builder_connect_signals(builder, EncontradoData);
//	g_signal_connect (EncontradoData->ex_total, "notify::expanded", G_CALLBACK(ex_total_expanded_cb), EncontradoData);

	/* Destroy builder, since we don't need it anymore */
	g_object_unref(G_OBJECT(builder));

	gtk_window_set_transient_for(GTK_WINDOW(EncontradoData->EncontradosWindows), GTK_WINDOW(WidgetGlobales->AppWindowProductos));
	gtk_window_resize(GTK_WINDOW(EncontradoData->EncontradosWindows), (ancho_pantalla*2)/3, (alto_pantalla*2)/3);
	gtk_window_set_modal(GTK_WINDOW(EncontradoData->EncontradosWindows), TRUE);

	apply_css(GTK_WIDGET(EncontradoData->EncontradosWindows), provider);

	gtk_widget_show(EncontradoData->EncontradosWindows);
}

G_MODULE_EXPORT void EncontradosWindows_destroy(G_GNUC_UNUSED GtkWidget *widget, ENCONTRADOS_WINDOWS *data)
{
	g_slice_free(ENCONTRADOS_WINDOWS, data);
	data = NULL;
}


#endif 
