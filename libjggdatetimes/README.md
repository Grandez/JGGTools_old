# Fechas y horas

La libreria estandar de C++ no aporta clases para el manejo de fechas y horas, si no que hereda la estructuras de C: `struct tm`, `time_t`etc.

Esta libreria pretende solventar este problema encapsulando las fechas y horas en clases que sean seguras y manejables pero manteniendo la compatibilidad con `struct tm`.

## Tipos de datos

De manera general podemos distinguir los siguientes tipos de datos:

- Date: Cuando solo nos interesa manejar una fecha independientemente de la hora
- Time: Cuando nos interesa manejar una hora independientemente de la fecha concreta
- DateTime: Cuando nos interesa tanto la fecha y la hora. Este tipo suele estar habitualmente a bases de datos
-Timestamp: Tipo de datos habitual en base de datos que, ademas de la fecha y la hora incluye una mayor precision, desde milisegundos hasta microsegundos, dependiendo del motor de la base de datos

### Date

El primer problema que nos encontramos al ennfretarnos a tipos de dato fecha es el formato de los mismos, ya que varia en función de los paises y la cultura, encontrandonos con los siguientes formatos:

- dd/mm/yy Usado en Europa normalmente
- mm/dd/yy Usado en los paises anglosajones
- yy/mm/dd Usado en paises orientales

Normalmente, los lenguajes de programacion requieren que se les indique el formato en el que esta especificada la fecha, lo cual puede ser propoenso a errores.

En esta libreria por defecto se usa el sistema de puntuación (locale) activo en el la maquina donde se ejecuta.

Por otro lado, las operaciones sobre fechas, segun idiomas o funciones no suelen ser fiables por que no se realiza un adecuado control de los limites de dias y meses (No voy a indicar ejemplos), o no realizan un control adecuado; supongamos por ejemplo, una funcion `dateadd` que suma meses:

1. Creamos un objeto Date como "31/03/20" (Ultima dia del mes de marzo)
2. Sumamos un mes. En función de la implementación nos podemos encontrar con que el resultado es:
   - 31/03/20 (Se ha ido un mes mas por que ha sumado 31 dias)
   - 30/04/20 (Aparentemente correcto, ha contemplado el mes natural y ha ajustado el dia)
3. Sumamos otro mes. Ahora el resultado puede ser:
   - 30/05/20 Lo cual puede ser erroneo si la intencion era mantener el hecho de que era el ultimo dia del mes
   
### Time

Esta clase no plantea demasiados problemas, el formato general siempre es hh:mm:ss y los limites estan bien establecidos, asi que se puede operar sobre el objeto sin ambiguedades

### DateTime

Esta clase se establece de manera general con el siguiente formato: `yyyy/mm/dd hh:mm:ss`.
Con lo que no hay ambigüedad en el tratamiento de la fecha salvo el caso ya mencionado de los ultimos dias de cada mes

### Timestamp

Esta clase, muy vinculada a bases de datos, se almacena internamente en una dato de 8 bytes pero se maneja como una cadena con el siguiente formato: `yyyy-mm-dd-hh:mm:ss.nnnnnn`
En muchos sistemas, ademas, se garantiza, dada la precision, que nunca se generarán dos timestamps iguales


## Clases

El objetivo de estas clases es manejar estos diferentes tipos de datos de manera coherente, garantizando, aparte de las operaciones típicas, las siguientes situaciones:

1. Garantizando que un Timestamp siempre sea único
2. Control del ultimo día de mes en las operaciones sobre fechas

Al respecto del ultimo punto permitiendo la siguiente secuencia de operaciones, asumiendo que tenemos una funcion `monthAdd(int cant, bool last)`

2000/01/31 + 1m -> 2000/02/29 + 1m -> 2000/03/31 + 1m -> 2000/04/30 + 1m -> 2000/04/31


