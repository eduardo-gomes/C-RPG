/*
TODO: inimigo, sala and test
*/
#pragma once
#include "headers.hpp"
using json = nlohmann::json;
void to_json(json& j, const loot *p){
	j = {
		{"loot",{
			{"noloot", p->noloot},
			{"xp", p->xp},
			{"money", p->money}
		}}
	};
}
void from_json(const json& j, loot *p){
	j.at("loot").at("noloot").get_to(p->noloot);
	j.at("loot").at("xp").get_to(p->xp);
	j.at("loot").at("money").get_to(p->money);
}

void to_json(json &j, const weapon *p){
	j = {
		{"material",p->material},
		{"xp",p->xp},
		{"damage_df",p->damage_df},
		{"damage_buff",p->damage_buff},
		{"precision",p->precision},
		{"precision_buff",p->precision_buff}
	};
}
void from_json(const json &j, weapon *p){
	j.at("material").get_to(p->material);
	j.at("xp").get_to(p->xp);
	j.at("damage_df").get_to(p->damage_df);
	j.at("damage_buff").get_to(p->damage_buff);
	j.at("precision").get_to(p->precision);
	j.at("precision_buff").get_to(p->precision_buff);
}

void to_json(json& j, const personagem *p){
	json j_loot, arma0, arma1;
	to_json(arma0, p->armas[0]);
	to_json(arma0, p->armas[1]);
	to_json(j_loot, (const loot*)p);
	j = {
			{"colectedxp", p->get_all_xp()},
			{"xp", p->get_xp()},
			{"level", p->get_level()},
			{"life_max", p->get_life_max()},
			{"life", p->get_life()},
			{"df_damage", p->get_df_damage()},
			{"df_critical", p->get_df_critical()},
			{"df_actionpoints", p->get_df_actionpoints()},
			{"df_magicalpoints", p->get_df_magicalpoints()},
			{"weapon",{
				{0, },
				{1, }
			}}
		};
	j.merge_patch(j_loot);
}
void from_json(const json &j, personagem *p){
	from_json(j, (loot*) p);
	j.at("colectedxp").get_to(p->colectedxp);
	j.at("xp").get_to(p->xp);
	j.at("level").get_to(p->level);
	j.at("life_max").get_to(p->life_max);
	j.at("life").get_to(p->life);
	j.at("df_damage").get_to(p->df_damage);
	j.at("df_critical").get_to(p->df_critical);
	j.at("df_actionpoints").get_to(p->df_actionpoints);
	j.at("df_magicalpoints").get_to(p->df_magicalpoints);
}

void to_json(json& j, const jogador& p){
	json j_pers;
	to_json(j_pers, (const personagem*)&p);
	j = {
		{"name", p.name},
		{"money", p.money},
		{"sk_life", p.sk_life},
		{"sk_damage", p.sk_damage},
		{"sk_critcal", p.sk_critcal},
		{"sk_actionpoints", p.sk_actionpoints},
		{"sk_magicalpoints", p.sk_magicalpoints}
	};
	j.merge_patch(j_pers);
}
void from_json(const json& j, jogador& p){
	from_json(j, (personagem*)(&p));
	j.at("name").get_to(p.name);
	j.at("money").get_to(p.money);
	j.at("sk_life").get_to(p.sk_life);
	j.at("sk_damage").get_to(p.sk_damage);
	j.at("sk_critcal").get_to(p.sk_critcal);
	j.at("sk_actionpoints").get_to(p.sk_actionpoints);
	j.at("sk_magicalpoints").get_to(p.sk_magicalpoints);
}