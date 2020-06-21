/**
    The code was written as a part of network implementation for Final Year Project at
                          The University of Dar es Salaam.

    ===========================================================================================
          Author: Emmanuel Julius Samson
           Reg #: 2016-04-01802
          Degree: B.Sc. Telecommmunications Engineering (2020)
       FYP Title: IP Networks QoS Optimization using ML and SDN
    ===========================================================================================


                              A simplified extract of the UDSM LAN
                    NB: The FW/BW node has not been implemented in the code
     _________________________________________________________________________________________
    |                                                                                         |
    |                                 Gateway Router to Selcom                                |
    |                                           |                                             |
    |                                           |                                             |
    |                                         FW/BW                                           |
    |                                           |                                             |
    |                                           |                                             |
    |                                 Core Distribution switch                                |
    |                                           |                                             |
    |                                           |                                             |
    |   ===========================================================================           |
    |   |                |             |             |             |              |           |
    |   |                |             |             |             |              |           |
    | Maths_Switch    Old_Library     CoET        Halls        CoICT_Router   New_Lib_Router  |
    |   |                |             |             |             |              |           |
    |   |                |             |             |             |              |           |
    | Switch           Switch        Switch        Switch         Switch        Switch        |
    | To_Depts        To_Depts      To_Blocks      To_Halls     To_Blocks       To_Floors     |
    |                                                                                         |
    |_________________________________________________________________________________________|


    ===========================================================================================

    Tasks:
      1. Create the network nodes
      2. Install the internet stack on each of the nodes
      3. Attach one or more network devices on each node and attach the device to channel
      4. Create the network interface for each network device
      5. Assign an IP address to each network interface

    ===========================================================================================

    Necessary Configurations:
    ---------------------------------------------------------------------------------------
    Routers:
      1. Gateway        : routers[0]    -- subnet1
      2. CoICT_Router   : routers[1]    -- subnet6
      3. New_Lib_Router : routers[2]    -- subnet7

    Distribution Switches:
      1. Core Distribution Swich : distribution_switches[0]   -- subnet1 || subnet 2 - 7
      2. Maths                   : distribution_switches[1]   -- subnet2
      3. Old Library             : distribution_switches[2]   -- subnet3
      4. CoET                    : distribution_switches[3]   -- subnet4
      5. Halls                   : distribution_switches[4]   -- subnet5

    Access switches:
      1. Maths/To_Departments         : access_switches[0]    -- subnet20
      2. Old_Library/To_Departments   : access_switches[1]    -- subnet30
      3. CoET/To_Blocks               : access_switches[2]    -- subnet40
      4. Halls/To_Halls               : access_switches[3]    -- subnet50
      5. CoICT_Router/To_Blocks       : access_switches[4]    -- subnet60
      6. New_Lib_Router/To_Floors     : access_switches[5]    -- subnet70

    ---------------------------------------------------------------------------------------


    ===========================================================================================

*/

// C++ specific libraries:
#include <string>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"

using namespace ns3;

int main (int argc, char *argv[]){

  // Declare some constants
  const int ROUTERS = 3;
  const int DISTRIBUTION_SWITCHES = 5;
  const int ACCESS_SWITCHES = 6;

  // Create the Network nodes
  NodeContainer routers, distribution_switches, access_switches;

  routers.Create(ROUTERS);
  distribution_switches.Create(DISTRIBUTION_SWITCHES);
  access_switches.Create(ACCESS_SWITCHES);

  // Install the internet stack on each network node above
  InternetStackHelper stack;
  stack.Install(routers);
  stack.Install(distribution_switches);
  stack.Install(access_switches);

  // Create a point-to-point helper
  PointToPointHelper p2p;

  // Create an address helper
  Ipv4AddressHelper address;

  // Configuring the subnets
  // Create a node container to hold the nodes that belong to subnet 1 and add
  // worstation 1 and router 1
  NodeContainer subnet1;
  NodeContainer subnet2, subnet3, subnet4;
  NodeContainer subnet5, subnet6, subnet7;
  NodeContainer subnet20, subnet30, subnet40, subnet50, subnet60, subnet70;

  // Subnet 1 Configuration
  subnet1.Add(routers.Get(0));
  subnet1.Add(distribution_switches.Get(0));

  NetDeviceContainer subnet1Devices = p2p.Install(subnet1);

  address.SetBase("10.1.1.0", "255.255.255.0");

  Ipv4InterfaceContainer subnet1Interfaces = address.Assign(subnet1Devices);


  // Subnet 2 Configuration
  subnet2.Add(distribution_switches.Get(0));
  subnet2.Add(distribution_switches.Get(1));
  NetDeviceContainer subnet2Devices = p2p.Install(subnet2);
  address.SetBase("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet2Interfaces = address.Assign(subnet2Devices);

  // Subnet 20 Configuration
  subnet20.Add(distribution_switches.Get(1));
  subnet20.Add(access_switches.Get(0));
  NetDeviceContainer subnet20Devices = p2p.Install(subnet20);
  address.SetBase("10.1.20.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet20Interfaces = address.Assign(subnet20Devices);


  // Subnet 3 Configuration
  subnet3.Add(distribution_switches.Get(0));
  subnet3.Add(distribution_switches.Get(2));
  NetDeviceContainer subnet3Devices = p2p.Install(subnet3);
  address.SetBase("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet3Interfaces = address.Assign(subnet3Devices);

  // Subnet 30 Configuration
  subnet30.Add(distribution_switches.Get(2));
  subnet30.Add(access_switches.Get(1));
  NetDeviceContainer subnet30Devices = p2p.Install(subnet30);
  address.SetBase("10.1.30.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet30Interfaces = address.Assign(subnet30Devices);

  // Subnet 4 Configuration
  subnet4.Add(distribution_switches.Get(0));
  subnet4.Add(distribution_switches.Get(3));
  NetDeviceContainer subnet4Devices = p2p.Install(subnet4);
  address.SetBase("10.1.4.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet4Interfaces = address.Assign(subnet4Devices);

  // Subnet 40 Configuration
  subnet40.Add(distribution_switches.Get(3));
  subnet40.Add(access_switches.Get(2));
  NetDeviceContainer subnet40Devices = p2p.Install(subnet40);
  address.SetBase("10.1.40.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet40Interfaces = address.Assign(subnet40Devices);

  // Subnet 5 Configuration
  subnet5.Add(distribution_switches.Get(0));
  subnet5.Add(distribution_switches.Get(4));
  NetDeviceContainer subnet5Devices = p2p.Install(subnet5);
  address.SetBase("10.1.5.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet5Interfaces = address.Assign(subnet5Devices);

  // Subnet 50 Configuration
  subnet50.Add(distribution_switches.Get(4));
  subnet50.Add(access_switches.Get(3));
  NetDeviceContainer subnet50Devices = p2p.Install(subnet50);
  address.SetBase("10.1.50.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet50Interfaces = address.Assign(subnet50Devices);

  // Subnet 6 Configuration
  subnet6.Add(distribution_switches.Get(0));
  subnet6.Add(distribution_switches.Get(5));
  NetDeviceContainer subnet6Devices = p2p.Install(subnet6);
  address.SetBase("10.1.6.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet6Interfaces = address.Assign(subnet6Devices);

  // Subnet 60 Configuration
  subnet60.Add(distribution_switches.Get(5));
  subnet60.Add(access_switches.Get(4));
  NetDeviceContainer subnet60Devices = p2p.Install(subnet60);
  address.SetBase("10.1.60.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet60Interfaces = address.Assign(subnet60Devices);

  // Subnet 7 Configuration
  subnet7.Add(distribution_switches.Get(0));
  subnet7.Add(distribution_switches.Get(6));
  NetDeviceContainer subnet7Devices = p2p.Install(subnet7);
  address.SetBase("10.1.7.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet7Interfaces = address.Assign(subnet7Devices);

  // Subnet 70 Configuration
  subnet70.Add(distribution_switches.Get(6));
  subnet70.Add(access_switches.Get(5));
  NetDeviceContainer subnet70Devices = p2p.Install(subnet70);
  address.SetBase("10.1.70.0", "255.255.255.0");
  Ipv4InterfaceContainer subnet70Interfaces = address.Assign(subnet70Devices);


  // Run the simulator
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}
