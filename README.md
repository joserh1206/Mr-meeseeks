# Mr. Meeseeks
Programa Box de Mr.Meeseeks el cual recibe del usuario una solicitud en forma de texto, por ejemplo "Quiero un café francés". O bien, podría solicitarse al Mr. Meeseeks realizar un cálculo en particular (una operación aritmética o lógica) o ejecutar un programa y esperar el resultado a positivo o no del mismo. 

El programa Box creará entonces (mediante un fork) un Mr. Meeseeks para atender dicha solicitud.

El programa Box podrá recibir múltiples solicitudes consecuentes, hasta que el usuario decida terminar el proceso despidiéndose. Al cerrar el programa Box el mismo deberá dar un breve informe de la cantidad de tareas solicitadas, el tiempo de duración de cada una, las tareas que se pudieron terminar y las que no, además para cada caso se deben indicar la cantidad de Mr. Meeseeks que se crearon para solucionar el problema.


Al iniciar, cada Mr. Meeseeks dará el mensaje de bienvenida: "Hi I'm Mr Meeseeks! Look at Meeeee. (pid, ppid, N, i)", donde pid y ppid serán los valores correspondientes al PID del Proceso Meeseeks creado y su PPID, N indicará el nivel e i indicará el número de instancia. Al iniciar, este valor N será de 1 al igual que la instancia en 1, pues es el primero en el primer nivel.

Los Meeseeks atienden solicitudes, las resuelven y desaparecen. Algunas solicitudes pueden ser fáciles y otras muy difíciles. 


A. 

Para las consultas textuales como "Quiero ser feliz!", se tratarán como una simulación de la realización de dicha tarea. Habrán dos posibles formas de determinar su dificultad: caso 1. consultar al usuario la dificultad de la solicitud, caso 2. dejarlo a la suerte del Mr. Meeseeks creado. En cualquier caso será con un valor de 0 a 100  el correspondiente a la probabilidad de dificultad, donde 100 es muy fácil (un solo Mr. Meeseeks lo solucionará) a 0 imposible (cientos o miles de Mr. Meeseeks no podrán con la tarea, podría generarse caos con los recursos del sistema hasta poder colapsar. En el caso 2, se debe estimar de forma aleatoria mediante una distribución de probabilidad para calcular el valor de dificultad de dicha solicitud. Para el caso de solicitudes imposibles, valoradas con 0, se debe establecer un plan de contingencia para evitar el colapso del sistema por la creación de miles de procesos. Debe documentar claramente las acciones que se tomarán en cada caso. 

Se debe considerar también el tiempo que durará la solicitud en ser completada (la simulación) por el Mr. Meeseeks, esto será mediante un cálculo de tiempo aleatorio de entre 0.5 a 5 segundos (para efectos de la simulación).

Luego del tiempo de espera el Mr. Meeseeks determinará si podrá satisfacer o no la solicitud. 

Para las tareas en un rango de 0 a 85, el Mr. Meeseeks evaluará la posibilidad de solicitar ayuda a otro Mr. Meeseeks para cumplir la solicitud. Para valores de 0 a 45 creará al menos 3 Mr. Meeseeks (acá N será N+1 con respecto a su padre, i tendrá valores 1, 2 y 3 para cada uno de los nuevos hijos), para valores de 45.01 a 85 creará al menos 1 Mr. Meeseeks nuevo  (acá N será N+1 con respecto a su padre, i permanece en 1). Se asume que de 85.01 a 100 la tarea la realizará 1 solo Mr. Meeseeks. 

Los Mr. Meeseeks nuevos vuelven a calcular la posibilidad de completar la tarea, tomando en cuenta que para tareas realizables (diferentes de 0) se debe ir disminuyendo y diluyendo la dificultad entre los distintos Mr. Meeseeks creados para que la tarea se vaya simplificando hasta que pueda ser ejecutada. Algo similar a la técnica de "añejamiento" vista en clase.

Como se indicó antes, al iniciar, cada Mr. Meeseeks dará el mensaje de bienvenida: "Hi I'm Mr Meeseeks! Look at Meeeee. (pid, ppid, N, i)".



B.

En el caso de los cálculos el programa recibe hileras de texto de operaciones aritméticas o lógicas y las procese y de el resultado o un error, se ejecuta un solo Mr. Meeseeks.



C.

Se debe considera el tiempo de ejecución del mismo y esperar el valor de retorno de dicho programa, algo que se acostumbra a hacer en programas en entonces Linux o UNIX que retornan valores como 0, 1 o incluso valores negativos o positivos mayores, para indicar que no hubo errores, que terminó con errores o bien con valores numéricos que indican tipos de errores. En ese caso solo se debe considerar si el programa terminó con éxito o no, para saber si el Mr. Meeseeks reportará la tarea como completada o no.



En General : 

Se hace uso de semáforos administrados por el sistema operativo para accesar los recursos compartidos, como el contador de niveles o instancias. Debe hacer uso de pipes para comunicar a los Mr. Meeseeks entre sí, cada Mr. Meeseeks deberá pasar por un mensaje privado vía pipe la solicitud hecha por el usuario. No se podrá usar una variable global para transmitir mensajes, pero sí una variable compartida global para el contador de Niveles e instancias (si lo requiere). Se recomienda el uso de la biblioteca pthreads para los semáforos y otros. 

Luego del tiempo tratando de resolver el problema, para las solicitudes con probabilidad de 85.01 a 100.0 el Mr. Meeseeks brindará un mensaje de respuesta al usuario indicando que la solicitud ha sido completada, agradece haberle servido y de despedirá del usuario con un mensaje final antes de desaparecer. Cuando un Mr. Meeseeks ha logrado resolver el problema, deberá comunicarlo vía pipes a su padre, éste lo comunicará a los hermanos del Mr. Meeseeks que solucionó el problema para que terminen, despidiéndose cada uno del usuario antes de desaparecer. El padre hará también lo mismo, comunicará a su padre la resolución del problema y se despedirá del usuario. Todos los procesos se irán despidiendo y desapareciendo recursivamente hacia atrás hasta llegar al padre original. Finalmente el Mr. Meeseeks original creado informará al usuario la resolución de la solicitud hecha y el Mr. Meeseeks que lo resolvió (con sus datos : pid, ppid, N, i).

Al terminar cada Mr. Meeseeks su trabajo asignado se devuelve el control al programa Box para esperar la siguiente solicitud.

Durante todo el proceso el programa deberá reportar mediante mensajes al usuario lo que ocurre. Para todos los mensajes que envíen los Mr. Meeseeks al usuario se deberá indicar siempre el pid y ppid del proceso. 
