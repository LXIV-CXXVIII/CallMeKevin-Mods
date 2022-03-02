#include "kImpactPotions.h"

ImpactfulPotions* ImpactfulPotions::GetSingleton() {
	static ImpactfulPotions singleton;
	return &singleton;
}

auto ImpactfulPotions::ProcessEvent(const RE::TESMagicEffectApplyEvent* a_event, RE::BSTEventSource<RE::TESMagicEffectApplyEvent>* a_eventSource)->RE::BSEventNotifyControl {
	if (!a_event) {
		return RE::BSEventNotifyControl::kContinue;
	}

	auto formid = 0x3EB15;
	auto form = RE::TESForm::LookupByID(formid);
	if (a_event->magicEffect == form->formID) {
		RE::PlayerCharacter::GetSingleton()->SetGraphVariableFloat("staggerMagnitude", 1.00f);
		RE::PlayerCharacter::GetSingleton()->NotifyAnimationGraph("staggerStart");
	}

	return RE::BSEventNotifyControl::kContinue;
}