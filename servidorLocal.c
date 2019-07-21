#ifndef SERVIDOR_LOCAL_C
#define SERVIDOR_LOCAL_C

void* thread_func_bucle_server_local(G_GNUC_UNUSED void *data)
{
	printf("Ini: BUCLE SERVER LOCAL\n");

	while(ON_BUCLE_SERVER_LOCAL)
	{
		pthread_t hilo_hijo_server_local; 
		int s = pthread_create(&hilo_hijo_server_local, NULL, thread_func_servidor_local, NULL); 
		if (s != 0)
		{
			printf("****** Error al crear el hilo hilo_hijo_server_local\n");
			exit(-1);
		}

		s = pthread_join(hilo_hijo_server_local, NULL); 
		if (s != 0)
		{
			printf("****** Error en join hilo hilo_hijo_server_local\n");
			exit(-1);
		}

		usleep(ESPERA_HILO_SERVER_LOCAL);
	}

	return NULL;
}


//static gpointer thread_func_servidor_local(G_GNUC_UNUSED gpointer data)
void* thread_func_servidor_local(G_GNUC_UNUSED void *data)
{
	int fd, fd2; /* los ficheros descriptores */
	struct sockaddr_in server; /* para la información de la dirección del servidor */
	struct sockaddr_in client; 	/* para la información de la dirección del cliente */
	unsigned int sin_size;

	/* A continuación la llamada a socket() */
	if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) 
	{  
		printf("Servidor Local: error en socket()\n");
		return NULL;
	}

	server.sin_family = AF_INET;         
	server.sin_addr.s_addr = INADDR_ANY;  /* INADDR_ANY coloca nuestra dirección IP automáticamente */
	memset(&(server.sin_zero),0,sizeof(unsigned char)*8);
	/* escribimos ceros en el reto de la estructura */

	int vg_puerto_escucha_temporal = 0;

	do {

		vg_puerto_escucha_temporal = rand()%MAX_PORT;
		vg_puerto_escucha_temporal = ((vg_puerto_escucha_temporal<MIN_PORT)?(vg_puerto_escucha_temporal+MIN_PORT):vg_puerto_escucha_temporal);
		server.sin_port = htons(vg_puerto_escucha_temporal); 
	
	} while(bind(fd,(struct sockaddr*)&server, sizeof(struct sockaddr))==-1);

	G_LOCK( vg_puerto_escucha );
	{
		vg_puerto_escucha = vg_puerto_escucha_temporal;
	}
	G_UNLOCK( vg_puerto_escucha );

	printf("bind(OK): %hu\n", vg_puerto_escucha);
	
	if(listen(fd,BACKLOG) == -1) /* llamada a listen() */
	{  
		printf("Servidor Local: error en listen()\n");
		return NULL;
	}

	printf("Servidor Local Mango Productos iniciado en [%hu]\n", vg_puerto_escucha);

	G_LOCK(vg_servidorLocal_vivo);
	{
		vg_servidorLocal_vivo = VERDADERO;
	}
	G_UNLOCK(vg_servidorLocal_vivo);

	int bucle = VERDADERO;
	int s;

	while(bucle) 
	{
		sin_size = sizeof(struct sockaddr_in);
		/* A continuación la llamada a accept() */
		if ((fd2 = accept(fd,(struct sockaddr *)&client,  &sin_size))==-1)
		{
			printf("Servidor Local: error en accept()\n");
			continue;
		}
		printf("Servidor Local: Se obtuvo una conexión desde %s\n", inet_ntoa(client.sin_addr)); /* que mostrará la IP del cliente */


		pthread_t hilo_hijo_server_local; 
		s = pthread_create(&hilo_hijo_server_local, NULL, manejo_conexion_server_local, (void*)&fd2);
		if (s != 0)
		{
			printf("Error al crear el hilo hilo_hijo_server_local [%d]\n",s);
		}
		
		s = pthread_join(hilo_hijo_server_local, NULL);
		if (s != 0)
		{
			printf("Error al join en el hilo hilo_hijo_server_local [%d]\n",s);
		}

		G_LOCK(vg_servidorLocal_vivo);
		{
			bucle = vg_servidorLocal_vivo;
		}
		G_UNLOCK(vg_servidorLocal_vivo);
	}

	close(fd);
	return NULL;
}


void *manejo_conexion_server_local(void *data)
{

	printf("manejo_conexion_servidor_local OK\n");

	int *fd2 = (int*)data;
//	char buf[MAXDATASIZE];  
	int numbytes;
	int ciclo		= 1;
	int codigoP2P=0;

	while(ciclo)
	{
		if ((numbytes=recv(*fd2,&codigoP2P,sizeof(int),0)) == -1)
		{  
			printf("Error al leer el cliente\n");
			ciclo = 0;
			continue; 	
		}

		if (!numbytes)
		{
			printf("Corte de Comunicacion\n");
			ciclo = 0;
			continue; 	
		}

		printf("codigoP2P=%d\n", codigoP2P);

		if (codigoP2P == 666) //Busqueda
		{
			REGBD_NECESIDAD registro;
			memset(&registro, 0, sizeof(REGBD_NECESIDAD));
			
			if ((numbytes=recv(*fd2,&registro,sizeof(REGBD_NECESIDAD),0)) == -1)
			{  
				printf("Error al leer el cliente\n");
				ciclo = 0;
				continue; 	
			}	

			printf("Buscar: %s\n", registro.nombre);

			GSList *lista_busqueda_local=NULL, *iterador=NULL;

			lista_busqueda_local = procesar_peticion_busqueda_local(&registro, lista_busqueda_local);

			int total = (int)g_slist_length(lista_busqueda_local);

			if (total)
			{
				send(*fd2, &total, sizeof(int), 0);
				for (iterador=lista_busqueda_local;iterador;iterador=iterador->next)
				{
					REGBD_ENCONTRADO *reg2Enviar = (REGBD_ENCONTRADO*)iterador->data;
					send(*fd2, reg2Enviar, sizeof(REGBD_ENCONTRADO),0); 
				}
			}

			g_slist_free_full(lista_busqueda_local, (GDestroyNotify)liberarMemoria_busqueda_local);
			lista_busqueda_local = NULL;

			ciclo = 0;
			continue; 	
		}

		if (codigoP2P == 999) //Peticion de Foto
		{

			int numFoto=0;
			unsigned int idProductoFoto=0;

			if ((numbytes=recv(*fd2,&numFoto,sizeof(int),0)) == -1)
			{  
				printf("Error al leer el cliente cod-999-numFoto\n");
				ciclo = 0;
				continue; 	
			}	

			if ((numbytes=recv(*fd2,&idProductoFoto,sizeof(unsigned int),0)) == -1)
			{  
				printf("Error al leer el cliente cod-999-idProducto\n");
				ciclo = 0;
				continue; 	
			}	

			char strRutaArchivo[LARGO_STR_RUTAS];
			memset(strRutaArchivo, '\0',sizeof(char)*LARGO_STR_RUTAS);
			sprintf(strRutaArchivo,"bd/productos/%u-%d.png",idProductoFoto, numFoto);

			FILE *ficheroFoto2send = fopen(strRutaArchivo, "rb");

			if (ficheroFoto2send)
			{

 				fseek(ficheroFoto2send, 0L, SEEK_END);
 				long int tamanioFoto = ftell(ficheroFoto2send); 
				printf("Enviado tamanio foto=%ld\n",tamanioFoto);

				send(*fd2, &tamanioFoto, sizeof(long int), 0);

				unsigned char *bytesFoto = (unsigned char*)malloc(sizeof(unsigned char)*tamanioFoto);

 				fseek(ficheroFoto2send, 0L, SEEK_SET);
				fread(bytesFoto, tamanioFoto, 1,ficheroFoto2send);

				G_GNUC_UNUSED long int bytesEnviado = send(*fd2, bytesFoto, tamanioFoto, 0);

				if (bytesFoto)
					free(bytesFoto);

				fclose(ficheroFoto2send);
			}

			ciclo = 0;
			continue; 	
		}
	}
	close(*fd2);

	return NULL;
}
#endif
