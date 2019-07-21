
/*
	propiedad de Jose Andres Morales Linares

*/
#ifndef DATA_H
#define DATA_H


char *estadosVenezuela[] = {
							"Todos",
							"Amazonas",
							"Anzoategui",
							"Apure",
							"Aragua",
							"Barinas",
							"Bolívar",
							"Carabobo",
							"Cojedes",
							"Delta Amacuro",
							"Distrito Capital",
							"Falcón",
							"Guárico",
							"Lara",
							"Mérida",
							"Miranda",
							"Monagas",
							"Nueva Esparta",
							"Portuguesa",
							"Sucre",
							"Táchira",
							"Trujillo",
							"Vargas",
							"Yaracuy",
							"Zulia", NULL};

char *municipios_aragua[] = {
								"Todos",
								"Bolívar (San Mateo)",
								"Camatagua(Camatagua)",
								"Francisco Linares Alcántara (Santa Rita)",
								"Girardot (Maracay)",
								"José Ángel Lamas (Santa Cruz)",
								"José Félix Ribas (La Victoria)",
								"José Rafael Revenga (El Consejo)",
								"Libertador (Palo Negro)",
								"Mario Briceño Iragorry (El Limón)",
								"Ocumare de la Costa de Oro (Ocumare de la Costa)",
								"San Casimiro (San Casimiro)",
								"San Sebastián (San Sebastián de los Reyes)",
								"Santiago Mariño (Turmero)",
								"Santos Michelena (Las Tejerías)",
								"Sucre (Cagua)",
								"Tovar (Colonia Tovar)",
								"Urdaneta (Barbacoas)",
								"Zamora (Villa de Cura)",
								NULL};

char *municipios_cojedes[] = {
								"Todos",
								"Anzoátegui (Cojedes)",
								"Ezequiel Zamora (San Carlos)",
								"Falcón (Tinaquillo)",
								"Girardot (El Baúl)",
								"Lima Blanco (Macapo)",
								"Pao de San Juan Bautista (El Pao)",
								"Ricaurte (Libertad)",
								"Rómulo Gallegos",
								"Tinaco (Tinaco)",
								"Tinaquillo (Tinaquillo)",
								NULL};

char *municipios_merida[] = {
								"Todos",
								"Alberto Adriani (El Vigía)",
								"Andrés Bello (La Azulita)",
								"Antonio Pinto Salinas (Santa Cruz de Mora)",
								"Sucre (Lagunillas)",
								"Tovar (Tovar)",
								"Tulio Febres Cordero (Nueva Bolivia)",
								"Zea (Zea)",
								NULL};

char *str_sector[] = {
					"[PQ-Alimentos]",
					"[PQ-Agricola]",
					"[PQ-Cosmeticos, Aseo, Limpieza]",
					"[PQ-Farmaceuticos]",
					"[PQ-Petroquimica y Plasticos]",
					"[PQ-Pinturas]",
					"[PM-Personal->(Aseo, Limpieza, Cosmeticos, Ropa, Calzado, etc.)]",
					"[PM-Hogar->(Electronicos, Electricos, Mecanicos, Quimicos, Limpieza, etc.)]",
					"[PM-Industrial->(Electronicos, Electricos, Mecanicos, Quimicos, Limpieza, etc.)]",
					"[PM-Automotriz->(Electronicos, Electricos, Mecanicos, Quimicos, Limpieza, etc.)]",
					"[PSP-Agricola]",
					"[PSP-Pecuario]",
					"[PSP-Avicola]",
					"[PSP-Porcino]",
					"[PSP-Piscicola]",
					"[PSP-Apicola]",
					NULL
						};

char *str_unidades[] = {
					"Sin Especificar",
					"Unidad",
					"Docena",
					"Centena",
					"Millar",
					"Gramo",
					"Kilo",
					"Saco de 20 Kilos",
					"Saco de 25 Kilos",
					"Saco de 42.5 Kilos",
					"Saco de 50 Kilos",
					"Quintal",
					"Tonelada",
					"Centimetro Cubico",
					"Cuarto de Galón",
					"Medio Galón",
					"Galón",
					"Cuñete",
					"Litro",
					"Bidon de 20 Litros",
					"Bidon de 25 Litros",
					"Bidon de 65 Litros",
					"Tambor de 200 Litros",
					"Varitanque de 1000 Litros",
					"Metro",
					"Kilometro",
					"Metro Cuadrado",
					"Hectarea",
					"Guacal",
					"Mano",
					"Cesta",
					"Paquete",
					"Caja",
					"Paleta",
					"Contenedor",
					"Camión 350",
					"Camión 750",
					"Gandola",
					"Hora",
					"Dia",
					"Mes",
					"Año",
					NULL};

char *str_presentacion[] = {
					"Sin Especificar",
					"Por unidad",
					"Por docena",
					"Por centena",
					"Por millar",
					"Por gramo",
					"Por kilo",
					"Por saco de 20 Kilos",
					"Por saco de 25 Kilos",
					"Por saco de 42.5 Kilos",
					"Por saco de 50 Kilos",
					"Por quintal",
					"Por tonelada",
					"Por centimetro Cubico",
					"Por cuarto de Galón",
					"Por medio Galón",
					"Por galón",
					"Por cuñete",
					"Por litro",
					"Por bidon de 20 Litros",
					"Por bidon de 25 Litros",
					"Por bidon de 65 Litros",
					"Por tambor de 200 Litros",
					"Por varitanque de 1000 Litros",
					"Por metro",
					"Por kilometro",
					"Por metro Cuadrado",
					"Por hectarea",
					"Por guacal",
					"Por mano",
					"Por cesta",
					"Por paquete",
					"Por caja",
					"Por paleta",
					"Por contenedor",
					"Por camión 350",
					"Por camión 750",
					"Por gandola",
					"Por hora",
					"Por dia",
					"Por mes",
					"Por año",
					NULL};

char *titulo_label_foto[] = {"Foto 1","Foto 2","Foto 3","Foto 4"};

  uint64 BITSET[64] = {
0x1ull, 0x2ull, 0x4ull, 0x8ull, 0x10ull, 0x20ull, 0x40ull, 0x80ull, 0x100ull, 0x200ull, 0x400ull, 0x800ull, 0x1000ull,
0x2000ull, 0x4000ull, 0x8000ull, 0x10000ull, 0x20000ull, 0x40000ull, 0x80000ull, 0x100000ull, 0x200000ull, 0x400000ull, 
0x800000ull, 0x1000000ull, 0x2000000ull, 0x4000000ull, 0x8000000ull, 0x10000000ull, 0x20000000ull, 0x40000000ull, 
0x80000000ull, 0x100000000ull, 0x200000000ull, 0x400000000ull, 0x800000000ull, 0x1000000000ull, 0x2000000000ull, 
0x4000000000ull, 0x8000000000ull, 0x10000000000ull, 0x20000000000ull, 0x40000000000ull, 0x80000000000ull, 0x100000000000ull,
0x200000000000ull, 0x400000000000ull, 0x800000000000ull, 0x1000000000000ull, 0x2000000000000ull, 0x4000000000000ull,
0x8000000000000ull, 0x10000000000000ull, 0x20000000000000ull, 0x40000000000000ull, 0x80000000000000ull, 0x100000000000000ull,
0x200000000000000ull, 0x400000000000000ull, 0x800000000000000ull, 0x1000000000000000ull, 0x2000000000000000ull, 0x4000000000000000ull,
0x8000000000000000ull};

 uint64 debruijn64  	= 0x07EDD5E59A4E28C2ull;

  int    TABLA_MSB1[256] = { 
0x0, 0x0, 0x1, 0x1, 0x2, 0x2, 0x2, 0x2, 0x3, 0x3,
0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x4, 0x4, 0x4,
0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4,
0x4, 0x4, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5,
0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5,
0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5,
0x5, 0x5, 0x5, 0x5, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6,
0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6,
0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6,
0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6,
0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6,
0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6,
0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x7, 0x7,
0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
0x7, 0x7, 0x7, 0x7, 0x7, 0x7};

//*Css
#ifdef __LINUX__ //Linux

const char *css_main =
"window {"\
"    background: #BDBDBD;"
"}"\
" "\
"menubar {"\
"    background: #BDBDBD;"
"}"\
" "\
"toolbar {"\
"    background: #BDBDBD;"
"    border-style: hidden;"\
"}"\
" "\
"separatortoolitem {"\
"    background: #474747;"
"}"\
" "\
"button {"\
"    color: black;"\
"    background-color: #BDBDBD;"\
"    border-style: solid;"\
"}"\
"button:hover {"\
"    background-color: white;"\
"}"\
" "\
"button:hover:active,"\
"button:active {"\
"    background-color: white;"\
"}";

#else

const char *css_main =
"GtkWindow {"\
"    background: #BDBDBD;"
"}"\
" "\
"GtkMenuBar {"\
"    background: #BDBDBD;"
"}"\
" "\
"GtkToolbar {"\
"    background: #BDBDBD;"
"    border-style: hidden;"\
"}"\
" "\
"GtkSeparatorToolItem {"\
"    background: #474747;"
"}"\
" "\
".button {"\
"    color: black;"\
"    background-color: #BDBDBD;"\
"    border-style: solid;"\
"}"\
".button:hover {"\
"    background-color: white;"\
"}"\
" "\
".button:hover:active,"\
".button:active {"\
"    background-color: white;"\
"}";

#endif

#endif
