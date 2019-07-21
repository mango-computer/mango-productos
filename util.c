#ifndef UTIL_C
#define UTIL_C

char* str2Mayusculas(char* s)
{
    char* tmp = s;

    for (;*tmp;++tmp) {
        *tmp = toupper((unsigned char) *tmp);
    }

    return s;
}

void liberarMemoria_busqueda_local(gpointer data)
{
	free((REGBD_ENCONTRADO*)data);
	data = NULL;
}

void liberarMemoria_lista_ips(gpointer data)
{
	free((REGBD_NECESIDAD_IP*)data);
	data = NULL;
}
void liberarMemoria_lista_productos(gpointer data)
{
	free((REGBD_PRODUCTO*)data);
	data = NULL;
}

void liberarMemoria_lista_necesidad(gpointer data)
{
	free((REGBD_NECESIDAD*)data);
	data = NULL;
}


void llenarComboMunicipios(int codEstado, int codMunicipio, NECESIDAD_WINDOWS *data)
{

	printf("llenarComboMunicipios(%d)\n", codEstado);

	gtk_combo_box_text_remove_all((GtkComboBoxText*)data->NecesidadWindow_combobox_municipio); //(GtkComboBoxText*)data->NecesidadWindow_combobox_municipio);

	switch(codEstado)
	{
		case 4:
		{
			printf("Aragua\n");
			//Estados
			for (int i=0;municipios_aragua[i];i++)
			{
				gtk_combo_box_text_append_text((GtkComboBoxText*)data->NecesidadWindow_combobox_municipio, municipios_aragua[i]);
			}
			g_object_set(G_OBJECT(data->NecesidadWindow_combobox_municipio), 	"active", codMunicipio, NULL);

			gtk_widget_set_sensitive(GTK_WIDGET(data->NecesidadWindow_combobox_municipio), TRUE);
		} break;

		case 8:
		{
			printf("Cojedes\n");
			//Estados
			for (int i=0;municipios_cojedes[i];i++)
			{
				gtk_combo_box_text_append_text((GtkComboBoxText*)data->NecesidadWindow_combobox_municipio, municipios_cojedes[i]);
			}
			g_object_set(G_OBJECT(data->NecesidadWindow_combobox_municipio), 	"active", codMunicipio, NULL);

			gtk_widget_set_sensitive(GTK_WIDGET(data->NecesidadWindow_combobox_municipio), TRUE);

		} break;

		case 14:
		{
			printf("Merida\n");
			for (int i=0;municipios_merida[i];i++)
			{
				gtk_combo_box_text_append_text((GtkComboBoxText*)data->NecesidadWindow_combobox_municipio, municipios_merida[i]);
			}
			g_object_set(G_OBJECT(data->NecesidadWindow_combobox_municipio), 	"active", codMunicipio, NULL);

			gtk_widget_set_sensitive(GTK_WIDGET(data->NecesidadWindow_combobox_municipio), TRUE);

		} break;

		default:
		{
			gtk_widget_set_sensitive(GTK_WIDGET(data->NecesidadWindow_combobox_municipio), FALSE);

		} break;
	}
}


char *getStrMinicipio(int codEstado, int codMunicipio)
{

	switch(codEstado)
	{
		case 4:
		{
			return municipios_aragua[codMunicipio];

		} break;

		case 8:
		{
			return municipios_cojedes[codMunicipio];

		} break;

		case 14:
		{
			return municipios_merida[codMunicipio];

		} break;

		default:
		{
			return NULL;

		} break;
	}

}

void remplazar_caracter(char *cadena, char c, char nc)
{
	int i=0;

	while(cadena[i])
	{
		if (cadena[i]==c) 
		{
			cadena[i] = nc;
		}
		i++;
	}
//	return cadena;
}

//************************************************** cargarRegistroNecesidad ************************************************************************
void cargarRegistroNecesidad(unsigned int idNecesidad, REGBD_NECESIDAD *registro)
{

	FILE *fichero = fopen(BD_NECESIDAD_DAT, "rb");

	if (fichero)
	{
		fseek(fichero, (long int)(idNecesidad*sizeof(REGBD_NECESIDAD)), SEEK_SET);
		fread(registro, sizeof(REGBD_NECESIDAD), 1,fichero);
		fclose(fichero);
	}

}

//************************************************ grabarRegistroNecesidad **************************************************************************
void grabarRegistroNecesidad(REGBD_NECESIDAD *registro)
{

	FILE *fichero = fopen(BD_NECESIDAD_DAT, "r+b");
	
	if (fichero)
	{
		fseek(fichero, (long int)(registro->idNecesidad*sizeof(REGBD_NECESIDAD)), SEEK_SET);
		fwrite(registro, sizeof(REGBD_NECESIDAD),1,fichero);
		fflush(fichero);
		fclose(fichero);
	
	} else {

		fichero = fopen(BD_NECESIDAD_DAT, "w+b");
		if (fichero) 				
		{
			fseek(fichero, (long int)(registro->idNecesidad*sizeof(REGBD_NECESIDAD)), SEEK_SET);
			fwrite(registro, sizeof(REGBD_NECESIDAD),1,fichero);
			fflush(fichero);
			fclose(fichero);
		}
	}
}

//*************************************************** grabarIdNecesidadLibre ***********************************************************************
void grabarIdNecesidadLibre(unsigned int id)
{
	FILE *fichero = fopen(ARCHIVO_IDNECESIDAD_DAT, "wb+");
	
	if (fichero)
	{
		fwrite(&id, sizeof(unsigned int),1,fichero);
		fflush(fichero);
		fclose(fichero);	
	}
}

//***************************************************** getSiguenteIdNecesidadLibre *********************************************************************
unsigned int getSiguenteIdNecesidadLibre()
{

	unsigned int idNecesidad=0;

	FILE *fichero = fopen(ARCHIVO_IDNECESIDAD_DAT, "rb");

	if (fichero)
	{
		fread(&idNecesidad, sizeof(unsigned int), 1,fichero);
		fclose(fichero);
	
	} else {
		
		fichero = fopen(ARCHIVO_IDNECESIDAD_DAT, "w+b");
		if (fichero)
		{
			fwrite(&idNecesidad, sizeof(unsigned int),1,fichero);
			fflush(fichero);
			fclose(fichero);
		}
	}

	return (idNecesidad+1);
}


//*********************************************************************************************************************************************
//*********************************************************************************************************************************************
//*********************************************************************************************************************************************
//*********************************************************************************************************************************************
//*********************************************************************************************************************************************

//************************************************** cargarRegistroProducto ************************************************************************
void cargarRegistroProducto(unsigned int idProducto, REGBD_PRODUCTO *registro)
{

	FILE *fichero = fopen(BD_PRODUCTOS_DAT, "rb");

	if (fichero)
	{
		fseek(fichero, (long int)(idProducto*sizeof(REGBD_PRODUCTO)), SEEK_SET);
		fread(registro, sizeof(REGBD_PRODUCTO), 1,fichero);
		fclose(fichero);
	}

}

//************************************************ grabarRegistroProducto **************************************************************************
void grabarRegistroProducto(REGBD_PRODUCTO *registro)
{

	FILE *fichero = fopen(BD_PRODUCTOS_DAT, "r+b");
	
	if (fichero)
	{
		fseek(fichero, (long int)(registro->idProducto*sizeof(REGBD_PRODUCTO)), SEEK_SET);
		fwrite(registro, sizeof(REGBD_PRODUCTO),1,fichero);
		fflush(fichero);
		fclose(fichero);
	
	} else {

		fichero = fopen(BD_PRODUCTOS_DAT, "w+b");
		if (fichero) 				
		{
			fseek(fichero, (long int)(registro->idProducto*sizeof(REGBD_PRODUCTO)), SEEK_SET);
			fwrite(registro, sizeof(REGBD_PRODUCTO),1,fichero);
			fflush(fichero);
			fclose(fichero);
		}
	}
}

//*************************************************** grabarIdProductoLibre ***********************************************************************
void grabarIdProductoLibre(unsigned int id)
{
	FILE *fichero = fopen(ARCHIVO_IDPRODUCTO_DAT, "wb+");
	
	if (fichero)
	{
		fwrite(&id, sizeof(unsigned int),1,fichero);
		fflush(fichero);
		fclose(fichero);	
	}
}

//***************************************************** getSiguenteIdProductoLibre *********************************************************************
unsigned int getSiguenteIdProductoLibre()
{

	unsigned int idProducto=0;

	FILE *fichero = fopen(ARCHIVO_IDPRODUCTO_DAT, "rb");

	if (fichero)
	{
		fread(&idProducto, sizeof(unsigned int), 1,fichero);
		fclose(fichero);
	
	} else {
		
		fichero = fopen(ARCHIVO_IDPRODUCTO_DAT, "w+b");
		if (fichero)
		{
			fwrite(&idProducto, sizeof(unsigned int),1,fichero);
			fflush(fichero);
			fclose(fichero);
		}
	}

	return (idProducto+1);
}


#endif
