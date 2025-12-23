#include <stdio.h>
#include <stdlib.h>
#include <ncursesw/ncurses.h>
#include <locale.h>
//#include <raylib.h>
#include <ncursesw/menu.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "HFA2_dialogos.h"
#include "HFA3_inventario.h"
#include "HFA5_art.h"
#define password1 "HOLA"
#define ruta "/home/noquesi/Desktop/Happy_Friend_Adventure/Saves/save.txt"
//Funcion global
bool ubermensch = false;
ITEM **opciones = NULL, **opciones_locales = NULL;
MENU *menu = NULL, *menu_local = NULL;
WINDOW *ventana = NULL, *ventana_local = NULL, *sub_ventana = NULL, *sub_ventana_local = NULL;

//Prototipos de las funciones a utilizar
void menuPrincipal();
void creadoraDeMenus(int n_options,
                    char **reference,
                    int length,
                    int width,
                    int axis_window_y,
                    int axis_window_x,
                    int largoV,
                    int anchoV,
                    int second_axis_window_y,
                    int second_axis_window_x,
                    bool menu_vertical,
                    bool tipo_menu,
                    int sub_indice
                    );
void nuevaPartida(void);
void continuarPartida(void);
void ajustes(void);
void prologo(void);
void salir(void);
void inicializarNcurses(void);
void flujo_Combate(bool *ptr_wizard, bool *ptr_warrior);
void liberarMemoria(int n_options, bool orden);
void comercianteConfig(int i, bool *ptr_wizard, bool *ptr_warrior, bool condicional);
void actualizarVentana(int index, int i, WINDOW *ventana_1, WINDOW *ventana_2, bool comerciante);
void incrementoStats(int index, int i, bool warrior, bool wizard, WINDOW *money);
void ventana_auxiliar_comerciante(int largo, int ancho, int eje_y, int eje_x, int s_largo, int s_ancho, int s_eje_y, int  s_eje_x, bool condicional, WINDOW **money);
void incrementoDinero(int i);
void extraccionVerossa(void);
void desactivadoMenuLimpieza(void);
void logica_combate(int i);
void ciclos_clases(int i, WINDOW *ventana_1);
void redibujadoPantalla(void);
int seleccionObjetivo(void);
void secuencia_Jefes(int i);
void logica_Guerrero(int i, WINDOW *ventana_1);
void desactivacionHabilidad(int i);
void configuracionGuerrero(int i, int target);
int calculoAtaqueGuerrero(void);
int calculoCuracionVampirismo(int ataque);
void aplicacionAtaque(int i, int target, int ataque);
void evaluacion_efectos(int i);
bool validacionJefes(int i);
void Bruto_config(int i);
void Gladio_config(int i);
void Verossa_config(int i);
void Parca_config(int i);
void Morte_config(void);
void DiosaEstelarIris(void);
void ataqueJefesBGVPMI(int nivel, int Verossa_lvl);
int defensaJugador(int ataque);
int evasionJugador(int ataque);
int seleccionJefe(int nivel, int Verossa_only);
char *nombreJefe(int nivel, int j);
void muerte(int i);
void exportacion(int i);
void guardarPartida(int i);
void enviado_a_archivo(int i);


//Nuestro main
int main(int argc, char *argv[]) {
srand(time(NULL)); //Para mis funciones que dependen de pseudoaleatoriedad
setlocale(LC_ALL, ""); //Para que el arte en braille se pueda apreciar
initscr(); //Se inicializa la biblioteca de ncurses
start_color(); //Se activa el color personalizado
init_pair(1, COLOR_RED, COLOR_BLACK); //Se definen colo de fondo (black) y un color rojo bajo subindice 1
       while (1) {
           menuPrincipal();
       }
}

//Aqui comienzan las funciones

void creadoraDeMenus(int n_options,
                    char **reference, //Donde se encuentran las opciones del menu
                    int length, //Largo de la ventana madre
                    int width, //Ancho de la ventana madre
                    int axis_window_y, //Ejes en y de la ventana madre
                    int axis_window_x, //Eje en x de la ventana madre
                    int largoV, //Largo de la sub-ventana
                    int anchoV, //Ancho de la sub-ventana
                    int second_axis_window_y, //Second axis_window (saxw) de la sub-ventana en y
                    int second_axis_window_x, //Eje en la sub-ventana x
                    bool menu_vertical,
                    bool tipo_menu,
                    int sub_indice) //Condicional para evaluar si el programa esta en la seccion del comerciante
    {
    if (tipo_menu == false) { //Indica la generacion de un menu estandar (1 columna con n filas)
        opciones = calloc(n_options + 1, sizeof(ITEM *)); //Se asigna memoria dinamica al menu
        for(int i=0;i<n_options;++i) {
            opciones[i] = new_item(reference[i], ""); //Se crean los items (opciones) del mismo
        }
        opciones[n_options] = (ITEM *)NULL; //La ultima opcion apunta a nulo
        //Se inicializa el menu y la posicion en la que estara
        menu = new_menu(opciones); //Se crea el menu con las opciones
        ventana = newwin(length, width, axis_window_y, axis_window_x); //Se crea una ventana global
        sub_ventana = derwin(ventana, largoV, anchoV, second_axis_window_y, second_axis_window_x); //Se crea una subventana global asociadaa la ventana principal
            keypad(ventana, TRUE); //Se activan las teclas especiales para la ventana
            set_menu_win(menu, ventana); //Se asocia el menu a la ventana global
            set_menu_sub(menu, sub_ventana); //La informacion del menu se mostrara en la subventana
            if (menu_vertical==true){
                set_menu_format(menu,1,4); //Para crear un menu horizontal
            }else{}
            set_menu_mark(menu, " > "); //Se imprime el digito para identificar la posicion actual del cursor
            post_menu(menu); //Se sube el menu
            refresh();
            wrefresh(ventana);
    }else{ //Indica que se tiene que trabajar con un menu local, similar al anterior pero este no vive mucho tiempo en la memoria
        opciones_locales = calloc(n_options + 1, sizeof(ITEM *));
        for (int i=0; i<n_options; i++) {
            opciones_locales[i] = new_item(reference[i], "");
        }
        opciones_locales[n_options] = (ITEM *)NULL;
        menu_local = new_menu(opciones_locales);
        ventana_local = newwin(length, width, axis_window_y, axis_window_x);
        keypad(ventana_local, TRUE);
            set_menu_win(menu_local, ventana_local);
            sub_ventana_local = derwin(ventana_local, largoV, anchoV, second_axis_window_y, second_axis_window_x);
            set_menu_sub(menu_local, sub_ventana_local);
            set_menu_mark(menu_local, ">");
            box(ventana_local, 0, 0);
        if (sub_indice == 0) { //Sub-indice para el comerciante
            mvwprintw(ventana_local, 1, 2, "%s", Texto[0].ventanaAuxiliar);
        }
        else if (sub_indice == 1) { //Sub-indice para los jefes
            mvwprintw(ventana_local, 1, 2, "%s", Texto[1].ventanaAuxiliar);
        }
        refresh();
        post_menu(menu_local);
        wrefresh(ventana_local);
    }
}

//Sirve para liberar la memoria de los menus
void liberarMemoria(int n_options, bool orden) {
    if (orden == false) { //Define si se tiene que liberar memoria local o global
        unpost_menu(menu); //Remueve el menu
        clear(); //Limpia la pantalla
            set_menu_win(menu, NULL);
            set_menu_sub(menu, NULL);
        delwin(sub_ventana);
        free_menu(menu); // libera memoria del menu
        for (int i=0;i<n_options;++i) { //Ciclo for que va liberando la memoria de cada uno de los items del menu
            free_item(opciones[i]);
        }
        free(opciones); //Se libera la memoria del arreglo de opciones
        delwin(ventana);
        opciones = NULL;
        menu = NULL;
        ventana = NULL;
        sub_ventana = NULL;
    }else {
        unpost_menu(menu_local);
            set_menu_win(menu_local, NULL);
            set_menu_sub(menu_local, NULL);
            delwin(sub_ventana_local);
        free_menu(menu_local); //Libera la memoria del menu
        for (int i=0;i<n_options;++i) { //Ciclo for que va liberando la memoria de cada uno de los items del menu
            free_item(opciones_locales[i]);
        }
        free(opciones_locales); //Se libera la memoria del arreglo de opciones
        werase(ventana_local);
        delwin(ventana_local);
        opciones_locales = NULL;
        menu_local = NULL;
        ventana_local = NULL;
        sub_ventana_local = NULL;
    }
}

//Funcion para evaluar la pantalla del usuario para que corresponda con las coordenadas esperadas
void ordenPantalla(void){
    gatoDelDestino();
    dialogosDelGatito();
}

//Funcion madre del codigo
void menuPrincipal(void) {
    menuArte();
    cbreak(); //Se desactiva la espera de enter para subir informacion a la terminal (util para usar las flechas)
    noecho(); //Se desactiva la vista de lo que el usuario escriba
    keypad(stdscr, TRUE); //Se activan teclas especiales del teclado
    creadoraDeMenus(5, elecciones, 6, 40, 16, 30, 6, 38, 0, 0, false, false, 29);
        //Se inicia la lectura de teclas
    int index, c;
        while(1) { //Ciclo infinito
            c = getch(); //Se declara la tecla c donde se guardara la tecla que el usuario ingrese
            switch(c) {
                case KEY_DOWN: //Se lee la flecha hacia arriba
                    menu_driver(menu, REQ_DOWN_ITEM); //Se desplaza hacia arriba el menu
                    index = item_index(current_item(menu));
                    wrefresh(ventana); //Se regresca la pantalla
                    break;
                case KEY_UP: //Se lee la flecha hacia abajo
                    menu_driver(menu, REQ_UP_ITEM); //Se desplaza hacia abajo el menu
                    index = item_index(current_item(menu));
                    wrefresh(ventana);
                    break;
                case 10: //Se lee la tecla enter
                    index = item_index(current_item(menu));
                    if (index ==0) { //Sub-indice de nueva partida
                        liberarMemoria(5, false);
                        nuevaPartida();
                        return;
                    }
                    else if (index ==1) {
                        liberarMemoria(5, false);
                        //continuarPartida(); TBC
                        return;
                    }
                    else if (index ==2) {
                        liberarMemoria(5, false);
                        ajustes();
                        clear();
                        return;
                    }
                    else if (index ==3) {
                        liberarMemoria(5, false);
                        //tutorial();
                        return;
                    }
                    else if (index ==4) {
                        liberarMemoria(5, false);
                        endwin(); //Se desactiva ncurses
                        exit(0);
                    }
                default:
                    break;
            }
        }
    }

//Opcion 1: Funcion de la nueva partida
void nuevaPartida(void) {
    bool *ptr_wizard = &Player.wizard, *ptr_warrior= &Player.warrior;
    char *ptr_nombre = Player.name;
    int *ptr_money = &Player.money;
    extraccionVerossa(); //Funcion sin impresion en la pantalla pero me sirve para sacar el nombre de las 3 Verossas
    ordenPantalla();
    introduccion(ptr_nombre, ptr_warrior, ptr_wizard);
    comerciante_1(ptr_nombre, ptr_money);
    flujo_Combate(ptr_wizard, ptr_warrior);
}
void flujo_Combate(bool *ptr_wizard, bool *ptr_warrior) {
    for (int i=0; i<4; i++){  //Determina la aparicion de los primeros jefes
        comercianteConfig(i, ptr_wizard, ptr_warrior, true);
            clear(); //Se actualiza la pantalla del comerciante
        escena(i); //Aparecen los dialogos introductorios del jefe a pelear
        logica_combate(i); //Funcion recursiva
            liberarMemoria(4, false); //Se libera la memoria de los combates
        incrementoDinero(i);
        clear();
        }
    clear();
    refresh();
    printw("Volviendo al menu principal");
    printw("\nPresiona Enter");
    refresh();
    saltoLinea();
    clear();
}
void comercianteConfig(int i, bool *ptr_wizard, bool *ptr_warrior, bool condicional) {
    comercianteMarin(); //arte en ascii
    dialogosComerciante(i);
    if (*ptr_warrior == true){
        for (int a=0; a<7; a++) {
            if (a == 6) {
                elecciones4[a] = "Salir";
                break;
            }else{
                elecciones4[a] = That_damn_struct.lvl[i].warrior[a].name; //Accedemos al nombre del item de warrior y creamos las opciones preliminares para el menu
            }
        }
    }else {
        for (int a=0; a<7; a++) {
            if (a == 6) {
                elecciones4[a] = "Salir";
                break;
            }else{
                elecciones4[a] = That_damn_struct.lvl[i].wizard[a].name; //Accedemos al nombre del item de wizard
            }
        }
    }
    WINDOW *money = newwin(3, 40, 0, 80);
        box(money, 0, 0);
        mvwprintw(money, 1,2, "Tu dinero actual son: %i monedas", Player.money);
        wrefresh(money);
    WINDOW *descripcion = newwin(4, 55, 14, 57); //Se crea una ventana para imprimir la descripcion de cada item
        box(descripcion, 0,0); //Se especifica su contorno
            wrefresh(descripcion);
    WINDOW *informacion = newwin(13, 29, 19, 91); //Se crea otra ventana para imprimir la informacion de cada item
    creadoraDeMenus(7, elecciones4, 10, 55, 4, 57, 7, 53, 2, 1, false, false, 29);
        box(ventana, 0, 0);
        mvwprintw(ventana, 1, 17, "Items disponibles:");
    wrefresh(ventana);
    actualizarVentana(0, i, informacion, money, true); //Para imprimir la primer posicion
    while (1) {
        int c, index; //Se lee la tecla
        c = getch();
        switch (c) {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                    index = item_index(current_item(menu));
                    actualizarVentana(index, i, informacion, money, true);
                    wrefresh(ventana);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                    index = item_index(current_item(menu));
                    actualizarVentana(index, i, informacion, money, true);
                    wrefresh(ventana);
                break;
            case 10:
                index = item_index(current_item(menu));
                if (index == 6) {
                    liberarMemoria(7, false);
                        delwin(money);
                        delwin(descripcion);
                        delwin(informacion);
                    refresh();
                    return;
                }
                else {
                    incrementoStats(index, i, ptr_warrior, ptr_wizard, money);
                    wrefresh(money);
                    break;
                }
            default:
                break;
        }
    }
}
void actualizarVentana(int index, int i, WINDOW *ventana_1, WINDOW *ventana_2, bool comerciante) { //Funcion con tres propositos excluyentes uno del otro
    //Proposito 1: Actualizar la ventana del comerciante
    if (comerciante==true) {
        wclear(ventana_1); //Se limpia la ventana relacionada a la informacion de las estadisticas del jugador
            box(ventana_1, 0,0);
        mvwprintw(ventana_1, 1, 9, "Tus stats:"); //Se reimprime el cabecero de la ventana
        if (index == 6) { //Si el indice esta sobre la opcion "salir", se imprime un mensaje unico
            mvwprintw(ventana_1, 3, 2, "Nada, solo continuas");
            mvwprintw(ventana_1, 4, 2, "a la siguiente parte");
            mvwprintw(ventana_1, 5, 2, "uwu");
        }else{ //En caso de estar en cualquier otro item, se imprimen sus estadisticas dependiendo de la clase del usuario
            if (Player.warrior == true) { //Si el usuario es un guerrero, se imprimen las estadisticas del item de guerrero en ese nivel
                mvwprintw(ventana_1, 2,1, "HP = %i + (%i)", Player.war.hp_max, That_damn_struct.lvl[i].warrior[index].hp);
                mvwprintw(ventana_1, 3,1, "HP_reg = %i + (%i)", Player.war.hp_reg, That_damn_struct.lvl[i].warrior[index].hp_reg);
                mvwprintw(ventana_1, 4,1, "ATK = %i + (%i)", Player.war.dmg, That_damn_struct.lvl[i].warrior[index].dmg);
                mvwprintw(ventana_1, 5,1, "CRIT = %.2f + (%.2f)", Player.war.crit_item, That_damn_struct.lvl[i].warrior[index].crit_item);
                mvwprintw(ventana_1, 6,1, "VAMP = %.2f + (%.2f)", Player.war.vampirism, That_damn_struct.lvl[i].warrior[index].vampirism);
                mvwprintw(ventana_1, 7,1, "DEF = %i + (%i)", Player.war.defense, That_damn_struct.lvl[i].warrior[index].def);
                mvwprintw(ventana_1, 8,1, "EVA = %i + (%i)", Player.war.eva, That_damn_struct.lvl[i].warrior[index].eva);
                mvwprintw(ventana_1, 10, 1, "Costo: $%i", That_damn_struct.lvl[i].warrior[index].cost);
            }else{//Si el usuario es un mago, se imprimen las estadisticas del item de mago en ese nivel
                mvwprintw(ventana_1, 2,1, "HP = %i + (%i)", Player.wiz.hp_max, That_damn_struct.lvl[i].wizard[index].hp);
                mvwprintw(ventana_1, 3,1, "Mana = %i + (%i)", Player.wiz.mana_max, That_damn_struct.lvl[i].wizard[index].mana);
                mvwprintw(ventana_1, 4,1, "Mana_Reg = %i + (%i)", Player.wiz.mana_reg, That_damn_struct.lvl[i].wizard[index].mana_reg);
                mvwprintw(ventana_1, 5,1, "Mana_csmp = %i + (%i)", Player.wiz.mana_csmp, That_damn_struct.lvl[i].wizard[index].mana_csmp);
                mvwprintw(ventana_1, 6, 1, "ATK = %i + (%i)", Player.wiz.dmg, That_damn_struct.lvl[i].wizard[index].dmg);
                mvwprintw(ventana_1, 7, 1, "EVA = %i + (%i)", Player.wiz.eva, That_damn_struct.lvl[i].wizard[index].eva);
                mvwprintw(ventana_1, 9, 1, "Costo: $%i", That_damn_struct.lvl[i].wizard[index].cost);
            }
        }
        mvwprintw(ventana_2, 1,2, "Tu dinero actual son: %i monedas", Player.money);
            wrefresh(ventana_1);
    //Proposito 2: Actualizar la cantidad de vida del enemigo actual
    }else {
        if (ventana_2 == NULL && ventana_1 != NULL) {
            //El programa detecta que solo una ventana cuenta con infomacion dentro
            if (i != 2) { //En caso de que el jefe 3 no este activo, se imprime la vida actual del jefe en turno
                wclear(ventana_1);
                    box(ventana_1, 0, 0);
                    wattron(ventana_1, COLOR_PAIR(1) | A_BLINK); //Se aplica un colorsito rojo junto a un leve parpadeo de la ventana
                mvwprintw(ventana_1, 1, 2, "%s --->HP(%i)", jefes_inicialesFinales[i].name, jefes_inicialesFinales[i].current_hp_boss); //Se imprime el nombre y vida del jefe
                    wrefresh(ventana_1);
            }else { //En caso de que el jefe 3 este activo, se imprime la vida de tooodos los jefes involucrados de ese arreglo en especifico
                wclear(ventana_1);
                    box(ventana_1, 0, 0);
                    wattron(ventana_1, COLOR_PAIR(1) | A_BLINK); //Tambien se aplica el color rojo y el leve parpadeo
                mvwprintw(ventana_1, 1, 2, "%s --->HP(%i)", jefe3_verossaSisters.name[0], jefe3_verossaSisters.current_hp_boss[0]);
                mvwprintw(ventana_1, 2, 2, "%s --->HP(%i)", jefe3_verossaSisters.name[1], jefe3_verossaSisters.current_hp_boss[1]);
                mvwprintw(ventana_1, 3, 2, "%s --->HP(%i)", jefe3_verossaSisters.name[2], jefe3_verossaSisters.current_hp_boss[2]);
                    wrefresh(ventana_1);
            }
        //Proposito 3: Imprimir en la ventana GLOBAL, la descripcion de cada opcion dentro del menu de opciones contra jefes, junto con la vida actual del jugador
        }else{
            unpost_menu(menu); //Se desactiva momentaneamente el menu para evitar inconvenientes
            wclear(ventana); //Se limpia la ventana
            if (Player.warrior == true) { //Se imprime la vida actual del jugador segun su clase
                mvwprintw(ventana, 1, 1, "%s ----> HP(%i)", Player.name, Player.war.current_hp_player); //Si es Guerrero
            }else{
                mvwprintw(ventana, 1, 1, "%s ----> HP(%i)", Player.name, Player.wiz.current_hp_player); //Si es un Mago
            }
            //Se imprimen las descripciones de cada opcion dentro del indice del menu
            if (index == 0 ) { //En caso de que el usuario ataque
                mvwprintw(ventana, 5,1,"Patea sus traseros!");
            }
            else if (index == 1) { //En caso de que el usuario se defienda
                mvwprintw(ventana, 5,1,"Esto te dejara una cicatriz");
            }
            else if (index == 2) { //En caso de que el usuario evada el ataque
                mvwprintw(ventana, 5,1,"Fan del azar? Deberias hacer mis parlays");
            }
            else if (index == 3) { //El jugador esta sobre la opcion de item
                mvwprintw(ventana, 5,1, "Hora de la Mousekeherramienta misteriosa");
            }
            post_menu(menu); //Se vuelve a subir el menu
                box(ventana, 0, 0); //Se dibuja el marquito alrededor del mismo
        }
    }
}
void incrementoStats(int index, int i, bool warrior, bool wizard, WINDOW *money) {
    int index_1, c_1;
    unpost_menu(menu); //Ocultamos momentaneamente el menu de los items pero no lo destruimos
    set_menu_win(menu, NULL); //Se desvincula el menu de la ventana
    set_menu_sub(menu, NULL);
    delwin(ventana); //Se elimina la ventana de la terminal
    ventana = NULL;
    creadoraDeMenus(2, elecciones3, 10, 55, 4, 57, 7, 54, 2, 1,false, true, 0);
    refresh();
    while (1){
        c_1 = getch();
        switch (c_1) {
            case KEY_UP:
                menu_driver(menu_local, REQ_UP_ITEM);
                wrefresh(ventana_local);
                break;
            case KEY_DOWN:
                menu_driver(menu_local, REQ_DOWN_ITEM);
                wrefresh(ventana_local);
                break;
            case 10:
                index_1 = item_index(current_item(menu_local));
                if (index_1 == 0) {
                    //Se leyo un si
                    if (Player.warrior == true) { //Se valida la clase
                        if (Player.money >= That_damn_struct.lvl[i].warrior[index].cost){
                            Player.war.hp_max += That_damn_struct.lvl[i].warrior[index].hp;
                            Player.war.hp_reg += That_damn_struct.lvl[i].warrior[index].hp_reg;
                            Player.war.dmg += That_damn_struct.lvl[i].warrior[index].dmg;
                            Player.war.crit_item += That_damn_struct.lvl[i].warrior[index].crit_item;
                            Player.war.vampirism += That_damn_struct.lvl[i].warrior[index].vampirism;
                            Player.war.defense += That_damn_struct.lvl[i].warrior[index].def;
                            Player.war.eva += That_damn_struct.lvl[i].warrior[index].eva;
                            Player.money -= That_damn_struct.lvl[i].warrior[index].cost;
                        }
                        else {
                            mvwprintw(ventana_local, 5, 1, "No tienes suficiente dinero comprar ese objeto");
                            mvwprintw(ventana_local, 6, 1, "Presiona Enter para continuar");
                            wrefresh(ventana_local);
                            saltoLinea();
                        }
                    }else{
                        if (Player.money >= That_damn_struct.lvl[i].wizard[index].cost) {
                            Player.wiz.hp_max += That_damn_struct.lvl[i].wizard[index].hp;
                            Player.wiz.mana_max += That_damn_struct.lvl[i].wizard[index].mana;
                            Player.wiz.mana_reg += That_damn_struct.lvl[i].wizard[index].mana_reg;
                            Player.wiz.mana_csmp += That_damn_struct.lvl[i].wizard[index].mana_csmp;
                            Player.wiz.dmg += That_damn_struct.lvl[i].wizard[index].dmg;
                            Player.wiz.eva += That_damn_struct.lvl[i].wizard[index].eva;
                            Player.money -= That_damn_struct.lvl[i].wizard[index].cost;
                        }else{
                            mvwprintw(ventana_local, 5, 1, "No tienes suficiente dinero comprar ese objeto");
                            mvwprintw(ventana_local, 6, 1, "Presiona Enter para continuar");
                            wrefresh(ventana_local);
                            saltoLinea();
                        }
                    }
                    liberarMemoria(2, true);
                    ventana_auxiliar_comerciante(10, 55, 4, 57, 7, 54, 2, 1, false, NULL); //Para el marco de opciones
                    ventana_auxiliar_comerciante(3, 40, 0, 80, 0, 0, 0, 0, true, &money); //Para la ventana de dinero
                        box(ventana, 0, 0);
                        mvwprintw(ventana, 1, 17, "Items disponibles:");
                    return;
                }else{ //Se lee que el usuario selecciono no
                    liberarMemoria(2, true);
                    ventana_auxiliar_comerciante(10, 55, 4, 57, 7, 54, 2, 1, false, NULL);
                        box(ventana, 0, 0);
                        mvwprintw(ventana, 1, 17, "Items disponibles:");
                    return;
                }
            default:
                break;
        }
    }
}
void ventana_auxiliar_comerciante(int largo, int ancho, int eje_y, int eje_x, int s_largo, int s_ancho, int s_eje_y, int  s_eje_x, bool condicional, WINDOW **money) {
    if (condicional == false) { //Le indica al programa que parte se modificara
        ventana = newwin(largo, ancho, eje_y, eje_x);
            set_menu_win(menu, ventana); //Se crea una ventana para el menu
            set_menu_sub(menu, derwin(ventana, s_largo, s_ancho, s_eje_y, s_eje_x)); //Se especifican los parametros de la misma
        box(ventana, 0, 0);
        mvwprintw(ventana, 1, 17, "Items disponibles:");
        post_menu(menu);
        wrefresh(ventana);
    }else{
        delwin(*money);
        *money = newwin(largo, ancho, eje_y, eje_x);
        box(*money, 0, 0);
        mvwprintw(*money, 1,2, "Tu dinero actual son: %i monedas", Player.money);
        wrefresh(*money);
    }
}

void extraccionVerossa(void) { //Se saca el nombre de opciones para Verossa
    for (int a=0; a<3; a++) {
            elecciones6Verossa[a] = jefe3_verossaSisters.name[a]; //En la lista de opciones se va enumerando a cada hermana
        }
    }
void incrementoDinero(int i){
    if (i==0) {
        Player.money += 2000;
    }
    else if (i==1) {
        Player.money += 4000;
    }
    else if (i==2) {
        Player.money += 6000;
    }
    else if (i==3){
        Player.money += 8000;
    }
}

void logica_combate(int i) {
    int *ptr_HP = &Player.war.current_hp_player, *ptr_HPMAX = &Player.war.hp_max;
    *ptr_HP = *ptr_HPMAX; //Se iguala la salud actual del jugador con su salud MAXIMA, para evitar que inicie el combate bajo de vida el jugador
    WINDOW *status = NULL; //Se crea una ventana dentro de la funcion, la cual indicara la vida del jefe actual
    //Primero: Se inicializa el arte del jefe asi como las ventanas que muestren su respectiva salud
    arteJefes(i); //Se muestra el arte en braille del jefe de turno y se refresca la terminal
        if (i != 2) { //Se imprime la vida actual en una ventana de cualquier jefe MENOS VEROSSA (jefe 3)
            status = newwin(3, 30, 0, 0);
                wattron(status, COLOR_PAIR(1) | A_BLINK); //Se aplica un colorsito cute kawaii junto a un parpadeo
                    box(status, 0, 0);
            mvwprintw(status, 1, 2, "%s --->HP(%i)", jefes_inicialesFinales[i].name, jefes_inicialesFinales[i].current_hp_boss);
                wrefresh(status);
        }else { //Se imprime la vida en una ventana del grupo de sub-jefes que conforman a Verossa
            status = newwin(6, 30, 0, 0);
                wattron(status, COLOR_PAIR(1) | A_BLINK);
                    box(status, 0, 0);
            mvwprintw(status, 1, 2, "%s --->HP(%i)", jefe3_verossaSisters.name[0], jefe3_verossaSisters.current_hp_boss[0]);
            mvwprintw(status, 2, 2, "%s --->HP(%i)", jefe3_verossaSisters.name[1], jefe3_verossaSisters.current_hp_boss[1]);
            mvwprintw(status, 3, 2, "%s --->HP(%i)", jefe3_verossaSisters.name[2], jefe3_verossaSisters.current_hp_boss[2]);
                wrefresh(status);
        }
    //Tercero: Se crea un menu que contendra las opciones, la vida del usuario y empieza con la informacion inicializada en el primer indice
        creadoraDeMenus(4, elecciones5, 8, 80, 23, 25, 5, 70,3,6,true,false, 29);
        box(ventana, 0, 0);
        if (Player.warrior == true) {
            mvwprintw(ventana, 1, 1, "%s ----> HP(%i)", Player.name, Player.war.current_hp_player);
        }else {
            mvwprintw(ventana, 1, 1, "%s ----> HP(%i)", Player.name, Player.wiz.current_hp_player);
        }
        mvwprintw(ventana,5,1,"Patea sus traseros!");
        wrefresh(ventana);
        logica_Guerrero(i, status); //Se llama a nuestra funcion recursiva
        return;
}
void logica_Guerrero(int i, WINDOW *ventana_1) { //Funcion recursiva para los combates
    if (Player.war.current_hp_player <= 0) { //Casos base
        delwin(ventana_1);
        muerte(i); //Aqui el juego termina y el usuario murio
    }
    else if (Estado_Jefe.jefe_derrotado[i] == true){ //Aqui el juego avanza a la siguiente etapa
        delwin(ventana_1);
        clear();
        return;
    }
    else{ //Cuerpo madre de la funcion recursvia
        Accion.defended = false; //Se reinicia a su estado default el booleano de defensa del jugador
        Accion.evaded = false;  //Se reinicia a su estado default el booleano de evasion del jugador
        ciclos_clases(i, ventana_1); //El jugador tiene el primer turno
        secuencia_Jefes(i); //Lo sigue el jefe
        return logica_Guerrero(i, ventana_1);
    }
}
void desactivacionHabilidad(int i) {
    if (i<2) { //Se desactiva cualquier habilidad activa de Bruto y Gladio
        jefes_inicialesFinales[i].ability.ability_active[0] = false;
    }
    else if (i>2) { //Se desactiva cualquier habilidad activa de Parca, Morte e Iris
        for (int a=0; a<4; a++) {
            jefes_inicialesFinales[i-1].ability.ability_active[a] = false;
        }
    }else {
        for (int a=0; a<3; a++) {
            jefe3_verossaSisters.ability_activa[a] = false;
        }
    }
}
void desactivadoMenuLimpieza(void) { //Se quita el menu y se limpia la ventana para dejarla lista para futuros rehusos
    unpost_menu(menu);
    wclear(ventana);
    wrefresh(ventana);
}
void ciclos_clases(int i, WINDOW *ventana_1) {
    int c, index, target;
    while (1) {
        c = getch();
        switch (c) {
            case KEY_LEFT:
                menu_driver(menu, REQ_LEFT_ITEM);
                    index = item_index(current_item(menu));
                actualizarVentana(index,0,NULL,NULL,false);
                    wrefresh(ventana);
                break;
            case KEY_RIGHT:
                menu_driver(menu, REQ_RIGHT_ITEM);
                    index = item_index(current_item(menu));
                actualizarVentana(index,0,NULL,NULL,false);
                    wrefresh(ventana);
                break;
            case 113: //Se detecta la tecla ESC
                desactivadoMenuLimpieza();
                    guardarPartida(i);
                    redibujadoPantalla();
                break;
            case 10:
                index = item_index(current_item(menu));
                if (index == 0) { // El usuario eligio la opcion de ataque
                    desactivadoMenuLimpieza();
                    if (i!=2) { //Mientras Verossa NO este activa
                            if (Player.warrior == true) {
                                configuracionGuerrero(i, 0);
                            }else{} //Configuracion Mago TBC
                        actualizarVentana(29,i,ventana_1,NULL,false);
                        return;
                    }else{ //Si verossa se activa (i==2)
                        target = seleccionObjetivo();
                            liberarMemoria(3, true);
                            configuracionGuerrero(i,target);
                            actualizarVentana(29,i,ventana_1,NULL,false);
                        return;
                    }
                }
                else if (index == 1) {// El usuario eligio la opcion de defensa
                    desactivadoMenuLimpieza();
                    Accion.defended = true;
                    return;
                }
                else if (index ==2) {// El usuario eligio la opcion de evasion
                    desactivadoMenuLimpieza();
                    Accion.evaded = true;
                    return;
                }
                else if (index == 3) { //El usuario eligio la opcoion de item
                    desactivadoMenuLimpieza();
                    endwin();
                    exit(1);
                }
                break;
            default:
                break;
        }
    }
}
void redibujadoPantalla(void) {
    unpost_menu(menu);
    wclear(ventana);
        box(ventana, 0, 0);
    post_menu(menu);
    if (Player.warrior == true) {
        mvwprintw(ventana, 1, 1, "%s -----> HP(%i)", Player.name, Player.war.current_hp_player);
    }else{
        mvwprintw(ventana, 1, 1, "%s -----> HP(%i)", Player.name, Player.wiz.current_hp_player);
    }
    mvwprintw(ventana,5,1,"Patea sus traseros!");
        wrefresh(ventana);
}
void configuracionGuerrero(int i, int target) {
    if (ubermensch == false){ //Se evalua si esta activado el modo ubermensch
        int ataque = calculoAtaqueGuerrero(); //Se recibe el ataque realizado por el jugador
        int curacion = calculoCuracionVampirismo(ataque); //Se evalua si EXISTIO una curacion (asuencia de curacion = -1)
        aplicacionAtaque(i, target, ataque); //Se aplica el ataque al jefe actual
        evaluacionAtaqueG(ataque, curacion);
    }else{
        aplicacionAtaque(i, target, 99999); //<--- Util para acabar con el jefe de un golpe y evaluar correcto funcionamiento del codigo
    }
}
int calculoAtaqueGuerrero(void) {
    int numero, *ptr_dmgG = &Player.war.dmg, dmg_local;
    float *ptr_Crit = &Player.war.crit_item;
    bool *ptr_Crit_Flag = &Crit_Flag.criticon;
    if (*ptr_Crit > 0) { //En caso de que el jugador tenga estadisticas de ataques criticos
        numero = rand() % 100 + 1; //Se genera un número pseudoaleatorio entre el 1 y 100
        if (*ptr_Crit >= numero) { //Si el número de nuestra probabilidad es mayor al número generado pseudoaleatoriamente, indica la deteccion de un critico
            *ptr_Crit_Flag = true; //Se manda una alerta global al programa para que funciones posteriores (las de dialogos) la puedan evaluar y reiniciar <-- Obligatorio esto ultimo
            dmg_local = *ptr_dmgG; //Se hace una copia local del ataque para no modificar el valor estandar del registro
            dmg_local = round(dmg_local*2.5); //Como se detecto un critico, se multiplica por el facto 2.5
            return dmg_local; //Regresa el ataque maximo realizado en caso de haber critico
        }else {
            return *ptr_dmgG; //Ausencia de critico
        }
    }else {
        return *ptr_dmgG; //Ausencia de critico
    }
}
int calculoCuracionVampirismo(int ataque) {
    float *ptr_vmp = &Player.war.vampirism;
    if (*ptr_vmp > 0) {
        int vmp, *ptr_P_HP = &Player.war.current_hp_player;
        float factor_vmp;
            factor_vmp = *ptr_vmp/100; //Se divide entre 100 el factor del vampirismo del jugador
            vmp = round(ataque * factor_vmp); //Se multiplica el ataque total por el factor, el resultado es una fraccion de ataque de la cual el usuario se cura
            *ptr_P_HP += vmp; //Se cura el usuario
        return vmp;
    }else{
        return -1; //Indica a funciones de impresion que no hubo regeneracion de vida
    }
}
void aplicacionAtaque(int i, int target, int ataque){
    /*El indice de los jefes en el registro sufre un desfase al llegar a indice 2 (donde se activa verrossa)
     Por ende esta funcion se encarga de corregir ese desfase */
    if (i<2) { //Ausencia de desfase
        jefes_inicialesFinales[i].current_hp_boss -= ataque;
    }
    else if (i>2){ //Aqui comienza el problema del desfase afectando a los jefes con indice 2,3,4 dentro del registro jefes_inicialesFinales
       jefes_inicialesFinales[i-1].current_hp_boss -= ataque; //Se corrige restandole 1 al indice
    }else{ //En caso de que i == 2
        jefe3_verossaSisters.current_hp_boss[target] -= ataque;
    }
}
//void configuracion_mago(void) {} //TBC
/*void evaluacionJefe(int i){
    if (i<2) {}
    } */
void secuencia_Jefes(int i) {
    bool estado = validacionJefes(i);
    if (estado==false) {
        if (i==0) { //
            Bruto_config(i);
        }
        else if (i==1){
            Gladio_config(i);
        }
        else if (i==2) {
            Verossa_config(i);
        }
        else if (i==3) {
            Parca_config(i);
        }
    }else {
        return;
    }
}
void muerte(int i) {
    endwin();
    printf("Te has muerto!\n");
    exit(0);
}
int seleccionObjetivo(void) {
    creadoraDeMenus(3, elecciones6Verossa, 8, 80, 23, 25, 5, 70,3,6,true,true, 29);
    int b,index_1, target;
    while (1) {
        b = getch();
        switch (b) {
            case KEY_UP:
                menu_driver(menu_local, REQ_UP_ITEM);
                    wrefresh(ventana_local);
                break;
            case KEY_DOWN:
                menu_driver(menu_local, REQ_DOWN_ITEM);
                    wrefresh(ventana_local);
                break;
            case 10:
                index_1 = item_index(current_item(menu_local));
                target = index_1;
                return target;
            default:
                break;
        }
    }
}
/*void evaluacion_efectos(int i) {
    if (i==1) {
    }
}
*/
bool validacionJefes(int i) {
    if (i<2) { //Aun no hay desfase
        if (jefes_inicialesFinales[i].current_hp_boss <= 0) {
            Estado_Jefe.jefe_derrotado[i] = true;
            return true; //Se determina que el jefe fue derrotado
        }else {
            return false; //El jefe aun cuenta con puntos de vida
        }
    }
    else if (i>2) { //Error de desfase
        if (jefes_inicialesFinales[i-1].current_hp_boss <= 0){ //Se resta 1 al indice para reajustarlo
            Estado_Jefe.jefe_derrotado[i] = true;
            return true;
        }else {
            return false;
        }
    }else {
        //Cuando i ==2
        int contador=0;
        for (int j=0; j<3; j++){
            if (jefe3_verossaSisters.current_hp_boss[j] <=0) {
                jefe3_verossaSisters.jefe_derrotado[j] = true;
                contador++;
            }
        }if (contador == 3) { //Los 3 jefes han sido derrotados
            Estado_Jefe.jefe_derrotado[i] = true;
            return true;
        }else{ //Solo 1 o mas fueron derrotados
            return false;
        }
    }
}
void Bruto_config(int i) {
    int numero = rand()%10 + 1;
        if (numero <= 8) {
            ataqueJefesBGVPMI(i, 0);
            redibujadoPantalla();
        }else {
            jefeHabilidad(i,0);
        }
}
void Gladio_config(int i) {
    int numero = rand()%10 + 1;
        if (numero <= 8) {
            ataqueJefesBGVPMI(i,0);
            redibujadoPantalla();
        }else{
            jefeHabilidad(i, 0);
    }
}
void Verossa_config(int i){
    int numero[2];
    for (int k=0; k<2; k++) {
        if (jefe3_verossaSisters.jefe_derrotado[k] == true) {
            numero[k] = -1; //Parametro que le indicara al programa que el jefe no realizo un ataque puesto que se encuentra derrotada
        } //No ocurre nada
        else{
            numero[k] = rand()%10 + 1; //Se genera un numero pseudoaleatorio el cual se guarda en un arreglo de 1 dimension
        }
    }
        for (int k=0; k<2; k++) {
            if (numero[k] == -1) { //No ocurre nada
            }
            else if (numero[k] >= 1 && numero[k] <= 8){ //El subindice del arreglo nos indica que jefe realizo el ataque
                //Se esta excluyendo a jefe3_verossaSisters.name[3] (Amanda), porque es un personaje que NO cuenta con ataque hostil al jugador
                ataqueJefesBGVPMI(i, k); //Se detecta un ataque y se pasa el subindice del jefe que lo realizo

            }else{
                //Habilidad actiada por el jefe de verossa en esa posicion
                jefeHabilidad(i, 0);
            }
        }
    redibujadoPantalla();
    }
void Parca_config(int i) {
    int numero = rand()%10 + 1;
        if (numero <= 8) {
            ataqueJefesBGVPMI(i,0);
            redibujadoPantalla();
        }else{
            jefeHabilidad(i, 0);
        }
}
void Morte_config(void) {} //TBC
void DiosaEstelarIris(void){}//TBC
int seleccionJefe(int nivel, int Verossa_only) {
    if (nivel<2) {
        int *ptr_Boss_Min = &jefes_inicialesFinales[nivel].boss_atck_min, *ptr_Boss_Max = &jefes_inicialesFinales[nivel].boss_atck_max;
        int ataque = rand()% (*ptr_Boss_Max - *ptr_Boss_Min) + *ptr_Boss_Min;
        return ataque;
    }
    else if (nivel>2) {
        int *ptr_Boss_Min = &jefes_inicialesFinales[nivel-1].boss_atck_min, *ptr_Boss_Max = &jefes_inicialesFinales[nivel-1].boss_atck_max;
        int ataque = rand()% (*ptr_Boss_Max - *ptr_Boss_Min) + *ptr_Boss_Min;
        return ataque;
    }else {
            int *ptr_Verossa_Min = &jefe3_verossaSisters.boss_atck_min[Verossa_only], *ptr_Verossa_Max = &jefe3_verossaSisters.boss_atck_max[Verossa_only];
            int ataque = rand()% (*ptr_Verossa_Max - *ptr_Verossa_Min) + *ptr_Verossa_Min;
            return ataque;
        }
    }
char *nombreJefe(int nivel, int j) {
    if (nivel<2) {
        char *ptr_jefe_nombre = jefes_inicialesFinales[nivel].name;
        return ptr_jefe_nombre;
    }
    else if (nivel>2) {
        char *ptr_jefe_nombre = jefes_inicialesFinales[nivel-1].name;
        return ptr_jefe_nombre;
    }else{
        char *ptr_Verossa_nombre = jefe3_verossaSisters.name[j];
        return ptr_Verossa_nombre;
    }
}
void ataqueJefesBGVPMI(int nivel, int Verossa_lvl) {
    //La configuracion de los ataques de los jefes
    wclear(ventana); //Borramos lo que sea que haya en la ventana
    wrefresh(ventana); //Actualizamos la ventana
    box(ventana, 0, 0); //Creamos un marco el cual AUN NO se vera
    int *ptr_P_HPG = &Player.war.current_hp_player, *ptr_P_HPW = &Player.wiz.current_hp_player;
    bool *ptr_warrior = &Player.warrior;
    int ataque = seleccionJefe(nivel, 0);
    if (Accion.defended == true) { //Se detecta si el usuario decidio defenderse
        int ataque_reducido = defensaJugador(ataque);
            dialogos_defensa(nivel, ataque_reducido, Verossa_lvl);
        }
        else if (Accion.evaded == true) { //Se detecta si el usuario decidio evadir el ataque
            int ataque_evadido = evasionJugador(ataque);
            dialogos_evasion(nivel, ataque_evadido, Verossa_lvl);
        }else {
            if (*ptr_warrior == true) {
                *ptr_P_HPG -= ataque;
                dialogo_ataque_recibido(nivel, ataque, Verossa_lvl); //Se imprime un dialogo relacionado
            }else {
                *ptr_P_HPW -= ataque;
                dialogo_ataque_recibido(nivel, ataque, Verossa_lvl);
            }
        }
    }
int defensaJugador(int ataque) {
    int *ptr_P_HPG = &Player.war.current_hp_player, *ptr_P_HPW = &Player.wiz.current_hp_player;
    int *ptr_defG = &Player.war.defense, *ptr_defW = &Player.wiz.defense;
    bool *ptr_warrior = &Player.warrior;
    float reduccion;
    float ataque_reducido;
        if (*ptr_warrior == true) { //En caso de que el jugador sea un Guerrero
            reduccion = *ptr_defG; //Se iguala a variable flotante la defensa del jugador (Que es de tipo entera)
            reduccion /= 100; //Se estima un porcentaje de reduccion del 0% al 100%
            ataque_reducido = ataque; //El valor del ataque original se guarda en una variable local
            ataque_reducido *= reduccion; //Se multiplica nuestra reduccion por nuestra variable local
            ataque -= ataque_reducido; //Se resta a nuestro ataque generado con rand, el factor de reduccion
            *ptr_P_HPG -= ataque; //Se resta a la vida actuaL del jugador, el ataque modificado
            return ataque;
        }else{ //En caso de que sea un Mago
            reduccion = *ptr_defW; //Se iguala a variable flotante la defensa del jugador (Que es de tipo entera)
            reduccion /= 100; //Se estima un porcentaje de reduccion del 0% al 100%
            ataque_reducido = ataque; //El valor del ataque original se guarda en una variable local
            ataque_reducido *= reduccion; //Se multiplica nuestra reduccion por nuestra variable local
            ataque -= ataque_reducido; //Se resta a nuestro ataque generado con rand, el factor de reduccion
            *ptr_P_HPW -= ataque; //Se resta a la vida actuaL del jugador, el ataque modificado
            return ataque;
        }
    }
int evasionJugador(int ataque){
    int *ptr_P_HPG = &Player.war.current_hp_player, *ptr_P_HPW = &Player.wiz.current_hp_player;
    int porcentaje = rand()%100 + 1;
    if (Player.warrior == true) {
        if (Player.war.eva > porcentaje) {
            return 0;
        }else{
            ataque = round(ataque * 1.30);
            *ptr_P_HPG -= ataque;
            return ataque;
        }
    }else {
        if (Player.wiz.eva > porcentaje) {
            return 0;
        }else {
            ataque = round(ataque * 1.15);
            *ptr_P_HPW -= ataque;
            return ataque;
        }
    }
}
void guardarPartida(int i) {
    creadoraDeMenus(2, elecciones3, 8, 80, 23, 25, 5, 70,3,6,true,true, 29);
        box(ventana_local, 0, 0);
    mvwprintw(ventana_local, 1, 7, "Deseas guarda tus estadisticas actuales?");
        wrefresh(ventana_local);
    //keypad(ventana_local, TRUE);
    int c, index;
    while (1) {
        c = getch();
        switch (c) {
            case KEY_DOWN:
                menu_driver(menu_local, REQ_DOWN_ITEM);
                index = item_index(current_item(menu_local));
                    wrefresh(ventana_local);
                break;
            case KEY_UP:
                menu_driver(menu_local, REQ_UP_ITEM);
                index = item_index(current_item(menu_local));
                    wrefresh(ventana_local);
                break;
            case 10:
                index = item_index(current_item(menu_local));
                    if (index == 0) { //Se lee un si
                        unpost_menu(menu_local);
                            wrefresh(ventana_local);
                        exportacion(i);
                            saltoLineaWin(ventana_local);
                        liberarMemoria(2, true);
                            redibujadoPantalla();
                            wrefresh(ventana);
                        return;
                    }else{
                       liberarMemoria(2, true);
                            redibujadoPantalla();
                            wrefresh(ventana);
                        return;
                    }
            default:
                break;
        }
    }
}
void exportacion(int i) { //Se asignan punteros al registro a exportar
    char *ptr_nombre = Exportacion.name;
    int *ptr_P_HP_MAX = &Exportacion.hp_max, *ptr_DMG = &Exportacion.dmg, *ptr_DEF = &Exportacion.defense, *ptr_EVA = &Exportacion.eva, *ptr_hp_reg = &Exportacion.hp_reg;
    int *ptr_money = &Exportacion.money;
    float *ptr_Crit = &Exportacion.crit, *ptr_Vamp = &Exportacion.vampirism;
    bool *ptr_Warrior = &Exportacion.warrior;
    bool *ptr_Estado_Jefe = Exportacion.jefe_derrotado, *ptr_Jefe_Muerto = Exportacion.jefe_muerto;
    //Se copia toda la informacion mediante punteros
    strcpy(ptr_nombre, Player.name);
    *ptr_P_HP_MAX = Player.war.hp_max;
    *ptr_DMG = Player.war.dmg;
    *ptr_DEF = Player.war.defense;
    *ptr_EVA = Player.war.eva;
    *ptr_hp_reg = Player.war.hp_reg;
    *ptr_money = Player.money;
    *ptr_Crit = Player.war.crit_item;
    *ptr_Vamp = Player.war.vampirism;
    *ptr_Warrior = Player.warrior;
    for (int j=0; j<6; j++) {
        ptr_Estado_Jefe[j] = Estado_Jefe.jefe_derrotado[j];
        ptr_Jefe_Muerto[j] = Estado_Jefe.jefe_muerto[j];
    enviado_a_archivo(i);
    }

}
void enviado_a_archivo(int i) {
    wclear(ventana_local);
    box(ventana_local,0,0);
        wrefresh(ventana_local);
    FILE *archivo = fopen(ruta, "w");
    if (archivo == NULL) {
        mvwprintw(ventana_local, 1, 1, "Error al abrir archivo.\n");
        mvwprintw(ventana_local, 2, 1, "Enter para volver al menu principal");
            wrefresh(ventana_local);
            saltoLineaWin(ventana_local);
        return;
    }else {
        fprintf(archivo, "Nombre: %s\n", Exportacion.name);
        fprintf(archivo, "HP_MAX: %i\n", Exportacion.hp_max);
        fprintf(archivo, "Nivel actual: %i\n", i);
        fprintf(archivo, "DMG: %i\n", Exportacion.dmg);
        fprintf(archivo, "DEF: %i\n", Exportacion.defense);
        fprintf(archivo, "EVA: %i\n", Exportacion.eva);
        fprintf(archivo, "HP_REG: %i\n", Exportacion.hp_reg);
        fprintf(archivo, "Money: %i\n", Exportacion.money);
        fprintf(archivo, "CRIT: %.2f\n", Exportacion.crit);
        fprintf(archivo, "VAMP: %.2f\n", Exportacion.vampirism);
        fprintf(archivo, "Warrior: %i\n", Exportacion.warrior);

        fprintf(archivo, "Estado_jefes: ");
        for (int j = 0; j < 6; j++) {
            fprintf(archivo, "%i ", Exportacion.jefe_derrotado[j]);
            }
        fprintf(archivo, "\n");
        fprintf(archivo, "Jefes_muertos: ");
        for (int j = 0; j < 6; j++) {
            fprintf(archivo, "%i ", Exportacion.jefe_muerto[j]);
        }
        fprintf(archivo, "\n");
        fclose(archivo);
        mvwprintw(ventana_local, 1, 1, "Informacion guardada con exito!\n");
        mvwprintw(ventana_local, 2, 1, "Presiona Enter para continuar");
    }
}
//Opcion 2: Cargado de partida
void continuarPartida(void){

}

//Opcion 3: Ajustes
void ajustes(void){
        clear();
        mvprintw(10, 22,"Deseas activar el modo ubermensch?\n");
        mvprintw(11,24,"Seras inmortal con el activado!\n");
        creadoraDeMenus(2, elecciones3, 2, 40, 13, 35, 2, 40, 0, 0,false, false, 29);
    int c, index;
    while (1) {
            c = getch();
            switch (c) {
                case KEY_DOWN:
                    menu_driver(menu, REQ_DOWN_ITEM);
                    index = item_index(current_item(menu));
                    wrefresh(ventana);
                    break;
                case KEY_UP:
                    menu_driver(menu, REQ_UP_ITEM);
                    index = item_index(current_item(menu));
                    wrefresh(ventana);
                    break;
                case 10:
                    index = item_index(current_item(menu));
                    if (index ==0){ //Se lee un si
                        liberarMemoria(2, false);
                        echo();
                        keypad(stdscr, FALSE);
                        c=0;
                        char intento[50];
                        printw("Ingresa el password para activar la funcion\n");
                        while(1){
                            getnstr(intento, 49);
                            if (c < 3) {
                                if(strcmp(intento, password1)==0){
                                    printw("\nEl password es correcto\nPresiona Enter para continuar");
                                    refresh();
                                    saltoLinea();
                                    ubermensch = TRUE;
                                    return;
                                }
                                else {
                                    c++;
                                    printw("\nEl password es incorrecto\n");
                                    refresh();
                                    continue;
                                }
                            }
                            else {
                                printw("\n[AMANDA]: T-Te has quedado s-sin intentos\nPor favorsito presiona enter para volver al menu principal T_T");
                                    refresh();
                                    saltoLinea();
                                return;
                            }
                        }
                    }
                    else{
                        return;
                    }
                default:
                    break;
            }
        }
    }