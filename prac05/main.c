#include "mailbox.h"

// Definición global del handle del Mailbox
Mailbox_t *TemperatureMailboxHandle;
Mailbox_t *HumidityMailboxHandle;

UART_HandleTypeDef huart2;

void println(const char *msg) {
	HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
}


void main(void)
{
    // ... Código de configuración del sistema ...

    // 1. Inicializar y obtener el puntero al Mailbox
    TemperatureMailboxHandle = Mailbox_Init();
	HumidityMailboxHandle = Mailbox_Init();
	if (TemperatureMailboxHandle == NULL || HumidityMailboxHandle == NULL) {
        // ("ERROR: Fallo al inicializar uno de los Mailboxes.\n");
        return;
    }

	// 2. Crear Tarea Remitente (T_Adquisicion, Alta Prioridad)
	// El handle (puntero) del Mailbox se pasa en el argumento 'argument'.
	osThreadNew(T_Adquisicion, 
				TemperatureMailboxHandle, // <-- Pasa el HANDLE aquí
				NULL); // Parámetros de configuración del thread (prioridad, stack, etc. si no son NULL)

	// 3. Crear Tarea Receptora (T_Monitoreo, Baja Prioridad)
	// El handle también se pasa en el argumento 'argument'.
	osThreadNew(T_Monitoreo, 
				TemperatureMailboxHandle, // <-- Pasa el mismo HANDLE aquí
				NULL); 
    

    // ... Código para osKernelStart() ...

}

void StartRed(void const * argument) {
{
	int freq=99;
	char msg[50];
	for(;;)
	{
		sprintf(msg, "Rojo: %d", freq); println(msg);
		osDelay(6000);
	}
}

// Ejemplo de cómo T_Monitoreo recibiría y usaría el handle:
void T_Monitoreo(void *argument)
{
    Mailbox_t *my_mailbox = (Mailbox_t *)argument; // Castea el argumento a nuestro tipo
    int received_data;
	
	char msg[50];
	for(;;)
    {
        received_data = Mailbox_Pend(my_mailbox); 
        sprintf(msg, "Temperatura: %d.%d", 
               received_data / 10, received_data % 10); println(msg);
               
        // No se necesita osDelay() ya que Mailbox_Pend() es bloqueante..
    }
}

void T_Monitoreo_Humedad(void *argument)
{
    Mailbox_t *my_mailbox = (Mailbox_t *)argument; 
    int received_data;

	char msg[50];
	for(;;)
    {
        received_data = Mailbox_Pend(my_mailbox); 
        sprintf(msg, "Humedad: %d.%d", 
               received_data / 10, received_data % 10); println(msg);
               
        // No se necesita osDelay() ya que Mailbox_Pend() es bloqueante.
    }
}

/* ******************** */

void T_Adquisicion(void *argument)
{
    // 1. Recibe y castea el argumento al tipo de puntero de Mailbox
    Mailbox_t *my_mailbox = (Mailbox_t *)argument; 
    int temp_sensor = 250; // Dato a enviar
    
	for(;;)
    {
        // ... Simulación de lectura del sensor ...
        temp_sensor += 1; 

        // 2. Usa el handle para llamar a la función de acceso específica
        Mailbox_Post(my_mailbox, temp_sensor); 

        // 3. Espera el siguiente ciclo de muestreo
        osDelay(5000); 
    }
}

void T_Adquisicion_Humedad(void *argument)
{
    // Castea el argumento para obtener el handle del Mailbox de Humedad
    Mailbox_t *my_mailbox = (Mailbox_t *)argument; 
    int current_humidity = 500; // Humedad inicial (50.0%)

	for(;;)
    {
        // 1. Simular lectura del sensor de humedad (el dato cambia)
        current_humidity += 10;
        if (current_humidity > 900) 
        {
            current_humidity = 400;
        }

        // 2. Enviar el dato de humedad al Mailbox específico
        Mailbox_Post(my_mailbox, current_humidity); 
        
        // 3. Espera el siguiente ciclo de muestreo
        osDelay(8000); 
    }
}