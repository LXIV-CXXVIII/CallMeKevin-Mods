#pragma once

class AllCopsAreBastards : public RE::BSTEventSink<RE::TESActivateEvent> {

public:
    static AllCopsAreBastards* GetSingleton();

    auto ProcessEvent(const RE::TESActivateEvent* a_event, RE::BSTEventSource<RE::TESActivateEvent>* a_eventSource)->RE::BSEventNotifyControl override;

protected:
    AllCopsAreBastards() = default;
    AllCopsAreBastards(const AllCopsAreBastards&) = delete;
    AllCopsAreBastards(AllCopsAreBastards&&) = delete;
    virtual ~AllCopsAreBastards() = default;

    auto operator=(const AllCopsAreBastards&)->AllCopsAreBastards & = delete;
    auto operator=(AllCopsAreBastards&&)->AllCopsAreBastards & = delete;
};