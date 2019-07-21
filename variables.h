
#ifndef VARIABLES_H
#define VARIABLES_H


GSList *gslista_encontrados[64];

int codBusqueda = 666;

REGBD_USER *vg_registroUser;
G_LOCK_DEFINE( vg_llave_registroUser );

unsigned int vg_llave_busqueda_stop=9999; //Esto se puede sustituir con aun arreglo y una clave hash para cada id, mas eficiente
G_LOCK_DEFINE( vg_llave_busqueda_stop );


GdkPixbuf *pixBusqueda;

GSList *lista_necesidad;
GSList *lista_productos;

uint64 flagGlobal_temporal;

//pthread_t hilo_hijo_check_ip; 
int ON_BUCLE_CHECK_IP 		= VERDADERO;
int ON_BUCLE_SERVER_LOCAL	= VERDADERO;

long ESPERA_HILO_CHECK_IP 		= 5000000L; //Micro Segundos 1 segundo-> 1  == 1000000
long ESPERA_HILO_SERVER_LOCAL 	= 5000000L;
long ESPERA_TIMER_ACTUALIZAR_NOTIFICACION = 5000; //En segundos, en milisegudos 1 segundo -> 1==1000   

IP vg_iplocal;
G_LOCK_DEFINE( vg_iplocal );

PUERTO vg_puerto_escucha 		= 0;
G_LOCK_DEFINE( vg_puerto_escucha );

unsigned int vg_identificador	= 1;

int vg_reputacion				= 0;
//G_LOCK_DEFINE( vg_reputacion );

int vg_index_seguimiento		= 0;

int vg_saludo_servidor_on		= FALSO;
G_LOCK_DEFINE( vg_saludo_servidor_on );

int vg_servidorLocal_vivo		= FALSO;
G_LOCK_DEFINE( vg_servidorLocal_vivo );

int ancho_pantalla;
int	alto_pantalla;

GtkStyleProvider *provider;

//GdkPixbuf *pixBanderas;

//*********************************Objetos Globales***********************************************************

WIDGET_GLOBALES		*WidgetGlobales;
FECHA				fechaSistema;


#endif
