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
	//logger = log_create("tp0.log", "login", 1, LOG_LEVEL_INFO);
	log_info (logger, "Soy un Log");

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
    config = config_create("cliente.config");
		
	valor = config_get_string_value(config,"CLAVE");
	ip = config_get_string_value(config,"IP");
    puerto = config_get_string_value(config,"PUERTO");
	log_info(logger, valor);
	log_info(logger, ip );
	log_info(logger, puerto);
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
     
	// Loggeamos el valor de config

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	
	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);
    
	enviar_mensaje(valor,conexion);
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
	if((nuevo_logger = log_create("tp0.log", "login", 1, LOG_LEVEL_INFO)) == NULL)
	{
		printf("No se puede crear el logger\n");
		exit(1);
	}

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	if((nuevo_config = config_create("./cliente.config")) == NULL)
	{
		printf ("No se puede leer el config\n"); 
		exit(2);
	}
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido; 
	while (1)
    {
        leido = readline("> ");

        if (leido[0] == '\0') 
        {
            break;
        }

        if (logger != NULL)
        {
            log_info(logger, "%s", leido);
        }
        free(leido);
    }
	// La primera te la dejo de yapa
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	// ¡No te olvides de liberar las lineas antes de regresar!
	/* leido = readline(">");

    // Leer y loguear líneas hasta recibir una cadena vacía
    while (leido != NULL && *leido != "") {
        // Loguear la línea si es necesario
        if (logger != NULL) {
            log_info(logger, leido);
        }
        // Liberar la memoria asignada por readline()
        free(leido);
        // Leer la siguiente línea
        leido = readline(">");
    }
    // Liberar la última línea antes de salir
    free(leido);
	*/
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido = NULL;
	t_paquete* paquete;
    paquete = crear_paquete();

    while (1) {
        leido = readline("> ");
        if (!leido) {
            break; 
        }
        if (!strncmp(leido, "", 4)) {
            free(leido);
            break;
        }
        agregar_a_paquete(paquete, leido, strlen(leido)+1);
        free(leido);
    }
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
