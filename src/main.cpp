#include "CallMeKevin/kProject.h"

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface * a_skse, SKSE::PluginInfo * a_info)
{
#ifndef NDEBUG
    auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
    auto path = logger::log_directory();
    if (!path) {
        return false;
    }

    *path /= "loki_CallMeKevin.log"sv;
    auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif

    auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

#ifndef NDEBUG
    log->set_level(spdlog::level::trace);
#else
    log->set_level(spdlog::level::info);
    log->flush_on(spdlog::level::info);
#endif

    spdlog::set_default_logger(std::move(log));
    spdlog::set_pattern("%g(%#): [%^%l%$] %v"s);

    logger::info("loki_CallMeKevin v1");

    a_info->infoVersion = SKSE::PluginInfo::kVersion;
    a_info->name = "loki_CallMeKevin";
    a_info->version = 1;

    if (a_skse->IsEditor()) {
        logger::critical("Loaded in editor, marking as incompatible"sv);
        return false;
    }

    const auto ver = a_skse->RuntimeVersion();
    if (ver < SKSE::RUNTIME_1_5_39) {
        logger::critical(FMT_STRING("Unsupported runtime version {}"), ver.string());
        return false;
    }

    return true;
}

static void SKSEMessageHandler(SKSE::MessagingInterface::Message* message) {

    switch (message->type) {
    case SKSE::MessagingInterface::kNewGame:
    case SKSE::MessagingInterface::kPostLoadGame: {
        break;
    }
    case SKSE::MessagingInterface::kPostLoad: {
        break;
    }
    default:
        break;
    }

}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface * a_skse)
{
    logger::info("CallMeKevin loaded");
    SKSE::Init(a_skse);
    SKSE::AllocTrampoline(128);

    auto ptr = Loki_CallMeKevin::GetSingleton();
    if (ptr->EnemySpawn) {
        Loki_CallMeKevin::InjectDamageHook();
    }
    if (ptr->CheeseSpawn) {
        Loki_CallMeKevin::InjectCheeseHook();
    }
    if (ptr->SweetrollSpawn) {
        Loki_CallMeKevin::InjectSweetrollHook();
    }
    if (ptr->EquipCosts) {
        Loki_CallMeKevin::EquipCostsYou();
    }
    if (ptr->AllCops) {
        Loki_CallMeKevin::ACAB();
    }
    if (ptr->PoniesForAll) {
        Loki_CallMeKevin::GiveMeAPony();
    }
    if (ptr->ImpactPotions) {
        Loki_CallMeKevin::PotionsImpact();
    }

    return true;
}