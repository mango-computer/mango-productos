
/*
export PATH=$PATH:PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin


DOS & Windows: \r\n 0D0A (hex), 13,10 (decimal)
Unix & Mac OS X: \n, 0A, 10
Macintosh (OS 9): \r, 0D, 13

https://linux.die.net/man/3/mcrypt

http://watch5s.co/movie/snowden/?watching
http://hdmovieslab.net/snowden-2016-full-hd-movie-free-download-720p-bluray/

broadwayd :5

Then point your web browser at http://127.0.0.1:8085. Start your applications like this:

GDK_BACKEND=broadway BROADWAY_DISPLAY=:5 gtk3-demo
//*/

//#include <mcrypt.h>

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <unistd.h>
//#include <glib.h>
#include <ctype.h>
//#include <time.h>
#include <errno.h>
//#include <math.h>
#include <sys/types.h>
//#include <dirent.h>
//#include <libgen.h>


//#include <ifaddrs.h>
#include <netinet/in.h> 
//#define h_addr h_addr_list[0] // Compatibilidad hacia atras 
#include <arpa/inet.h>
#include<sys/socket.h>
#include<netdb.h>



//************************************************************
//************************************************************

#if defined (_WIN32) || defined(_WIN64)
//Windows
#else
#define __LINUX__ 			//** Activo: Linux Des-Activo: Windows
#endif

//************************************************************
//************************************************************

#define SO_LINUX									0 
#define SO_WIN 										1
#define SO_MAC   									2

#ifdef __LINUX__ //Linux
#define SISTEMA_OPERATIVO							SO_LINUX // Para cada sistema cambiar esta variable
#else
#define SISTEMA_OPERATIVO							SO_WIN // Para cada sistema cambiar esta variable
#endif

#ifdef __LINUX__ //Linux
#include <linux/limits.h>
#else
#include <windows.h>
#include <tchar.h>
#include <shellapi.h>
#include <direct.h>
//#include <Processthreadsapi.h> //Versiones de Windows 8 y Server 2012 para usar CreateProcess
#endif

#include "macros.h"
#include "enums.h"
#include "tipoDatos.h"
#include "data.h"

#include "prototipos.h"
#include "variables.h"


#include "ini.c"
#include "util.c"
#include "mi_css.c"
#include "appWindow.c"
#include "mensajesGui.c"
#include "aboutWindow.c"
#include "menubar.c"
#include "tbutton.c"

#include "toolbar_seguimiento.c"
#include "toolbar_encontrados.c"
#include "toolbar_mis_productos.c"
#include "toolbar_proveedores.c"

#include "treeview_seguimiento.c"
#include "treeview_encontrados.c"
#include "treeview_mis_productos.c"
#include "treeview_proveedores.c"
#include "barraNotificacion.c"
#include "util_red.c"
#include "manejo_ip_local.c"
#include "servidorLocal.c"
#include "productoWindow.c"
#include "selectWindow.c"
#include "operacionesBit.c"
#include "visorFotoWindow.c"
#include "necesidadWindow.c"
#include "busqueda.c"
#include "encontradosWindow.c"

//*************************************************************************************************************************************

int main(int argc, char **argv)
{

	GtkBuilder 		*builder;
	GError 			*error		= NULL;

	//Inicio del motor grafico
	gtk_init(&argc, &argv);

	//***********************
	ini_variables_globales();
	//***********************

	builder = gtk_builder_new();

	if( !gtk_builder_add_from_file(builder,"AppWindowProductos.ui", &error))
	{
		if (error)
		{
			g_warning("%s", error->message);
			perror("ERROR:main::->PANTALLA_PRINCIPAL_UI");
			g_error_free(error);
			error = NULL;

		} else {

			printf("ERROR:main::->PANTALLA_PRINCIPAL_UI -[No documentado error==NULL]\n");
		}

		mostrarMensaje("Error","Qué vergonzoso, no he podido dibujar la ventana de principal","");
		exit(1);
	}

	APPWINDOW_DATA *AppData		= g_slice_new(APPWINDOW_DATA);
	WidgetGlobales				= g_slice_new(WIDGET_GLOBALES);


	// Crear todas las referencias a todos los objetos visuales de la interface
	GW(scrolledwindow_treeview_seguimiento);
	GW(scrolledwindow_treeview_encontrados);
	GW(scrolledwindow_treeview_mis_productos);
	GW(scrolledwindow_treeview_proveedores);
	GW(toolbar_seguimiento);
	GW(toolbar_encontrados);
	GW(toolbar_mis_productos);
	GW(toolbar_proveedores);
	GW(togglebutton_seguimientos);
	GW(togglebutton_encontrados);
	GW(togglebutton_mis_productos);
	GW(togglebutton_proveedores);


	// Crear todas las referencias a todos los objetos visuales de la interface Globales
	GWG(AppWindowProductos);
	GWG(treeview_seguimiento);
	GWG(treeview_encontrados);
	GWG(treeview_mis_productos);
	GWG(treeview_proveedores);
	GWG(imagen_notificacion_conexion);
	GWG(imagen_notificacion_servidor_local);
	GWG(label_notificacion_reputacion);

	/* Connect signals */
	gtk_builder_connect_signals(builder, AppData);

	/* Destroy builder, since we don't need it anymore */
	g_object_unref(G_OBJECT(builder));


	// ** Treeview Seguimiento **
//*
	GtkTreeModel *items_model_seguimiento = create_items_model_seguimiento();
	gtk_tree_view_set_model(GTK_TREE_VIEW(WidgetGlobales->treeview_seguimiento), items_model_seguimiento);
	add_columns_seguimiento(GTK_TREE_VIEW(WidgetGlobales->treeview_seguimiento));
	g_object_unref(items_model_seguimiento);
//*/
	// ** Treeview Encontrados **
	GtkTreeModel *items_model_encontrados = create_items_model_encontrados();
	gtk_tree_view_set_model(GTK_TREE_VIEW(WidgetGlobales->treeview_encontrados), items_model_encontrados);
	add_columns_encontrados(GTK_TREE_VIEW(WidgetGlobales->treeview_encontrados));
	g_object_unref(items_model_encontrados);

	// ** Treeview Mis Productos **
	GtkTreeModel *items_model_mis_productos = create_items_model_mis_productos();
	gtk_tree_view_set_model(GTK_TREE_VIEW(WidgetGlobales->treeview_mis_productos), items_model_mis_productos);
	add_columns_mis_productos(GTK_TREE_VIEW(WidgetGlobales->treeview_mis_productos));
	g_object_unref(items_model_mis_productos);

	// ** Treeview Proveedores **
	GtkTreeModel *items_model_proveedores = create_items_model_proveedores();
	gtk_tree_view_set_model(GTK_TREE_VIEW(WidgetGlobales->treeview_proveedores), items_model_proveedores);
	add_columns_proveedores(GTK_TREE_VIEW(WidgetGlobales->treeview_proveedores));
	g_object_unref(items_model_proveedores);

	//*** CSS
	provider = GTK_STYLE_PROVIDER (gtk_css_provider_new ());
	gtk_css_provider_load_from_data(GTK_CSS_PROVIDER (provider), css_main, strlen(css_main)*sizeof(char), NULL);
	apply_css(GTK_WIDGET(WidgetGlobales->AppWindowProductos), provider);

	gtk_window_resize(GTK_WINDOW(WidgetGlobales->AppWindowProductos), (ancho_pantalla*2)/3, (alto_pantalla*2)/3);
	gtk_widget_show(WidgetGlobales->AppWindowProductos);	


	int s;
//*
	//Lanzar ciclo de Servidor Local
	pthread_t hilo_server_local; 
	s = pthread_create(&hilo_server_local, NULL, thread_func_bucle_server_local, NULL); 
	if (s != 0)
	{
		printf("****** Error al crear el hilo hilo_server_local\n");
		exit(-1);
	}

//*/
//*
	//Lanzar ciclo de verificaciones del IP
	pthread_t hilo_check_ip; 
	s = pthread_create(&hilo_check_ip, NULL, thread_func_bucle_check_ip, NULL); 
	if (s != 0)
	{
		printf("****** Error al crear el hilo hilo_check_ip\n");
		exit(-1);
	}
//*/

	gdk_threads_add_timeout( ESPERA_TIMER_ACTUALIZAR_NOTIFICACION, cb_timeout_update_barra_notificacion, (gpointer)WidgetGlobales );

	//Llenado de Treeview
	recargarTreeview_mis_productos();
	recargarTreeview_seguimiento();

	/* Start main loop */
	gtk_main();

	g_slice_free(APPWINDOW_DATA, AppData);
	AppData = NULL;

	g_slice_free(WIDGET_GLOBALES, WidgetGlobales);
	WidgetGlobales = NULL;

	//Liberar GSList
	g_slist_free_full(lista_necesidad, (GDestroyNotify)liberarMemoria_lista_necesidad);
	lista_necesidad = NULL;

	g_slist_free_full(lista_productos, (GDestroyNotify)liberarMemoria_lista_productos);
	lista_productos = NULL;

	if (pixBusqueda)
	{
		g_object_unref(pixBusqueda);
	}

	for (int i=0;i<64;i++)
	{
		if (gslista_encontrados[i])
		{
			printf("LIBERAR MEMORIA gslista_encontrados[%d]\n", i);
			//Primera linea

			g_slist_free_full(gslista_encontrados[i], (GDestroyNotify)liberarMemoria_busqueda_local);
			gslista_encontrados[i] = NULL;
		}
	}	


	exit(0);

}




