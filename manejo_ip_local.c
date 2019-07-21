#ifndef MANEJO_IP_LOCAL_C
#define MANEJO_IP_LOCAL_C

void* thread_func_bucle_check_ip(G_GNUC_UNUSED void *data)
{
	printf("Ini: thread_func_bucle_check_ip\n");

	while(ON_BUCLE_CHECK_IP)
	{
		if (ES_VALIDO_PUERTO(vg_puerto_escucha))
		{
			pthread_t hilo_hijo_check_ip; 
			int s = pthread_create(&hilo_hijo_check_ip, NULL, thread_func_check_ip_local, NULL); 

			if (s != 0)
			{
				printf("****** Error al crear el hilo hilo_hijo_check_ip\n");
				exit(-1);
			}

			s = pthread_join(hilo_hijo_check_ip, NULL); 
			if (s != 0)
			{
				printf("****** Error en join hilo hilo_hijo_check_ip\n");
				exit(-1);
			}
		}

		usleep(ESPERA_HILO_CHECK_IP);
	}

	return NULL;
}


void* thread_func_check_ip_local(G_GNUC_UNUSED void *data)
{

	char msm[MAXDATASIZE];
	char respuesta[MAXDATASIZE];
	memset(respuesta,'\0',sizeof(char)*MAXDATASIZE);

	int estado_saludo = FALSO;

	int descript = servidor_abrir_conexion();

	//printf("ip_local descript=%d\n", descript);

	if (descript)
	{
		memset(msm,'\0',sizeof(char)*MAXDATASIZE);
		sprintf(msm,"110 hola %u %hu", vg_identificador, vg_puerto_escucha); 

		if (servidor_send(descript, msm, respuesta))
		{

			if (!strncmp(respuesta,"110 hola",8)) //el servidor acepto el saludo 
			{
			//	printf("S->C: [%s]\n", respuesta);
				sscanf(respuesta,"110 hola %u %d",&vg_iplocal.s_addr, &vg_reputacion);

//				printf("IP:PORT R --> %s:%hu %d\n", inet_ntoa(vg_iplocal), vg_puerto_escucha, vg_reputacion); /* que mostrará la IP del cliente */

				memset(msm,'\0',sizeof(char)*MAXDATASIZE);
				strcpy(msm,"100 salir");

				estado_saludo = VERDADERO;

				memset(respuesta,'\0',sizeof(char)*MAXDATASIZE);
				if (servidor_send(descript, msm, respuesta))
				{
					if (!strncmp(respuesta,"100 salir",8)) //el servidor acepto el saludo 
					{
						servidor_send(descript, msm, respuesta);
					}
				}
			}
		}

		close(descript);
	}


	G_LOCK(vg_saludo_servidor_on);
	{
		vg_saludo_servidor_on = estado_saludo;
	}
	G_UNLOCK(vg_saludo_servidor_on);

	return NULL;
}

#endif
