#pragma once

#include "SimulationData.cuh"

__global__ void cudaNextTimestep_prepare(SimulationData data, SimulationStatistics statistics);
__global__ void cudaNextTimestep_physics_init(SimulationData data);
__global__ void cudaNextTimestep_physics_fillMaps(SimulationData data);
__global__ void cudaNextTimestep_physics_calcFluidForces(SimulationData data);  //requires threads/block = (ceilf(smoothingLength * 2) * 2 + 1)^2
__global__ void cudaNextTimestep_physics_calcCollisionForces(SimulationData data);
__global__ void cudaNextTimestep_physics_applyForces(SimulationData data);
__global__ void cudaNextTimestep_physics_verletPositionUpdate(SimulationData data);
__global__ void cudaNextTimestep_physics_calcConnectionForces(SimulationData data, bool considerAngles);
__global__ void cudaNextTimestep_physics_verletVelocityUpdate(SimulationData data);
__global__ void cudaNextTimestep_cellFunction_prepare_substep1(SimulationData data);
__global__ void cudaNextTimestep_cellFunction_prepare_substep2(SimulationData data);
__global__ void cudaNextTimestep_cellFunction_nerve(SimulationData data, SimulationStatistics statistics);
__global__ void cudaNextTimestep_cellFunction_neuron(SimulationData data, SimulationStatistics statistics);
__global__ void cudaNextTimestep_cellFunction_constructor_completenessCheck(SimulationData data, SimulationStatistics statistics);
__global__ void cudaNextTimestep_cellFunction_constructor_process(SimulationData data, SimulationStatistics statistics);
__global__ void cudaNextTimestep_cellFunction_injector(SimulationData data, SimulationStatistics statistics);
__global__ void cudaNextTimestep_cellFunction_attacker(SimulationData data, SimulationStatistics statistics);
__global__ void cudaNextTimestep_cellFunction_defender(SimulationData data, SimulationStatistics statistics);
__global__ void cudaNextTimestep_cellFunction_transmitter(SimulationData data, SimulationStatistics statistics);
__global__ void cudaNextTimestep_cellFunction_muscle(SimulationData data, SimulationStatistics statistics);
__global__ void cudaNextTimestep_cellFunction_sensor(SimulationData data, SimulationStatistics statistics);
__global__ void cudaNextTimestep_cellFunction_reconnector(SimulationData data, SimulationStatistics statistics);
__global__ void cudaNextTimestep_cellFunction_detonator(SimulationData data, SimulationStatistics statistics);
__global__ void cudaNextTimestep_physics_applyInnerFriction(SimulationData data);
__global__ void cudaNextTimestep_physics_applyFriction(SimulationData data);
__global__ void cudaNextTimestep_structuralOperations_substep1(SimulationData data);
__global__ void cudaNextTimestep_structuralOperations_substep2(SimulationData data);
__global__ void cudaNextTimestep_structuralOperations_substep3(SimulationData data);
__global__ void cudaNextTimestep_structuralOperations_substep4(SimulationData data);
__global__ void cudaNextTimestep_structuralOperations_substep5(SimulationData data);

__global__ void cudaInitClusterData(SimulationData data);
__global__ void cudaFindClusterIteration(SimulationData data);
__global__ void cudaFindClusterBoundaries(SimulationData data);
__global__ void cudaAccumulateClusterPosAndVel(SimulationData data);
__global__ void cudaAccumulateClusterAngularProp(SimulationData data);
__global__ void cudaApplyClusterData(SimulationData data);

__global__ void cudaResetDensity(SimulationData data);
