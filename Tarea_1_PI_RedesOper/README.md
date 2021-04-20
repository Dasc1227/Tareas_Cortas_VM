# Tarea Corta 1: Mini servidor web con sockets

Este programa corresponde a un miniservidor web programado en C utilizando sockets. El programa esta hecho de dos archivos: El Cliente y el servidor. El proposito del programa es que el lado del servidor copie y guarde en un directorio archivos enviados por el lado del cliente. 

Para correr el programa se abren dos consolas y se corren los siguientes comandos:

-en una consola se corre el servidor como parametro el puerto a usar, por defecto se usa el puerto 8080.

gcc server.c -o server 

./server 8080

y se corre en la otra consola el clienteL

gcc client.c -o client

./client 8080 test.txt

