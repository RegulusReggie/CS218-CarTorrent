/*
 * SegPacket.cpp
 *
 *  Created on: Nov 23, 2017
 *      Author: Reggie
 */

#ifndef SRC_SEGPACKET_H_
#define SRC_SEGPACKET_H_

#include "SegPacketMessage_m.h"

class SegPacket {
    public:
        SegPacket(std::string pid, SegPacketMessage* spm, simtime_t ts) {
            m_packet_id = pid;
            m_seg_num = spm->getSegNum();
            m_size = spm->getDataArraySize();
            m_data = (unsigned char*) malloc(m_size);
            for (int i = 0; i < m_size; i++)
                m_data[i] = spm->getData(i);
            m_timestamp = ts;
        }

        ~SegPacket() {
            free(m_data);
        }

        std::string getPacketId() const { return m_packet_id; }
        int getSegNum() const { return m_seg_num; }
        unsigned char* getData() const { return m_data; }
        simtime_t getTimestamp() const { return m_timestamp; }
        size_t getDataSize() const { return m_size; }
        void setTimestamp(simtime_t ts) { m_timestamp = ts; }

    private:
        std::string m_packet_id;
        int m_seg_num;
        unsigned char* m_data;
        simtime_t m_timestamp;
        size_t m_size;
};

#endif /* SRC_SEGPACKET_H_ */

