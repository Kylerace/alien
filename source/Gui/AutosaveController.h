#pragma once

#include <chrono>

#include "EngineInterface/Definitions.h"
#include "Definitions.h"
#include "AlienWindow.h"

class _AutosaveController : public _AlienWindow
{
public:
    _AutosaveController(SimulationController const& simController);
    ~_AutosaveController();

    void shutdown();

    bool isActive() const;
    void setActive(bool value);

    void processIntern() override;
    void processBackground() override;

private:
    void onSave();

    SimulationController _simController;

    bool _active = true;
    int _minutesToAutosave = 40;
    std::optional<std::chrono::steady_clock::time_point> _startTimePoint;
    int _lastSave = 0;
    bool _alreadySaved = false;
};