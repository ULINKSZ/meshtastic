#pragma once
#include <NodeDB.h>
#include <cstdint>
#define ONE_DAY 24 * 60 * 60
#define ONE_MINUTE_MS 60 * 1000

<<<<<<< HEAD
#define default_gps_update_interval IF_ROUTER(ONE_DAY, 2 * 60)
#define default_telemetry_broadcast_interval_secs IF_ROUTER(ONE_DAY / 2, 30 * 60)
#define default_broadcast_interval_secs IF_ROUTER(ONE_DAY / 2, 15 * 60)
=======
#define default_gps_update_interval IF_ROUTER(ONE_DAY, 1 * 60)
#define default_telemetry_broadcast_interval_secs IF_ROUTER(ONE_DAY / 2, 30 * 60)
#define default_broadcast_interval_secs IF_ROUTER(ONE_DAY / 2, 2 * 60)
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
#define default_wait_bluetooth_secs IF_ROUTER(1, 60)
#define default_sds_secs IF_ROUTER(ONE_DAY, UINT32_MAX) // Default to forever super deep sleep
#define default_ls_secs IF_ROUTER(ONE_DAY, 5 * 60)
#define default_min_wake_secs 10
<<<<<<< HEAD
#define default_screen_on_secs IF_ROUTER(1, 60 * 10)
#define default_node_info_broadcast_secs 3 * 60 * 60
#define min_node_info_broadcast_secs 60 * 60 // No regular broadcasts of more than once an hour
=======
#define default_screen_on_secs IF_ROUTER(1, 30 * 1)
#define default_node_info_broadcast_secs  2 * 60
#define min_node_info_broadcast_secs 1 * 60 // No regular broadcasts of more than once an hour
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447

#define default_mqtt_address "mqtt.meshtastic.org"
#define default_mqtt_username "meshdev"
#define default_mqtt_password "large4cats"
#define default_mqtt_root "msh"

<<<<<<< HEAD
#define IF_ROUTER(routerVal, normalVal) \
=======
#define IF_ROUTER(routerVal, normalVal)                                                                                          \
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
    ((config.device.role == meshtastic_Config_DeviceConfig_Role_ROUTER) ? (routerVal) : (normalVal))

class Default
{
<<<<<<< HEAD
public:
=======
  public:
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
    static uint32_t getConfiguredOrDefaultMs(uint32_t configuredInterval);
    static uint32_t getConfiguredOrDefaultMs(uint32_t configuredInterval, uint32_t defaultInterval);
    static uint32_t getConfiguredOrDefault(uint32_t configured, uint32_t defaultValue);
    static uint32_t getConfiguredOrDefaultMsScaled(uint32_t configured, uint32_t defaultValue, uint32_t numOnlineNodes);
    static uint8_t getConfiguredOrDefaultHopLimit(uint8_t configured);

<<<<<<< HEAD
private:
    static float congestionScalingCoefficient(int numOnlineNodes)
    {
        if (numOnlineNodes <= 40)
        {
            return 1.0; // No scaling for 40 or fewer nodes
        }
        else
        {
=======
  private:
    static float congestionScalingCoefficient(int numOnlineNodes)
    {
        if (numOnlineNodes <= 40) {
            return 1.0; // No scaling for 40 or fewer nodes
        } else {
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
            // Sscaling based on number of nodes over 40
            int nodesOverForty = (numOnlineNodes - 40);
            return 1.0 + (nodesOverForty * 0.075); // Each number of online node scales by 0.075
        }
    }
};