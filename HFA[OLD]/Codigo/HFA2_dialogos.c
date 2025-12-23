#include <ncursesw/menu.h>
#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "HFA1_main.h"
#include "HFA3_inventario.h"
#include "HFA5_art.h"
//Prototipos
void magoEnojado(int s);
//Cuerpo de funciones
void saltoLinea(void) {
    refresh();
    while (getch() !='\n'){}
}
void saltoLineaWin(WINDOW *ventana_1){
    wrefresh(ventana_1);
    while (wgetch(ventana_1) != '\n'){}
}
void liberarMemoria1(int n_opciones, ITEM **opciones, MENU *menuP, WINDOW *ventana) {
    unpost_menu(menuP); //Remueve el menu
    free_menu(menuP); //Libera la memoria del menu
    for (int i=0;i<n_opciones;++i) { //Ciclo for que va liberando la memoria de cada uno de los items del menu
        free_item(opciones[i]);
    }
    free(opciones); //Se libera la memoria del arreglo de opciones
    delwin(ventana);
    touchwin(stdscr);
    refresh();
}
void nombreYclase(char *ptr_nombre, bool *ptr_warrior, bool *ptr_wizard);
void dialogosDelGatito(int y, int x) {
    noecho();
    cbreak();
    WINDOW *ventanaGato = newwin(10,60,7,32);
    keypad(ventanaGato, FALSE);
    mvwaddstr(ventanaGato, 0, 0, "Meow");
    mvwaddstr(ventanaGato, 1, 0, "Soy el gatito del destino!");
    mvwaddstr(ventanaGato, 2, 0, "En este juego tendras que presionar enter");
    mvwaddstr(ventanaGato, 3, 0, "para avanzar los dialogos de los personajes.");
    mvwaddstr(ventanaGato, 4, 0, "Pongamoslo a prueba.");
    wrefresh(ventanaGato);
    while (1) {
    mvwaddstr(ventanaGato, 6, 0, "Presiona enter-nya\n");
        wrefresh(ventanaGato);
        int tecla = wgetch(ventanaGato);
        wclear(ventanaGato);
        wrefresh(ventanaGato);
        if (tecla == '\n') {
            mvwaddstr(ventanaGato, 0, 0, "Meowtastico!");
            mvwaddstr(ventanaGato, 1, 0, "Ya estas listo para continuar!\n");
            wrefresh(ventanaGato);
            saltoLineaWin(ventanaGato);
            break;
        }
        else {
            mvwaddstr(ventanaGato, 0, 0, "._.");
            mvwaddstr(ventanaGato, 1, 0, "Acaso no sabes leer?");
            mvwaddstr(ventanaGato, 2, 0, "Te dije que presiones enter >:(");
            mvwaddstr(ventanaGato, 3, 0, "Intentemos otra vez");
            wrefresh(ventanaGato);
        }
    }
        wclear(ventanaGato);
        wrefresh(ventanaGato);
    mvwaddstr(ventanaGato, 0, 0, "Supongo que te estas preguntando:");
        saltoLineaWin(ventanaGato);
    mvwaddstr(ventanaGato, 1, 0, "Por que aun esta este gato molesto aqui?");
        saltoLineaWin(ventanaGato);
    mvwaddstr(ventanaGato, 2, 0, "Jejejeje");
        saltoLineaWin(ventanaGato);
    mvwaddstr(ventanaGato, 3, 0, "Veras, mi creador sabio investigo de todo");
        saltoLineaWin(ventanaGato);
    mvwaddstr(ventanaGato, 4, 0, "Pero no encontro forma de ajustar la pantalla");
        saltoLineaWin(ventanaGato);
    mvwaddstr(ventanaGato, 6, 0, "Como sea, voy a analizar tu pantalla...");
        saltoLineaWin(ventanaGato);
        wclear(ventanaGato);
        wrefresh(ventanaGato);
    while (1){
        int filas = getmaxy(stdscr);
        int columnas = getmaxx(stdscr);
        wclear(ventanaGato);
        wrefresh(ventanaGato);
        if(filas >= 30 && columnas >= 118){
            mvwaddstr(ventanaGato, 1, 0, "Perfecto! Tu terminal esta en la resolucion esperada!");
            saltoLineaWin(ventanaGato);
            mvwaddstr(ventanaGato, 3, 0, "Disfruta la experiencia meow");
            saltoLineaWin(ventanaGato);
            break;
        }
        else {
            mvwaddstr(ventanaGato, 1, 0, "Por favor pon la terminal en pantalla completa");
            mvwaddstr(ventanaGato, 2, 0, "Y presiona Enter para actualizar cambios :3");
            saltoLineaWin(ventanaGato);
            refresh();
            mvwaddstr(ventanaGato, 4, 0, "Volvamoslo a intentar!");
            saltoLineaWin(ventanaGato);
        }
    }
    keypad(ventanaGato, TRUE);
    delwin(ventanaGato);
}
void introduccion(char *ptr_nombre, bool *ptr_warrior, bool *ptr_wizard){
    clear();
    int c;
    printw("La fiesta en mezontle estuvo muy buena anoche. Rumbeaste tanto que olvidaste tu nombre.\n");
        saltoLinea();
    printw("Como sea, te despierta un molesto sonido, volteas y resulta ser tu despertador, es Lunes y tienes que ir a trabajar.\n");
        saltoLinea();
    printw("Sin embargo, cuando sales de tu cama, escuchas gritos y explosiones afuera de tu casa, te asomas por la ventana...\n");
        saltoLinea();
    printw("\nY ves a.... Seres de otro planeta que invaden tu colonia!!!! \nComo sea, no le das importancia porque tu prioridad ahorita es llegar temprano al trabajo.\n");
        saltoLinea();
    printw("\nMientras desayunas ves las noticias: Europa ha caido ante la invasion dimensional! es lo que sale en tvAzteca.\n");
        saltoLinea();
    printw("Te preguntas si cancelaran el partido de tu maquina celeste (el cruz azul) por todas estas anomalias.\n");
        saltoLinea();
    printw("\nMientras te das una ducha, activas tu modo reflexivo y piensas: \n\t''Si hay una invasion de seres de otro mundo "
         "no creo que este intacto mi trabajo.\n\t\tY si no esta intacto mi trabajo, no tendria que ir a trabajar''.\n");
        saltoLinea();
    printw("\n\t(Los dioses de la pereza lograron iluminar tu coco)\n");
        saltoLinea();
    printw("\nLa euforia invade tu cuerpo y por primera vez en 3 largas decadas, te sientes libre totalmente.\n");
        saltoLinea();
    printw("El hecho de no tener que verle la cara al pelonchas de tu jefe te da la sensacion de auto-cumplimiento.\n");
        saltoLinea();
    printw("\nMientras cantabas con extasis unas rolas de Tito Doble P; una explosion de colores sacude tu ducha!\n");
        saltoLinea();
    printw("Asustado, agarras tu patito de goma como arma para ver que ocurrio. Cuando corres las cortinas, ves a....\n");
        saltoLinea();
    printw("\nUN MAGO!!!\n");
        saltoLinea();
    printw("\nSu aspecto de tercera edad te hace recordar a un profesor al cual no tengo permitido mencionar en esta introduccion.\n");
        saltoLinea();
    printw("\nEl mago te voltea a ver y te dirige la palabra...\n");
        saltoLinea();
        clear();
    printw("[MAGO]: Oh querido y sabio joven, permiteme presentarme como el mago.\n");
        saltoLinea();
    printw("\n[MAGO]: Supongo que te estaras preguntando que esta pasando aqui, porque de la noche a la madrugada salieron estas \nabominables bestias?!\n");
        saltoLinea();
    printw("\n[MAGO]: Veras, todo esto sucedio por culpa de los malvados cientificos: Ceron e Inclan.\n");
        saltoLinea();
    printw("\n[MAGO]: Estaban obsesionados con la creacion de una maquina de cafe infinita\n");
        saltoLinea();
    printw("\n[MAGO]: Pero terminaron abriendo las puertas a uno de los mayores males de este universo!\n");
        saltoLinea();
    printw("\n[MAGO]: Sin embargo, joven padawan, sientete orgulloso ya que tus habilidades y destrezas han hecho que la asociacion \nde magos te haya seleccionado "
         "para ser el encargado de salvar este planeta de las garras de los invasores de otro mundo!");
        saltoLinea();
    printw("\n[MAGO]: Y porque todos nuestros mejores candidatos ya estan muertos.\n");
        saltoLinea();
    printw("\n[MAGO] Como sea humano, estas dispuesto a arriesgar tu vida para proteger a este planeta?\n");
        refresh();
    int n_opciones = 2;
    ITEM **decisiones =  calloc(n_opciones + 1, sizeof(ITEM *));
        for (int i = 0; i < n_opciones; i++) {
            decisiones[i] = new_item(elecciones1[i], "");
        }
        decisiones[n_opciones] = (ITEM *)NULL;
        MENU *menu = new_menu(decisiones);
        WINDOW *ventanaMenu1 = newwin(2, 40, 18, 0);
        keypad(ventanaMenu1, TRUE);
        set_menu_win(menu, ventanaMenu1);
        set_menu_mark(menu, " > ");
        set_menu_sub(menu, derwin(ventanaMenu1, 2, 40, 0, 0));
            refresh();
            post_menu(menu);
            wrefresh(ventanaMenu1);
    while (1){
        c = getch();
        switch (c) {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                wrefresh(ventanaMenu1);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                wrefresh(ventanaMenu1);
                break;
            case 10:
                if(strcmp(item_name(current_item(menu)), "Aceptar encomienda del Mago")==0) {
                    liberarMemoria1(n_opciones, decisiones, menu, ventanaMenu1);
                    printw("\n[MAGO]: Admiro tu valentia y dedicacion en esta cruzada, la verdad es que nadie espera que sobrevivas.\n");
                        saltoLinea();
                    printw("\n[MAGO]: Pero no te preocupes, yo sere tu guia.\n");
                        saltoLinea();
                        nombreYclase(ptr_nombre, ptr_warrior, ptr_wizard);
                    return;
                }
                else if(strcmp(item_name(current_item(menu)), "Rechazar encomienda del Mago")==0) {
                    liberarMemoria1(n_opciones, decisiones, menu, ventanaMenu1);
                    printw("\n[MAGO]: Realmente no tenias otra opcion, los demas magos ya decidieron que tu seras el proximo "
                         "salvador de la humanidad.No te preocupes, nadie tiene fe de que sobreviviras.\n");
                        saltoLinea();
                        nombreYclase(ptr_nombre, ptr_warrior, ptr_wizard);
                    return;
                }
                default:
                break;
            }
        }
    }
void nombreYclase(char *ptr_nombre, bool *ptr_warrior, bool *ptr_wizard) {
    echo();
    nocbreak();
    keypad(stdscr, FALSE);
    clear();
    printw("[MAGO]: Pero antes de comenzar esta travesia contigo, cuentame, cual quieres que sea el nombre que escribamos\nen tu tumba? (Escribe tu nombre)\n");
    int s=3;
        while (s>=0){
            getnstr(ptr_nombre, 29);
            int a=0, n=0;
            if (ptr_nombre[0] == ' ' || ptr_nombre[0] == '\0') { //Se validan errores iniciales del usuario
                if (ptr_nombre[0]=='\0'){ //El usuario dio enter
                    printw("[MAGO]: Acaso no tienes nombre? Ingresa algo!\n");
                    refresh();
                    s--;
                    magoEnojado(s);
                }
                else{ //El usuario ingreso un espacio en la primera posicion
                    printw("\n[MAGO]: Por las barbas de Merlin! Como es posible que tu nombre empiece con espacio!!!\n(Vuelve a ingresar tu nombre)\n");
                    refresh();
                    s--;
                    magoEnojado(s);
                }
            }
            else {
                while (ptr_nombre[a]!='\0') {
                    int b = (int)ptr_nombre[a]; //Se obtiene el valor en ASCII de cada caracter ingresado
                        if ((b>=65 && b<=90) || (b>=97 && b<=122) || b==32){ //Solo se permiten mayusculas, minusculas y los espacios DESPUES de la primera posicion
                        }
                        else {
                            n++;
                        }
                    a++;
                }
                if (n>0) {
                        printw("\n[MAGO]: Lo siento, al tipo con ese nombre lo mataron la semana pasada.\n(Tu nombre tiene uno o varios caracteres ilegales!)\n"
                               "Vuelve a ingresar otro nombre.\n");
                        refresh();
                        s--;
                        magoEnojado(s);
                    }
                else if (n==0){
                    noecho();
                    printw("\n[MAGO]: Mi sangre es tu sangre %s, la humanidad te recordara por mil siglos!", ptr_nombre);
                        saltoLinea();
                    break;
                }
            }
        }
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    clear();
    printw("[MAGO]: Ahora dime %s, que profesion te gustaria ser?\n", ptr_nombre);
    refresh();
    //Creamos otro menu para esta decision
    int n_opciones = 2;
    ITEM **decisiones2 =  calloc(n_opciones + 1, sizeof(ITEM *));
    for (int i = 0; i < n_opciones; i++) {
        decisiones2[i] = new_item(elecciones2[i], "");
    }
    decisiones2[n_opciones] = (ITEM *)NULL;
    MENU *menu2 = new_menu(decisiones2);
    WINDOW *ventanaMenu2 = newwin(2, 40, 2, 0);
    set_menu_win(menu2, ventanaMenu2);
    set_menu_mark(menu2, " > ");
    set_menu_sub(menu2, derwin(ventanaMenu2, 2, 40, 0, 0));
    refresh();
    post_menu(menu2);
    wrefresh(ventanaMenu2);
    while (1) {
        int c = getch();
        switch (c) {
            case KEY_DOWN:
                menu_driver(menu2, REQ_DOWN_ITEM);
                wrefresh(ventanaMenu2);
                break;
            case KEY_UP:
                menu_driver(menu2, REQ_UP_ITEM);
                wrefresh(ventanaMenu2);
                break;
            case 10:
                if (strcmp(item_name(current_item(menu2)), "Mago")==0){
                    liberarMemoria1(n_opciones, decisiones2, menu2, ventanaMenu2);
                    //*ptr_wizard = TRUE;
                    printw("\n[MAGO]: No le hagas caso a la estadistica \n");
                        saltoLinea();
                    printw("\n[MAGO]: Los ultimos 20 discipulos que tuve se murieron.\n");
                        saltoLinea();
                    printw("\n[MAGO]: No es para desalentarte\n");
                        saltoLinea();
                    printw("\n[MAGO]: Anyways, es hora de forjarte un nombre...\n");
                        saltoLinea();
                        clear();
                    printw("[MAGO]: Espera.... \n");
                        saltoLinea();
                    printw("\n[MAGO]: Me comentan mis superiores que Diego aun no implementa las mecanicas del Mago!\n");
                        saltoLinea();
                    printw("\n[MAGO]: Que barbaridad! Que opinara Yuliana de esto!");
                        saltoLinea();
                    printw("\n[MAGO]: Te voy a asignar la profesion de Guerrero");
                    *ptr_warrior = TRUE;
                        saltoLinea();
                        clear();
                    tituloArte();
                        saltoLinea();
                    return;
                }
                else if (strcmp(item_name(current_item(menu2)), "Guerrero")==0){
                    *ptr_warrior = TRUE;
                    liberarMemoria1(n_opciones, decisiones2, menu2, ventanaMenu2);
                    printw("\n[MAGO]: Ush, barbaros que solo les gusta golpear todo\n");
                        saltoLinea();
                    printw("\n[MAGO]: No entiendo como hay gente que prefiere esa profesion\n");
                        saltoLinea();
                    printw("\n[MAGO]: Pero con esa mini espada que tienes, creo que te ira bien...\n");
                        saltoLinea();
                        clear();
                    tituloArte();
                        saltoLinea();
                    return;
                }
                default:
                break;
        }

    }
}
void magoEnojado(int s) {
    if (s==0) {
        noecho();
        cbreak();
        printw("\nSi no eres capaz de acatar esta instruccion\nNo sirves para salvar al mundo.\nEnter para salir del juego.");
            saltoLinea();
        endwin();
        exit(0);
    }
}

void comerciante_1(char *ptr_nombre, int *ptr_money){
    clear();
    printw("[MAGO]: Es hora de equiparte, %s\n", ptr_nombre);
        saltoLinea();
    printw("\n[MAGO]: A diferencia de cierto presidente que goberno con abrazos y no balazos, para derrotar a los enemigos no son\nsuficientes los abrazos\n");
        saltoLinea();
    printw("\n[MAGO]: Te presento al comerciante Marin, el se encargara de traerte los mejores items\n");
        saltoLinea();
    printw("\n[MAGO]: Sin embargo el no es comunista, tienes que pagarle cierta cantidad de dinero para obtener lo que quieras\n");
        saltoLinea();
    printw("\n[MAGO CAPITALISTA]: Larga vida al capitalismo!\n");
        saltoLinea();
    printw("\n[MAGO]: Como veo que no tienes ni donde caerte muerto, te voy a prestar dinero...\n");
        saltoLinea();
    printw("El mago te entrega %i monedas\n", *ptr_money);
        saltoLinea();
    printw("\n[MAGO]: Ya no te interrumpo mas, compra lo que consideres optimo y bonito para decorar tu tumba.\n");
        saltoLinea();
        clear();
}
void dialogosComerciante(int a) {
    if (a==0) {
        mvprintw(5, 4,"Yo:");
        mvprintw(6, 1,"Darth Marin soy");
        mvprintw(7, 1,"tu comerciante...");
    }
    else if (a==1) {
        mvprintw(4, 2,"Hmmm");
        mvprintw(5, 2,"No te gustaria");
        mvprintw(6, 2,"pasarte");
        mvprintw(7, 2,"al lado");
        mvprintw(8, 2,"Oscuro?");
    }
    else if (a==2){
        mvprintw(4, 2,"Me sorprende");
        mvprintw(5,2, "que sigas");
        mvprintw(6, 2,"vivo...");
    }
    else if (a==3) {
        mvprintw(4, 1,"Pronto");
        mvprintw(5,1, "Darth Woo");
        mvprintw(6, 1,"reclamara");
        mvprintw(7, 1,"lo que a las");
        mvprintw(8, 1,"Ras-Cas les");
        mvprintw(9, 1,"pertenece!");
    }
}
void restaurar_borde(WINDOW *ventana_1) {
    wclear(ventana_1);
    wrefresh(ventana_1);
    box(ventana_1,0,0);
    wrefresh(ventana_1);
}
void escena(int i) {
clear(); //Se limpia lo que sea que haya en la pantalla
WINDOW *ventana_1;
char *ptr_nombre = Player.name;
    if (i==0) { //Aparicion de bruto
        char *boss_name = jefes_inicialesFinales[i].name;
    printw("Una vez concluyes tu proceso de compra con el comerciante, sales de tu departamento....\n");
        saltoLinea();
    printw("\n[MAGO]: No tenemos tiempo que perder, %s.\n", ptr_nombre);
        saltoLinea();
    printw("\nMiras a tu alrededor y ves muchos monstruos en tu cuadra\n");
        saltoLinea();
    printw("\nSin embargo..... todos estan amarrados a un poste?\n");
        saltoLinea();
    printw("\nSe te olvida que vives en la pochota y aqui los que estan en peligro son los monstruos\n");
        saltoLinea();
    printw("\nPasando por la papeleria Lupe, escuchas un destrozos\n");
        saltoLinea();
    printw("\nEl mago y tu, desconsertados se asoman a ver que ocurre\n");
        saltoLinea();
    printw("\n[??????]: RAAAAAAAAAA\n");
        saltoLinea();
    printw("\nEs como si una bestia estuviera dentro!\n");
        saltoLinea();
    printw("\n[MAGO]: SAL DE AHI ESPANTOSA CRIATURA!\n");
        saltoLinea();
    printw("\n[MAGO]: Mi aprendiz con lustros de entrenamiento de mi parte, no te tiene miedo\n");
        saltoLinea();
    printw("\n>No conoces al Mago por mas de 10 minutos\n");
        saltoLinea();
    printw("\nEscuchas pasos salir de la papeleria.....\n");
        saltoLinea();
    printw("\nEntonces, ves a un monstruo de 3 metros salir de ahi");
        saltoLinea();
        clear();
    arteJefes(i); //Se muestra el arte de Bruto
        ventana_1 = newwin(8, 80, 23, 25); //Se crea nuestra ventana
        box(ventana_1,0,0);
    mvwprintw(ventana_1,1,2,"[???]: Yo ser %s!!!", boss_name);
        saltoLineaWin(ventana_1);
    mvwprintw(ventana_1, 2, 2, "[%s]: Y YO QUERER NOBEL DE LA LITERATURA", boss_name);
        saltoLineaWin(ventana_1);
    mvwprintw(ventana_1,3,2, "[MAGO]: Y que haces en una papeleria?");
        saltoLineaWin(ventana_1);
    mvwprintw(ventana_1, 4, 2, "[%s]: lapiz necesitar", boss_name);
        saltoLineaWin(ventana_1);
    mvwprintw(ventana_1, 5, 2, "[%s]: Escribir historias romance adolecente", boss_name);
        saltoLineaWin(ventana_1);
        restaurar_borde(ventana_1);
    mvwprintw(ventana_1, 1, 2, "[MAGO]: Es hora de que me muestres que es lo que tienes");
        saltoLineaWin(ventana_1);
    mvwprintw(ventana_1, 2, 2, "[MAGO]: %s, es hora de que pelees contra este papanatas!", ptr_nombre);
        saltoLineaWin(ventana_1);
        restaurar_borde(ventana_1);
    mvwprintw(ventana_1, 3, 2, "\t%s se prepara para pelear!!", boss_name);
        saltoLineaWin(ventana_1);
        delwin(ventana_1);
        clear();
    }
    else if (i == 1) { //Aparicion de Gladio
        char *boss_name = jefes_inicialesFinales[i].name;
    printw("Ese comerciante cada vez es mas carero, es lo unico que puedes pensar\n");
        saltoLinea();
    printw("\nSaliendo ves a un hombre muy apuesto y valiente mostrando sus musculos\n");
        saltoLinea();
    printw("\nEsta intentando ligar con unas mujeres cerca\n");
        saltoLinea();
    printw("\n[???]: Entonces mami, te recuerdo que mi unico mundo soy yo, entiende tu lugar nena\n");
        saltoLinea();
    printw("\n[???]: A veces me gustaria ir a la luna solo para ver como es el mundo sin mi\n");
        saltoLinea();
    printw("\n[???]: No te preocupes chiquilla, hombres perfectos solo existimos uno\n");
        saltoLinea();
    printw("\nAl juzgar por la reaccion de las mujeres, te das cuenta que ligar no es su fuerte\n");
        saltoLinea();
    printw("\n[MAGO]: Por las barbas de Merlin! Con esa labia espantas hasta a mi abuela sorda!\n");
        saltoLinea();
    printw("\nHay un momento de silencio incomodo... Las mujeres aprovecharon esto para irse del lugar\n");
        saltoLinea();
    printw("\n[???]: Acaso noto a alguien inferior dirigiendole la palabra a la maxima encarnacion de la perfeccion?\n");
        saltoLinea();
    printw("\n[???]: Por si no sabias maldito anciano, mi nombre es %s\n", boss_name);
        saltoLinea();
    printw("\n[%s]: Y ahora estoy muy enfadado porque espantaste a mis mujeres\n", boss_name);
        saltoLinea();
    printw("\n[MAGO]: Y a mi me importa un bledo lo que pienses!\n");
        saltoLinea();
        clear();
        ventana_1 = newwin(8, 80, 23, 25);
        box(ventana_1,0,0);
        arteJefes(i);
    mvwprintw(ventana_1,1,2, "[MAGO]: Porque junto a mi esta mi discipulo mejor entrenado!" );
        saltoLineaWin(ventana_1);
    mvwprintw(ventana_1, 2,2, "[MAGO]: Y el no dudara ni un segundo en defenderme");
        saltoLineaWin(ventana_1);
    mvwprintw(ventana_1,3,2, "[MAGO]: Y si escucharas lo que el dijo de ti...");
        saltoLineaWin(ventana_1);
        restaurar_borde(ventana_1);
    mvwprintw(ventana_1, 1, 2, "Intentas explicarle la situacion a %s", boss_name);
        saltoLineaWin(ventana_1);
    mvwprintw(ventana_1,2,2, "Pero ya es muy tarde, ahora la trae contra ti!");
        saltoLineaWin(ventana_1);
        restaurar_borde(ventana_1);
    mvwprintw(ventana_1, 1,2,"[%s]: Dejame adivinar...", boss_name);
        saltoLineaWin(ventana_1);
    mvwprintw(ventana_1, 2, 2, "[%s]: Tu nombre es %s, no?", boss_name, ptr_nombre);
        saltoLineaWin(ventana_1);
    mvwprintw(ventana_1, 3, 2, "[%s]: Lo sabia, nunca me equivoco", boss_name);
        saltoLineaWin(ventana_1);
    mvwprintw(ventana_1, 4, 2, "[%s]: Lo intuia porque es nombre de incompetente", boss_name);
        saltoLineaWin(ventana_1);
        restaurar_borde(ventana_1);
    mvwprintw(ventana_1, 1, 2, "[%s]: Preparate a morir %s", boss_name, ptr_nombre);
        saltoLineaWin(ventana_1);
    mvwprintw(ventana_1, 2, 2, "[%s]: A manos de la perfeccion encarnada.", boss_name);
        saltoLineaWin(ventana_1);
        restaurar_borde(ventana_1);
    mvwprintw(ventana_1, 3, 2, "\t%s se prepara para pelear!", boss_name);
        saltoLineaWin(ventana_1);
        delwin(ventana_1);
        clear();
    }
    else if (i == 2) {  //Aparicion de las Verossa's
        printw("Afortunadamente el comerciante Marin puso su puesto en plaza Americas\n");
            saltoLinea();
        printw("\nTe estabas cansando de tener que ir a la facultad de ingenieria en el lab de robotica\n");
            saltoLinea();
        printw("\nSin embargo, cuando te disponias a salir escuchas una discusion entre mujeres\n");
            saltoLinea();
        printw("\n[Mujeres]: *discusion con tono de pelea*\n");
            saltoLinea();
        printw("\n[MAGO]: Ciertamente esto es muy comun\n");
            saltoLinea();
        printw("\n[MAGO MACHISTA]: En lo personal considero que las mujeres deberian estar en ----\n");
            saltoLinea();
        printw("\nAntes de que el Mago fuera a soltar una frase digna de cancelacion de este proyecto...\n");
            saltoLinea();
        printw("\nUna explosion sacude Plaza Americas!\n");
            saltoLinea();
        printw("\n[MUJER 1]: TE DIJE UN MILLON DE VECES, QUE CON MI DINERO NO TE METES\n"); //Mariana habla
            saltoLinea();
        printw("\n[MUJER 2]: Ara Ara, дорогой, pense que al ser hermanas podiamos compartir\n"); //Sveta habla
            saltoLinea();
        printw("\n[MUJER 1] COMPARTIR UNA #$@$!@ QUERIA PEDIR UN VESTIDO EN TEMU\n");
            saltoLinea();
        printw("\n[MUJER 3]: P-por f-f-favor no peleen h-hermanitas\n");
            saltoLinea();
        printw("\n[MUJER 1 Y 2]: SILENCIO AMANDA!\n");
            saltoLinea();
        printw("\n[%s]: >.<\n", jefe3_verossaSisters.name[2]);
            saltoLinea();
        printw("\n[MAGO]: A ver bola de escandalosas, nos vamos relajando todos, no se si escucharon\n");
            saltoLinea();
        printw("\n[MAGO]: Pero hubo una explosion en este centro comercial y todos estan evacuando\n");
            saltoLinea();
            clear();
        printw("[MUJER 1, 2 Y %s]: ...\n", jefe3_verossaSisters.name[2]);
            saltoLinea();
        printw("\nLas 3 mujeres miran desconcertadas al Mago\n");
            saltoLinea();
        printw("\n[MUJER 1]: Vuelve a tu asilo viejo ridiculo!\n");
            saltoLinea();
        printw("\nIntentas intevernir pero notas algo raro en ellas....\n");
            saltoLinea();
        printw("\nNo lucen como mujeres normales....\n");
            saltoLinea();
        printw("\nTienen colas demoniacas!\n");
            saltoLinea();
        printw("\nTe das cuenta, que la explosion de hace unos segundos....\n");
            saltoLinea();
        printw("\n[MAGO]: No te atrevas a hablarle asi al Mago!\n");
            saltoLinea();
        printw("\nEl Mago y la mujer 1 comienzan a discutir\n");
            saltoLinea();
        printw("\nIntentas avisarle al Mago de que son una amenaza demoniaca, pero el Mago dice:\n");
            saltoLinea();
        printw("\n[MAGO]: Y que si soy un anciano! En mis tiempos ustedes eran menos escandalosas!\n");
            saltoLinea();
        printw("\n.");
            saltoLinea();
        printw(".");
            saltoLinea();
        printw("."); //Sin salto de linea en los dos puntos, se logra efecto de 3 puntos suspensivos
            saltoLinea();
        printw("\n\t...Una segunda explosion sacude el centro comercial...\n");
            clear();
        ventana_1 = newwin(8, 80, 23, 25);
        box(ventana_1,0,0);
        arteJefes(i);
        mvwprintw(ventana_1, 1, 2, "[Mujer 1]: Mira anciano ridiculo");
            saltoLineaWin(ventana_1);
        mvwprintw(ventana_1, 2, 2, "[Mujer 2]: Si hay algo que nos molesta");
            saltoLineaWin(ventana_1);
        mvwprintw(ventana_1, 3, 2, "[%s]: %s, %s, por favor no, ya me quiero ir", jefe3_verossaSisters.name[2], jefe3_verossaSisters.name[1], jefe3_verossaSisters.name[0]);
            saltoLineaWin(ventana_1);
        mvwprintw(ventana_1, 4, 2, "[%s y %s]: Es que la UV cancele clases por todo", jefe3_verossaSisters.name[1], jefe3_verossaSisters.name[0]);
            saltoLineaWin(ventana_1);
            restaurar_borde(ventana_1);
        mvwprintw(ventana_1, 1, 2, "[%s]: Pero si hay algo que nos molesta aun mas!", jefe3_verossaSisters.name[1]);
            saltoLineaWin(ventana_1);
        mvwprintw(ventana_1, 2, 2, "[%s]: Es escuchar a un anciano machista!", jefe3_verossaSisters.name[0]);
            saltoLineaWin(ventana_1);
        mvwprintw(ventana_1, 3, 2, "[MAGO]: Yo no dije nada, fue el!");
            saltoLineaWin(ventana_1);
        mvwprintw(ventana_1, 4, 2, "El mago te apunta con su dedo");
            saltoLineaWin(ventana_1);
        mvwprintw(ventana_1, 5, 2, "Las Verossa's te voltean a ver!");
            saltoLineaWin(ventana_1);
            restaurar_borde(ventana_1);
        mvwprintw(ventana_1, 1, 2, "A veces te preguntas: Por que siempre yo?");
            saltoLineaWin(ventana_1);
            restaurar_borde(ventana_1);
        mvwprintw(ventana_1, 1, 2, "Las Verossa's se preparan para atacarte!");
            saltoLineaWin(ventana_1);
        delwin(ventana_1);
        clear();
    }
    else if (i == 3) {  //Aparicion de Parca
        printw("[MAGO]: Joven Padawan, te tengo muy buenas noticias!\n");
            saltoLinea();
        printw("\nDespues de haber tenido que combatir contra una roca con patas, un narcisista...\n");
            saltoLinea();
        printw("\nY tener el rabo pelado por culpa de las Verossas\n");
            saltoLinea();
        printw("\nSolo deseas que el mago te diga que ya te puedes tomar un descanso\n");
            saltoLinea();
        printw("\n[MAGO]: La federacion de Cafes ha multado al doc ceron y al profe Inclan\n");
            saltoLinea();
        printw("\nTu vida es una tragicomedia.\n");
            saltoLinea();
        printw("\nMientras vas caminando en la calle notas que los animales corren en direccion opuesta a ti\n");
            saltoLinea();
        printw("\nNotas que los colores comienzan a desvanecerse en el paisaje\n");
            saltoLinea();
        printw("\nEscuchan un grito a lo lejos.... Pero no es de un animal o persona\n");
            saltoLinea();
        printw("\nEs de algo que no se puede considerar si quiera un ser vivo/demoniaco\n");
            saltoLinea();
        printw("\nA lo lejos logras apreciar una figura espantosa\n");
            saltoLinea();
            clear();
        printw("\nUn espantapajaros posa mirandote a ti\n");
            saltoLinea();
        printw("\nAntes de que te de tiempo de procesar que esta sucediendo, todo se oscurece\n");
            saltoLinea();
        printw("\nNo puedes ver ni siquiera la palma de tu mano\n");
            saltoLinea();
        printw("\n[MAGO]: Quien cojones apago la luz!?\n");
            saltoLinea();
        printw("\nLas luces vuelven a su estado normal, y sabes, que lo que sea que hayas visto....\n");
            saltoLinea();
        printw("\nEsta justo detras de ti.\n");
            saltoLinea();
            clear();
        ventana_1 = newwin(8, 80, 23, 25);
        box(ventana_1,0,0);
        arteJefes(i);
        mvwprintw(ventana_1, 1, 2, "[MAGO]: Ahora lo entiendo");
            saltoLineaWin(ventana_1);
        mvwprintw(ventana_1, 2,2, "[MAGO]: Hemos llamado la atencion de la parca.");
            saltoLineaWin(ventana_1);
        mvwprintw(ventana_1, 4, 2, "4375616e646f2044696f73206d652076696f2c2061706172746f206c61206d6972616461");
            saltoLineaWin(ventana_1);
            restaurar_borde(ventana_1);
        mvwprintw(ventana_1, 1, 2, "%s se prepara para atacarte!", jefes_inicialesFinales[i-1].name);
            saltoLineaWin(ventana_1);
            delwin(ventana_1);
        clear();
    }
}
void dialogo_ataque_recibido(int indice_jefe, int ataque_recibido, int indice_Verossa) {
    wclear(ventana); //Se limpia contenido de la ventana (incluyendo el borde)
    wrefresh(ventana); //Se actualizan cambios
    box(ventana,0,0); //Se crea el borde pero aun NO se muestra
    int numero;
    numero = rand()% 2; //Se genera un numero entre 0 y 1
    if (indice_jefe ==0 ) {//DIalogos para bruto
        if (numero ==0) { //Dialogo 1
            mvwprintw(ventana, 2, 1, "[%s]: Golpear %s", jefes_inicialesFinales[indice_jefe].name, jefes_inicialesFinales[indice_jefe].name);
            mvwprintw(ventana, 3, 1, "[%s]: Espera Bruto no lastimarte, %s", jefes_inicialesFinales[indice_jefe].name,Player.name);
            mvwprintw(ventana, 4, 1, "%s te ataca y pierdes %i puntos de vida!", jefes_inicialesFinales[indice_jefe].name, ataque_recibido);
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
        }else {
            mvwprintw(ventana, 2, 1, "[%s]: %s preguntarse...", jefes_inicialesFinales[indice_jefe].name, jefes_inicialesFinales[indice_jefe].name);
            mvwprintw(ventana, 3, 1, "[%s]: Si nobel de la literatura tendra", jefes_inicialesFinales[indice_jefe].name);
            mvwprintw(ventana, 4, 1, "Esas palabras tristes de %s te hacen perder %i puntos de vida", jefes_inicialesFinales[indice_jefe].name, ataque_recibido);
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
        }
    }
    else if (indice_jefe ==1) { //Dialogos para Gladio
        if (numero == 1) {
            mvwprintw(ventana, 2, 1, "[%s]: Observa mi perfeccion!", jefes_inicialesFinales[indice_jefe].name);
            mvwprintw(ventana, 3, 1, "[%s]: Solo no quieras replicarme", jefes_inicialesFinales[indice_jefe].name);
            mvwprintw(ventana, 4, 1, "%s te ataca y pierdes %i puntos de vida!", jefes_inicialesFinales[indice_jefe].name, ataque_recibido);
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
        }else {
            mvwprintw(ventana, 2, 1, "[%s]: Acaso veo envidia en tus ojos?!", jefes_inicialesFinales[indice_jefe].name);
            mvwprintw(ventana, 4, 1, "%s te ataca y pierdes %i puntos de vida!", jefes_inicialesFinales[indice_jefe].name, ataque_recibido);
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
        }
    }
    else if (indice_jefe==2) { //Dialogos para las 2 primeras Verossas
        if (indice_Verossa == 0) {
            if (numero == 1) {
                mvwprintw(ventana, 2, 1, "[%s]: Puedes correr mi cielito", jefe3_verossaSisters.name[indice_Verossa]);
                mvwprintw(ventana, 3, 1, "[%s]: Pero yo te encontrare siempre <3", jefe3_verossaSisters.name[indice_Verossa]);
                mvwprintw(ventana, 4, 1, "%s te ataca y pierdes %i puntos de vida!", jefe3_verossaSisters.name[indice_Verossa], ataque_recibido);
                mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
            }else {
                mvwprintw(ventana, 2, 1, "[%s]: Siento que de seguir asi", jefe3_verossaSisters.name[indice_Verossa]);
                mvwprintw(ventana, 3, 1, "[%s]: Me quedare sin mi cielito", jefe3_verossaSisters.name[indice_Verossa]);
                mvwprintw(ventana, 4, 1, "%s te ataca y pierdes %i puntos de vida!", jefe3_verossaSisters.name[indice_Verossa], ataque_recibido);
                mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
            }
        }else{
            if (numero ==1) {
                mvwprintw(ventana, 2, 1, "[%s]: Soy mucha mujer para ti, loser", jefe3_verossaSisters.name[indice_Verossa]);
                mvwprintw(ventana, 3, 1, "[%s]: Deberias alabarme", jefe3_verossaSisters.name[indice_Verossa]);
                mvwprintw(ventana, 4, 1, "%s te ataca y pierdes %i puntos de vida!", jefe3_verossaSisters.name[indice_Verossa], ataque_recibido);
                mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
            }else {
                mvwprintw(ventana, 2, 1, "[%s]: Aqui esta mi instagram: _velssa", jefe3_verossaSisters.name[indice_Verossa]);
                mvwprintw(ventana, 3, 1, "[%s]: Acabando contigo quiero que me agregues", jefe3_verossaSisters.name[indice_Verossa]);
                mvwprintw(ventana, 4, 1, "%s te ataca y pierdes %i puntos de vida!", jefe3_verossaSisters.name[indice_Verossa], ataque_recibido);
                mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
            }
        }
    }
    else if (indice_jefe==3) { //Dialogos para la parca
        if (numero ==1) {
            mvwprintw(ventana, 2, 1, "[%s]: 321983129082903890218903891208", jefes_inicialesFinales[indice_jefe-1].name); //Se soluciona el error del desfase
            mvwprintw(ventana, 3, 1, "[MAGO]: Ni siquiera yo entiendo que es lo que trata de decir");
            mvwprintw(ventana, 4, 1, "%s te ataca y pierdes %i puntos de vida!", jefes_inicialesFinales[indice_jefe-1].name, ataque_recibido);
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
        }else {
            mvwprintw(ventana, 2, 1, "[%s]: Sufr1m13nt0...... m10", jefes_inicialesFinales[indice_jefe-1].name); //Se soluciona el error del desfase
            mvwprintw(ventana, 3, 1, "[%s]: po123r f123avor ac123ab1123r", jefes_inicialesFinales[indice_jefe-1].name);
            mvwprintw(ventana, 4, 1, "%s te ataca y pierdes %i puntos de vida!", jefes_inicialesFinales[indice_jefe-1].name, ataque_recibido);
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
        }
    }
    else if (indice_jefe==4) { //Dialogos para Morte
        if (numero ==1) {
            mvwprintw(ventana, 2, 1, "[%s]: ...............", jefes_inicialesFinales[indice_jefe-1].name); //Se soluciona el error del desfase
            mvwprintw(ventana, 3, 1, "\tSangre");
            mvwprintw(ventana, 4, 1, "%s te ataca y pierdes %i puntos de vida!", jefes_inicialesFinales[indice_jefe-1].name, ataque_recibido);
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
        }else {
            mvwprintw(ventana, 2, 1, "[%s]: ....................", jefes_inicialesFinales[indice_jefe-1].name); //Se soluciona el error del desfase
            mvwprintw(ventana, 3, 1, "[%s]: ..........................", jefes_inicialesFinales[indice_jefe-1].name);
            mvwprintw(ventana, 4, 1, "%s te ..... y ..... %i ....... vida!", jefes_inicialesFinales[indice_jefe-1].name, ataque_recibido);
            mvwprintw(ventana, 6, 1, "Presiona Enter para MORIR!");
        }
    }
    else if (indice_jefe==5) { //Dialogos para la Diosa Estelar Iris
        if (numero ==1) {
            mvwprintw(ventana, 2, 1, "[%s]: Por favor entiende", jefes_inicialesFinales[indice_jefe-1].name); //Se soluciona el error del desfase
            mvwprintw(ventana, 3, 1, "[%s]: No me puedes ganar.", jefes_inicialesFinales[indice_jefe-1].name);
            mvwprintw(ventana, 4, 1, "%s te ataca y pierdes %i puntos de vida!", jefes_inicialesFinales[indice_jefe-1].name, ataque_recibido);
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
        }else {
            mvwprintw(ventana, 2, 1, "[%s]: Eres un digno adversario", jefes_inicialesFinales[indice_jefe-1].name); //Se soluciona el error del desfase
            mvwprintw(ventana, 3, 1, "[%s]: Tal vez tenga piedad cuando mueras", jefes_inicialesFinales[indice_jefe-1].name);
            mvwprintw(ventana, 4, 1, "%s te ataca y pierdes %i puntos de vida!", jefes_inicialesFinales[indice_jefe-1].name, ataque_recibido);
            mvwprintw(ventana, 6, 1, "Presiona Enter para seguir las ordenes de su realeza!");
        }
    }
    wrefresh(ventana); //Muestra los mvwprintw junto con el borde
        saltoLineaWin(ventana);
}
void dialogos_defensa(int indice_jefe, int ataque_reducido, int indice_Verossa){
    if (indice_jefe==0){ //Dialogo de Bruto

    }
    else if (indice_jefe==1){//Reaccion de Gladio

    }
    else if (indice_jefe==2){//Reaccion de las Verossa's

    }
    else if (indice_jefe==3) {//Reaccion de Parca

    }
    else if (indice_jefe==4) {//Reaccion de Morte

    }
    else if (indice_jefe==5) {//Reaccion de Iris

    }
}
void dialogos_evasion(int indice_jefe, int ataque_evadido, int indice_Verossa) {
    wclear(ventana); //Se limpia contenido de la ventana (incluyendo el borde)
        wrefresh(ventana); //Se actualizan cambios
        box(ventana,0,0); //Se crea el borde pero aun NO se muestra
    if (ataque_evadido > 0) { //Condicional que evalua si el usuario NO logro evadir el ataque
        if (indice_jefe==0){ //Dialogo de Bruto
            mvwprintw(ventana, 2, 1, "[%s]: Brutooo.... confundido?", jefes_inicialesFinales[indice_jefe].name);
            mvwprintw(ventana, 3, 1, "[%s]: Preguntarse Bruto.... que quiso %s hacer", jefes_inicialesFinales[indice_jefe].name,Player.name);
            mvwprintw(ventana, 4, 1, "Fallaste la evasion!  Perdiste %i puntos de vida", ataque_evadido);
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
                wrefresh(ventana); //Muestra los mvwprintw junto con el borde
                saltoLineaWin(ventana);
        }
        else if (indice_jefe==1){//Reaccion de Gladio
            mvwprintw(ventana, 2, 1, "[%s]: Intentabas esquivarme? Por favor… yo mismo podria enseñarte como se hace.",jefes_inicialesFinales[indice_jefe].name);
            mvwprintw(ventana, 3, 1, "[%s]: Entiende, la perfeccion --yo-- no falla, tu en cambio, si", jefes_inicialesFinales[indice_jefe].name);
            mvwprintw(ventana, 4, 1, "Fallaste la evasion!  Perdiste %i puntos de vida", ataque_evadido);
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
                wrefresh(ventana);
                saltoLineaWin(ventana);
        }
        else if (indice_jefe==2){//Reaccion de las Verossa's
            if (indice_Verossa == 0) { //Reaccion de Dasha
                mvwprintw(ventana, 2, 1, "[%s]: Que tierno cuchurrumi, pero tendras que ser mas rapido", jefe3_verossaSisters.name[indice_Verossa]);
                mvwprintw(ventana, 3, 1, "[%s]: Si quieres escapar de mi, jejeje", jefe3_verossaSisters.name[indice_Verossa]);
                mvwprintw(ventana, 4, 1, "[%s] Oye tu, DEJA DE ANDAR DE INTENSA!", jefe3_verossaSisters.name[1]); //Habla Sveta
                mvwprintw(ventana, 5, 1, "[%s]: Venga chicas, no peleen >.<", jefe3_verossaSisters.name[2]); //Habla Amanda
                mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
                    wrefresh(ventana);
                    saltoLineaWin(ventana);
                wclear(ventana);
                mvwprintw(ventana, 3, 1, "Fallaste la evasion! Recibiste %i", ataque_evadido);
                mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
                    wrefresh(ventana);
                    saltoLineaWin(ventana);
            }else {//Reaccion de Sveta
                mvwprintw(ventana, 2, 1, "[%s]: JA!, todos los hombres fallan ante mis encantos!", jefe3_verossaSisters.name[indice_Verossa]);
                mvwprintw(ventana, 3, 1, "[%s]: Es el precio de ser hermosa, pocas lo entienden", jefe3_verossaSisters.name[indice_Verossa]);
                mvwprintw(ventana, 4, 1, "Fallaste la evasion!  Perdiste %i puntos de vida", ataque_evadido);
                mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
                    wrefresh(ventana);
                    saltoLineaWin(ventana);
            }
        }
        else if (indice_jefe==3) {//Reaccion de Parca
            mvwprintw(ventana, 2, 1, "[%s]: JU82RJDA;DN128P9DHQ8FH8EWHDFN32OMFDEOWFJ238P2NU", jefes_inicialesFinales[indice_jefe-1].name);
            mvwprintw(ventana, 3, 1, "[%s]: ...", jefes_inicialesFinales[indice_jefe-1].name);
            mvwprintw(ventana, 4, 1, "Fallaste la evasion!  Perdiste %i puntos de vida", ataque_evadido);
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
                wrefresh(ventana);
                saltoLineaWin(ventana);
        }
        else if (indice_jefe==4) {//Reaccion de Morte
            mvwprintw(ventana, 2, 1, "[%s]: ........", jefes_inicialesFinales[indice_jefe-1].name);
            mvwprintw(ventana, 3, 1, "Sientes la presencia de Morte observarte con detenimiento...");
            mvwprintw(ventana, 4, 1, "Fallaste la evasion!  Perdiste %i puntos de vida", ataque_evadido);
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
                wrefresh(ventana);
                saltoLineaWin(ventana);
        }
        else if (indice_jefe==5) {//Reaccion de Iris
            mvwprintw(ventana, 2, 1, "[%s]: Patetico", jefes_inicialesFinales[indice_jefe-1].name);
            mvwprintw(ventana, 4, 1, "Fallaste la evasion!  Perdiste %i puntos de vida", ataque_evadido);
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
                wrefresh(ventana);
                saltoLineaWin(ventana);
        }
    }else { //El usuario logro evadir el ataque
        if (indice_jefe==0){ //Dialogo de Bruto
            mvwprintw(ventana, 2, 1, "[%s]: Wow Bruto solo decir", jefes_inicialesFinales[indice_jefe].name);
            mvwprintw(ventana, 3, 1, "Evasion realizada con exito!");
            mvwprintw(ventana, 4, 1, "No pierdes puntos de vida en este turno");
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
                wrefresh(ventana);
                saltoLineaWin(ventana);
        }
        else if (indice_jefe==1){//Reaccion de Gladio
            mvwprintw(ventana, 2, 1, "[%s]: Intentando opacarme?", jefes_inicialesFinales[indice_jefe].name);
            mvwprintw(ventana, 3, 1, "[%s]: Ni siquiera un espejo me opaca!", jefes_inicialesFinales[indice_jefe].name);
            mvwprintw(ventana, 4, 1, "Evasion realizada con exito!");
            mvwprintw(ventana, 5, 1, "No pierdes puntos de vida en este turno");
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
                wrefresh(ventana);
                saltoLineaWin(ventana);
        }
        else if (indice_jefe==2){//Reaccion de las Verossa's
            if (indice_Verossa == 0){
                mvwprintw(ventana, 2, 1, "[%s]: Вы оставили меня без слов!", jefe3_verossaSisters.name[indice_Verossa]);
                mvwprintw(ventana, 3, 1, "[%s]: No todos hablamos tu idioma, cabeza-hueca", jefe3_verossaSisters.name[indice_Verossa]);
                mvwprintw(ventana, 4, 1, "Evasion realizada con exito!");
                mvwprintw(ventana, 5, 1, "No pierdes puntos de vida en este turno");
                mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
                    wrefresh(ventana);
                    saltoLineaWin(ventana);
            }else {
                mvwprintw(ventana, 2, 1, "[%s]: COMO TE ATREVES A IGNORARME!?", jefe3_verossaSisters.name[indice_Verossa]);
                mvwprintw(ventana, 3, 1, "[%s]: YO TE PROMETO QUE ME ENCARGARE DE QUE TU----",jefe3_verossaSisters.name[indice_Verossa]);
                mvwprintw(ventana, 4, 1, "[%s]: Luego se cuestiona por que no sale de la friendzone jejeje", jefe3_verossaSisters.name[indice_Verossa-1]);
                mvwprintw(ventana, 6, 1, "Enter para continuar");
                    wrefresh(ventana);
                    saltoLineaWin(ventana);
                    wclear(ventana);
                    wrefresh(ventana);
                box(ventana, 0, 0);
                mvwprintw(ventana, 2, 1, "[MAGO]: Gran idea el ignorar a una mujer");
                mvwprintw(ventana, 3, 1, "[MAGO]: Acaso te quieres morir!?");
                mvwprintw(ventana, 4, 1, "Evasion realizada con exito!");
                mvwprintw(ventana, 5, 1, "No pierdes puntos de vida en este turno");
                mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
                    wrefresh(ventana);
                    saltoLineaWin(ventana);
            }
        }
        else if (indice_jefe==3) {//Reaccion de Parca
            mvwprintw(ventana, 2, 1, "[%s]: ERROR", jefes_inicialesFinales[indice_jefe-1].name);
            mvwprintw(ventana, 3, 1, "Evasion realizada con exito!");
            mvwprintw(ventana, 4, 1, "No pierdes puntos de vida en este turno");
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
                wrefresh(ventana);
                saltoLineaWin(ventana);
        }
        else if (indice_jefe==4) {//Reaccion de Morte
            mvwprintw(ventana, 2, 1, "Los gritos son incesantes...");
            mvwprintw(ventana, 3, 1, "%s se retuerce del odio", jefes_inicialesFinales[indice_jefe-1].name);
            mvwprintw(ventana, 4, 1, "Evasion realizada con exito!");
            mvwprintw(ventana, 5, 1, "No pierdes puntos de vida en este turno");
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
                wrefresh(ventana);
                saltoLineaWin(ventana);
        }
        else if (indice_jefe==5) {//Reaccion de Iris
            mvwprintw(ventana, 2, 1, "[%s]: Admiro tu coraje %s", jefes_inicialesFinales[indice_jefe-1].name, Player.name);
            mvwprintw(ventana, 3, 1, "[%s]: Pero te reitero que no tienes oportunidad contra mi!", jefes_inicialesFinales[indice_jefe-1].name);
            mvwprintw(ventana, 4, 1, "Evasion realizada con exito!");
            mvwprintw(ventana, 5, 1, "No pierdes puntos de vida en este turno");
            mvwprintw(ventana, 6, 1, "Presiona Enter para continuar");
                wrefresh(ventana);
                saltoLineaWin(ventana);
        }
    }
    redibujadoPantalla();
}
void evaluacionAtaqueG(int ataque, int curacion) {
    if (Crit_Flag.criticon == true && curacion != -1) { //Se detecta un critico junto a una curacion de vampirismo
        mvwprintw(ventana, 2, 1, "Impacto Critico detectado + Vampirismo realizado eficazmente!");
        mvwprintw(ventana, 3, 1, "Tu ataque tuvo una potencia de %i puntos y te curaste %i puntos de vida!", ataque, curacion);
        mvwprintw(ventana, 4, 1, "Lord Dracula debe estar orgulloso de ti!");
        mvwprintw(ventana, 6, 1, "Presiona Enter para continuar.");
        Crit_Flag.criticon = false; //Se reinicia el Flag IMPORTANTE PARA EVITAR ERRORES
    }
    else if (Crit_Flag.criticon == true) { //Presencia de un critico pero ausencia de curacion
        mvwprintw(ventana, 2, 1, "Impacto Critico detectado!");
        mvwprintw(ventana, 3, 1, "Tu ataque tuvo una potencia de %i puntos!", ataque);
        mvwprintw(ventana, 5, 1, "Presiona Enter para continuar.");
        Crit_Flag.criticon = false;
    }
    else if (Crit_Flag.criticon == false && curacion != -1) { //Ausencia de critico pero presencia de curacion
        mvwprintw(ventana, 2, 1, "Vampirismo realizado eficazmente!");
        mvwprintw(ventana, 3, 1, "Te curaste %i puntos de vida e infligiste un ataque de %i puntos!", curacion, ataque);
        mvwprintw(ventana, 4, 1, "Tal vez te podrias acostumbrar al sabor de la sangre...");
        mvwprintw(ventana, 5, 1, "Presiona Enter para continuar.");
    }
    else { //Ausencia de critico y de vampirismo
        mvwprintw(ventana, 2, 1, "Tu ataque tuvo una potencia de %i puntos!", ataque);
        mvwprintw(ventana, 5, 1, "Presiona Enter para continuar.");
    }
    box(ventana, 0, 0);
    wrefresh(ventana);
    saltoLineaWin(ventana);
}
void jefeHabilidad(int i, int verossa_level) {
    wclear(ventana);
    wrefresh(ventana);
    box(ventana, 0, 0);
    if (i==0) { //Habilidad de Bruto
        mvwprintw(ventana, 2, 1, "%s activa su habilidad!", jefes_inicialesFinales[i].name);
        mvwprintw(ventana, 3, 1, "Pero Diego aun no crea funciones de habilidad!");
        mvwprintw(ventana, 4, 1, "[%s]: Injusticia", jefes_inicialesFinales[i].name);
        mvwprintw(ventana, 5, 1, "Presiona Enter para continuar");
    }
    else if (i==1) { //Habilidad de Gladio
        mvwprintw(ventana, 2, 1, "%s activa su habilidad!", jefes_inicialesFinales[i].name);
        mvwprintw(ventana, 3, 1, "[%s]: Oye Diego, cuando me asignaras habilidades?!", jefes_inicialesFinales[i].name);
        mvwprintw(ventana, 5, 1, "Presiona Enter para continuar");
    }
    else if (i==2) { //Habilidad de Verossa
        if (verossa_level==0) {
            mvwprintw(ventana, 2, 1, "[%s]: Ara Ara, que ocurrio con mi habilidad", jefe3_verossaSisters.name[verossa_level]);
            mvwprintw(ventana, 3, 1, "%s aun no tiene su habilidad definida!", jefe3_verossaSisters.name[verossa_level]);
            mvwprintw(ventana, 5, 1, "Presiona Enter para continuar");
        }else {
            mvwprintw(ventana, 2, 1, "%s intenta activar su habilidad!", jefe3_verossaSisters.name[verossa_level]);
            mvwprintw(ventana, 3, 1, "[%s]: No se vale jugador, no tengo mis habilidades?!", jefe3_verossaSisters.name[verossa_level]);
            mvwprintw(ventana, 5, 1, "Presiona Enter para continuar");
        }
    }
    else if (i==3) { //Habilidad de Parca
        mvwprintw(ventana, 2, 1, "%s sabe que no tiene habilidad aun", jefes_inicialesFinales[i-1].name);
        mvwprintw(ventana, 3, 1, "[%s]:.....", jefes_inicialesFinales[i-1].name);
        mvwprintw(ventana, 5, 1, "Presiona Enter para continuar");
    }
    wrefresh(ventana);
    saltoLineaWin(ventana);
    redibujadoPantalla();
}

void irisvielle_fall(void) {} //Aparicion de la Diosa Estelar Iris TBC
void blood_fear_screams_while_I_Enjoy(void) {} //Aparicion de Morte TBC


