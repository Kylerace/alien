#include "AutosaveController.h"

#include <imgui.h>
#include "AlienImGui.h"

#include "Base/Resources.h"
#include "Base/GlobalSettings.h"
#include "EngineInterface/SerializerService.h"
#include "EngineInterface/SimulationController.h"

#include "Viewport.h"
#include "DelayedExecutionController.h"
#include "OverlayMessageController.h"
#include "SerializationHelperService.h"

/* TODOKYLER: remove
namespace
{
    auto constexpr MinutesForAutosave = 40;
}
*/

_AutosaveController::_AutosaveController(SimulationController const& simController)
    : _AlienWindow("Autosave", "windows.autosave sources", false)
    , _simController(simController)
{
    _startTimePoint = std::chrono::steady_clock::now();
    _active = GlobalSettings::getInstance().getBool("controllers.auto save.active", true);
    _minutesToAutosave = GlobalSettings::getInstance().getInt("controllers.auto save.minutes", 40);
}

_AutosaveController::~_AutosaveController()
{
    GlobalSettings::getInstance().setBool("controllers.auto save.active", _active);
    GlobalSettings::getInstance().setInt("controllers.auto save.minutes", _minutesToAutosave);
}

void _AutosaveController::shutdown()
{
    if (!_active) {
        return;
    }
    onSave();
}

bool _AutosaveController::isActive() const
{
    return _active;
}

void _AutosaveController::setActive(bool value)
{
    _active = value;
}



void _AutosaveController::processBackground()
{
    if (!_active) {
        return;
    }

    auto durationSinceStart = std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now() - *_startTimePoint).count();
    if (durationSinceStart > 0 && (durationSinceStart - _lastSave) > _minutesToAutosave) {
        _lastSave = durationSinceStart;
        printOverlayMessage("Auto saving ...");
        delayedExecution([=, this] { onSave(); });
    }
    //if (durationSinceStart > 0 && durationSinceStart % _minutesToAutosave == 1 && _alreadySaved) {
    //    _alreadySaved = false;
    //}
}

void _AutosaveController::processIntern() 
{
    AlienImGui::Checkbox(
        AlienImGui::CheckboxParameters()
            .name("active")
            .defaultValue(true)
            .tooltip("Toggle to autosave periodically"),
        _active
    );

    AlienImGui::SliderInt(
        AlienImGui::SliderIntParameters()
            .name("autosave period")
            .min(1)
            .max(1440)
            .logarithmic(true)
            .infinity(false)
            .tooltip("the simulation will autosave this many minutes"),
        &_minutesToAutosave
    );

}

void _AutosaveController::onSave()
{
    DeserializedSimulation sim = SerializationHelperService::getDeserializedSerialization(_simController);
    SerializerService::serializeSimulationToFiles(Const::AutosaveFile, sim);
}