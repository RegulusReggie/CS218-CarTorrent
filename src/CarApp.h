/*
 * CarApp.h
 *
 *  Created on: Nov 7, 2017
 *      Author: Reggie
 */

#ifndef SRC_CARAPP_H_
#define SRC_CARAPP_H_

#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"
#include "lib/coding/codetorrentencoder.h"
#include "lib/coding/codetorrentdecoder.h"
#include "lib/coding/CodeTorrentUtility.h"
#include "SegPacketMessage_m.h"
#include "CacheInfoMessage_m.h"
#include "PacketRequestMessage_m.h"
#include "NetworkCodingMessage_m.h"
#include "SegPacket.h"
#include "CodingPacket.h"
#include "InfoEntry.h"
#include "FileEntry.h"
#include "Commons.h"
#include <unordered_map>
#include <set>

typedef std::unordered_map<std::string, std::string*> packet_t;
typedef std::unordered_map<std::string, int> seg_counts_t;
typedef std::unordered_map<std::string, size_t*> packet_size_t;
typedef std::unordered_map<std::string, simtime_t> start_time_t;
typedef std::unordered_map<std::string, codetorrentdecoder*> decoder_t;
typedef std::unordered_map<std::string, std::set<int>> coding_seg_t;
typedef std::set<std::string> complete_t;
typedef std::unordered_map<int, simtime_t> neighbors_t;
typedef std::set<int> id_set_t;
typedef std::unordered_map<int, id_set_t> file_seg_neigh_t;
typedef std::unordered_map<std::string, file_seg_neigh_t> neighbor_file_count_t;


using Veins::TraCIMobility;
using Veins::TraCICommandInterface;
//using Veins::AnnotationManager; //add for annotations

class CarApp : public BaseWaveApplLayer {
    public:
        ~CarApp();
        virtual void initialize(int stage);

    protected:
        simtime_t lastDroveAt;
        bool sentMessage;
        int currentSubscribedServiceId;
    protected:
        virtual void onWSM(WaveShortMessage* wsm);

        virtual void handleLowerMsg(cMessage* msg);
        virtual void handleSelfMsg(cMessage* msg);
        virtual void handlePositionUpdate(cObject* obj);

        void onSPM(SegPacketMessage* spm);
        void cacheSPM(SegPacketMessage* spm);
        void onCIM(CacheInfoMessage* cim);
        void onPRM(PacketRequestMessage* prm);
        void onNCM(NetworkCodingMessage* ncm);
        void cacheNCM(NetworkCodingMessage* ncm);

    private:
        SegPacket** cache;
        CodingPacket** cache_ncm;
        int cache_capacity = 0;
        int cache_size;
        int num_hop_allowed = 1;
        bool merge_info_allowed = false;
        packet_t packets;
        seg_counts_t packet_seg_counts;
        packet_size_t packet_size;
        std::vector<InfoEntry*> info_table;
        std::vector<FileEntry*> file_table;
        bool cache_updated;
        start_time_t packet_start_time;
        decoder_t decoderref;
        complete_t packet_complete;
        coding_seg_t packet_coding_segs;
        neighbors_t neighbors;
        neighbor_file_count_t neighbor_file_count;

        CodeTorrentUtility* ctu;
        bool network_coding = false;

        // helper function
        void printMessage(std::string msg, int type = 0);
        InfoEntry* findInfoEntry(std::string id, int seg);
        void writeFile(std::string blockStorageId, CodedBlockPtr block);
        CodedBlockPtr getFile(std::string blockStorageId);
        void writeFile(std::string filename, const unsigned char* content, size_t size);
        void getFile(std::string filename, unsigned char* content, size_t fileSize);
        void getDataFromSpm(SegPacketMessage* spm, unsigned char* content);
        std::string gen_random_string(int length);
        int getNumNeighborsWithFileSeg(std::string id, int seg);

        int stats_num_msg_sent = 0;
        int stats_num_msg_received = 0;

        void refreshDisplay() const;
};

#endif /* SRC_CARAPP_H_ */
