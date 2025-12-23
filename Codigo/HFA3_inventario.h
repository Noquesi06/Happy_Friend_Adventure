#ifndef HFA_HFA3_INVENTARIO_H
#define HFA_HFA3_INVENTARIO_H
#include <stdbool.h>

struct abilities {
    char name_ability[4][30];
    bool ability_active[4];
};

struct bosses {
    char name[30];
    int hp_boss, current_hp_boss, boss_atck_min, boss_atck_max;
    struct abilities ability;
};

struct verossa{
    char name[3][20], name_ability[3][30];
    int hp_boss[3], current_hp_boss[3], boss_atck_min[3], boss_atck_max[3];
    bool ability_activa[3], jefe_derrotado[3];
};

struct estado_Jefe {
    bool jefe_derrotado[6], jefe_muerto[6];
};

struct player_stats_wizard{
    int hp_max, current_hp_player, dmg, defense, eva, dmg_taken_passive, dmg_taken_active, mana_max, current_mana_player, mana_csmp, hp_reg, mana_reg;
};

struct player_stats_warrior{
    int hp_max, current_hp_player, dmg, defense, eva, dmg_taken_passive, dmg_taken_active, hp_reg;
    float crit_item, vampirism;
};
struct player_stats{
    int money;
    char name[30];
    bool wizard, warrior;
    struct player_stats_warrior war;
    struct player_stats_wizard wiz;
};
struct critico {
    bool criticon;
};

struct  player_action{
    bool defended, evaded;
};

struct items_warrior{
    char name[50];
    int dmg, hp, cost, hp_reg, def, eva;
    float crit_item, vampirism;
    char desc[200];
};
struct items_wizard{
    char name[50];
    int dmg, hp, mana, mana_reg, mana_csmp, cost, eva;
    char desc[200];
};

struct items_lvl{
    struct items_warrior warrior[6];
    struct items_wizard wizard[6];
};

struct items{
    struct items_lvl lvl[4];
};

struct cantidadPocimas {
    int pocimas_curacion, pocimas_mana;
};

struct informacion {
    char ventanaAuxiliar[40];
};
struct informacionExportar { //Funcion exclusiva para exportar la informacion del Guerrero, Mago TBA
    char name[30]; //Nombre del guerrero
    int hp_max, dmg, defense, eva, hp_reg, money; //Estadisticas del luchador
    float crit, vampirism;
    int indice_Jefe;
    bool warrior; //Parametro del warrior
    bool jefe_derrotado[6], jefe_muerto[6];
};

extern struct bosses jefes_inicialesFinales[5];
extern struct verossa jefe3_verossaSisters;
extern struct estado_Jefe Estado_Jefe;
extern struct player_stats Player;
extern struct critico Crit_Flag;
extern struct player_action Accion;
extern struct items That_damn_struct;
extern struct cantidadPocimas Pocimas;
extern struct informacion Texto[3];
extern struct informacionExportar Exportacion;

extern char *elecciones[];
extern char *elecciones1[];
extern char *elecciones2[];
extern char *elecciones3[];
extern char *elecciones4[7];
extern char *elecciones5[];
extern char *elecciones6Verossa[4];

#endif //HFA_HFA3_INVENTARIO_H