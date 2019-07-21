Mango Productos

Mango Bienes y Servicios, es un prototipo de programa de intercambio de información sobre ofertas y
demandas de bienes y servicios entre usuarios directamente por medio de una red p2p.
En principio esta pensado para equipos sobre mesa, pero luego en una segunda etapa se puede llegar a
celulares y tablets.
El uso del programa es para un publico muy amplio, no se limita a un sector determinado, podría ser
usado por instituciones publicas y privadas, empresas del estado y privadas, organizaciones y por
particulares, es crear una comunidad virtual.
Mientras mas personas puedan publicar sus productos, servicios o necesidades el sistema tendrá una
amplia gama de posibilidades de encontrar lo que se necesita, o en otro sentido, de encontrar quien
quiere el producto que estas ofertando.
El sistema publica por igual bienes, servicios y necesidades.

Como probar e Instalar

Ejecutar el archivo ./linux-compilar.sh para compilar en linux.
Para compilar necesita tener las librerías GTK3 para desarrolladores.
Para efectos de probar se debe caracterizar de forma manual las fuentes antes de compilar
¿Cómo se hace eso?
Abrimos el archivo macros.h
En las lineas 14, 15 y 16 modificamos lo siguiente
#define NOMBRE_EMPRESA "Mango-Electrodomesticos"
#define DIRECCION_EMPRESA "Parque Aragua"
#define TELEFONO_EMPRESA "0414-365.21.98, 0426-987.25.41"
NOMBRE_EMPRESA → se debe colocar entre comillas el nombre de la empresa o personas
DIRECCION_EMPRESA → se debe colocar entre comillas la dirección de la empresa imaginaria
TELEFONO_EMPRESA → se debe colocar entre comillas los teléfonos de la empresa imaginaria
El largo deberá limitarse a lo que dice las macros
#define MAXDIRECCION
#define MAXNOMBRE
#define MAXFABRICANTE
128
64
40#define MAXTELEFONO
64
Luego de modificado estos valores grabamos y cerramos el documento.
Ahora abrimos ini.c
En las lineas 33 y 34 modificamos lo siguiente
vg_registroUser->id = 1;
vg_registroUser->codEstado = 4;
vg_registroUser->codMunicipio = 1;
vg_registroUser->id contiene el valor id único en todo el sistema, para nuestro ejemplo es 1 (dejarlo
así)
vg_registroUser->codEstado aquí se puede colocar sólo (4=Aragua), (8=Cojedes), (14=Merida) los
demás no están implementados.
Acá se configura el estado donde se encuentra el registro del ofertante de productos
Luego de modificado estos valores grabamos y cerramos el documento.
Ahora abrimos variables.h
En la linea 38 modificamos lo siguiente
unsigned int vg_identificador
= 1;
Este valor debe ser igual al id de vg_registroUser→id, para este caso es 1
Luego de modificado el valor grabamos y cerramos el documento.
Ahora abrimos macros.h
En la linea 61 modificamos lo siguiente
#define STR_IP_SERVER "127.0.0.1"
ESTO ES MUY IMPORTANTE (COMO TODO LO DEMÁS TAMBIÉN), LA VARIABLE
STR_IP_SERVER TIENE LA IP DONDE ESTA UBICADO EL SERVIDOR CONTROL
Luego de todo esto se ha configurado el sistema procedemos a compilar
Ejecutar el archivo ./linux-compilar.sh para compilar en linux.Recuerden que por cada nodo que se quiera ejecutar para probar la red p2p hay que hacer este
procedimiento, es importante recordar que se debe ir aumento el id de uno en uno, es decir
primero id es 1, luego es 2, así sucesivamente.
Es importante copiar la información de quien es cada ID porque luego la vamos a necesitar
cuando instalemos el servidor control.
Ejemplo hay que recordar que el ID=1 pertenece a Mango-Electrodomesticos, que es codEstado 4
y Municipio 1
y que la segunda compilación es ID=2 pertenece a Campo-Salle, que es codEstado 8 y Municipio
2
Por ejemplo:
Ahora vamos a configurar el servidor
Para compilar solamente ejecutar make
para arrancar ejecutar ./server-mp
desde otro terminal abrir un telnet en el puerto 3550
procedemos a registrar cada clientes
por ejemplo para registrar el ID=1 (los Ids son generados automaticamente cada
vez que se registra un cliente)
130 crear user Mango-Electrodomesticos 4 1 15500
el ultimo parámetro se supone que es el puerto de escucha del cliente, es obvio que un sistema
terminado este paso es automático entre los programas, por ahora tenemos que hacerlo nosotros.
Luego tecleamos 100 y otra vez 100 para salir
Asi lo hacemos sucesivamente por cada cliente.
Se debe tener cuidado en los pasos, porque sino esta bien configurado el sistema no
funcionara.

Para mayor informacion abrir el documento AboutMe.pdf


