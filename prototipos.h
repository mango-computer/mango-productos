#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

//encontradosWindows.c
void abrir_encontradoProducto(int numAuto);

//necesidadWindow.c
void abrirNecesidadWindow(unsigned int idNecesidad);
G_MODULE_EXPORT void NecesidadWindow_button_aceptar_clicked(GtkButton *widget, NECESIDAD_WINDOWS *data);
G_MODULE_EXPORT void NecesidadWindow_button_cerrar_clicked(GtkButton *widget, NECESIDAD_WINDOWS *data);
G_MODULE_EXPORT void NecesidadWindow_destroy(G_GNUC_UNUSED GtkWidget *widget, NECESIDAD_WINDOWS *data);
G_MODULE_EXPORT void NecesidadWindow_entry_precio_insert_text_cb(G_GNUC_UNUSED GtkEditable *editable, G_GNUC_UNUSED gchar *new_text, G_GNUC_UNUSED gint new_text_length,
		G_GNUC_UNUSED gpointer position, G_GNUC_UNUSED NECESIDAD_WINDOWS *user_data);

//visorFotoWindow.c
void abrirVisor(char *rutaFoto, GtkWidget *ventana);

//operacionesBit.c
void imprimirBitTablero(uint64 numero);
void imprimirBits(uint64 numero);
static inline int bitScanForwardBruijn(uint64 bb); 
static inline int convertir2lista(uint64 bb, uint8 *lista);
static inline uint32 cuentaBit(uint64 bitmap);
static inline uint32 bitScanLast(uint64 bitmap);


//selectWindow.c
void abrirSelectWindow(GtkWidget *text);
G_MODULE_EXPORT gboolean SectorWindows_key_press_event(G_GNUC_UNUSED GtkWidget *widget, GdkEvent *event, SELECT_SECTOR_WINDOWS *data);
G_MODULE_EXPORT void SectorWindows_destroy(G_GNUC_UNUSED GtkWidget *widget, SELECT_SECTOR_WINDOWS *data);
G_MODULE_EXPORT void SectorWindows_boton_aceptar_clicked_cb(GtkButton *widget, SELECT_SECTOR_WINDOWS *data);
G_MODULE_EXPORT void SectorWindows_check_productos_quimicos_alimentos_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data);
G_MODULE_EXPORT void SectorWindows_check_productos_quimicos_agricola_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data);
G_MODULE_EXPORT void SectorWindows_check_productos_quimicos_cosmeticos_aseo_limpieza_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data);
G_MODULE_EXPORT void SectorWindows_check_productos_quimicos_farmaceuticos_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data);
G_MODULE_EXPORT void SectorWindows_check_productos_quimicos_pp_plasticos_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data);
G_MODULE_EXPORT void SectorWindows_check_productos_quimicos_pinturas_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data);
G_MODULE_EXPORT void SectorWindows_check_productos_manufacturados_Automotriz_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data);
G_MODULE_EXPORT void SectorWindows_check_productos_manufacturados_uso_hogar_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data);
G_MODULE_EXPORT void SectorWindows_check_productos_manufacturados_uso_industrial_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data);
G_MODULE_EXPORT void SectorWindows_check_productos_manufacturados_uso_personal_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data);
G_MODULE_EXPORT void SectorWindows_check_productos_sector_primario_agricola_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data);
G_MODULE_EXPORT void SectorWindows_check_productos_sector_primario_pecuario_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data);
G_MODULE_EXPORT void SectorWindows_check_productos_sector_primario_avicola_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data);
G_MODULE_EXPORT void SectorWindows_check_productos_sector_primario_porcino_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data);
G_MODULE_EXPORT void SectorWindows_check_productos_sector_primario_piscicola_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data);
G_MODULE_EXPORT void SectorWindows_check_productos_sector_primario_apicola_toggled_cb(GtkToggleButton *togglebutton, SELECT_SECTOR_WINDOWS  *data);

//productoWindow.c
void abrirProductosWindows(unsigned int idProducto);
G_MODULE_EXPORT void ProductoWindow_drag_data_received(
			G_GNUC_UNUSED GtkWidget 			*widget,
            GdkDragContext   					*context,
            G_GNUC_UNUSED gint              	x,
            G_GNUC_UNUSED gint              	y,
            GtkSelectionData 					*data,
            G_GNUC_UNUSED guint             	info,
            guint             					time,
            PRODUCTOS_WINDOWS      				*datax);

void subirFoto(char *filename, PRODUCTOS_WINDOWS *data);
G_MODULE_EXPORT gboolean ProductoWindow_eventbox_imagen_subir_archivo_button_press_event_cb(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED GdkEvent *event, 
	 PRODUCTOS_WINDOWS *data);
G_MODULE_EXPORT void ProductoWindow_boton_subir_archivo_open_clicked_cb(GtkButton *widget, PRODUCTOS_WINDOWS *data);

//util.c
char* str2Mayusculas(char* s);
void liberarMemoria_busqueda_local(gpointer data);
void liberarMemoria_lista_ips(gpointer data);
void liberarMemoria_lista_necesidad(gpointer data);
void liberarMemoria_lista_productos(gpointer data);
void llenarComboMunicipios(int codEstado, int codMunicipio, NECESIDAD_WINDOWS *data);
char *getStrMinicipio(int codEstado, int codMunicipio);
void remplazar_caracter(char *cadena, char c, char nc);
unsigned int getSiguenteIdProductoLibre();
void grabarRegistroProducto(REGBD_PRODUCTO *registro);
void grabarIdProductoLibre(unsigned int id);
void cargarRegistroNecesidad(unsigned int idNecesidad, REGBD_NECESIDAD *registro);
void grabarRegistroNecesidad(REGBD_NECESIDAD *registro);
void grabarIdNecesidadLibre(unsigned int id);
unsigned int getSiguenteIdNecesidadLibre();


//servidorLocal.c
void* thread_func_servidor_local( void *data);
void* thread_func_bucle_server_local( void *data);
void* manejo_conexion_server_local(void *data);

//manejo_ip_local.c
void* thread_func_bucle_check_ip( void *data);
void* thread_func_check_ip_local( void *data);

//util_red.c
int getIPBD(unsigned int id, unsigned int idNecesidad, REGBD_NECESIDAD_IP *p2p_ip);
int abrir_conexion_p2p(IP ip, unsigned int puerto);
char* getIpLocal();
int servidor_abrir_conexion();
int servidor_send(int descriptor, char* msm, char *respuesta);
int enviarPingServidorLocal();

//barraNotificacion.c
static gboolean cb_timeout_update_barra_notificacion( gpointer data_out );

//busqueda.c
void* thread_func_bucle_busqueda(void *data);
GSList *buscarIps(REGBD_NECESIDAD *registro, GSList *listaIps);
GSList* procesar_peticion_busqueda_local(REGBD_NECESIDAD *registro, GSList *lista_busqueda_local);

//appWindow.c
G_MODULE_EXPORT void salir(GtkWidget *widget, APPWINDOW_DATA *data);
G_MODULE_EXPORT gboolean AppWindow_key_press_event(GtkWidget *widget, GdkEvent *event, APPWINDOW_DATA *data);

//treeview_seguimiento.c
static void recargarTreeview_seguimiento();
G_MODULE_EXPORT gboolean treeview_seguimiento_button_release_event_cb
			(G_GNUC_UNUSED GtkWidget* widget,  GdkEvent *evento, G_GNUC_UNUSED APPWINDOW_DATA *data);
static GtkTreeModel* create_items_model_seguimiento();
static void add_columns_seguimiento(GtkTreeView *treeview);
static void recargarTreeview_seguimiento();

//treeview_encontrados.c
static void recargarTreeview_encontrados();
static GtkTreeModel* create_items_model_encontrados();
static void add_columns_encontrados(GtkTreeView *treeview);

//treeview_mis_productos.c
static GtkTreeModel* create_items_model_mis_productos();
static void add_columns_mis_productos(GtkTreeView *treeview);
static void recargarTreeview_mis_productos();

//treeview_proveedores.c
static GtkTreeModel* create_items_model_proveedores();
static void add_columns_proveedores(GtkTreeView *treeview);

//aboutWindow.c
void mostrarAboutWindow();

//menubar.c
//Menu Seguimientos
G_MODULE_EXPORT void item_about_activate_cb(GtkImageMenuItem *item, APPWINDOW_DATA *data);
G_MODULE_EXPORT void item_seguimiento_nuevo_activate_cb(GtkImageMenuItem *item, APPWINDOW_DATA *data);
G_MODULE_EXPORT void item_seguimiento_editar_activate_cb(GtkImageMenuItem *item,APPWINDOW_DATA *data);
G_MODULE_EXPORT void item_seguimiento_eliminar_activate_cb(GtkImageMenuItem *item, APPWINDOW_DATA *data);
//Menu Encontrados
G_MODULE_EXPORT void item_encontrados_ver_activate_cb(GtkImageMenuItem *item, APPWINDOW_DATA *data);
G_MODULE_EXPORT void item_encontrados_grabar_activate_cb(GtkImageMenuItem *item, APPWINDOW_DATA *data);
G_MODULE_EXPORT void item_encontrados_bloquear_resultado_activate_cb(GtkImageMenuItem *item, APPWINDOW_DATA *data);
//Menu Proveedores
G_MODULE_EXPORT void item_mis_productos_nuevo_activate_cb(GtkImageMenuItem *item, APPWINDOW_DATA *data);
G_MODULE_EXPORT void item_mis_productos_editar_activate_cb(GtkImageMenuItem *item, APPWINDOW_DATA *data);
G_MODULE_EXPORT void item_mis_productos_eliminar_activate_cb(GtkImageMenuItem *item, APPWINDOW_DATA *data);
//Menu Mantenimiento
G_MODULE_EXPORT void item_mantenimiento_perfil_activate_cb(GtkImageMenuItem *item, APPWINDOW_DATA *data);
G_MODULE_EXPORT void item_mantenimiento_red_activate_cb(GtkImageMenuItem *item, APPWINDOW_DATA *data);
//Menu Ayuda
G_MODULE_EXPORT void item_ayuda_activate_cb(GtkImageMenuItem *item,APPWINDOW_DATA *data);

//toolbar_seguimiento.c
G_MODULE_EXPORT void toolBoton_seguimiento_buscar_clicked_cb(GtkButton *widget, APPWINDOW_DATA *data);
G_MODULE_EXPORT void toolBoton_seguimiento_nuevo_clicked_cb(GtkWidget *button, APPWINDOW_DATA *data);
G_MODULE_EXPORT void toolBoton_seguimiento_editar_clicked_cb(GtkWidget *button, APPWINDOW_DATA *data);
G_MODULE_EXPORT void toolBoton_seguimiento_eliminar_clicked_cb(GtkWidget *button, APPWINDOW_DATA *data);

//toolbar_encontrados.c
G_MODULE_EXPORT void toolBoton_encontrados_ver_clicked_cb(GtkWidget *button, APPWINDOW_DATA *data);
G_MODULE_EXPORT void toolBoton_encontrados_grabar_clicked_cb(GtkWidget *button, APPWINDOW_DATA *data);
G_MODULE_EXPORT void toolBoton_encontrados_bloquear_clicked_cb(GtkWidget *button, APPWINDOW_DATA *data);
G_MODULE_EXPORT void toolBoton_encontrados_chat_clicked_cb(GtkWidget *button, APPWINDOW_DATA *data);

//toolbar_mis_productos.c
G_MODULE_EXPORT void toolBoton_mis_productos_nuevo_clicked_cb(GtkWidget *button, APPWINDOW_DATA *data);
G_MODULE_EXPORT void toolBoton_mis_productos_editar_clicked_cb(GtkWidget *button, APPWINDOW_DATA *data);
G_MODULE_EXPORT void toolBoton_mis_productos_eliminar_clicked_cb(GtkWidget *button, APPWINDOW_DATA *data);
G_MODULE_EXPORT void toolBoton_mis_productos_chat_clicked_cb(GtkWidget *button, APPWINDOW_DATA *data);

//toolbar_proveedores.c
G_MODULE_EXPORT void toolBoton_proveedores_ver_clicked_cb(GtkWidget *button, APPWINDOW_DATA *data);
G_MODULE_EXPORT void toolBoton_proveedores_buscar_clicked_cb(GtkWidget *button, APPWINDOW_DATA *data);
G_MODULE_EXPORT void toolBoton_proveedores_calificar_clicked_cb(GtkWidget *button, APPWINDOW_DATA *data);
G_MODULE_EXPORT void toolBoton_proveedores_eliminar_clicked_cb(GtkWidget *button, APPWINDOW_DATA *data);

//ini.c
void ini_variables_globales();

//mensajesGui.c
void mostrarMensaje(const char *msmTitulo, const char *msm, const char *entrada_user);

//aboutWindow.c
void mostrarAboutWindow();

#endif
