#include "disco_elysium_ripoffEditor.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

IMPLEMENT_GAME_MODULE(Fdisco_elysium_ripoffEditorModule, disco_elysium_ripoffEditor);

DEFINE_LOG_CATEGORY(disco_elysium_ripoffEditor)

#define LOCTEXT_NAMESPACE "disco_elysium_ripoffEditor"

void Fdisco_elysium_ripoffEditorModule::StartupModule()
{
    UE_LOG(disco_elysium_ripoffEditor, Warning, TEXT("disco_elysium_ripoffEditor: Log Started"));
}

void Fdisco_elysium_ripoffEditorModule::ShutdownModule()
{
    UE_LOG(disco_elysium_ripoffEditor, Warning, TEXT("disco_elysium_ripoffEditor: Log Ended"));
}

#undef LOCTEXT_NAMESPACE
