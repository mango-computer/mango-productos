

#ifndef TIPODATOS_H
#define TIPODATOS_H
//***************************************************** Ini calculo pareo *********************************************************
#ifdef _MSC_VER
  typedef unsigned __int64 		uint64;
#else
  typedef unsigned long long int 	uint64;
#endif

//************************* user ********************

/*
struct tm
{
        int     tm_sec;          Seconds: 0-59 (K&R says 0-61?) 
        int     tm_min;          Minutes: 0-59 
        int     tm_hour;         Hours since midnight: 0-23 
        int     tm_mday;         Day of the month: 1-31 
        int     tm_mon;          Months *since* january: 0-11 
        int     tm_year;         Years since 1900 
        int     tm_wday;         Days since Sunday (0-6) 
        int     tm_yday;         Days since Jan. 1: 0-365 
        int     tm_isdst;        +1 Daylight Savings Time, 0 No DST,
                                 -1 don't know 
};
//*/

typedef unsigned int 	uint32;
typedef unsigned char 	uint8;

typedef unsigned short int PUERTO;
typedef struct in_addr IP;

//Data BD
typedef struct {

	unsigned int id;
	IP ip;
	unsigned short int puerto;

} REGBD_NECESIDAD_IP;


//Data BD
typedef struct {

	unsigned int id;
	int codEstado;
	int codMunicipio;
	int	reputacion;
	char nombre[MAXNOMBRE];
	char direccion[MAXDIRECCION];
	char telefono[MAXTELEFONO];

} REGBD_USER;

typedef struct {

	unsigned int idProducto;
	int activo;
	uint64 flag_categoria;
	char nombre[MAX_CAMPOS_PRODUCTO];
	char descripcion[MAX_CAMPOS_PRODUCTO];
	unsigned long int precio;
	int disponibilidad;
	int codUnidad;
	int codPresentacion;
	char fabricante[MAXFABRICANTE];
	int nuevo;
	int fabricacion;
	int transporte; 
	int flag_fotos;
	char descripcionFoto1[MAX_CAMPOS_PRODUCTO];
	char descripcionFoto2[MAX_CAMPOS_PRODUCTO];
	char descripcionFoto3[MAX_CAMPOS_PRODUCTO];
	char descripcionFoto4[MAX_CAMPOS_PRODUCTO];

} REGBD_PRODUCTO;

typedef struct {

	unsigned int idNecesidad;
	int activo;
	uint64 flag_categoria;
	char nombre[MAX_CAMPOS_PRODUCTO];
	char descripcion[MAX_CAMPOS_PRODUCTO];
	unsigned long int precio; // maximo 4294.967.295 Bs
	int disponibilidad;
	int codUnidad;
	int codPresentacion;
	char fabricante[MAXFABRICANTE];
	int nuevo;
	int fabricacion;
	int transporte; 
	int codEstado;
	int codMunicipio;
	int busqueda;	

} REGBD_NECESIDAD;

typedef struct {

	unsigned int idNecesidad;
	unsigned int idProductoProveedor;
	unsigned int idProveedor;
	int activo;
	uint64 flag_categoria;
	char nombre[MAX_CAMPOS_PRODUCTO];
	char descripcion[MAX_CAMPOS_PRODUCTO];
	unsigned long int precio; // maximo 4294.967.295 Bs
	int disponibilidad;
	int codUnidad;
	int codPresentacion;
	char fabricante[MAXFABRICANTE];
	int nuevo;
	int fabricacion;
	int transporte; 
	int codEstado;
	int codMunicipio;
	char nombre_empresa[MAXNOMBRE];
	char direccion_empresa[MAXDIRECCION];
	char telefono[MAXTELEFONO];
	int flag_fotos;
	char descripcionFoto1[MAX_CAMPOS_PRODUCTO];
	char descripcionFoto2[MAX_CAMPOS_PRODUCTO];
	char descripcionFoto3[MAX_CAMPOS_PRODUCTO];
	char descripcionFoto4[MAX_CAMPOS_PRODUCTO];

} REGBD_ENCONTRADO;

//Reg en Ram para acceso directo

typedef struct {

	unsigned int id;
	PUERTO puerto_escucha;
	IP ip;

} INDEX_BUSQUEDA;


//Columnas treeview torneo

typedef struct
{
	unsigned int anio;
	unsigned int mes;
	unsigned int dia;

} FECHA;

typedef struct
{
	FECHA fecha;
	int hora;
	int minuto;

} MOMENTO;

typedef struct
{
	GtkWidget 	*scrolledwindow_treeview_seguimiento;
	GtkWidget 	*scrolledwindow_treeview_encontrados;
	GtkWidget 	*scrolledwindow_treeview_mis_productos;
	GtkWidget 	*scrolledwindow_treeview_proveedores;
	GtkWidget 	*toolbar_seguimiento;
	GtkWidget 	*toolbar_encontrados;
	GtkWidget 	*toolbar_mis_productos;
	GtkWidget 	*toolbar_proveedores;

	GtkWidget 	*togglebutton_seguimientos;
	GtkWidget 	*togglebutton_encontrados;
	GtkWidget 	*togglebutton_mis_productos;
	GtkWidget 	*togglebutton_proveedores;

} APPWINDOW_DATA;

typedef struct
{
	GtkWidget 	*AppWindowProductos;
	GtkWidget 	*treeview_seguimiento;
	GtkWidget 	*treeview_encontrados;
	GtkWidget 	*treeview_mis_productos;
	GtkWidget 	*treeview_proveedores;
	GtkWidget 	*imagen_notificacion_conexion;
	GtkWidget 	*imagen_notificacion_servidor_local;
	GtkWidget 	*label_notificacion_reputacion;

} WIDGET_GLOBALES;

typedef struct
{
	GtkWidget *ProductoWindow;

	GtkWidget *ProductoWindow_entry_nombres;
	GtkWidget *ProductoWindow_entry_descripcion;
	GtkWidget *ProductoWindow_entry_precio;
	GtkWidget *ProductoWindow_entry_fabricante;
	GtkWidget *ProductoWindow_spin_stock;
	GtkWidget *ProductoWindow_comboboxtext_unidad;
	GtkWidget *ProductoWindow_comboboxtext_presentacion;
	GtkWidget *ProductoWindow_check_fabricacion_propia;
	GtkWidget *ProductoWindow_check_nuevo;
	GtkWidget *ProductoWindow_check_transporte;

	GtkWidget *ProductoWindow_imagen_subir_archivo_label;
	GtkWidget *ProductoWindow_imagen_subir_archivo;
	GtkWidget *ProductoWindow_imagen1;
	GtkWidget *ProductoWindow_imagen2;
	GtkWidget *ProductoWindow_imagen3;
	GtkWidget *ProductoWindow_imagen4;

	GtkWidget *ProductoWindow_entry_imagen1;
	GtkWidget *ProductoWindow_entry_imagen2;
	GtkWidget *ProductoWindow_entry_imagen3;
	GtkWidget *ProductoWindow_entry_imagen4;

	GtkWidget *ProductoWindow_boton_select_sector_entry;

	char foto1[LARGO_STR_RUTAS];
	int foto1_on;

	char foto2[LARGO_STR_RUTAS];
	int foto2_on;

	char foto3[LARGO_STR_RUTAS];
	int foto3_on;

	char foto4[LARGO_STR_RUTAS];
	int foto4_on;

	int fotoSeleccionada;

	unsigned int idProducto;

} PRODUCTOS_WINDOWS;


typedef struct
{
	GtkWidget *EncontradosWindows;

	GtkWidget *EncontradosWindows_entry_nombres;
	GtkWidget *EncontradosWindows_entry_descripcion;
	GtkWidget *EncontradosWindows_entry_precio;
	GtkWidget *EncontradosWindows_entry_fabricante;
	GtkWidget *EncontradosWindows_spin_stock;
	GtkWidget *EncontradosWindows_comboboxtext_unidad;
	GtkWidget *EncontradosWindows_comboboxtext_presentacion;
	GtkWidget *EncontradosWindows_check_fabricacion_propia;
	GtkWidget *EncontradosWindows_check_nuevo;
	GtkWidget *EncontradosWindows_check_transporte;

	GtkWidget *EncontradosWindows_imagen1;
	GtkWidget *EncontradosWindows_imagen2;
	GtkWidget *EncontradosWindows_imagen3;
	GtkWidget *EncontradosWindows_imagen4;

	GtkWidget *EncontradosWindows_entry_imagen1;
	GtkWidget *EncontradosWindows_entry_imagen2;
	GtkWidget *EncontradosWindows_entry_imagen3;
	GtkWidget *EncontradosWindows_entry_imagen4;

	GtkWidget *EncontradosWindows_boton_select_sector_entry;

} ENCONTRADOS_WINDOWS;


typedef struct
{
	GtkWidget *NecesidadWindow;

	GtkWidget *NecesidadWindow_entry_nombres;
	GtkWidget *NecesidadWindow_entry_descripcion;
	GtkWidget *NecesidadWindow_entry_precio;
	GtkWidget *NecesidadWindow_entry_fabricante;
	GtkWidget *NecesidadWindow_spin_stock;
	GtkWidget *NecesidadWindow_comboboxtext_unidad;
	GtkWidget *NecesidadWindow_comboboxtext_presentacion;
	GtkWidget *NecesidadWindow_check_fabricacion_propia;
	GtkWidget *NecesidadWindow_check_nuevo;
	GtkWidget *NecesidadWindow_check_transporte;
	GtkWidget *NecesidadWindow_combobox_estado;
	GtkWidget *NecesidadWindow_combobox_municipio;

	GtkWidget *NecesidadWindow_boton_select_sector_entry;
	unsigned int idNecesidad;

} NECESIDAD_WINDOWS;

typedef struct
{
	GtkWidget *visorFotoWindows;
	GtkWidget *visorFotoWindows_foto;
	GtkWidget *visorFotoWindows_foto_viewport_scroll;

} VISOR_FOTO_WINDOWS;

typedef struct
{
	GtkWidget *SectorWindows;
	//Check
	GtkWidget *SectorWindows_check_productos_quimicos_alimentos;
	GtkWidget *SectorWindows_check_productos_quimicos_agricola;
	GtkWidget *SectorWindows_check_productos_quimicos_cosmeticos_aseo_limpieza;
	GtkWidget *SectorWindows_check_productos_quimicos_farmaceuticos;
	GtkWidget *SectorWindows_check_productos_quimicos_pp_plasticos;
	GtkWidget *SectorWindows_check_productos_quimicos_pinturas;
	GtkWidget *SectorWindows_check_productos_manufacturados_Automotriz;
	GtkWidget *SectorWindows_check_productos_manufacturados_uso_hogar;
	GtkWidget *SectorWindows_check_productos_manufacturados_uso_industrial;
	GtkWidget *SectorWindows_check_productos_manufacturados_uso_personal;
	GtkWidget *SectorWindows_check_productos_sector_primario_agricola;
	GtkWidget *SectorWindows_check_productos_sector_primario_pecuario;
	GtkWidget *SectorWindows_check_productos_sector_primario_avicola;
	GtkWidget *SectorWindows_check_productos_sector_primario_porcino;
	GtkWidget *SectorWindows_check_productos_sector_primario_piscicola;
	GtkWidget *SectorWindows_check_productos_sector_primario_apicola;

	uint64 flag_sector;

	GtkWidget *entrySector;

} SELECT_SECTOR_WINDOWS;



#endif
