#include "kACAB.h"

AllCopsAreBastards* AllCopsAreBastards::GetSingleton() {
	static AllCopsAreBastards singleton;
	return &singleton;
}

auto AllCopsAreBastards::ProcessEvent(const RE::TESActivateEvent* a_event, RE::BSTEventSource<RE::TESActivateEvent>* a_eventSource) -> RE::BSEventNotifyControl {
	if (!a_event) {
		return RE::BSEventNotifyControl::kContinue;
	}
	if (!a_event->actionRef && !a_event->objectActivated) {
		return RE::BSEventNotifyControl::kContinue;
	}
	auto object = a_event->objectActivated.get();
	if (object) {
		auto actor = object->As<RE::Actor>();
		if (actor) {
			if (actor->IsGuard()) {
				actor->SetActorValue(RE::ActorValue::kAggresion, 3.00f); // frenzy all guards
				actor->SetActorValue(RE::ActorValue::kConfidence, 4.00f); // make them willing to kill
				RE::FormID formid = 0xF;
				auto form = RE::TESForm::LookupByID(formid);
				actor->StealAlarm(RE::PlayerCharacter::GetSingleton(), form, 1000, 1000, actor->As<RE::TESForm>(), false); // aggro them onto you lol
			}
		}
	}
	return RE::BSEventNotifyControl::kContinue;
}