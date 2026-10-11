#include "etc_controller.h"
#include "mbed.h"
#include <cstdio>

PinName PC1, PC2;

ETCController etc{PC1, PC2};

CAN can{PB_8, PB_9, 500000};

// Predefined for use in main()
void send_etc_CAN_messages();
void send_sme_CAN_messages();

int main() {
    printf("Hello World!!\n");

    /*
        Make send_CAN messages loop consistently
        at 20hz (20 messages / second)
    */



    // No need to edit this while loop
    while (true) {
        // Must implement in etc/ subfolder
        etc.update_state();
    }

    return 0;
}

/* 
    Must send the VCU_TPDO_STATUS CAN message with
    VCU_ETC_READY_TO_DRIVE & VCU_ETC_MOTOR_ENABLED
    set to 1, and VCU_ETC_IMPLAUS_APPS_OUT_OF_RANGE
    & VCU_ETC_IMPLAUS_APPS_DEVIATION properly added.
*/
void send_etc_CAN_messages() {   
    uint8_t vcu_tpdo_status[8];
    
    // sets first two bits of message to 1
    vcu_tpdo_status[0] |= 1 << 1;
    vcu_tpdo_status[0] |= 1 << 2;

    // sets 5th adn 7th bits to whatever etc.READY_TO_DRIVE evaluated to (0 or 1)
    vcu_tpdo_status[0] |= etc.READY_TO_DRIVE << 5;
    vcu_tpdo_status[0] |= etc.READY_TO_DRIVE << 7;

    // sets all remaining bits to 0
    for (int byte = 0; byte < 8; byte++){
        for (int i = 0; i < 8; i++) {
            if (i != 0 || i != 2 || i != 4 || i != 6) {
                vcu_tpdo_status[byte] &= ~(1 << (i + 1));
            }
        }
    }
    CANMessage status_msg{403, vcu_tpdo_status, 8};
    can.write(status_msg);
}

/*
    Must send the SME_RPDO_Throttle_Demand CAN
    message with SME_THROTL_TorqueDemand set to the
    torque demand determined by the ETC.
*/
void send_sme_CAN_messages() {}

/*
    CAN NODE - has CAN tranceiver that feeds its output into the MCU.
                - tranceiver converts from "CAN logic" into Digital Logic.

    CAN Bus - it's a twisted pair of wires for CAN High & CAN Low.

    When a digital 0 is sent, both wires remain at the same recessive voltage.

    When a digital 1 is sent, both wires go to their dominant voltage (CAN High and CAN low).

    The difference between the two voltages is the information that we are trying to transmit.

    CAN Arbitration - allows for packet-prioritazation with no overhead

*/
