#pragma once

class EquippingCostsMoney : public RE::BSTEventSink<RE::TESEquipEvent> {

public:
    static EquippingCostsMoney* GetSingleton();

    auto ProcessEvent(const RE::TESEquipEvent* a_event, RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource)->RE::BSEventNotifyControl override;

protected:
    EquippingCostsMoney() = default;
    EquippingCostsMoney(const EquippingCostsMoney&) = delete;
    EquippingCostsMoney(EquippingCostsMoney&&) = delete;
    virtual ~EquippingCostsMoney() = default;

    auto operator=(const EquippingCostsMoney&)->EquippingCostsMoney & = delete;
    auto operator=(EquippingCostsMoney&&)->EquippingCostsMoney & = delete;

};