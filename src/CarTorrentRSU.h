/*
 * RSU.h
 *
 *  Created on: Nov 20, 2017
 *      Author: Reggie
 */

#ifndef SRC_CARTORRENTRSU_H_
#define SRC_CARTORRENTRSU_H_

#include "lib/coding/codetorrentencoder.h"

#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "SegPacketMessage_m.h"
#include "NetworkCodingMessage_m.h"
#include "Commons.h"

class CarTorrentRSU : public BaseWaveApplLayer {
    public:
        ~CarTorrentRSU();
    protected:
        virtual void initialize(int stage);
        virtual void onWSM(WaveShortMessage* wsm);
        virtual void onWSA(WaveServiceAdvertisment* wsa);
        virtual void handleSelfMsg(cMessage* msg);
        void populateSPM(SegPacketMessage* spm, int numSegs, std::string packetId, int segNum, const unsigned char* data, size_t data_size);
        void populateNCM(NetworkCodingMessage* ncm, const char* id, CodedBlockPtr block, int coding_num, size_t filesize);

    private:
        int packet_size;
        std::string packet_id = "testfile";
        SegPacketMessage** spm_segs;
        bool useNetworkCoding = false;
        codetorrentencoder* encoderref;
        int coding_generated = 0;
        int stats_num_msg_sent = 0;

        void refreshDisplay() const;
};


#endif /* SRC_CARTORRENTRSU_H_ */
