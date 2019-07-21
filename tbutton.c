#ifndef TBUTTON_C
#define TBUTTON_C

//*********************************************** togglebutton_seguimientos_toggled_cb ********************************************
G_MODULE_EXPORT void togglebutton_seguimientos_toggled_cb(GtkToggleButton *togglebutton, APPWINDOW_DATA *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		//Envia señal a desactivar el togglebutton Encontrados
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_encontrados)))
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->togglebutton_encontrados), FALSE);
		}

		//Envia señal a desactivar el togglebutton de Mis Productos
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_mis_productos)))
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->togglebutton_mis_productos), FALSE);
		}

		//Envia señal a desactivar el togglebutton de Proveedores
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_proveedores)))
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->togglebutton_proveedores), FALSE);
		}

		//Muestra el toolbar de los Seguimiento
		if (!gtk_widget_get_visible(data->toolbar_seguimiento))
		{
			gtk_widget_show_all(data->toolbar_seguimiento);		
		}

		//Muestra el treeview de Seguimiento
		if (!gtk_widget_get_visible(data->scrolledwindow_treeview_seguimiento))
		{
			gtk_widget_show_all(data->scrolledwindow_treeview_seguimiento);
		}

//		page_ayuda_referencia = AYUDA_PAGE_MENU_TORNEOS;

	} else { //Desactivar

		//Oculta el toolbar de los Torneos
		if (gtk_widget_get_visible(data->toolbar_seguimiento))
		{
			gtk_widget_hide(data->toolbar_seguimiento);
		}

		//Oculta el treeview de los Torneos
		if (gtk_widget_get_visible(data->scrolledwindow_treeview_seguimiento))
		{
			gtk_widget_hide(data->scrolledwindow_treeview_seguimiento);
		}

		//Muesta la imagen de fondo sino hay nada mas activo
		if ((!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_encontrados))) && 
			(!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_mis_productos))) &&
			(!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_proveedores))))
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->togglebutton_seguimientos), TRUE);
		}
	}
}


//*********************************************** togglebutton_encontrados_toggled_cb ********************************************
G_MODULE_EXPORT void togglebutton_encontrados_toggled_cb(GtkToggleButton *togglebutton, APPWINDOW_DATA *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		//Envia señal a desactivar el togglebutton Seguimientos
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_seguimientos)))
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->togglebutton_seguimientos), FALSE);
		}

		//Envia señal a desactivar el togglebutton de Mis Productos
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_mis_productos)))
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->togglebutton_mis_productos), FALSE);
		}

		//Envia señal a desactivar el togglebutton de Proveedores
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_proveedores)))
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->togglebutton_proveedores), FALSE);
		}

		//Muestra el toolbar de Encontrados
		if (!gtk_widget_get_visible(data->toolbar_encontrados))
		{
			gtk_widget_show_all(data->toolbar_encontrados);		
		}

		//Muestra el treeview de Encontrados
		if (!gtk_widget_get_visible(data->scrolledwindow_treeview_encontrados))
		{
			gtk_widget_show_all(data->scrolledwindow_treeview_encontrados);
		}

//		page_ayuda_referencia = AYUDA_PAGE_MENU_TORNEOS;

	} else { //Desactivar

		//Oculta el toolbar de Encontrados
		if (gtk_widget_get_visible(data->toolbar_encontrados))
		{
			gtk_widget_hide(data->toolbar_encontrados);
		}

		//Oculta el treeview de Encontrados
		if (gtk_widget_get_visible(data->scrolledwindow_treeview_encontrados))
		{
			gtk_widget_hide(data->scrolledwindow_treeview_encontrados);
		}

		//Muesta la imagen de fondo sino hay nada mas activo
		if ((!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_seguimientos))) && 
			(!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_mis_productos))) &&
			(!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_proveedores))))
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->togglebutton_encontrados), TRUE);
		}
	}
}

//*********************************************** togglebutton_mis_productos_toggled_cb ********************************************
G_MODULE_EXPORT void togglebutton_mis_productos_toggled_cb(GtkToggleButton *togglebutton, APPWINDOW_DATA *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		//Envia señal a desactivar el togglebutton Seguimientos
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_seguimientos)))
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->togglebutton_seguimientos), FALSE);
		}

		//Envia señal a desactivar el togglebutton de Encontrados
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_encontrados)))
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->togglebutton_encontrados), FALSE);
		}

		//Envia señal a desactivar el togglebutton de Proveedores
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_proveedores)))
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->togglebutton_proveedores), FALSE);
		}

		//Muestra el toolbar de Mis Productos
		if (!gtk_widget_get_visible(data->toolbar_mis_productos))
		{
			gtk_widget_show_all(data->toolbar_mis_productos);		
		}

		//Muestra el treeview de Mis Productos
		if (!gtk_widget_get_visible(data->scrolledwindow_treeview_mis_productos))
		{
			gtk_widget_show_all(data->scrolledwindow_treeview_mis_productos);
		}

//		page_ayuda_referencia = AYUDA_PAGE_MENU_TORNEOS;

	} else { //Desactivar

		//Oculta el toolbar de Mis Productos
		if (gtk_widget_get_visible(data->toolbar_mis_productos))
		{
			gtk_widget_hide(data->toolbar_mis_productos);
		}

		//Oculta el treeview de Mis Productos
		if (gtk_widget_get_visible(data->scrolledwindow_treeview_mis_productos))
		{
			gtk_widget_hide(data->scrolledwindow_treeview_mis_productos);
		}

		//Muesta la imagen de fondo sino hay nada mas activo
		if ((!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_seguimientos))) && 
			(!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_encontrados))) &&
			(!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_proveedores))))
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->togglebutton_mis_productos), TRUE);
		}
	}
}

//*********************************************** togglebutton_proveedores_toggled_cb ********************************************
G_MODULE_EXPORT void togglebutton_proveedores_toggled_cb(GtkToggleButton *togglebutton, APPWINDOW_DATA *data)
{
	gboolean activo = gtk_toggle_button_get_active(togglebutton);

	if (activo)
	{
		//Envia señal a desactivar el togglebutton Seguimientos
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_seguimientos)))
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->togglebutton_seguimientos), FALSE);
		}

		//Envia señal a desactivar el togglebutton de Encontrados
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_encontrados)))
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->togglebutton_encontrados), FALSE);
		}

		//Envia señal a desactivar el togglebutton de Mis Productos
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_mis_productos)))
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->togglebutton_mis_productos), FALSE);
		}

		//Muestra el toolbar de Proveedores
		if (!gtk_widget_get_visible(data->toolbar_proveedores))
		{
			gtk_widget_show_all(data->toolbar_proveedores);		
		}

		//Muestra el treeview de Proveedores
		if (!gtk_widget_get_visible(data->scrolledwindow_treeview_proveedores))
		{
			gtk_widget_show_all(data->scrolledwindow_treeview_proveedores);
		}

//		page_ayuda_referencia = AYUDA_PAGE_MENU_TORNEOS;

	} else { //Desactivar

		//Oculta el toolbar de Proveedores
		if (gtk_widget_get_visible(data->toolbar_proveedores))
		{
			gtk_widget_hide(data->toolbar_proveedores);
		}

		//Oculta el treeview de Proveedores
		if (gtk_widget_get_visible(data->scrolledwindow_treeview_proveedores))
		{
			gtk_widget_hide(data->scrolledwindow_treeview_proveedores);
		}

		//Muesta la imagen de fondo sino hay nada mas activo
		if ((!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_seguimientos))) && 
			(!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_encontrados))) &&
			(!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->togglebutton_mis_productos))))
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->togglebutton_proveedores), TRUE);
		}
	}
}

#endif


