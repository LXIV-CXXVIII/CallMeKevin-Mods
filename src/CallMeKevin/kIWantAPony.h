#pragma once

class IWantAPony : public RE::BSTEventSink<RE::TESActivateEvent> {

public:
    static IWantAPony* GetSingleton();

    auto ProcessEvent(const RE::TESActivateEvent* a_event, RE::BSTEventSource<RE::TESActivateEvent>* a_eventSource)->RE::BSEventNotifyControl override;

protected:
    IWantAPony() = default;
    IWantAPony(const IWantAPony&) = delete;
    IWantAPony(IWantAPony&&) = delete;
    virtual ~IWantAPony() = default;

    auto operator=(const IWantAPony&)->IWantAPony & = delete;
    auto operator=(IWantAPony&&)->IWantAPony & = delete;
};