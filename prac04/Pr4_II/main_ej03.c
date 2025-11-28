# include "pool.h"


void main() {

    Pool_Init();

}


void StartCtrl() {

    // Cambio de parpadeo  del LED verde a 1Hz 
    // Cambio de parpadeo  del LED rojo a 10Hz 
    Pool_EscribirFrecRojo(10);
    Pool_EscribirFrecVerde(1);
    osDelay(8000);

    // Cambio de parpadeo  del LED verde a 10Hz 
    // Cambio de parpadeo  del LED rojo a 1Hz 
    Pool_EscribirFrecRojo(1);
    Pool_EscribirFrecVerde(10);
    osDelay(8000);
}

void StartGreen() {
    // Ajustar parpadeo cada 10 segundos
    int freq = Pool_LeerFrecVerde();
    Blocking_Freq(PIN_GREEN, 10000, freq);
}

void StartRed() {
    // Ajustar parpadeo cada 6 segundos
    int freq = Pool_LeerFrecRojo();
    Blocking_Freq(PIN_RED, 6000, freq);
    
}
