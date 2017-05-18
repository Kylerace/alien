#ifndef FACTORYFACADE_H
#define FACTORYFACADE_H

#include <QtGlobal>
#include <QVector2D>

#include "model/Entities/CellTO.h"
#include "model/Features/CellFeatureEnums.h"
#include "model/Entities/Descriptions.h"

#include "Definitions.h"

class BuilderFacade
{
public:
	virtual ~BuilderFacade() = default;

	virtual SimulationController* buildSimulationController(int maxRunngingThreads, IntVector2D gridSize, IntVector2D universeSize
		, SymbolTable* symbolTable, SimulationParameters* parameters) const = 0;
	virtual SimulationAccess* buildSimulationAccess(SimulationContextApi* context) const = 0;
	virtual SymbolTable* buildDefaultSymbolTable() const = 0;
	virtual SimulationParameters* buildDefaultSimulationParameters() const = 0;
};

#endif // FACTORYFACADE_H
