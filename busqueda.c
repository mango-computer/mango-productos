
#ifndef BUSQUEDA_C
#define BUSQUEDA_C


GSList *buscarIps(REGBD_NECESIDAD *registro, GSList *listaIps)
{
	//Buscar IP de posibles vendedores
	//Solo criterio de sector, estado y municipio
	int descript = servidor_abrir_conexion();

	char msm[MAXDATASIZE];

	if (descript)
	{
		memset(msm,'\0',sizeof(char)*MAXDATASIZE);
		sprintf(msm,"150 busquedad %u %d %d", vg_registroUser->id, registro->codEstado , registro->codMunicipio); 

		send(descript, msm, sizeof(char)*MAXDATASIZE, 0);
		int cantidadIP=0;
		recv(descript, &cantidadIP, sizeof(int), 0);

		if (cantidadIP)
		{
			char ruta[LARGO_STR_RUTAS];
			memset(ruta,'\0', sizeof(char)*LARGO_STR_RUTAS);
			sprintf(ruta,"bd/busqueda/%u-tablaips.dat", registro->idNecesidad);

			FILE *ipBusqueda = fopen(ruta,"w+b");

			if (ipBusqueda)
			{
				fseek(ipBusqueda, 0L, SEEK_SET);

				for (int i=0;i<cantidadIP;i++)
				{
					REGBD_NECESIDAD_IP *reg_ip = (REGBD_NECESIDAD_IP *) malloc(sizeof(REGBD_NECESIDAD_IP));

					memset(reg_ip,0,sizeof(REGBD_NECESIDAD_IP));
					recv(descript, reg_ip, sizeof(REGBD_NECESIDAD_IP), 0);

					//Se graba la lista de los IP a un archivo para busqueda posteriores
					fwrite(reg_ip, sizeof(REGBD_NECESIDAD_IP),1,ipBusqueda);
					fflush(ipBusqueda);

					listaIps = g_slist_prepend(listaIps, reg_ip);
				}

				fclose(ipBusqueda);
			}
		}

		close(descript);
	}

	return listaIps;
}

void* thread_func_bucle_busqueda(void *data)
{
	printf("Ini: HILO FUNCION DE BUSQUEDA\n");

	REGBD_NECESIDAD *registro = (REGBD_NECESIDAD*)data;
//*****
	
	int estado_saludo=FALSO;

	G_LOCK(vg_saludo_servidor_on);
	{
		estado_saludo = vg_saludo_servidor_on;
	}
	G_UNLOCK(vg_saludo_servidor_on);

	//Buscar IP de posibles vendedores
	//Solo criterio de sector, estado y municipio
	if (estado_saludo)
	{
		GSList *listaIps = NULL;

		listaIps = buscarIps(registro, listaIps);

		int total = (int)g_slist_length(listaIps);

		if (total)
		{
			REGBD_NECESIDAD_IP *ip;
			int f=0;
			
			for (GSList *iterador=listaIps;iterador;iterador=iterador->next)
			{
				ip = (REGBD_NECESIDAD_IP*)iterador->data;
				
				if ((f=abrir_conexion_p2p(ip->ip, ip->puerto)) != -1)
				{
					//Busqueda directa P2P con todos los criterios a evaluar
					send(f, &codBusqueda, sizeof(int), 0);
					send(f, registro, sizeof(REGBD_NECESIDAD), 0);
							
					int resultados=0;
					recv(f, &resultados, sizeof(int), 0);

					if (resultados)
					{
						//Borrar los datos de la anterior lista
						//GSList *lista_resultados=NULL;
						g_slist_free_full(gslista_encontrados[registro->idNecesidad], (GDestroyNotify)liberarMemoria_busqueda_local);
						gslista_encontrados[registro->idNecesidad] = NULL;


						for (int resuls=0;resuls<resultados;resuls++)
						{
							REGBD_ENCONTRADO *regEncontrado = (REGBD_ENCONTRADO*)malloc(sizeof(REGBD_ENCONTRADO)); 

							memset(regEncontrado, 0, sizeof(REGBD_ENCONTRADO));
							recv(f, regEncontrado, sizeof(REGBD_ENCONTRADO), 0);
							printf("ClienteP2P -> Publicacion Recibida: %s\n", regEncontrado->nombre);

							//Cargar a una lista general indexada
							//lista_resultados = g_slist_prepend(lista_resultados, regEncontrado);
							gslista_encontrados[registro->idNecesidad] = 
										g_slist_prepend(gslista_encontrados[registro->idNecesidad], regEncontrado);
						}

						recargarTreeview_encontrados();
					}
					close(f);
				}
			}
			g_slist_free_full(listaIps, (GDestroyNotify)liberarMemoria_lista_ips);
			listaIps = NULL;
		}

	}

//*****
	free(registro); //viene de afuera
	registro = NULL;

	return registro;

}

GSList* procesar_peticion_busqueda_local(REGBD_NECESIDAD *regNecesidad, GSList *lista_busqueda_local)
{

printf("Funcion procesar_peticion_busqueda_local\n");

	FILE *fichero = fopen(BD_PRODUCTOS_DAT, "rb");

	int largo_nombre = MAXNOMBRE+1;
	const char s[2] = " ";

	char *token_nombre;
	char *tokenNombres[MAXNOMBRE];
	char str_nombre[largo_nombre];
	int on_buscarnombre=FALSO;
	int cn=0;
	char *temporal_nombre = (char*)malloc(sizeof(char)*MAXNOMBRE);

	char *token_descripcion;
	char *tokenDescripcion[MAXNOMBRE];
	char str_descripcion[largo_nombre];
	int on_buscarDescripcion=FALSO;
	int cd=0;
	char *temporal_descripcion = (char*)malloc(sizeof(char)*MAXNOMBRE);

	char *token_fabricante;
	char *tokenFabricante[MAXFABRICANTE];
	char str_fabricante[MAXFABRICANTE+1];
	int on_buscarFabricante=FALSO;
	int cf=0;
	char *temporal_fabricante = (char*)malloc(sizeof(char)*MAXFABRICANTE);


	if (fichero)
	{

//		fseek(fichero, 0L, SEEK_SET);
		REGBD_PRODUCTO registro;
		memset(&registro, 0, sizeof(REGBD_PRODUCTO));

		fseek(fichero, (long int)(sizeof(REGBD_PRODUCTO)), SEEK_SET);

		//****************** Nombre del Producto **********************
		if (strlen(regNecesidad->nombre))
		{
			memset(str_nombre, '\0', sizeof(char)*largo_nombre);
			strcpy(str_nombre, regNecesidad->nombre);

			for (int c=0;c<64;c++)
			{
				tokenNombres[c] = '\0';
			}

			token_nombre=strtok(str_nombre, s);
			if (token_nombre) on_buscarnombre = VERDADERO;
	
			while( token_nombre && (cn<MAXNOMBRE) )
			{
				token_nombre = str2Mayusculas(token_nombre);

				tokenNombres[cn++] = token_nombre;
				token_nombre = strtok(NULL, s);
			}
		}

		//***************** Descripcion ************************
		if (strlen(regNecesidad->descripcion))
		{
			memset(str_descripcion, '\0', sizeof(char)*largo_nombre);
			strcpy(str_descripcion, regNecesidad->descripcion);

			for (int c=0;c<64;c++)
			{
				tokenDescripcion[c] = '\0';
			}

			token_descripcion=strtok(str_descripcion, s);
			if (token_descripcion) on_buscarDescripcion = VERDADERO;
	
			while( token_descripcion && (cd<MAXNOMBRE) )
			{
				token_descripcion = str2Mayusculas(token_descripcion);

				tokenDescripcion[cd++] = token_descripcion;
				token_descripcion = strtok(NULL, s);
			}
		}


		//***************** Fabricante ************************
		if (strlen(regNecesidad->fabricante))
		{
			memset(str_fabricante, '\0', sizeof(char)*MAXFABRICANTE+1);
			strcpy(str_fabricante, regNecesidad->fabricante);

			for (int c=0;c<64;c++)
			{
				tokenFabricante[c] = '\0';
			}

			token_fabricante=strtok(str_fabricante, s);
			if (token_fabricante) on_buscarFabricante = VERDADERO;
	
			while( token_fabricante && (cf<MAXFABRICANTE) )
			{
				token_fabricante = str2Mayusculas(token_fabricante);

				tokenFabricante[cf++] = token_fabricante;
				token_fabricante = strtok(NULL, s);
			}
		}

		while(fread(&registro, sizeof(REGBD_PRODUCTO), 1,fichero))
		{
			if (!registro.activo) continue;

			//*********************************** Zona de Filtro ********************************************
			//*********************************** Zona de Filtro ********************************************

printf("Dentro del bucle de filtro de busqueda\n");

			if ((regNecesidad->codEstado>0) && (regNecesidad->codEstado != vg_registroUser->codEstado))
			{
				printf("Corte 1\n");
				continue;
			}

			if ((regNecesidad->codMunicipio>0) && (regNecesidad->codMunicipio != vg_registroUser->codMunicipio)) 	
			{
				printf("Corte 2\n");
				continue;
			}

			if (regNecesidad->nuevo != registro.nuevo) 						
			{
				printf("Corte 2\n");
				continue;
			}

			if (regNecesidad->fabricacion != registro.fabricacion) 		
			{
				printf("Corte 3\n");
				continue;
			}

			if (regNecesidad->transporte != registro.transporte) 			
			{
				printf("Corte 4\n");
				continue;
			}

			//El precio de busqueda mas un 50% como limite de precio en busqueda, solo si, la unidad esta activa y el precio es mayor que cero
			if (regNecesidad->codUnidad && registro.precio)
			{
				unsigned long int precio_limite = (unsigned long int)(regNecesidad->precio * 3); 

				if (registro.precio > precio_limite)
				{
					printf("Corte 5\n");
					continue;
				}

			}

			if (regNecesidad->codPresentacion)
			{
				if (regNecesidad->codPresentacion != registro.codPresentacion)
				{
					printf("Corte 6\n");
					continue;
				}
		
				if ((regNecesidad->disponibilidad) && (regNecesidad->disponibilidad >registro.disponibilidad)) 
				{
					printf("Corte 7\n");
					continue;
				}
			}


			//********************** Nombre *******************
			if (on_buscarnombre && strlen(registro.nombre))
			{
				int cc=0;
				int encontrado = VERDADERO;

				while(tokenNombres[cc])
				{
					strcpy(temporal_nombre,registro.nombre);
					temporal_nombre = str2Mayusculas(temporal_nombre);

					if (!strstr( temporal_nombre, tokenNombres[cc]) )
					{
						encontrado = FALSO;
						break;
					} 	
					cc++;
				}

				if (!encontrado) continue;
			}

			//********************** descripcion *******************
			if (on_buscarDescripcion && strlen(registro.descripcion))
			{
				int cc=0;
				int encontrado = VERDADERO;

				while(tokenDescripcion[cc])
				{
					strcpy(temporal_descripcion,registro.descripcion);
					temporal_descripcion = str2Mayusculas(temporal_descripcion);

					if (!strstr( temporal_descripcion, tokenDescripcion[cc]) )
					{
						encontrado = FALSO;
						break;
					} 	
					cc++;
				}

				if (!encontrado) continue;
			}

			//********************** fabricante *******************
			if (on_buscarFabricante && strlen(registro.fabricante))
			{
				int cc=0;
				int encontrado = VERDADERO;

				while(tokenFabricante[cc])
				{
					strcpy(temporal_fabricante,registro.fabricante);
					temporal_fabricante = str2Mayusculas(temporal_fabricante);

					if (!strstr( temporal_fabricante, tokenFabricante[cc]) )
					{
						encontrado = FALSO;
						break;
					} 	
					cc++;
				}

				if (!encontrado) continue;
			}


			//*********************************** Zona de Filtro ********************************************
			//*********************************** Zona de Filtro ********************************************


			REGBD_ENCONTRADO *regEncontrado = (REGBD_ENCONTRADO*)malloc(sizeof(REGBD_ENCONTRADO)); 
			memset(regEncontrado,0,sizeof(REGBD_ENCONTRADO));

printf("Producto OK [%s]\n", regEncontrado->nombre);

			regEncontrado->idProductoProveedor 	= registro.idProducto;
			regEncontrado->idNecesidad			= regNecesidad->idNecesidad;
			regEncontrado->idProveedor			= vg_registroUser->id;
			strcpy(regEncontrado->nombre, registro.nombre);
			strcpy(regEncontrado->descripcion, registro.descripcion);
			regEncontrado->precio 				= registro.precio; 
			regEncontrado->disponibilidad 		= registro.disponibilidad;
			regEncontrado->codUnidad			= registro.codUnidad;
			regEncontrado->codPresentacion		= registro.codPresentacion;
			strcpy(regEncontrado->fabricante, registro.fabricante);
			regEncontrado->nuevo				= registro.nuevo;
			regEncontrado->fabricacion			= registro.fabricacion;
			regEncontrado->transporte			= registro.transporte; 
			regEncontrado->codEstado			= vg_registroUser->codEstado;
			regEncontrado->codMunicipio			= vg_registroUser->codMunicipio;		
			strcpy(regEncontrado->nombre_empresa, vg_registroUser->nombre);
			strcpy(regEncontrado->direccion_empresa, vg_registroUser->direccion);
			strcpy(regEncontrado->telefono, vg_registroUser->telefono);
			regEncontrado->flag_fotos			= registro.flag_fotos;

			strcpy(regEncontrado->descripcionFoto1, registro.descripcionFoto1);
			strcpy(regEncontrado->descripcionFoto2, registro.descripcionFoto2);
			strcpy(regEncontrado->descripcionFoto3, registro.descripcionFoto3);
			strcpy(regEncontrado->descripcionFoto4, registro.descripcionFoto4);


			lista_busqueda_local = g_slist_prepend(lista_busqueda_local, regEncontrado);

		} 
	
		fclose(fichero);
		if (lista_busqueda_local)
		{
			lista_busqueda_local = g_slist_reverse(lista_busqueda_local);
		}
	}

	if(temporal_nombre)
		free(temporal_nombre);

	if(temporal_descripcion)
		free(temporal_descripcion);

	return lista_busqueda_local;	
}


#endif
