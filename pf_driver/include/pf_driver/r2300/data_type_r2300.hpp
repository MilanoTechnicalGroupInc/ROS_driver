#include "pf_driver/data_type.h"

#pragma pack(1)

struct PacketHeaderR2300 : public PacketHeader {
    std::uint16_t magic;                //magic byte (0xa25c) marking the beginning of a packet
    std::uint16_t packet_type;          //scan data packet type (0x0041 - 'A'; 0x0042 - 'B'; 0x0043 - 'C')
    std::uint32_t packet_size;          //overall packet size in bytes (header + payload)
    std::uint16_t header_size;          //header size in bytes (offset to payload data)
    std::uint16_t scan_number;          //sequence number for scan (incremented for every scan, starting with 0, overflows)
    std::uint16_t packet_number;        //sequence number for packet (counting packets of a particular scan, starting with 1)
    std::uint16_t layer_index;          //vertical layer index (0..3)
    std::int32_t layer_inclination;     //vertical layer inclination [1/10000 degree]
    std::uint64_t timestamp_raw;        //raw timestamp of first scan point in this packet in NTP time format
    std::uint64_t reserved1;            //reserved - all bits zero for devices without switching I/Q
    std::uint32_t status_flags;         //scan status flags (TODO: should this be a struct? or provide masking to extract specific flags)
    std::uint32_t scan_frequency;       //frequency of head rotation  (1/1000Hz)
    std::uint16_t num_points_scan;      //number of scan points (samples) within complete scan
    std::uint16_t num_points_packet;    //total number of scan points within this packet
    std::uint16_t first_index;          //index of first scan point within this packet
    std::int32_t first_angle;           //absolute angle of first scan point within this packet  (1/10000°)
    std::int32_t angular_increment;     //delta between two succeding scan points (1/10000°); CCW rotation: +ve, CW rotation: -ve
    std::uint32_t reserved2;            //reserved - all bits zero for devices without switching I/Q
    std::uint32_t reserved3;            //reserved - all bits zero for devices without switching I/Q
    std::uint64_t reserved4;            //reserved - all bits zero for devices without switching I/Q
    std::uint64_t reserved5;            //reserved - all bits zero for devices without switching I/Q
};

struct PacketTypeC1 : public PacketType {   //distance and amplitude (compact)
    PacketHeaderR2300 header;
    struct Data {
        std::uint32_t distance:20;          //distance 20 bit, amplitude 12 bit
        std::uint16_t amplitude:12;         //distance 20 bit, amplitude 12 bit
    };
    Data data;
};

#pragma pack()