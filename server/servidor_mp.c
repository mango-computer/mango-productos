
//************************************************** Include *******************************************************


//In Linux it is %llu and in Windows it is %I64u

// Ver numero de hilos del proceso -> ps hH p 6454 | wc -l

#include <stdio.h>
#include <sys/types.h>
//#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>

#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <glib.h>

#ifdef _MSC_VER
  typedef unsigned __int64 			uint64;
#else
  typedef unsigned long long int 	uint64;
#endif


//************************************************** Macros ************************************************************

#define FALSO 		0
#define VERDADERO 	1


#define VER

#define PORT 			3550 /* El puerto que será abierto */
#define BACKLOG 		10 /* El número de conexiones permitidas */
#define MAXDATASIZE 	128
#define MAXNOMBRE 		64
#define MAX_USER_MP		1000000
#define PAGINA			4096

#define MSM_SALIR 						100
#define MSM_HOLA  						110
#define MSM_CHAO						120
#define MSM_CHAO_OK						121
#define MSM_CREAR_USER  				130
#define MSM_INFO_USER_UPDATE			140
#define MSM_BUSQUEDA					150
#define MSM_QUIEN_ES					160
#define MSM_GET_IP						165
#define MSM_NO_EXISTE_ID				500
#define MSM_PUERTO_ESCUCHA_NO_VALIDO	510
#define MSM_VER_ID_ONLINE				520
#define MSM_COMANDO_DESCONOCIDO			600

#define MSM_SALIR_TXT						"100 salir"
#define MSM_HOLA_TXT  						"110 hola"
#define MSM_CHAO_TXT						"120 chao"
#define MSM_CHAO_OK_TXT						"121 chao ok"
#define MSM_CREAR_USER_TXT  				"130 crear user"
#define MSM_INFO_USER_UPDATE_TXT			"140 update user"
#define MSM_BUSQUEDA_TXT					"150 busquedad"
#define MSM_QUIEN_ES_TXT					"160 quien es"
#define MSM_NO_EXISTE_ID_TXT				"500 no existe id"
#define MSM_PUERTO_ESCUCHA_NO_VALIDO_TXT	"510 puerto no valido"
#define MSM_COMANDO_DESCONOCIDO_TXT			"600 comando desconocido"

#define ES_VALIDO_PUERTO(p) ((p>10000 && p<60000))

//********************************************* Data ********************************************************************

char *msm_saludo = "Servidor Mango Productos 1.0";


//************************************************** Estructuras *******************************************************

typedef unsigned short int PUERTO;

//Data BD
typedef struct {

	unsigned int id;
	int cod_estado;
	int cod_municipio;
	int	reputacion;
	char nombre[MAXNOMBRE];

} REGBD_USER_MP;


typedef struct in_addr IP;

//Reg en Ram para acceso directo
typedef struct {

	REGBD_USER_MP reg_user;
	int online;
	PUERTO puerto_escucha;
	IP ip;

} REG_USER_MP;
/*
typedef struct {

	unsigned int id;
	PUERTO puerto_escucha;
	IP ip;

} INDEX_BUSQUEDA;
//*/
typedef struct {

	unsigned int id;
	IP ip;
	unsigned short int puerto;

} REGBD_NECESIDAD_IP;


/*
struct in_addr 
{
   unsigned long s_addr;
};
*/

//Data para el hilo
typedef struct {

	int idf;
	IP ip;

} DATA_HILO;


//********************************************* variables globales *****************************************************
pthread_mutex_t mutex_lista_user_mp_en_ram;
pthread_mutex_t mutex_lista_user_mp_activos;
pthread_mutex_t mutex_bd;

REG_USER_MP *lista_user_mp_en_ram;
GSList *lista_user_mp_activos = NULL;
int servidor_vivo = 1;


//******************************************* Funciones *********************************************************************

//**************************************************** liberarMemoriaListaIp **********************************************
void liberarMemoriaListaIp(gpointer data)
{
	free((REGBD_NECESIDAD_IP*)data);
	data = NULL;
}

//******************************************* actualizar_user_mp ***********************************************
int actualizar_user_mp(unsigned int id_user_mp, char *nombre_empresa, int cod_estado, int cod_municipio)
{
	int result = 0;

	// ****************** MUTEX **************************
	pthread_mutex_lock(&mutex_lista_user_mp_en_ram);
	{
		if ( (lista_user_mp_en_ram + id_user_mp)->reg_user.id == id_user_mp )
		{
			result = 1;

			(lista_user_mp_en_ram + id_user_mp)->reg_user.cod_estado		= cod_estado;
			(lista_user_mp_en_ram + id_user_mp)->reg_user.cod_municipio		= cod_municipio;

			memset((lista_user_mp_en_ram + id_user_mp)->reg_user.nombre, '\0', sizeof(char)*MAXNOMBRE);

			if (strlen(nombre_empresa)>=MAXNOMBRE)
			{
				strncpy((lista_user_mp_en_ram + id_user_mp)->reg_user.nombre, nombre_empresa,MAXNOMBRE-1); 

			} else {

				strcpy((lista_user_mp_en_ram + id_user_mp)->reg_user.nombre, nombre_empresa);
			}
		}
	}
	pthread_mutex_unlock(&mutex_lista_user_mp_en_ram);
	// ****************** MUTEX **************************

	if (result)
	{
		// ****************** MUTEX **************************
		pthread_mutex_lock(&mutex_bd);
		{
			FILE *fichero = fopen("data_mp.dat", "w+b");
			if (fichero) 				
			{
				
				fseek(fichero, (long int)(id_user_mp*sizeof(REGBD_USER_MP)), SEEK_SET);
				fwrite(&(lista_user_mp_en_ram + id_user_mp)->reg_user, sizeof(REGBD_USER_MP),1,fichero);
				fflush(fichero);
				fclose(fichero);
			}
		} 
		pthread_mutex_unlock(&mutex_bd);
		// ****************** MUTEX **************************
	}


	return result;
}

//******************************************* crear_listaip_segun_criterio***********************************************
GSList* crear_listaip_segun_criterio(GSList* lista, int cod_estado, int cod_municipio)
{


	// ****************** MUTEX **************************
	pthread_mutex_lock(&mutex_lista_user_mp_activos);
	pthread_mutex_lock(&mutex_lista_user_mp_en_ram);
	{
		GSList *iterador = NULL;
		unsigned int id = 0;
		
		for (iterador=lista_user_mp_activos;iterador;iterador=iterador->next)
		{
			id = GPOINTER_TO_UINT(iterador->data);

			if ((cod_estado>0) && ((lista_user_mp_en_ram + id)->reg_user.cod_estado								!= cod_estado)) 	continue;
			if ((cod_estado>0) && (cod_municipio>0) && ((lista_user_mp_en_ram + id)->reg_user.cod_municipio 	!= cod_municipio)) 	continue;

			REGBD_NECESIDAD_IP *data = (REGBD_NECESIDAD_IP*)malloc(sizeof(REGBD_NECESIDAD_IP));
			if (data)
			{
				memcpy(&data->ip, &(lista_user_mp_en_ram + id)->ip, sizeof(IP));
				data->id 		= id;
				data->puerto	= (lista_user_mp_en_ram + id)->puerto_escucha;
				lista = g_slist_prepend(lista, data);
			}
		}
	}
	pthread_mutex_unlock(&mutex_lista_user_mp_en_ram);
	pthread_mutex_unlock(&mutex_lista_user_mp_activos);
	// ****************** MUTEX **************************

	return lista; 
}

//******************************************* crear_user_mp***********************************************
unsigned int crear_user_mp(char *nombre_empresa, int cod_estado, int cod_municipio, IP *ip, PUERTO puerto_escucha)
{
	unsigned int id_libre=0;

	// ****************** MUTEX **************************
	pthread_mutex_lock(&mutex_lista_user_mp_en_ram);
	{
		//Buscar Id Libre
		for (unsigned int i=1;i<MAX_USER_MP;i++)
		{
			if ((lista_user_mp_en_ram + i)->reg_user.id) continue;

			id_libre=i;
			break;
		}
	}
	pthread_mutex_unlock(&mutex_lista_user_mp_en_ram);
	// ****************** MUTEX **************************

	if (id_libre)
	{
		REGBD_USER_MP reg;
		memset(&reg,0,sizeof(REGBD_USER_MP));

		// ****************** MUTEX **************************
		pthread_mutex_lock(&mutex_bd);
		{
			FILE *fichero = fopen("data_mp.dat", "r+b");
			if (!fichero)
			{
				fichero = fopen("data_mp.dat", "w+b");
			}

			if (fichero) 				
			{
				reg.id 				= id_libre;
				reg.cod_estado		= cod_estado;
				reg.cod_municipio	= cod_municipio;
				reg.reputacion		= 0;
				
				if (strlen(nombre_empresa)>=MAXNOMBRE)
				{
					 strncpy(reg.nombre, nombre_empresa,MAXNOMBRE-1); 

				} else {

					strcpy(reg.nombre, nombre_empresa);
				}

				fseek(fichero, (long int)(id_libre*sizeof(REGBD_USER_MP)), SEEK_SET);
				fwrite(&reg, sizeof(REGBD_USER_MP),1,fichero);
				fflush(fichero);
				fclose(fichero);
			}
		} 
		pthread_mutex_unlock(&mutex_bd);
		// ****************** MUTEX **************************


		// ****************** MUTEX **************************
		pthread_mutex_lock(&mutex_lista_user_mp_en_ram);
		{
			memcpy(&(lista_user_mp_en_ram + id_libre)->reg_user, &reg, sizeof(REGBD_USER_MP));
			(lista_user_mp_en_ram + id_libre)->online  			= 1;
			(lista_user_mp_en_ram + id_libre)->puerto_escucha	= puerto_escucha;
			(lista_user_mp_en_ram + id_libre)->ip.s_addr 		= ip->s_addr;
		}
		pthread_mutex_unlock(&mutex_lista_user_mp_en_ram);
		// ****************** MUTEX **************************

		// ****************** MUTEX **************************
		pthread_mutex_lock(&mutex_lista_user_mp_activos);
		{
			lista_user_mp_activos = g_slist_prepend(lista_user_mp_activos, GUINT_TO_POINTER(id_libre)); 
		}
		pthread_mutex_unlock(&mutex_lista_user_mp_activos);
		// ****************** MUTEX **************************

	}

	return id_libre;
} 


//******************************************* manejo_conexion***********************************************
//******************************************* manejo_conexion***********************************************
//******************************************* manejo_conexion***********************************************
//******************************************* manejo_conexion***********************************************
void *manejo_conexion(void *data)
{
//	printf("manejo_conexion OK\n");

	DATA_HILO *ptr_data = (DATA_HILO*)data;
	char buf[MAXDATASIZE];  
	int numbytes;
	int ciclo=1;
	int cod_msm = 0;

	int salirEnviando = FALSO;

	while(ciclo)
	{
		if ((numbytes=recv(ptr_data->idf,buf,MAXDATASIZE,0)) == -1)
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

		buf[numbytes]='\0';
		printf("C->S[%s][numbytes=%d]\n",buf, numbytes);
		if (buf[0]=='x' && buf[1]=='X' && buf[2]=='x')
		{
			printf("Parada Forzada\n");
			ciclo = 0;
			servidor_vivo = 0;
			continue; 							
		}

	 	cod_msm = ((buf[0]-48)*100) + ((buf[1]-48)*10) + (buf[2]-48); 

		switch(cod_msm)
		{
			//********************************** MSM_HOLA 
			case MSM_HOLA:
			{
				unsigned int id_user_mp=0;
				PUERTO puerto_escucha = 0;
				sscanf(buf, "110 hola %u %hu", &id_user_mp, &puerto_escucha);
								
				if (ES_VALIDO_PUERTO(puerto_escucha)) //Existe id de user mp y el puerto del cliente es valido
				{
					int reputacion = -1;
					// ****************** MUTEX **************************
					pthread_mutex_lock(&mutex_lista_user_mp_en_ram);
					{
						if ( (lista_user_mp_en_ram + id_user_mp)->reg_user.id == id_user_mp )
						{
							reputacion 	= (lista_user_mp_en_ram + id_user_mp)->reg_user.reputacion;
							(lista_user_mp_en_ram + id_user_mp)->puerto_escucha = puerto_escucha;
							(lista_user_mp_en_ram + id_user_mp)->ip.s_addr 		= ptr_data->ip.s_addr;

printf("id= %u [%u]\n", id_user_mp, ptr_data->ip.s_addr);

							if (!(lista_user_mp_en_ram + id_user_mp)->online)
							{
								(lista_user_mp_en_ram + id_user_mp)->online	= 1;
								lista_user_mp_activos = g_slist_prepend(lista_user_mp_activos, GUINT_TO_POINTER(id_user_mp)); 
							}
						}
					}
					pthread_mutex_unlock(&mutex_lista_user_mp_en_ram);
					// ****************** MUTEX **************************

					if (reputacion != -1)
					{
						//Enviar Reputacion con el comando HOLA
						char str_temp[MAXDATASIZE];
						memset(str_temp, '\0', sizeof(char)*MAXDATASIZE);
						sprintf(str_temp, "%s %u %d", MSM_HOLA_TXT, (lista_user_mp_en_ram + id_user_mp)->ip.s_addr, reputacion);
					//	printf("S->C: [%s]\n", str_temp);
						send(ptr_data->idf, str_temp, strlen(str_temp), 0);
			
					} else {

					//	printf("S->C: [%s]\n", MSM_NO_EXISTE_ID_TXT);
						send(ptr_data->idf,MSM_NO_EXISTE_ID_TXT, strlen(MSM_NO_EXISTE_ID_TXT),0);
					}
	
				} else {

				//	printf("S->C: [%s]\n", MSM_PUERTO_ESCUCHA_NO_VALIDO_TXT);
					send(ptr_data->idf,MSM_PUERTO_ESCUCHA_NO_VALIDO_TXT, strlen(MSM_PUERTO_ESCUCHA_NO_VALIDO_TXT),0);
				}

//				ciclo = 0;
				continue;

			} break;

			//********************************** MSM_CHAO 
			case MSM_CHAO:
			{
				unsigned int id_user_mp=0;
				sscanf(buf, "120 chao %u", &id_user_mp);

				PUERTO puerto_escucha = 0;

				// ****************** MUTEX **************************
				pthread_mutex_lock(&mutex_lista_user_mp_en_ram);
				{
					if ( (lista_user_mp_en_ram + id_user_mp)->online )
					{
						puerto_escucha 	= (lista_user_mp_en_ram + id_user_mp)->puerto_escucha;
						(lista_user_mp_en_ram + id_user_mp)->puerto_escucha = 0;
						(lista_user_mp_en_ram + id_user_mp)->online = 0;
					}
				}
				pthread_mutex_unlock(&mutex_lista_user_mp_en_ram);
				// ****************** MUTEX **************************

				char str_temp[MAXDATASIZE];
				memset(str_temp, '\0', sizeof(char)*MAXDATASIZE);

				if (puerto_escucha) 
				{
					// ****************** MUTEX **************************
					pthread_mutex_lock(&mutex_lista_user_mp_activos);
					{

						GSList *iterador = NULL;
						unsigned int id = 0;
		
						for (iterador=lista_user_mp_activos;iterador;iterador=iterador->next)
						{
							id = GPOINTER_TO_UINT(iterador->data);

							if (id == id_user_mp)
							{
								lista_user_mp_activos = g_slist_remove(lista_user_mp_activos, iterador->data);
								break;
							}
						}
					}
					pthread_mutex_unlock(&mutex_lista_user_mp_activos);
					// ****************** MUTEX **************************

				//	printf("S->C: [%s]\n", MSM_CHAO_OK_TXT);
					send(ptr_data->idf, MSM_CHAO_OK_TXT, strlen(MSM_CHAO_OK_TXT), 0);

				} else { 
				
					sprintf(str_temp, "%s %u", MSM_NO_EXISTE_ID_TXT, id_user_mp);
				//	printf("S->C: [%s]\n", str_temp);
					send(ptr_data->idf,str_temp,strlen(str_temp),0);
				}	
				
//				ciclo = 0;
				continue; 	

			} break;


			//********************************** MSM_CREAR_USER
			case MSM_CREAR_USER:
			{
				int cod_estado		= 0;
				int cod_municipio	= 0;
				PUERTO puerto_escucha=0;
				char nombre_empresa[MAXNOMBRE];
				unsigned int id_nuevo=0;
				memset(nombre_empresa, '\0',sizeof(char)*MAXNOMBRE);

				sscanf(buf, "130 crear user %s %d %d %hu", nombre_empresa, &cod_estado, &cod_municipio, &puerto_escucha);
				if (ES_VALIDO_PUERTO(puerto_escucha))
				{
					id_nuevo = crear_user_mp(nombre_empresa, cod_estado, cod_municipio, &ptr_data->ip, puerto_escucha);
					char str_temp[MAXDATASIZE];
					memset(str_temp, '\0', sizeof(char)*MAXDATASIZE);
					sprintf(str_temp, "%s %u", MSM_CREAR_USER_TXT, id_nuevo);

					printf("S->C: [%s]\n", str_temp);
					send(ptr_data->idf, str_temp, strlen(str_temp), 0);

				} else {

					printf("S->C: [%s]\n", MSM_PUERTO_ESCUCHA_NO_VALIDO_TXT);
					send(ptr_data->idf, MSM_PUERTO_ESCUCHA_NO_VALIDO_TXT, strlen(MSM_PUERTO_ESCUCHA_NO_VALIDO_TXT), 0);
				}

//				ciclo = 0;
				continue; 	
	
			} break;

			//********************************** MSM_INFO_USER_UPDATE
			case MSM_INFO_USER_UPDATE:
			{
				int cod_estado			= 0;
				int cod_municipio		= 0;
				unsigned int id_user_mp	= 0;
				char nombre_empresa[MAXNOMBRE];
		
				memset(nombre_empresa, '\0',sizeof(char)*MAXNOMBRE);

				sscanf(buf, "140 update user %u %s %d %d", &id_user_mp, nombre_empresa, &cod_estado, &cod_municipio);
				int res = actualizar_user_mp(id_user_mp, nombre_empresa, cod_estado, cod_municipio);

				//Enviar resultado, en caso de ser 0, el cliente sabrá que no se pudo actualizar la data
				char str_temp[MAXDATASIZE];
				memset(str_temp, '\0', sizeof(char)*MAXDATASIZE);
				sprintf(str_temp, "%s %d", MSM_INFO_USER_UPDATE_TXT, res);
				printf("S->C: [%s]\n", str_temp);
				send(ptr_data->idf, str_temp, strlen(str_temp), 0);
//				ciclo = 0;

				continue; 	

			} break;


			//********************************** MSM_QUIEN_ES
			case MSM_QUIEN_ES:
			{
				unsigned int id_user_mp	= 0;

				sscanf(buf, "160 quien es %u", &id_user_mp);
				int reputacion = -1;
				REG_USER_MP reg;

				// ****************** MUTEX **************************
				pthread_mutex_lock(&mutex_lista_user_mp_en_ram);
				{
					if ( (lista_user_mp_en_ram + id_user_mp)->reg_user.id == id_user_mp )
					{
						reputacion 	= (lista_user_mp_en_ram + id_user_mp)->reg_user.reputacion;
						memcpy(&reg, (lista_user_mp_en_ram + id_user_mp), sizeof(REG_USER_MP));
					}
				}
				pthread_mutex_unlock(&mutex_lista_user_mp_en_ram);
				// ****************** MUTEX **************************
							
				if (reputacion != -1) //Existe id de user mp
				{
					char str_temp[MAXDATASIZE];
					memset(str_temp, '\0', sizeof(char)*MAXDATASIZE);

					sprintf(str_temp, "%s %s %d %d %d %d %u %hu", 
						MSM_QUIEN_ES_TXT, 
						reg.reg_user.nombre,
  						reg.reg_user.cod_estado, 
						reg.reg_user.cod_municipio, 
						reg.reg_user.reputacion,
						reg.online,
						reg.ip.s_addr,
						reg.puerto_escucha);

					printf("S->C: [%s]\n", str_temp);
					send(ptr_data->idf, str_temp, strlen(str_temp), 0);

				} else { 

					printf("S->C: [%s]\n", MSM_NO_EXISTE_ID_TXT);
					send(ptr_data->idf,MSM_NO_EXISTE_ID_TXT,strlen(MSM_NO_EXISTE_ID_TXT),0);
				}

				continue; 	

			} break;

			//********************************** MSM_GET_IP
			case MSM_GET_IP:
			{
				unsigned int id_user_mp	= 0;

				sscanf(buf, "165 getip %u", &id_user_mp);
				int reputacion = -1;
				REG_USER_MP reg;

				// ****************** MUTEX **************************
				pthread_mutex_lock(&mutex_lista_user_mp_en_ram);
				{
					if ( (lista_user_mp_en_ram + id_user_mp)->reg_user.id == id_user_mp )
					{
						reputacion 	= (lista_user_mp_en_ram + id_user_mp)->reg_user.reputacion;
						memcpy(&reg, (lista_user_mp_en_ram + id_user_mp), sizeof(REG_USER_MP));
					}
				}
				pthread_mutex_unlock(&mutex_lista_user_mp_en_ram);
				// ****************** MUTEX **************************
							
				if (reputacion != -1) //Existe id de user mp
				{
					printf("S->C: [%u]\n", reg.ip.s_addr);
					send(ptr_data->idf, &reg.ip, sizeof(reg.ip), 0);

				} else { 
					
					int noip=0;
			
					printf("S->C: [0]\n");
					send(ptr_data->idf,&noip,sizeof(int),0);
				}

				continue; 	

			} break;


			//********************************** MSM_BUSQUEDA
			case MSM_BUSQUEDA:
			{
				unsigned int id_user_mp	= 0;
				int cod_estado			= 0;
				int cod_municipio		= 0;

				sscanf(buf, "150 busquedad %u %d %d", &id_user_mp, &cod_estado, &cod_municipio);
							
				char str_temp[MAXDATASIZE];
				memset(str_temp, '\0', sizeof(char)*MAXDATASIZE);

				//Crear una lista con todas las ip y luego enviar una a una
				GSList *list = NULL, *iterador = NULL;
				list = crear_listaip_segun_criterio(list, cod_estado, cod_municipio);
				int total = (int)g_slist_length(list);
				REGBD_NECESIDAD_IP *ipdata;

				if (total)
				{
					send(ptr_data->idf, &total, sizeof(int), 0);
					printf("S->C: [total=%d]\n", total);

					for (iterador=list;iterador;iterador=iterador->next)
					{
						ipdata = (REGBD_NECESIDAD_IP*)iterador->data;
						send(ptr_data->idf, ipdata, sizeof(REGBD_NECESIDAD_IP),0); 
						//*inet_ntoa(ip->sin_addr) -> Devuelve la IP en char asi 192.168.2.1
//						sprintf(str_temp, "%u %hu %u", ipdata->id, ipdata->puerto_escucha, ipdata->ip.s_addr); 
//						printf("S->C: [%s]\n", str_temp);
//						send(ptr_data->idf, str_temp, strlen(str_temp), 0);
					}

				} else {
					
					int cero=0;	
					printf("S->C: [0]\n");
					send(ptr_data->idf, &cero, sizeof(int), 0);
				}

				if (list)
				{
					g_slist_free_full(list, (GDestroyNotify)liberarMemoriaListaIp);
					list = NULL;
				}

//				ciclo = 0;
				continue; 	

			} break;

			//********************************** MSM_VER_ID_ONLINE
			case MSM_VER_ID_ONLINE:
			{

				// ****************** MUTEX **************************
				pthread_mutex_lock(&mutex_lista_user_mp_activos);
				{
					GSList *iterador = NULL;
					unsigned int id = 0;
		
					for (iterador=lista_user_mp_activos;iterador;iterador=iterador->next)
					{
						id = GPOINTER_TO_UINT(iterador->data);
						printf("id:[%d]\n",id);
					}

					int total = (int)g_slist_length(lista_user_mp_activos);
					printf("Total: [%d]\n", total);
				}
				pthread_mutex_unlock(&mutex_lista_user_mp_activos);
				// ****************** MUTEX **************************
				continue; 	

			} break;

			//********************************** MSM_SALIR
			case MSM_SALIR:
			{
				if (salirEnviando)
				{
					//printf("S->C: [%s]\n", MSM_SALIR_TXT);
					send(ptr_data->idf,MSM_SALIR_TXT,strlen(MSM_SALIR_TXT),0);
					ciclo = 0;

				} else {

					//printf("S->C: [%s]\n", MSM_SALIR_TXT);
					send(ptr_data->idf,MSM_SALIR_TXT,strlen(MSM_SALIR_TXT),0);
					salirEnviando = VERDADERO;
				}

				continue; 	

			} break;

			default:
			{
				printf("S->C: [%s]\n", MSM_COMANDO_DESCONOCIDO_TXT);
				send(ptr_data->idf,MSM_COMANDO_DESCONOCIDO_TXT,strlen(MSM_COMANDO_DESCONOCIDO_TXT),0);
//				ciclo = 0;
				continue; 	

			} break;

		} //Fin del switch

	} // Fin de while ciclo

//	printf("cerrado el hilo\n");

	close(ptr_data->idf);
	free(ptr_data); 

	return NULL;
}

//*************************************************************************************************************************
//*************************************************************************************************************************
//************************************************************ Main *******************************************************
//*************************************************************************************************************************
//*************************************************************************************************************************

int main(G_GNUC_UNUSED int nump, G_GNUC_UNUSED char *param[])
{
	int s;

	lista_user_mp_en_ram = (REG_USER_MP*)malloc(sizeof(REG_USER_MP)*MAX_USER_MP);

	if (!lista_user_mp_en_ram)
	{
		printf("No se pudo crear la lista de user mp, fallo de malloc\n");
		exit(-1);
	}

	memset(lista_user_mp_en_ram,0,sizeof(REG_USER_MP)*MAX_USER_MP);	

	//Carga de los user registrados
	FILE *fichero = fopen("data_mp.dat", "rb");
	if (fichero) 				
	{
		size_t i, contador;
		size_t tt = sizeof(REGBD_USER_MP); 
		REGBD_USER_MP *reg_carga = (REGBD_USER_MP*)malloc(tt*PAGINA);

		fseek(fichero, 0L, SEEK_SET);
		while( (contador=fread(reg_carga, tt, PAGINA, fichero)) )
		{
			for (i=0;i<contador;i++)
			{
				if ((reg_carga+i)->id)
				{
					memcpy( &(lista_user_mp_en_ram + (reg_carga+i)->id)->reg_user, (reg_carga+i), tt);
					printf("user:[%s] [id:%u] [online:%d] [reputacion:%d]\n", 
						(lista_user_mp_en_ram + (reg_carga+i)->id)->reg_user.nombre, 
						(lista_user_mp_en_ram + (reg_carga+i)->id)->reg_user.id,
						(lista_user_mp_en_ram + (reg_carga+i)->id)->online,
						(lista_user_mp_en_ram + (reg_carga+i)->id)->reg_user.reputacion);
				}
			}
		}

		if (reg_carga)
		{
			free(reg_carga);
		}

		fclose(fichero);
	}

	pthread_mutex_init(&mutex_lista_user_mp_en_ram, NULL);
	pthread_mutex_init(&mutex_lista_user_mp_activos, NULL);
	pthread_mutex_init(&mutex_bd, NULL);

	int fd, fd2; /* los ficheros descriptores */
	struct sockaddr_in server; /* para la información de la dirección del servidor */
	struct sockaddr_in client; 	/* para la información de la dirección del cliente */
	unsigned int sin_size;

	/* A continuación la llamada a socket() */
	if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) 
	{  
		printf("error en socket()\n");
		exit(-1);
	}

	server.sin_family = AF_INET;         
	server.sin_port = htons(PORT); /* ¿Recuerdas a htons() de la sección "Conversiones"? =) */
	server.sin_addr.s_addr = INADDR_ANY;  /* INADDR_ANY coloca nuestra dirección IP automáticamente */

	memset(&(server.sin_zero),0,sizeof(unsigned char)*8);
	/* escribimos ceros en el reto de la estructura */

	/* A continuación la llamada a bind() */
	if(bind(fd,(struct sockaddr*)&server, sizeof(struct sockaddr))==-1) 
	{
		printf("error en bind() \n");
		exit(-1);
	}     

	if(listen(fd,BACKLOG) == -1) /* llamada a listen() */
	{  
		printf("error en listen()\n");
		exit(-1);
	}

	printf("Servidor Mango Productos iniciado en [%d]\n", PORT);

	sin_size = sizeof(struct sockaddr_in);

	while(servidor_vivo) 
	{
		/* A continuación la llamada a accept() */
		if ((fd2 = accept(fd,(struct sockaddr *)&client,  &sin_size))==-1)
		{
			printf("error en accept()\n");
			continue;
		}
		printf("Se obtuvo una conexión desde %s\n", inet_ntoa(client.sin_addr)); /* que mostrará la IP del cliente */

		DATA_HILO *ptr_data = (DATA_HILO*) malloc(sizeof(DATA_HILO));
		if (ptr_data)
		{
			ptr_data->idf 		= fd2;
			ptr_data->ip.s_addr	= client.sin_addr.s_addr;

			pthread_t hilo_hijo; 
			s = pthread_create(&hilo_hijo, NULL, manejo_conexion, (void*)ptr_data);
			if (s != 0)
			{
				printf("Error al crear el hilo [%d]\n",s);
			}
			
			s = pthread_join(hilo_hijo, NULL);
			if (s != 0)
			{
				printf("Error al join en el hilo [%d]\n",s);
			}

	//		printf("Volver al inicio del hilo main\n");

		} else {

			printf("No se puede crear el hilo porque no hay memoria disponible para malloc\n");
		}
	}

	if (lista_user_mp_en_ram)
	{
		free(lista_user_mp_en_ram);
	}


	exit(0);
}

