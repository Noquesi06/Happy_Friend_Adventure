#include <stdio.h>
#include <stdbool.h>
#define MAX 4 
#define MAX2 6

struct abilities {
    char name_ability[4][30];
    bool ability_active[4];
};
struct bosses{
    char name[30];
    int hp_boss, current_hp_boss, boss_atck_min, boss_atck_max;
    struct abilities ability;
}jefes_inicialesFinales[5] = {
    {"Bruto", 1000, 1000, 30, 45,   {"Duro como la roca","","","", false, false, false, false}}, //Habilidades del mismo
    {"Gladius", 4850, 4850, 40, 70, {"Lo se, soy perfecto", "","", "", false, false,false, false}}, // Boss2
    {"Parca el verdugo de Dios", 10000, 10000, 65, 105,{"Miedo", "Tormento", "Almas en pena", "", false, false, false, false}}, // Boss 4 (Boss 3 se define de otra manera)
    {"Morte", 20000, 20000, 105, 140, {"Disolucion", "Masacre", "Desesperacion", "Veredicto final", false, false, false, false}},   // Boss 5 (Ruta B)
    {"Diosa estelar Iris", 25000, 25000, 95, 150,  {"Descenso cosmico", "Paz", "Vampirismo", "Se acabo", false, false, false, false}}, // Boss 5 (Ruta A)
    };

struct verossa{ //Boss 3
    char name[3][20], name_ability[3][30];
    int hp_boss[3], current_hp_boss[3], boss_atck_min[3], boss_atck_max[3];
    bool ability_activa[3], jefe_derrotado[3];
}jefe3_verossaSisters = {
    {"Sveta", "Mariana", "Amanda"}, {"Я твой щит", "Que husmeas pervertidoo!", "Las protegere!"},{7500, 5000, 6500}, {7500, 5000, 6500}, {30, 45, 0}, {50, 65, 0}, false, false, false, false, false, false,
    };
struct estado_Jefe {
    bool jefe_derrotado[6], jefe_muerto[6];
}Estado_Jefe={
    {false, false, false, false,false,false},
    {false, false, false, false, false, false}
};
struct player_stats_wizard{
    int hp_max, current_hp_player, dmg, eva, dmg_taken_passive, dmg_taken_active, mana_max, current_mana_player, mana_csmp, mana_reg;
};

struct player_stats_warrior{
    int hp_max, current_hp_player, dmg, defense, eva, dmg_taken_passive, dmg_taken_active, hp_reg;
    float crit, vampirism;
};

struct player_stats{
    int money;
    char name[30];
    bool wizard, warrior;
    struct player_stats_warrior war;
    struct player_stats_wizard wiz;
}Player= {
    1000,{""}, false, false,
    {1000, 0, 10,   5, 5, 0, 0, 0, 0, 0}, //Warrior
    {1100, 0, 10,  5, 0, 0, 0, 0, 0,  0}, //Wizard
    
};
struct critico {
    bool criticon;
} Crit_Flag ={
    false
};
struct  player_action{
    bool defended, evaded;
}Accion={
    false, false
};
struct items_warrior{ //Definicion del las estadisticas para los objetos de la clase warrior
    char name[50];
    int dmg, hp, cost, hp_reg, def, eva;
    float crit_item, vampirism;
    char desc[200];
};
struct items_wizard{ //Definicion del las estadisticas para los objetos de la clase wizard
    char name[50];
    int dmg, hp, mana, mana_reg, mana_csmp, cost, eva;
    char desc[200];
};
struct items_lvl{ //Registro que contendra la cantidad de objetos para cada clase
    struct items_warrior warrior[MAX2];
    struct items_wizard wizard[MAX2];
};
struct items{ //Registro que agrupara los objetos de acuerdo al nivel actual del juego
    struct items_lvl lvl[MAX];
}That_damn_struct ={ //Se inicializan los items
    .lvl={ 
        [0]={ //Lvl 0 (Objetos iniciales)
            .warrior={
                {"Espada oxidada", 13, 0,   350, 0, 0, 0, 7,0,"vio tiempos mejores,pero que el oxido no te engane,siempre se tiene poder oculto "},
                {"Hueso de gladiador", 20, 0,   300, 0, 0, 0,0, 0,"Aun se escuchan los gritos del coliseo..."},
                {"Colmillo de vampiro", 10, 0,  550, 0, 0, 0, 0,8,"un colmillo largo y retorcido que puede arrebatar o dar vida...todo depende de tu intencion mas profunda"},
                {"Bandita curativa", 0, 200,   200, 5, 0, 0, 0,0,"banda el recodo, banda malandra,no, la banda que cura y da fuerza solo tu sabes cual es "},
                {"Pocion de furia", 0, 0,   100, 0, 0, 0, 0,0,"dejeme los platos sin lavar la noche anterior y vas a ver los efectos de la posion de furia en mama"}, // 3 ataques +200% dmg
                {"Pocion de vida diminuta", 0, 50,   50, 0, 0, 0, 0,0," lo diminuto puede romper lo mas duro."}
            },
            .wizard={ //Wizard
                {"Varita de caramelo", 11, 0, 40, 0, 0, 300, 0, "delgada, delgada pero dulce y envolvente, hasta el mas agrio y rancio cae bajo su influjo"},
                {"Cabeza espeluznante", 15, 0, 66, 0, 0, 550, 0, " la mejor manera de paralizar al enemigo, dejarlo sin fuerzas, derrotado mi podar esta en que te vea recien levandado en la manana, "}, // manaMAX +100
                {"Pocima diminuta de mana", 0, 0, 50, 0, 0, 50, 0, " la que nunca falla, la que siempre esta ahi, con poder infinito, recargable, transportable a todas partes solo hace falta que tengas confianza y siempre creas"},
                {"Bandita curativa", 0, 200, 0, 0, 0, 200, 0, " "},
                {"Bandita de magia", 0, 0, 0, 40, 0, 300, 0, " hay banditas que por arte de magia te llenan de energia. que son? los amigos? la familia? los hobbies? tu musica? tu eliges,solo debes deteectarla y usarla"}, // manaMAX=100
                {"Pocion de vida diminuta", 0, 50, 0, 0, 0, 50, 0, " a veces se hace necesario volverse diminuto para poner las cosas en contexto para ver las cosas en con otra prespectiva"}
            } 
        },

        [1] = { //Lvl 1 (Tras derrotar a bruto)
            .warrior = {
                {"Garra de chiquilin", 50, 0,   900, 0, 0, 0, 15,0,"peligrosisima!!!! es chiquita pero letal,rompe lo qeu toca y te hace arder hasta el alma"},
                {"Espada de oro", 80, 0, 750, 0, 0, 0, 0,0," capaz de atravezar pensamientos mas mordacez las palabras duras,los sentimientos mas negros, llena de luz y guia,abre el camino para quien esta perdido"},
                {"Dedo de nosferatu", 50, 0,   1250, 0, 0, 0, 0,15," el dedo qeu revela lo oculto, el dedo qeu indica al culpable, el dedo juzgador....pero cuidado que mientras un dedo apunta hacia el frente tres dedos te apuntan a ti"},
                {"Escudo de capitan america", 0, 0,  1000, 0, 20, 0,0, 0,"el gringito que no puede faltar, el escudo que te protege de lo fake, el que te da el poder de concer entre lo real y lo falso"},
                {"Tenis Jordan", 0, 0,   900, 0, 0, 15, 0,0," da el salto, atrevete, pega el brico que te lleve a alcanzar las metas propuestas, salta alto con la fuerza de tus piernas... jordan sera tu fan"},
                {"Pocion de curacion mediana", 0, 100,  100, 0, 0, 0, 0,0,"si no le echas ganas,solo tendras la mitad, llegaras a medio camino, te faltaran 5 centavos para el peso"}
            },
                .wizard = {
                {"Sombrero seleccionador", 70, 0, 100, 0, 0, 950, 0, "te hace ver cool, te da estilo, te ves sexy y lo mejor te ayuda a ver distinguier quien es quien y te muestra como eres"},
                {"Libro de Ecuaciones Diferenciales", 60, 0, 80, 0, 0, 1550, 0, "volvimos a la prepa? quieres sufrir.... no hay dicha si sufrimiento este libro le abre las puertas aunque tengas que sufrir"},
                {"Vara gigante", 120, 0, 190, 0, 0, 2000, 0, "impulsate con al vara para llegar mas lejos, para subir mas alto para alcanzar lo que parece lejano: si,el mango en la copa del arbol"},
                {"Tenis Jordan edicion lujo", 0, 0, 0, 0, 0, 1200, 30, "el entrenamiento de pierna en el gym se ve potencializado con estos tenis... ya no corres ...vuelas!!! "},
                {"Bandita de magia mejorada", 0, 0, 0, 60, 0, 400, 0, " cuando te rodeas de las situaciones adecuadas,de la gente adecuada, de las ideas adecuadas, de los objetivos adecuados la curita potencializa tu poder! sos es non plus ultra!"},
                {"Pocion de curacion mediana", 0, 100, 0, 0, 0, 100, 0, ""}
                }
            },

        [2] = { //Lvl 2 (Tras derrotar a gladius)
            .warrior = {
                {"Peluca de Gladius", 0, 0,  3000, 0, 0, 0, 35, 0,"ponte la peluca y te despelucas pero podras ver lo qeu otros ven, sentir lo que otros sienten, vivir lo que otros viven"},
                {"Macuahuitl", 120, 0,  3500, 0, 0, 0, 0,0,"a veces hay que ayudarle a los otros a comprender, el macuahuitl te ayudara a ponerle las ideas en orden o a qeu sus neuronas hagana click"},
                {"Espada sangrienta", 55, 0,4000, 0, 0, 0, 0,20,"utilizada para infundir terror, mostros elfos y humanos hullen den su presencia, usala con sabiduria porque tanto reguerito de sangre lo limpias vos"},
                {"Armadura de iron man", 0, 0,   2000, 0, 30, 0, 0,0,"te protege contra el mal de ojo, los amarres, las malas energias, las palabras hirientes, los falsos amigos las malas intensiones pero ojo "},
                {"Chaleco antibalas", 0, 500,   500, 30, 10, 0, 0,0,"repele todo tipo de balas: las balas de tus piropos, las balas de tu mirada,las balas de tus palabras  mi amor"},
                {"Pocion de vida grande", 0, 150,  150, 0, 0, 0,  0,0,"estas destinado a esta pocion tomala y todo se va hacer mas grande: tus suenos,tus metas, tus capacidades, tu potencial... no temas a ingerirla."}
            },
            .wizard = {
                {"Anillo del hobbit", 0, 0, 0, 0, 0, 2000, 0, "utilizalo y desapreceras, podras ver sin que te vean ....agarraras a todos en curva y una ventaja tendras"},
                {"Varita con craneo adherido", 165, 0, 200, 0, 0, 2500, 0, " o baculo que llaman! te abre las puertas, tocas corazones, lees mentes y emociones pero si en ultimas eso no es util para una recalibracion cognitiva o golpe en la cabeza es sirve"},
                {"Collar de dientes", 40, 0, 150, 0, 0, 1500, 0, " hay que incarle el dientre no solo al pan de muerto, a los proyectos, a las metas.... te da fortaleza eso si hay que revisar que no traiga caries o inseguridades escondidas por ahi"},
                {"Anillo de compromiso", 0, 0, 0, 80, 0, 1500, 0, "excelente herramienta que te da un partner para construir, edificar algo nuevo, duradero y valioso"},
                {"Alas de angel", 0, 0, 0, 0, 0, 1000, 20, "llenas de poder,te elevan mas alla de los viles morales solo debe tener cuidado de no tener los pies embarrados....porque encontes nunca te elevaras"},
                {"Pocion de curacion grande", 0, 150, 0, 0, 0, 150, 0, ""}
            }
        },

        [3] = { //Lvl 3 (Tras derrotar a las hermanas Verossa)
            .warrior = {
                {"Collar del parcero caido", -50, 0,   4000, 0, 0, 0, 40,0,"el bling bling no puede faltar, te da peresonalidad,brillo,imagen... recuerda que lo de afuera debe reflejar lo de adentro"},
                {"Lanza de Teseo", 140, 0,   4000, 0, 0, 0, 0,0,"de dara el la valentia de un heroe,la grandeza de un dios,la fuerza de un gladiador, pero cuidado no se que el gego te meta el pie"},
                {"Tu tambien Brutus?", 50, 0,  5000, 0, 0, 0, 0, 35," todos se vuelven tus aliados o tus enemigos debepede el desodorante qeu uses....asi la vida"},
                {"Bendicion de baskina (They love you)", 0, 0,  6500, 0, 0, 0, 0, 0,""},
                {"Caparazon de tortuga", 0, 500,   1000, 0, 30, 0, 0,0,"a veces necesitas un medio para protegerte del mundo, para aislarte y estasr con vos, y hacer tus cositas con calma "},
                {"Pocion de vida grande", 0, 150,   150, 0, 0, 0, 0,0,""}
            },
            .wizard = {
                {"Chamarra ahegao", 100, 0, 350, 0, 0, 2000, 0, "Tu no los matas, tu olor lo hace"},
                {"Varita de Gandalf", 185, 0, 500, 0, 0, 5000, 0, " se ve inofensiva.. puede ser del tamano de un mondadientes o de un baculo depende para que lo uses pero es igual de letal sin importar"},
                {"Libro de Ecuaciones Diferenciales Vol 2", 0, 0, 0, 0, 0, 5000, 0, "canas verdes?si,son producto de este libro,la furia de hulk al no entender te hizo el pelo verde pero te dio fuerza, no chilles"},
                {"Bendicion de baskina (They love you)", 0, 0, 0, 0, 0, 6500, 0, ""}, 
                {"Pocima de mana grande", 0, 0, 500, 0, 0, 200, 0, ""},
                {"Pocion de curacion grande", 0, 150, 0, 0, 0, 150, 0, ""}
            }
        }
    }
};
struct cantidadPocimas {
    int pocimas_curacion, pocimas_mana;
}Pocimas={
    0,0
};
//Menu auxiliar
struct informacion { //Declaracion del registro que mostrara texto en los menus auxiliares
    char ventanaAuxiliar[40];
} Texto[3] ={ //Inicializacion del menu auxiliar
    [0] ={"Seguro de comprar este item?"},
    [1] ={"Amenazas presentes"},
    [2] = {""}
};
struct informacionExportar { //Funcion exclusiva para exportar la informacion del Guerrero, Mago TBA
    char name[30]; //Nombre del guerrero
    int hp_max, dmg, defense, eva, hp_reg, money; //Estadisticas del luchador
    float crit, vampirism;
    int indice_Jefe;
    bool warrior; //Parametro del warrior
    bool jefe_derrotado[6], jefe_muerto[6];
}Exportacion = {
    {""}, 0,0,0,0,0,0,0,0,0,false,false,false,false,false,false,false, false, false, false, false, false, false
}; //Si inicializa todo en: string vacios, ceros y falses, para evitar contener basura en nuestro registro

char *elecciones[] = { //Estas seran las opciones del menu de inicio
    "Nueva partida",
    "Continuar",
    "Ajustes",
    "Tutorial",
    "Salir",
};
char *elecciones1[]={ //Para decidir si apoyar o denegar participar en el jugo
    "Aceptar encomienda del Mago",
    "Rechazar encomienda del Mago",
};
char *elecciones2[]={ //Para definir la clase del usuarioi
    "Guerrero",
    "Mago",
};
char *elecciones3[]={ //Para el modo ubermensch
    "Si",
    "No",
};
char *elecciones4[7]; //Accedera al nombre de los items para crear sus opciones con base a ellos

char *elecciones5[]={
    "Atacar", "Defenderse", "Evadir", "Item"
};
char *elecciones6Verossa[4]; //Accedera al nombre del jefe "Verossa"
