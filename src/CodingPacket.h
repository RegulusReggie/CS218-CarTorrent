/*
 * CodingPacket.h
 *
 *  Created on: Dec 3, 2017
 *      Author: Reggie
 */

#ifndef SRC_CODINGPACKET_H_
#define SRC_CODINGPACKET_H_

#include "NetworkCodingMessage_m.h"

class CodingPacket {
    public:
        CodingPacket(std::string pid, NetworkCodingMessage* ncm, simtime_t ts) {
            m_packet_id = pid;
            m_file_size = ncm->getFileSize();
            m_gen = ncm->getGen();
            m_num_blocks_gen = ncm->getNumBlocksGen();
            m_block_size = ncm->getBlockSize();
            m_coding_num = ncm->getCodingNum();

            m_coeffs_size = ncm->getCoeffsArraySize();
            m_coeffs = (unsigned char*) malloc(m_coeffs_size);
            for (int i = 0; i < m_coeffs_size; i++)
                m_coeffs[i] = ncm->getCoeffs(i);

            m_sums_size = ncm->getSumsArraySize();
            m_sums = (unsigned char*) malloc(m_sums_size);
            for (int i = 0; i < m_sums_size; i++)
                m_sums[i] = ncm->getSums(i);

            m_timestamp = ts;
        }

        ~CodingPacket() {
            free(m_coeffs);
            free(m_sums);
        }

        std::string getPacketId() const { return m_packet_id; }
        long getFileSize() const { return m_file_size; }
        int getGen() const { return m_gen; }
        int getNumBlocksGen() const { return m_num_blocks_gen; }
        int getBlockSize() const { return m_block_size; }
        int getCodingNum() const { return m_coding_num; }
        size_t getCoeffsSize() const { return m_coeffs_size; }
        size_t getSumsSize() const { return m_sums_size; }
        unsigned char* getCoeffs() const { return m_coeffs; }
        unsigned char* getSums() const { return m_sums; }
        simtime_t getTimestamp() const { return m_timestamp; }
        void setTimestamp(simtime_t ts) { m_timestamp = ts; }

    private:
        std::string m_packet_id;
        long m_file_size;
        int m_gen;
        int m_num_blocks_gen;
        int m_block_size;
        int m_coding_num;
        unsigned char* m_coeffs;
        unsigned char* m_sums;
        simtime_t m_timestamp;
        size_t m_coeffs_size;
        size_t m_sums_size;
};

#endif /* SRC_CODINGPACKET_H_ */
