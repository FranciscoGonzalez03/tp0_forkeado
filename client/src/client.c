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
	log_info(logger,"Hola! Soy un log");
	//log_destroy(logger);
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
	
	valor = config_get_string_value(config, "VALOR");
	log_info(logger,valor);
	ip = config_get_string_value(config, "IP");
	log_info(logger,ip);
	puerto = config_get_string_value(config, "PUERTO");
	log_info(logger,puerto);
	
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */
	leer_consola(logger);
	//log_destroy(logger);
	//config_destroy(config);
	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor

	log_info(logger,"Antes de crear conexion");
	conexion = crear_conexion(ip, puerto);
	log_info(logger,"Cree la conexion en la linea anterior");

	//Pruebo hacer un handshake
	testeo_handshake(conexion); //toDO
	log_info(logger,"Handshake");

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion);
	log_info(logger,"Envie mensaje");	
	// Armamos y enviamos el paquete
	paquete(conexion);
	log_info(logger,"Paquete cargado Paquete");	
	log_info(logger,"Envie Paquete");	
	log_destroy(logger);
	config_destroy(config);
	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	nuevo_logger = log_create("src/tp0.log","LOG_INICIAL",true,LOG_LEVEL_INFO);
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	nuevo_config = config_create("tp0.config");
	if (nuevo_config == NULL) {
    // ¡No se pudo crear el config!
    // Terminemos el programa
	printf("No se pudo configurar");
	exit(1);
	}
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	 while (leido != NULL && leido[0] != '\0') {
        // Loguear la línea
        log_info(logger, "Entrada recibida: %s", leido);

        // Liberar la memoria asignada por readline
        free(leido);

        // Leer la siguiente línea
        leido = readline("> ");
    }
	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete
	
	leido = readline("> ");
	 while (leido != NULL && leido[0] != '\0') {
        // Mostrar leido y agregar a paquete
        printf("Contenido leido: %s\n", leido);
		agregar_a_paquete(paquete, leido, strlen(leido)+1);

        // Liberar la memoria asignada por readline
        free(leido);

        // Leer la siguiente línea
        leido = readline("> ");
    }
	free(leido);
	enviar_paquete(paquete, conexion);
	printf("Paquete enviado\n");
	eliminar_paquete(paquete);
	printf("Paquete eliminado\n");
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
