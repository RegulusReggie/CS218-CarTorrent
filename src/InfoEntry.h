/*
 * InfoEntry.cpp
 *
 *  Created on: Nov 23, 2017
 *      Author: Reggie
 */

#ifndef SRC_INFOENTRY_H_
#define SRC_INFOENTRY_H_

class InfoEntry {
    public:
        InfoEntry(int addr, std::string pid, int seg_num) {
            m_packet_id = pid;
            m_seg_num = seg_num;
            m_addr = addr;
            m_hops = 0;
        }

        InfoEntry() {
            m_packet_id = "";
            m_seg_num = -1;
            m_addr = -1;
            m_hops = 0;
        }

        InfoEntry(InfoEntry& other) {
            m_packet_id = other.getPacketId();
            m_seg_num = other.getSegNum();
            m_addr = other.getAddress();
            m_hops = other.getHops();
        }

        std::string getPacketId() const { return m_packet_id; }
        int getSegNum() const { return m_seg_num; }
        int getAddress() const { return m_addr; }
        void setAddress(int addr) { m_addr = addr; }
        int getHops() const { return m_hops; }
        void setHops(int h) { m_hops = h; }

    private:
        std::string m_packet_id;
        int m_seg_num;
        int m_addr;
        int m_hops;
};

#endif /* SRC_INFOENTRY_H_ */
