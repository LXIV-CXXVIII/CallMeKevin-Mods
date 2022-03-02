#include "kEquipCosts.h"

EquippingCostsMoney* EquippingCostsMoney::GetSingleton() {  // Equip
	static EquippingCostsMoney singleton;
	return &singleton;
}

auto EquippingCostsMoney::ProcessEvent(const RE::TESEquipEvent* a_event, RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource) -> RE::BSEventNotifyControl {
	if (!a_event) {
		return RE::BSEventNotifyControl::kContinue;
	}

	if (a_event->actor->IsPlayerRef()) {
		auto form = RE::TESForm::LookupByID(a_event->baseObject);
		const auto inv = a_event->actor->GetInventory([](RE::TESBoundObject& a_object) -> bool {
			return a_object.IsGold();
		});

		if (form) {
			if (a_event->equipped) {
				if (form->IsWeapon()) {
					auto formid = 0x0f;
					if (auto boundObject = RE::TESForm::LookupByID(formid)->As<RE::TESBoundObject>(); boundObject) {
						a_event->actor->RemoveItem(boundObject, 100, RE::ITEM_REMOVE_REASON::kSteal,
							nullptr, nullptr);
					}
				}
				if (form->IsArmor()) {
					auto formid = 0x0f;
					if (auto boundObject = RE::TESForm::LookupByID(formid)->As<RE::TESBoundObject>(); boundObject) {
						a_event->actor->RemoveItem(boundObject, 50, RE::ITEM_REMOVE_REASON::kSteal,
							nullptr, nullptr);
					}
				}
			}
		}
	}

	return RE::BSEventNotifyControl::kContinue;
}