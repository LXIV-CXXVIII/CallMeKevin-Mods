#pragma once

class ImpactfulPotions : public RE::BSTEventSink<RE::TESMagicEffectApplyEvent> {

public:
    static ImpactfulPotions* GetSingleton();

    auto ProcessEvent(const RE::TESMagicEffectApplyEvent* a_event, RE::BSTEventSource<RE::TESMagicEffectApplyEvent>* a_eventSource)->RE::BSEventNotifyControl override;

protected:
    ImpactfulPotions() = default;
    ImpactfulPotions(const ImpactfulPotions&) = delete;
    ImpactfulPotions(ImpactfulPotions&&) = delete;
    virtual ~ImpactfulPotions() = default;

    auto operator=(const ImpactfulPotions&)->ImpactfulPotions & = delete;
    auto operator=(ImpactfulPotions&&)->ImpactfulPotions & = delete;

};