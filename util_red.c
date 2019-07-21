#ifndef UTIL_RED_C
#define UTIL_RED_C


int getIPBD(unsigned int id, unsigned int idNecesidad, REGBD_NECESIDAD_IP *p2p_ip)
{
	int resul = FALSO;

	char ruta[LARGO_STR_RUTAS];
	memset(ruta,'\0', sizeof(char)*LARGO_STR_RUTAS);
	sprintf(ruta,"bd/busqueda/%u-tablaips.dat", idNecesidad);

printf("ruta=%s\n", ruta);

	FILE *ipBusquedabd = fopen(ruta,"rb");

	if (ipBusquedabd)
	{
		fseek(ipBusquedabd, 0L, SEEK_SET);

		while(fread(p2p_ip, sizeof(REGBD_NECESIDAD_IP), 1,ipBusquedabd))
		{
			printf("%u==%u\n",p2p_ip->id, id);

			if (p2p_ip->id==id)
			{
				resul = VERDADERO;
				break;
			}
		}

		fclose(ipBusquedabd);
	}	

	return resul;
}

int abrir_conexion_p2p(IP ip, unsigned int puerto)
{
    int s=0;
    struct sockaddr_in inf;

    if((s=socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		return s;
	}

    inf.sin_family = AF_INET;
    inf.sin_port = htons(puerto);
    inf.sin_addr.s_addr = ip.s_addr;
    memset(inf.sin_zero, 0, 8);

    if(connect(s, (struct sockaddr*)&inf, sizeof(inf)) == -1)
	{
		return -1;
	}

	return s;
}


int servidor_abrir_conexion()
{
    int s=0;
    struct sockaddr_in inf;

    if((s=socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		return FALSO;
	}

    inf.sin_family = AF_INET;
    inf.sin_port = htons(PORT);
    inf.sin_addr.s_addr = inet_addr(STR_IP_SERVER);
    memset(inf.sin_zero, 0, 8);

    if(connect(s, (struct sockaddr*)&inf, sizeof(inf)) == -1)
	{
		return FALSO;
	}

	return s;
}

int servidor_send(int descriptor, char* msm, char *respuesta)
{
    send(descriptor, msm, sizeof(char)*MAXDATASIZE, 0);

   	char temp[MAXDATASIZE];
	memset(respuesta, 0, sizeof(char)*MAXDATASIZE);
	memset(temp, 0, sizeof(char)*MAXDATASIZE);
 
	recv(descriptor, temp, sizeof(char)*MAXDATASIZE, 0);
	memcpy(respuesta, temp, sizeof(char)*MAXDATASIZE);

    return VERDADERO;
}

#endif
