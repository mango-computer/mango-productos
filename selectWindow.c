

#ifndef SELECT_WINDOW_C
#define SELECT_WINDOW_C

G_MODULE_EXPORT gboolean SectorWindows_key_press_event(G_GNUC_UNUSED GtkWidget *widget, GdkEvent *event, SELECT_SECTOR_WINDOWS *data)
{

//	printf("key: %x\n", ((GdkEventKey*)event)->keyval);

	switch (((GdkEventKey*)event)->keyval)
	{
		case 0xff1b: // GDK_KEY_Escape:
		{
			gtk_widget_destroy(data->SectorWindows);

		} break;
	}

	return FALSE;
}

G_MODULE_EXPORT void SectorWindows_destroy(G_GNUC_UNUSED GtkWidget *widget, SELECT_SECTOR_WINDOWS *data)
{
	data->entrySector = NULL;
	g_slice_free(SELECT_SECTOR_WINDOWS, data);
	data = NULL;
}

G_MODULE_EXPORT void SectorWindows_boton_cerrar_clicked_cb(G_GNUC_UNUSED GtkButton *widget, SELECT_SECTOR_WINDOWS *data)
{
	gtk_widget_destroy(data->SectorWindows);
}

G_MODULE_EXPORT void SectorWindows_boton_aceptar_clicked_cb(G_GNUC_UNUSED GtkButton *widget, SELECT_SECTOR_WINDOWS *data)
{
	flagGlobal_temporal = data->flag_sector;
//	imprimirBits(flagGlobal_temporal);

	char msm[1024];
	memset(msm, '\0', sizeof(char)*1024);

	for (int i=0;i<16;i++)
	{
		if (data->flag_sector & BITSET[i])
		{
			strcat(msm, str_sector[i]);
		}
	}

	gtk_entry_set_text(GTK_ENTRY(data->entrySector), msm);
	gtk_widget_destroy(data->SectorWindows);
}

G_MODULE_EXPORT void SectorWindows_check_productos_quimicos_alimentos_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data)
{

	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		data->flag_sector |= BITSET[PQ_ALIMENTOS];

	} else {

		data->flag_sector &= ~BITSET[PQ_ALIMENTOS];
	}
}

G_MODULE_EXPORT void SectorWindows_check_productos_quimicos_agricola_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		data->flag_sector |= BITSET[PQ_AGRICOLA];

	} else {

		data->flag_sector &= ~BITSET[PQ_AGRICOLA];
	}
}

G_MODULE_EXPORT void SectorWindows_check_productos_quimicos_cosmeticos_aseo_limpieza_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		data->flag_sector |= BITSET[PQ_COSME_ASEO_LIMPIEZA];

	} else {

		data->flag_sector &= ~BITSET[PQ_COSME_ASEO_LIMPIEZA];
	}
}

G_MODULE_EXPORT void SectorWindows_check_productos_quimicos_farmaceuticos_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		data->flag_sector |= BITSET[PQ_FARMACEUTICOS];

	} else {

		data->flag_sector &= ~BITSET[PQ_FARMACEUTICOS];
	}

}

G_MODULE_EXPORT void SectorWindows_check_productos_quimicos_pp_plasticos_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		data->flag_sector |= BITSET[PQ_PETROQUIMICA_PLASTICOS];

	} else {

		data->flag_sector &= ~BITSET[PQ_PETROQUIMICA_PLASTICOS];
	}
}

G_MODULE_EXPORT void SectorWindows_check_productos_quimicos_pinturas_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		data->flag_sector |= BITSET[PQ_PINTURAS];

	} else {

		data->flag_sector &= ~BITSET[PQ_PINTURAS];
	}
}

G_MODULE_EXPORT void SectorWindows_check_productos_manufacturados_Automotriz_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		data->flag_sector |= BITSET[PM_AUTOMOTRIZ];

	} else {

		data->flag_sector &= ~BITSET[PM_AUTOMOTRIZ];
	}

}

G_MODULE_EXPORT void SectorWindows_check_productos_manufacturados_uso_hogar_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		data->flag_sector |= BITSET[PM_USO_HOGAR];

	} else {

		data->flag_sector &= ~BITSET[PM_USO_HOGAR];
	}
}

G_MODULE_EXPORT void SectorWindows_check_productos_manufacturados_uso_industrial_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		data->flag_sector |= BITSET[PM_USO_INDUSTRIAL];

	} else {

		data->flag_sector &= ~BITSET[PM_USO_INDUSTRIAL];
	}

}

G_MODULE_EXPORT void SectorWindows_check_productos_manufacturados_uso_personal_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		data->flag_sector |= BITSET[PM_USO_PERSONAL];

	} else {

		data->flag_sector &= ~BITSET[PM_USO_PERSONAL];
	}
}


G_MODULE_EXPORT void SectorWindows_check_productos_sector_primario_agricola_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		data->flag_sector |= BITSET[PSP_AGRICOLA];

	} else {

		data->flag_sector &= ~BITSET[PSP_AGRICOLA];
	}
}

G_MODULE_EXPORT void SectorWindows_check_productos_sector_primario_pecuario_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		data->flag_sector |= BITSET[PSP_PECUARIO];

	} else {

		data->flag_sector &= ~BITSET[PSP_PECUARIO];
	}
}

G_MODULE_EXPORT void SectorWindows_check_productos_sector_primario_avicola_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		data->flag_sector |= BITSET[PSP_AVICOLA];

	} else {

		data->flag_sector &= ~BITSET[PSP_AVICOLA];
	}
}

G_MODULE_EXPORT void SectorWindows_check_productos_sector_primario_porcino_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		data->flag_sector |= BITSET[PSP_PORCINO];

	} else {

		data->flag_sector &= ~BITSET[PSP_PORCINO];
	}
}

G_MODULE_EXPORT void SectorWindows_check_productos_sector_primario_piscicola_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		data->flag_sector |= BITSET[PSP_PISCICOLA];

	} else {

		data->flag_sector &= ~BITSET[PSP_PISCICOLA];
	}
}

G_MODULE_EXPORT void SectorWindows_check_productos_sector_primario_apicola_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		data->flag_sector |= BITSET[PSP_APICOLA];

	} else {

		data->flag_sector &= ~BITSET[PSP_APICOLA];
	}
}


void abrirSelectWindow(GtkWidget *text)
{

	GtkBuilder		*builder;
	GError 			*error		= NULL;
	SELECT_SECTOR_WINDOWS 	*SelectSector;

	builder = gtk_builder_new();

	if( !gtk_builder_add_from_file(builder,"SectorWindows.ui", &error) )
	{
		g_warning("%s", error->message);
		printf("abrirProductosWindows::SectorWindows.ui -[%s]\n",error->message);
		mostrarMensaje("Error","Qué vergonzoso, no he podido dibujar la ventana de seleccion de sector","");
		g_error_free(error);
		error = NULL;
		return;
	}

	SelectSector = g_slice_new(SELECT_SECTOR_WINDOWS);

	SelectSector->entrySector = text;

	SelectSector->flag_sector ^= SelectSector->flag_sector;

	GWS(SectorWindows);
	GWS(SectorWindows_check_productos_quimicos_alimentos);
	GWS(SectorWindows_check_productos_quimicos_agricola);
	GWS(SectorWindows_check_productos_quimicos_cosmeticos_aseo_limpieza);
	GWS(SectorWindows_check_productos_quimicos_farmaceuticos);
	GWS(SectorWindows_check_productos_quimicos_pp_plasticos);
	GWS(SectorWindows_check_productos_quimicos_pinturas);
	GWS(SectorWindows_check_productos_manufacturados_Automotriz);
	GWS(SectorWindows_check_productos_manufacturados_uso_hogar);
	GWS(SectorWindows_check_productos_manufacturados_uso_industrial);
	GWS(SectorWindows_check_productos_manufacturados_uso_personal);
	GWS(SectorWindows_check_productos_sector_primario_agricola);
	GWS(SectorWindows_check_productos_sector_primario_pecuario);
	GWS(SectorWindows_check_productos_sector_primario_avicola);
	GWS(SectorWindows_check_productos_sector_primario_porcino);
	GWS(SectorWindows_check_productos_sector_primario_piscicola);
	GWS(SectorWindows_check_productos_sector_primario_apicola);

	/* Connect signals */
	gtk_builder_connect_signals(builder, SelectSector);
//	g_signal_connect (ProductoData->ex_total, "notify::expanded", G_CALLBACK(ex_total_expanded_cb), ProductoData);

	/* Destroy builder, since we don't need it anymore */
	g_object_unref(G_OBJECT(builder));

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(SelectSector->SectorWindows_check_productos_quimicos_alimentos),
			 (flagGlobal_temporal & BITSET[PQ_ALIMENTOS]));

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(SelectSector->SectorWindows_check_productos_quimicos_agricola),
			 (flagGlobal_temporal & BITSET[PQ_AGRICOLA]));

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(SelectSector->SectorWindows_check_productos_quimicos_cosmeticos_aseo_limpieza),
			 (flagGlobal_temporal & BITSET[PQ_COSME_ASEO_LIMPIEZA]));

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(SelectSector->SectorWindows_check_productos_quimicos_farmaceuticos),
			 (flagGlobal_temporal & BITSET[PQ_FARMACEUTICOS]));

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(SelectSector->SectorWindows_check_productos_quimicos_pp_plasticos),
			 (flagGlobal_temporal & BITSET[PQ_PETROQUIMICA_PLASTICOS]));

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(SelectSector->SectorWindows_check_productos_quimicos_pinturas),
			 (flagGlobal_temporal & BITSET[PQ_PINTURAS]));

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(SelectSector->SectorWindows_check_productos_manufacturados_Automotriz),
			 (flagGlobal_temporal & BITSET[PM_AUTOMOTRIZ]));

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(SelectSector->SectorWindows_check_productos_manufacturados_uso_hogar),
			 (flagGlobal_temporal & BITSET[PM_USO_HOGAR]));

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(SelectSector->SectorWindows_check_productos_manufacturados_uso_industrial),
			 (flagGlobal_temporal & BITSET[PM_USO_INDUSTRIAL]));

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(SelectSector->SectorWindows_check_productos_manufacturados_uso_personal),
			 (flagGlobal_temporal & BITSET[PM_USO_PERSONAL]));

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(SelectSector->SectorWindows_check_productos_sector_primario_agricola),
			 (flagGlobal_temporal & BITSET[PSP_AGRICOLA]));

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(SelectSector->SectorWindows_check_productos_sector_primario_pecuario),
			 (flagGlobal_temporal & BITSET[PSP_PECUARIO]));

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(SelectSector->SectorWindows_check_productos_sector_primario_avicola),
			 (flagGlobal_temporal & BITSET[PSP_AVICOLA]));

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(SelectSector->SectorWindows_check_productos_sector_primario_porcino),
			 (flagGlobal_temporal & BITSET[PSP_PORCINO]));

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(SelectSector->SectorWindows_check_productos_sector_primario_piscicola),
			 (flagGlobal_temporal & BITSET[PSP_PISCICOLA]));

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(SelectSector->SectorWindows_check_productos_sector_primario_apicola),
			 (flagGlobal_temporal & BITSET[PSP_APICOLA]));


	SelectSector->flag_sector = flagGlobal_temporal;

	gtk_window_set_transient_for(GTK_WINDOW(SelectSector->SectorWindows), GTK_WINDOW(WidgetGlobales->AppWindowProductos));
	gtk_window_resize(GTK_WINDOW(SelectSector->SectorWindows), (ancho_pantalla/2), (alto_pantalla/2));
	gtk_window_set_modal(GTK_WINDOW(SelectSector->SectorWindows), TRUE);
	apply_css(GTK_WIDGET(SelectSector->SectorWindows), provider);
	gtk_widget_show(SelectSector->SectorWindows);

}

#endif
