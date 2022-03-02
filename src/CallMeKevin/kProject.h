#pragma once
#include "C:/dev/simpleini-master/SimpleIni.h"
#include "CallMeKevin/kACAB.h"
#include "CallMeKevin/kEquipCosts.h"
#include "CallMeKevin/kImpactPotions.h"
#include "CallMeKevin/kIWantAPony.h"

class Loki_CallMeKevin {

public:
    Loki_CallMeKevin();
    ~Loki_CallMeKevin();
    static Loki_CallMeKevin* GetSingleton();
    static void InjectDamageHook();
    static void InjectCheeseHook();
    static void InjectSweetrollHook();

    static void EquipCostsYou();
    static void ACAB();
    static void GiveMeAPony();
    static void PotionsImpact();

    bool EnemySpawn = false; 
    bool CheeseSpawn = false;
    bool SweetrollSpawn = false;

    bool EquipCosts = false;
    bool AllCops = false;
    bool PoniesForAll = false;
    bool ImpactPotions = false;

private:
    static RE::TESObjectREFR* PlaceAtMe(RE::TESObjectREFR* self, RE::TESForm* a_form, std::uint32_t count, bool forcePersist, bool initiallyDisabled);
    static void HandleHealthDamage_Character(RE::Character* a_char, RE::Actor* a_attacker, float a_damage);
    static float DoCheeseSpawn(RE::Actor* a_actor, float a_zPos, RE::TESObjectCELL* a_cell);
    static float DoSweetrollSpawn(RE::Actor* a_actor, float a_zPos, RE::TESObjectCELL* a_cell);

	static inline REL::Relocation<decltype(HandleHealthDamage_Character)> _HandleHealthDamage_Character;
    static inline REL::Relocation<decltype(DoCheeseSpawn)> _DoCheeseSpawn;
    static inline REL::Relocation<decltype(DoSweetrollSpawn)> _DoSweetrollSpawn;

    static inline std::vector<RE::FormID> enemyVector = {
     0x23A93,
     0x351C3,
     0x7E87D,
     0x45C5F,
     0x35B5E,
     0x2D1DE,
     0x2D1E0,
     0x2D1FC,
     0x2D1FD,
     0x26C52,
     0x23AB4,
     0x23AB5,
     0x23AB6,
     0x23AB7,
     0x23A8A,
     0x23A8B,
     0x23A8C,
     0x1D4B5,
     0x58303,
     0xA91A0,
     0xA91A0,
     0xA91A0,
     0xA91A0,
     0xA91A0,
     0xA91A0,
     0xA91A0,
     0xA91A0,
     0xA91A0,
     0xA91A0,
    };
    static inline std::vector<RE::FormID> cheeseVector = {
     0x64B31,
     0x64B32,
     0x64B33,
     0x64B34,
     0x64B35,
     0x64B36,
     0x669A3,
    };
    static inline std::vector<RE::FormID> foodVector = {
     0x64B3D,
     0x64B3D,
     0x64B3D,
     0x64B3D,
     0x64B3D,
     0x64B3D,
     0x64B3D,
     0x64B3D,
     0x64B3D,
     0x64B3D,
     0x64B3D,
     0x64B3D,
     0x64B3D,
     0x64B3D,
     0x64B3D,
     0x64B3D,
     0x64B3E,
     0x64B3F,
     0x64B40,
     0x64B41,
     0x64B42,
     0x64B43,
     0x65C97,
     0x65C98,
     0x65C99,
     0x65C9A,
     0x65C9B,
     0x65C9C,
     0x65C9D,
     0x65C9E,
     0x65C9F,
     0x721E8,
     0x7224C,
     0x7224E,
     0x722B0,
     0x722BB,
     0x722C2,
     0x722C7,
    };

protected:

};