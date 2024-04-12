#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	logger = log_create("tp0.log", "login", 1, LOG_LEVEL_INFO);
	log_info (logger, "Soy un Log");
	log_destroy (logger);

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
    
	config = config_create("cliente.config");
	valor = config_get_string_value(config,"CLAVE");
	ip = config_get_string_value(config,"IP");
    puerto =config_get_string_value(config,"PUERTO");
	log_info(logger, "CLAVE: %s", puerto);
	log_info(logger,"IP: %s ", ip);
	log_info(logger, "PUERTO: %s ", puerto);
	//config_destroy(config);
	//log_destroy(logger);

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
     
	// Loggeamos el valor de config

	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	
	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);
    
	enviar_mensaje("CLAVE",conexion);
	// Enviamos al servidor el valor de CLAVE como mensaje

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	// ¡No te olvides de liberar las lineas antes de regresar!
	 leido = readline(">");

    // Leer y loguear líneas hasta recibir una cadena vacía
    while (leido != NULL && *leido != '\0') {
        printf("%s\n", leido);
        // Loguear la línea si es necesario
        if (logger != NULL) {
            log_info(logger, "%s\n", leido);
        }
        // Liberar la memoria asignada por readline()
        free(leido);
        // Leer la siguiente línea
        leido = readline(">");
    }
    // Liberar la última línea antes de salir
    free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;
    paquete = crear_paquete();

leido = readline(">");
    // Leer y loguear líneas hasta recibir una cadena vacía
    while (leido != NULL && *leido != '\0') {
        printf("%s\n", leido);
        // Loguear la línea si es necesario
        if (paquete != NULL) {
            agregar_a_paquete(paquete,leido,strlen(leido)+1);
        }
        // Liberar la memoria asignada por readline()
        free(leido);
        // Leer la siguiente línea
        leido = readline(">");
    }
    // Liberar la última línea antes de salir
    free(leido);
	
	enviar_paquete(paquete,conexion);

    eliminar_paquete(paquete);
    // Leemos y esta vez agregamos las lineas al paquete
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	  log_destroy(logger);
	  config_destroy(config);
	  liberar_conexion(conexion);
}
