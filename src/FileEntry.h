/*
 * FileEntry.h
 *
 *  Created on: Dec 13, 2017
 *      Author: Reggie
 */

#ifndef SRC_FILEENTRY_H_
#define SRC_FILEENTRY_H_

class FileEntry {
    public:
        FileEntry(int addr, std::string pid, int seg_num) {
            m_packet_id = pid;
            m_seg_num = seg_num;
            m_addr = addr;
            m_hops = 0;
        }

        FileEntry() {
            m_packet_id = "";
            m_seg_num = -1;
            m_addr = -1;
            m_hops = 0;
        }

        FileEntry(FileEntry& other) {
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

#endif /* SRC_FILEENTRY_H_ */
