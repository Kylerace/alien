﻿#pragma once

#include "Base.cuh"
#include "Definitions.cuh"

struct AddConnectionOperation {
    bool addTokens;
    Cell* cell;
    Cell* otherCell;
};

struct DelConnectionsOperation
{
    Cell* cell;
};

struct DelConnectionOperation
{
    Cell* cell1;
    Cell* cell2;
};

struct DelCellOperation
{
    Cell* cell;
    int cellIndex;
};

struct DelCellAndConnectionOperations
{
    Cell* cell;
    int cellIndex;
};

union OperationData
{
    AddConnectionOperation addConnectionOperation;
    DelConnectionsOperation delConnectionsOperation;
    DelConnectionOperation delConnectionOperation;
    DelCellOperation delCellOperation;
    DelCellAndConnectionOperations delCellAndConnectionOperation;
};

struct Operation
{
    enum class Type
    {
        AddConnections,
        DelConnections,
        DelConnection,
        DelCell,
        DelCellAndConnections,
    };
    Type type;
    OperationData data;
};
