#include "kProject.h"

Loki_CallMeKevin::Loki_CallMeKevin() {
	CSimpleIniA ini;
	ini.SetUnicode();
	auto filename = L"Data/SKSE/Plugins/Loki_CallMeKevin/Loki_CallMeKevin.ini";
	SI_Error rc = ini.LoadFile(filename);
	const char* section = "TOGGLES";

	this->EnemySpawn = ini.GetBoolValue(section, "bEnemySpawn", false);
	this->CheeseSpawn = ini.GetBoolValue(section, "bCheeseSpawn", false);
	this->SweetrollSpawn = ini.GetBoolValue(section, "bSweetrollSpawn", false);

	this->EquipCosts = ini.GetBoolValue(section, "bEquipCosts", false);
	this->AllCops = ini.GetBoolValue(section, "bAllCops", false);
	this->PoniesForAll = ini.GetBoolValue(section, "bPoniesForAll", false);
	this->ImpactPotions = ini.GetBoolValue(section, "bImpactfulPotions", false);
};

Loki_CallMeKevin::~Loki_CallMeKevin() {

};

Loki_CallMeKevin* Loki_CallMeKevin::GetSingleton() {
	static Loki_CallMeKevin* singleton = new Loki_CallMeKevin();
	return singleton;
};





void Loki_CallMeKevin::InjectDamageHook() {
	REL::Relocation<std::uintptr_t> vtbl{ REL::ID(261397) };
	_HandleHealthDamage_Character = vtbl.write_vfunc(0x104, HandleHealthDamage_Character);
	logger::info("Damage Hook installed");
};

void Loki_CallMeKevin::InjectCheeseHook() {
	REL::Relocation<std::uintptr_t> cheese{ REL::ID(36357) };
	auto& trampoline = SKSE::GetTrampoline();
	_DoCheeseSpawn = trampoline.write_call<5>(cheese.address() + 0x6D3, DoCheeseSpawn);
};
// you might be thinking; Loki these 2 hook the same spot. 
// Yes they do, because instead of deciding which module to execute in the hook itself
// I just decided to abuse write_call and hook them separately, since each call is saved
// and therefore both hooks will work together, or apart from each other.
void Loki_CallMeKevin::InjectSweetrollHook() {
	REL::Relocation<std::uintptr_t> sweetroll{ REL::ID(36357) };
	auto& trampoline = SKSE::GetTrampoline();
	_DoSweetrollSpawn = trampoline.write_call<5>(sweetroll.address() + 0x6D3, DoSweetrollSpawn);
};
void Loki_CallMeKevin::EquipCostsYou() {
	auto sourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
	if (sourceHolder) { sourceHolder->AddEventSink(EquippingCostsMoney::GetSingleton()); }
}
void Loki_CallMeKevin::ACAB() {
	auto sourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
	if (sourceHolder) { sourceHolder->AddEventSink(AllCopsAreBastards::GetSingleton()); }
}
void Loki_CallMeKevin::GiveMeAPony() {
	auto sourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
	if (sourceHolder) { sourceHolder->AddEventSink(IWantAPony::GetSingleton()); }
}
void Loki_CallMeKevin::PotionsImpact() {
	auto sourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
	if (sourceHolder) { sourceHolder->AddEventSink(ImpactfulPotions::GetSingleton()); }
}





RE::TESObjectREFR* Loki_CallMeKevin::PlaceAtMe(RE::TESObjectREFR* self, RE::TESForm* a_form, std::uint32_t count, bool forcePersist, bool initiallyDisabled)
{
	using func_t = RE::TESObjectREFR* (RE::BSScript::Internal::VirtualMachine*, RE::VMStackID, RE::TESObjectREFR*, RE::TESForm*, std::uint32_t, bool, bool);
	RE::VMStackID frame = 0;//Not important, probably.
	REL::Relocation<func_t> func{ REL::ID(55672)/*9951F0*/ };
	auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();

	return func(vm, frame, self, a_form, count, forcePersist, initiallyDisabled);
};

/*
https://www.cplusplus.com/reference/cstdlib/rand/
*/
void Loki_CallMeKevin::HandleHealthDamage_Character(RE::Character* a_char, RE::Actor* a_attacker, float a_damage) {
	if (a_char->IsPlayerRef() && (a_damage >= 1.00f)) {
		auto random = rand() % 24 + 0;
		auto FormID = enemyVector.at(random);

		auto form = RE::TESForm::LookupByID(FormID);
		PlaceAtMe(RE::PlayerCharacter::GetSingleton(), form, 1, false, false);
	};
	return _HandleHealthDamage_Character(a_char, a_attacker, a_damage);
};

float Loki_CallMeKevin::DoCheeseSpawn(RE::Actor* a_actor, float a_zPos, RE::TESObjectCELL* a_cell) {
	if (a_actor->IsPlayerRef() && a_actor->IsSprinting()) {
		auto random = rand() % 6 + 0;
		auto FormID = cheeseVector.at(random);

		auto form = RE::TESForm::LookupByID(FormID);
		PlaceAtMe(RE::PlayerCharacter::GetSingleton(), form, 1, false, false);
	}
	return _DoCheeseSpawn(a_actor, a_zPos, a_cell);
};

float Loki_CallMeKevin::DoSweetrollSpawn(RE::Actor* a_actor, float a_zPos, RE::TESObjectCELL* a_cell) {
	if (a_actor->IsPlayerRef() && a_actor->GetCharController()->context.currentState == RE::hkpCharacterStateType::kInAir) {
		auto random = rand() % 37 + 0;
		auto FormID = foodVector.at(random);

		auto form = RE::TESForm::LookupByID(FormID);
		PlaceAtMe(RE::PlayerCharacter::GetSingleton(), form, 1, false, false);
	}
	return _DoSweetrollSpawn(a_actor, a_zPos, a_cell);
};