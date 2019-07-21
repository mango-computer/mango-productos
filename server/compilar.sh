#gcc 'pkg-config --cflags --libs glib-2.0' -o servermp servidor_mp.c

gcc -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -lglib-2.0 -o servermp servidor_mp.c -lpthread
