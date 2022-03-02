#include "CallMeKevin/kIWantAPony.h"

IWantAPony* IWantAPony::GetSingleton() {
	static IWantAPony singleton;
	return &singleton;
}

auto IWantAPony::ProcessEvent(const RE::TESActivateEvent* a_event, RE::BSTEventSource<RE::TESActivateEvent>* a_eventSource)->RE::BSEventNotifyControl {
	if (!a_event) {
		return RE::BSEventNotifyControl::kContinue;
	}
	if (!a_event->actionRef || !a_event->objectActivated) {
		return RE::BSEventNotifyControl::kContinue;
	}
	auto object = a_event->objectActivated.get();
	if (object) {
		auto actor = object->As<RE::Actor>();
		if (actor) {
			if (actor->IsHorse()) {
				const auto scriptFactory = RE::IFormFactory::GetConcreteFormFactoryByType<RE::Script>();
				const auto script = scriptFactory ? scriptFactory->Create() : nullptr;
				if (script) {
					float scale = 0.5f;
					script->SetCommand(fmt::format(FMT_STRING("setscale {}"), scale));
					script->CompileAndRun(actor);
				}
			}
		}
	}
	return RE::BSEventNotifyControl::kContinue;
}