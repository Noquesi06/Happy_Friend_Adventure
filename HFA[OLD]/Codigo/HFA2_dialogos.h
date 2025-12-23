#ifndef DIALOGOS_H
#define DIALOGOS_H

void introduccion(char *ptr_nombre, bool *ptr_warrior, bool *ptr_wizard);
void dialogosDelGatito(void);
void saltoLinea(void);
void saltoLineaWin(WINDOW *ventana);
void comerciante_1(char *ptr_nombre, int *ptr_money);
void dialogosComerciante(int a);
void escena(int i);
void dialogo_ataque_recibido(int indice_jefe, int ataque_recibido, int indice_Verossa);
void evaluacionAtaqueG(int ataque, int curacion);
void dialogos_defensa(int indice_jefe, int ataque_reducido, int indice_Verossa);
void dialogos_evasion(int indice_jefe, int ataque_evadido, int indice_Verossa);
void jefeHabilidad(int i, int verossa_lvl);
#endif
