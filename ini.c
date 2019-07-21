#ifndef INI_C
#define INI_C


//***************************************************** ini_variables_globales *************************************************
void ini_variables_globales()
{
	//Inicializar semilla para el random
	time_t t;
	srand((unsigned) time(&t));

	//************* Cargas de tiempo y fechas ****************
	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	fechaSistema.anio = tlocal->tm_year + 1900;
	fechaSistema.mes  = tlocal->tm_mon  + 1;
	fechaSistema.dia  = tlocal->tm_mday;

	//Para Maximizar segun los pixeles del monitor
	GdkScreen *GdkPantalla 	= gdk_screen_get_default(); 
	ancho_pantalla 			= gdk_screen_get_width(GdkPantalla);
	alto_pantalla  			= gdk_screen_get_height(GdkPantalla);

	memset(&vg_iplocal,0,sizeof(IP));

	pixBusqueda	= gdk_pixbuf_new_from_file("img/buscando.png",NULL);

	vg_registroUser = (REGBD_USER *)malloc(sizeof(REGBD_USER));

	memset(vg_registroUser,0,sizeof(REGBD_USER));

	vg_registroUser->id = 1;
	vg_registroUser->codEstado = 4;
	vg_registroUser->codMunicipio = 1;
	vg_registroUser->reputacion = 0;
	strcpy(vg_registroUser->nombre,NOMBRE_EMPRESA);
	strcpy(vg_registroUser->direccion,DIRECCION_EMPRESA);
	strcpy(vg_registroUser->telefono,TELEFONO_EMPRESA);

	for (int e=0;e<64;e++)
	{
		gslista_encontrados[e] = NULL;
	}

}

#endif
