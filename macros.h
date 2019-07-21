#ifndef MACROS_H
#define MACROS_H

/*

Variables a modificar

vg_identificador
vg_registroUser->id 

//*/


#define NOMBRE_EMPRESA "Mango-Electrodomesticos"
#define DIRECCION_EMPRESA "Parque Aragua"
#define TELEFONO_EMPRESA "0414-365.21.98, 0426-987.25.41"

#define MAX_CAMPOS_PRODUCTO 64

#define ARCHIVO_IDPRODUCTO_DAT "bd/IdProducto.dat"
#define BD_PRODUCTOS_DAT "bd/bdProductos.dat"

#define ARCHIVO_IDNECESIDAD_DAT "bd/IdNecesidad.dat"
#define BD_NECESIDAD_DAT "bd/bdNecesidad.dat"



#define RUTA_IMAGEN_SUBIR "img/subirArchivos.png"

#define TITULO_APLICACION	"Mango Productos"

#define W_GET_OBJECT(builder, name)						GTK_WIDGET(gtk_builder_get_object(builder, #name))
#define APPDATA_GET_OBJECT(builder, name, type, data)	data->name = type(gtk_builder_get_object(builder, #name))
#define APPDATA_GET_WIDGET(builder, name, data)			APPDATA_GET_OBJECT(builder, name, GTK_WIDGET, data)
#define GW(name) 										APPDATA_GET_WIDGET(builder, name, AppData)
#define GWG(name) 										APPDATA_GET_WIDGET(builder, name, WidgetGlobales)

#define GWP(name) 										APPDATA_GET_WIDGET(builder, name, ProductoData)
#define GWE(name) 										APPDATA_GET_WIDGET(builder, name, EncontradoData)
#define GWN(name) 										APPDATA_GET_WIDGET(builder, name, NecesidadData)
#define GWS(name) 										APPDATA_GET_WIDGET(builder, name, SelectSector)
#define GWVF(name) 										APPDATA_GET_WIDGET(builder, name, visorData)


//#define GW_TORNEO(name)									APPDATA_GET_WIDGET(builder, name, TorneoData)

#ifdef __LINUX__ //Linux y Mac
#define	LARGO_STR_RUTAS					PATH_MAX
#else
#define	LARGO_STR_RUTAS					MAX_PATH
#endif

#define MAXDIRECCION 	128
#define MAXNOMBRE 		64
#define MAXFABRICANTE	40
#define MAXTELEFONO		64

#define MAXDATASIZE 	128
#define MAX_CRITERIO	64
#define PORT 			3550
#define STR_IP_SERVER 	"127.0.0.1"

#define MIN_PORT		10000
#define MAX_PORT		60000
#define ES_VALIDO_PUERTO(p) ((p>=MIN_PORT && p<=MAX_PORT))

#define BACKLOG			10


#define PQ_ALIMENTOS 				0
#define PQ_AGRICOLA 				1
#define PQ_COSME_ASEO_LIMPIEZA 		2
#define PQ_FARMACEUTICOS 			3
#define PQ_PETROQUIMICA_PLASTICOS 	4
#define PQ_PINTURAS 				5

#define PM_USO_PERSONAL				6
#define PM_USO_HOGAR 				7
#define PM_USO_INDUSTRIAL			8
#define PM_AUTOMOTRIZ 				9

#define PSP_AGRICOLA 				10
#define PSP_PECUARIO 				11
#define PSP_AVICOLA 				12
#define PSP_PORCINO 				13
#define PSP_PISCICOLA 				14
#define PSP_APICOLA 				15


#endif
