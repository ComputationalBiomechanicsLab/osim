#include <OpenSim/Analyses/RegisterTypes_osimAnalyses.h>
#include <OpenSim/Common/RegisterTypes_osimCommon.h>
#include <OpenSim/Simulation/RegisterTypes_osimSimulation.h>
#include <OpenSim/Tools/RegisterTypes_osimTools.h>
#include <OpenSim/Actuators/RegisterTypes_osimActuators.h>
#include <OpenSim/ExampleComponents/RegisterTypes_osimExampleComponents.h>

int main(int argc, char** argv)
{
    RegisterTypes_osimCommon();
    RegisterTypes_osimSimulation();
    RegisterTypes_osimActuators();
    RegisterTypes_osimAnalyses();
    RegisterTypes_osimTools();
    RegisterTypes_osimExampleComponents();
    return 0;
}
