/*
 * CarApp.cpp
 *
 *  Created on: Nov 7, 2017
 *      Author: Reggie
 */


#include <stdlib.h>
#include <utility>
#include "CarApp.h"
#include <stdio.h>
#include <cstdlib>

using Veins::TraCIMobilityAccess;
using Veins::AnnotationManagerAccess;

Define_Module(CarApp);

void CarApp::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);
    if (stage == 0) {
        cache_size = 0;
        cache_capacity = par("cacheCapacity").longValue();
        num_hop_allowed = par("hopsAllowed").longValue();
        merge_info_allowed = par("mergeInfoAllowed").boolValue();
        network_coding = par("networkCoding").boolValue();
        cache = new SegPacket* [cache_capacity];
        cache_ncm = new CodingPacket* [cache_capacity];
        packets.clear();
        packet_seg_counts.clear();
        packet_size.clear();
        info_table.clear();
        cache_updated = false;
        packet_start_time.clear();
        decoderref.clear();
        packet_complete.clear();
        packet_coding_segs.clear();
        ctu = new CodeTorrentUtility();
        neighbors.clear();
        srand(time(NULL));

        WaveShortMessage* periodic_self_wsm = new WaveShortMessage();
        periodic_self_wsm->setKind(PERIODIC_SELF_CHECK);
        scheduleAt(simTime() + uniform(0.01, 0.2), periodic_self_wsm);

        /*
        WaveShortMessage* wsm = new WaveShortMessage();
        wsm->setKind(FILE_REQ_MESSAGE);
        wsm->setSenderAddress(myId);
        sendDown(wsm->dup());
        delete wsm;
        */
    }
}

CarApp::~CarApp() {
    delete [] cache;
    delete [] cache_ncm;

    for (packet_t::iterator it = packets.begin(); it != packets.end(); it++) {
        delete [] it->second;
    }

    for (int i = 0; i < info_table.size(); i++) {
        delete info_table[i];
    }

    for (packet_size_t::iterator it = packet_size.begin(); it != packet_size.end(); it++)
        delete [] it->second;

    for (decoder_t::iterator it = decoderref.begin(); it != decoderref.end(); it++)
        delete it->second;

    delete ctu;
}

void CarApp::onWSM(WaveShortMessage* wsm) {
    if (wsm->getSerial() + 1 < num_hop_allowed && wsm->getSenderAddress() != myId) {
        wsm->setSerial(wsm->getSerial() + 1);
        sendDown(wsm->dup());
        stats_num_msg_sent++;
    }
}

// Regular Torrent style
void CarApp::getDataFromSpm(SegPacketMessage* spm, unsigned char* content) {
    for (int j = 0; j < spm->getDataArraySize(); j++) {
        content[j] = spm->getData(j);
    }
}

void CarApp::onSPM(SegPacketMessage* spm) {

    std::string str_id(spm->getPacketId(), 0, 256);

    if (spm->getKind() == RSU_BROADCAST_MESSAGE || spm->getRecipientAddress() == myId) {
        cacheSPM(spm);
        printMessage("received spm of packet_" + str_id
                                        + " seg_" + std::to_string(spm->getSegNum())
                                        + " from " + std::to_string(spm->getSenderAddress()), RECEIVE_PKT_MSG);

            // save packet segments
            packet_t::const_iterator got = packets.find(str_id);

            // create new packet file if non exist
            if (got == packets.end()) {
                std::string* new_packet = new std::string [spm->getNumSegs()]();
                new_packet[spm->getSegNum()] = "../files/" + gen_random_string(20);
                unsigned char* content = (unsigned char*) malloc(spm->getDataArraySize() * sizeof(unsigned char));;
                getDataFromSpm(spm, content);
                writeFile(new_packet[spm->getSegNum()], content, spm->getDataArraySize());
                free(content);
                packets[str_id] = new_packet;
                packet_seg_counts[str_id] = 1;
                packet_start_time[str_id] = simTime();
                packet_size[str_id] = new size_t[spm->getNumSegs()];
                packet_size[str_id][spm->getSegNum()] = spm->getDataArraySize();
                return;
            } else {
                std::string id = got->first;
                if (packets[id][spm->getSegNum()] == "") {
                    packets[id][spm->getSegNum()] = "../files/" + gen_random_string(20);
                    unsigned char* content = (unsigned char*) malloc(spm->getDataArraySize() * sizeof(unsigned char));;
                    getDataFromSpm(spm, content);
                    writeFile(packets[id][spm->getSegNum()], content, spm->getDataArraySize());
                    free(content);
                    packet_seg_counts[id] = packet_seg_counts[id] + 1;
                    packet_size[id][spm->getSegNum()] = spm->getDataArraySize();
                    // output packet if complete
                    if (packet_seg_counts[id] == spm->getNumSegs()) {
                                   printMessage("pakcet_" + id + " complete in "
                                           + (simTime() - packet_start_time[id]).str(), FILE_COMPLETE_MSG);
                                   std::string out_file = "../files/" + std::to_string(myId) + "_" + id;
                                   size_t fileSize = 0;
                                   for (int j = 0; j < spm->getNumSegs(); j++) fileSize += packet_size[id][j];
                                   unsigned char* content = (unsigned char*) malloc(fileSize);
                                   size_t offset = 0;
                                   for (int j = 0; j < spm->getNumSegs(); j++) {
                                       unsigned char* sub_content = (unsigned char*) malloc(packet_size[id][j]);
                                       getFile(packets[id][j], sub_content, packet_size[id][j]);
                                       memcpy(content + offset, sub_content, packet_size[id][j]);
                                       free(sub_content);
                                       offset += packet_size[id][j];
                                       // delete temporary files
                                       std::remove(packets[id][j].c_str());
                                   }
                                   writeFile(out_file, content, fileSize);
                                   free(content);
                               }
                           }
            }
    }
}

InfoEntry* CarApp::findInfoEntry(std::string id, int seg) {
    for (int i = 0; i < info_table.size(); i++) {
        if (info_table[i]->getPacketId().compare(id) == 0 && info_table[i]->getSegNum() == seg) {
            return info_table[i];
        }
    }

    return nullptr;
}

void CarApp::cacheSPM(SegPacketMessage* spm) {
    std::string str_id(spm->getPacketId(), 0, 256);

    // check existence
    for (int i = 0; i < cache_size; i++) {
        if (cache[i]->getPacketId().compare(str_id) == 0 && cache[i]->getSegNum() == spm->getSegNum()) {
            printMessage("packet in cache, dropped", CACHE_DBG_MSG);
            return;
        }
    }

    // LRU cache
    if (cache_size == cache_capacity) {

        // find least recently used cache entry to replace
        int delete_idx = 0;
        for (int i = 1; i < cache_size; i++) {
            if (cache[delete_idx]->getTimestamp() > cache[i]->getTimestamp())
                delete_idx = i;
        }
        printMessage("delete packet_" + cache[delete_idx]->getPacketId()
                    + " seg_" + std::to_string(cache[delete_idx]->getSegNum()) + " from cache_" + std::to_string(delete_idx), CACHE_DBG_MSG);

        // erase the deleted cache entry info from local info table
        for (int i = 0; i < info_table.size(); i++) {
            if (info_table[i]->getAddress() == myId && info_table[i]->getPacketId().compare(cache[delete_idx]->getPacketId()) == 0
                    && info_table[i]->getSegNum() == cache[delete_idx]->getSegNum()) {
                info_table.erase(info_table.begin() + i);
                break;
            }
        }

        // replace cache entry
        printMessage("cached packet_" + str_id + " seg_"
                                + std::to_string(spm->getSegNum()) + " at cache_" + std::to_string(delete_idx), CACHE_DBG_MSG);

        delete(cache[delete_idx]);
        cache[delete_idx] = new SegPacket(str_id, spm, simTime());
    } else {

        // cache new packet
        printMessage("cached packet_" + str_id + " seg_"
                + std::to_string(spm->getSegNum()) + " at cache_" + std::to_string(cache_size), CACHE_DBG_MSG);
        cache[cache_size] = new SegPacket(str_id, spm, simTime());
        cache_size++;
    }

    if (InfoEntry* ie = findInfoEntry(str_id, spm->getSegNum())) {
        ie->setAddress(myId);
        ie->setHops(0);
    } else {
        info_table.push_back(new InfoEntry(myId, str_id, spm->getSegNum()));
    }

    cache_updated = true;
}

void CarApp::onCIM(CacheInfoMessage* cim) {

    printMessage("received cim of size " + std::to_string(cim->getInfoArraySize()) + " from " + std::to_string(cim->getSenderAddress()), TABLE_DBG_MSG);

    neighbors[cim->getSenderAddress()] = simTime();
    for (int i = 0; i < cim->getFileArraySize(); i++) {
        FileEntry fe = cim->getFile(i);
        if (neighbor_file_count.find(fe.getPacketId()) == neighbor_file_count.end()) {
            neighbor_file_count[fe.getPacketId()] = file_seg_neigh_t();
            neighbor_file_count[fe.getPacketId()][fe.getSegNum()] = id_set_t();
        } else if (neighbor_file_count[fe.getPacketId()].find(fe.getSegNum()) == neighbor_file_count[fe.getPacketId()].end()) {
            neighbor_file_count[fe.getPacketId()][fe.getSegNum()] = id_set_t();
        }
        neighbor_file_count[fe.getPacketId()][fe.getSegNum()].insert(fe.getAddress());
    }

    std::vector<InfoEntry*> to_merge;
    to_merge.clear();
    for (int i = 0; i < cim->getInfoArraySize(); i++) {
        InfoEntry ie = cim->getInfo(i);
        bool found = true;
        // look up received info table for available packets
        if (network_coding) {
            decoder_t::iterator got = decoderref.find(ie.getPacketId());
            if (got != decoderref.end() && packet_coding_segs[got->first].find(ie.getSegNum()) == packet_coding_segs[got->first].end())
                found = false;
        } else {
            packet_t::iterator got = packets.find(ie.getPacketId());
            if (got != packets.end() && packets[got->first][ie.getSegNum()] == "")
                found = false;
        }

        if (!found) {
                // request for particular packet
                printMessage("send prm of packet_" + ie.getPacketId()
                        + " seg_" + std::to_string(ie.getSegNum())
                        + " to " + std::to_string(ie.getAddress()), PRM_DBG_MSG);
                PacketRequestMessage* prm = new PacketRequestMessage();
                prm->setPacketId(ie.getPacketId().c_str());
                prm->setSegNum(ie.getSegNum());
                populateWSM(prm);
                prm->setKind(PRM_MESSAGE);
                prm->setSenderAddress(myId);
                prm->setRecipientAddress(ie.getAddress());
                sendDown(prm->dup());
                delete(prm);
                stats_num_msg_sent++;
            }

        if (merge_info_allowed) {

            // try to merge this info entry to local table
            if (ie.getHops() < num_hop_allowed - 1) {
                bool found = false;
                for (int i = 0; i < info_table.size(); i++) {
                    if (info_table[i]->getPacketId().compare(ie.getPacketId()) == 0 && info_table[i]->getSegNum() == ie.getSegNum()) {
                       if (info_table[i]->getHops() > ie.getHops()) {
                           info_table[i]->setAddress(ie.getAddress());
                           info_table[i]->setHops(ie.getHops());
                       }
                       found = true;
                       break;
                    }
                }
                if (!found) {
                    ie.setHops(ie.getHops() + 1);
                    to_merge.push_back(new InfoEntry(ie));
                }
            }
        }
    }

    if (merge_info_allowed && to_merge.size() != 0) {
        info_table.insert(info_table.end(), to_merge.begin(), to_merge.end());
        printMessage("Table updated from size " + std::to_string(info_table.size() - to_merge.size())
        + " to size " + std::to_string(info_table.size()), TABLE_DBG_MSG);
    }
}

void CarApp::onPRM(PacketRequestMessage* prm) {
    std::string str_id(prm->getPacketId(), 0, 256);
    printMessage("received prm of packet_" + str_id
                            + " seg_" + std::to_string(prm->getSegNum())
                            + " from " + std::to_string(prm->getSenderAddress()), PRM_DBG_MSG);
    if (prm->getRecipientAddress() == myId) {
        for (int i = 0; i < cache_size; i++) {
            if (network_coding) {
                if (cache_ncm[i]->getPacketId().compare(str_id) == 0 && cache_ncm[i]->getCodingNum() == prm->getSegNum()) {
                    printMessage("send ncm of packet_" + str_id
                        + " codingnum_" + std::to_string(prm->getSegNum())
                        + " to " + std::to_string(prm->getSenderAddress()), PRM_DBG_MSG);

                    NetworkCodingMessage* ncm = new NetworkCodingMessage();
                    ncm->setPacketId(str_id.c_str());
                    ncm->setCodingNum(prm->getSegNum());
                    ncm->setFileSize(cache_ncm[i]->getFileSize());
                    ncm->setGen(cache_ncm[i]->getGen());
                    ncm->setNumBlocksGen(cache_ncm[i]->getNumBlocksGen());
                    ncm->setBlockSize(cache_ncm[i]->getBlockSize());
                    ncm->setCoeffsArraySize(cache_ncm[i]->getCoeffsSize());
                    ncm->setSumsArraySize(cache_ncm[i]->getSumsSize());

                    unsigned char* cache_coeffs = cache_ncm[i]->getCoeffs();
                    for (int j = 0; j < cache_ncm[i]->getCoeffsSize(); j++) {
                        ncm->setCoeffs(j, cache_coeffs[j]);
                    }

                    unsigned char* cache_sums = cache_ncm[i]->getSums();
                    for (int j = 0; j < cache_ncm[i]->getSumsSize(); j++) {
                        ncm->setSums(j, cache_sums[j]);
                    }
                    populateWSM(ncm);
                    ncm->setKind(NCM_MESSAGE);
                    ncm->setSenderAddress(myId);
                    ncm->setRecipientAddress(prm->getSenderAddress());
                    sendDown(ncm->dup());
                    delete(ncm);
                    stats_num_msg_sent++;
                    // mark the cache entry as recently used
                    printMessage("cache_" + std::to_string(i) + " used recently", 100);
                    cache_ncm[i]->setTimestamp(simTime());
                    return;
                }
            } else {
                if (cache[i]->getPacketId().compare(str_id) == 0 && cache[i]->getSegNum() == prm->getSegNum()) {
                    printMessage("send spm of packet_" + str_id
                        + " seg_" + std::to_string(prm->getSegNum())
                        + " to " + std::to_string(prm->getSenderAddress()), PRM_DBG_MSG);

                    // send cached packet of interest to requester
                    SegPacketMessage* spm = new SegPacketMessage();
                    spm->setPacketId(str_id.c_str());
                    spm->setSegNum(prm->getSegNum());
                    spm->setDataArraySize(cache[i]->getDataSize());
                    unsigned char* cache_data = cache[i]->getData();
                    for (int j = 0; j < cache[i]->getDataSize(); j++) {
                        spm->setData(j, cache_data[j]);
                    }
                    populateWSM(spm);
                    spm->setKind(SPM_MESSAGE);
                    spm->setSenderAddress(myId);
                    spm->setRecipientAddress(prm->getSenderAddress());
                    sendDown(spm->dup());
                    delete(spm);
                    stats_num_msg_sent++;
                    // mark the cache entry as recently used
                    printMessage("cache_" + std::to_string(i) + " used recently", 100);
                    cache[i]->setTimestamp(simTime());
                    return;
                }
            }
        }
    }
}

void CarApp::onNCM(NetworkCodingMessage* ncm) {
    printMessage("received ncm", RECEIVE_PKT_MSG);

    std::string str_id(ncm->getPacketId(), 0, 256);

    if (ncm->getKind() == RSU_BROADCAST_MESSAGE || ncm->getRecipientAddress() == myId) {
        cacheNCM(ncm);
        printMessage("received ncm of packet_" + str_id
                + " codingnum_" + std::to_string(ncm->getCodingNum())
                + " from " + std::to_string(ncm->getSenderAddress()) + " size " + std::to_string(packet_coding_segs[str_id].size()), NCM_DBG_MSG);

        if (packet_complete.find(str_id) != packet_complete.end())
            return;

        CodedBlockPtr block = (CodedBlockPtr) malloc(sizeof(CodedBlock));
        block->gen = ncm->getGen();
        block->num_blocks_gen = ncm->getNumBlocksGen();
        block->block_size = ncm->getBlockSize();
        block->coeffs = (CoeffsPtr) malloc(ncm->getNumBlocksGen());
        block->sums = (BlockPtr) malloc(DEFAULT_BLOCK_SIZE);
        for (int i = 0; i < ncm->getCoeffsArraySize(); i++) {
            block->coeffs[i] = ncm->getCoeffs(i);
        }
        for (int i = 0; i < ncm->getSumsArraySize(); i++) {
            block->sums[i] = ncm->getSums(i);
        }

        if (decoderref.find(str_id) == decoderref.end()) {
            std::string out_file = "../files/" + std::to_string(myId) + "_" + str_id;
            decoderref[str_id] = new codetorrentdecoder(ncm->getFileSize(), out_file.c_str(), DEFAULT_BLOCK_SIZE);
            packet_start_time[str_id] = simTime();
        }

        if (decoderref[str_id]->store_block(0,block->coeffs,block->sums)) {
            file_table.push_back(new FileEntry(myId, str_id, ncm->getCodingNum()));
            packet_coding_segs[str_id].insert(ncm->getCodingNum());
            printMessage("packet_" + str_id + "codingnum_" + std::to_string(ncm->getCodingNum()) + " is innovative", NCM_DBG_MSG);
            if (decoderref[str_id]->decode()) {
                packet_complete.insert(str_id);
                printMessage("pakcet_" + str_id + " complete in "
                        + (simTime() - packet_start_time[str_id]).str(), FILE_COMPLETE_MSG);
            }
        }

        ctu->freeCodedBlock(&block);
    }
}

int CarApp::getNumNeighborsWithFileSeg(std::string id, int seg) {
    if (neighbor_file_count.find(id) == neighbor_file_count.end())
        return 0;
    else if (neighbor_file_count[id].find(seg) == neighbor_file_count[id].end())
        return 0;
    else
        return neighbor_file_count[id][seg].size();
}

void CarApp::cacheNCM(NetworkCodingMessage* ncm) {
    std::string str_id(ncm->getPacketId(), 0, 256);

    // check existence
    for (int i = 0; i < cache_size; i++) {
        if (cache_ncm[i]->getPacketId().compare(str_id) == 0 && cache_ncm[i]->getCodingNum() == ncm->getCodingNum()) {
            printMessage("packet in cache, dropped", CACHE_DBG_MSG);
            return;
        }
    }

    // probabilistic drop
    if (ncm->getKind() == RSU_BROADCAST_MESSAGE && rand() % (neighbors.size() + 1) != 0) return;

    // cache
    if (cache_size == cache_capacity) {
        // find least recently used cache entry to replace
        int delete_idx = 0;
        int max = getNumNeighborsWithFileSeg(cache_ncm[0]->getPacketId(), cache_ncm[0]->getCodingNum());

        /*for (int i = 1; i < cache_size; i++) {
            if (cache_ncm[delete_idx]->getTimestamp() > cache_ncm[i]->getTimestamp())
                delete_idx = i;
        }*/
        for (int i = 1; i < cache_size; i++) {
            int num_neighbors = getNumNeighborsWithFileSeg(cache_ncm[i]->getPacketId(), cache_ncm[i]->getCodingNum());
            if (num_neighbors > max) {
                max = num_neighbors;
                delete_idx = i;
            } else if (num_neighbors == max) {
                if (cache_ncm[i]->getTimestamp() < cache_ncm[delete_idx]->getTimestamp())
                    delete_idx = i;
            }
        }
        printMessage("delete packet_" + cache_ncm[delete_idx]->getPacketId()
                    + " codingnum_" + std::to_string(cache_ncm[delete_idx]->getCodingNum()) + " from cache_" + std::to_string(delete_idx), CACHE_DBG_MSG);

        // erase the deleted cache entry info from local info table
        for (int i = 0; i < info_table.size(); i++) {
            if (info_table[i]->getAddress() == myId && info_table[i]->getPacketId().compare(cache_ncm[delete_idx]->getPacketId()) == 0
                    && info_table[i]->getSegNum() == cache_ncm[delete_idx]->getCodingNum()) {
                info_table.erase(info_table.begin() + i);
                break;
            }
        }

        // replace cache entry
        printMessage("cached packet_" + str_id + " codingnum_"
                                    + std::to_string(ncm->getCodingNum()) + " at cache_" + std::to_string(delete_idx), CACHE_DBG_MSG);
        delete(cache_ncm[delete_idx]);
        cache_ncm[delete_idx] = new CodingPacket(str_id, ncm, simTime());
    } else {

        // cache new packet
        printMessage("cached packet_" + str_id + " codingnum_"
                    + std::to_string(ncm->getCodingNum()) + " at cache_" + std::to_string(cache_size), CACHE_DBG_MSG);
        cache_ncm[cache_size] = new CodingPacket(str_id, ncm, simTime());
        cache_size++;
    }

    if (InfoEntry* ie = findInfoEntry(str_id, ncm->getCodingNum())) {
        ie->setAddress(myId);
        ie->setHops(0);
    } else {
        info_table.push_back(new InfoEntry(myId, str_id, ncm->getCodingNum()));
    }
    cache_updated = true;
}

void CarApp::handleLowerMsg(cMessage* msg) {

    stats_num_msg_received++;
    WaveShortMessage* wsm = dynamic_cast<WaveShortMessage*>(msg);
    ASSERT(wsm);
    if (SegPacketMessage* spm = dynamic_cast<SegPacketMessage*> (wsm)) {
        onSPM(spm);
        onWSM(wsm);
        delete(msg);
    } else if (CacheInfoMessage* cim = dynamic_cast<CacheInfoMessage*>(wsm)) {
        onCIM(cim);
        onWSM(wsm);
        delete(msg);
    } else if (PacketRequestMessage* prm = dynamic_cast<PacketRequestMessage*>(wsm)) {
        onPRM(prm);
        onWSM(wsm);
        delete(msg);
    } else if (NetworkCodingMessage* ncm = dynamic_cast<NetworkCodingMessage*>(wsm)) {
        onNCM(ncm);
        onWSM(wsm);
        delete(msg);
    } else {
        stats_num_msg_received--;
        BaseWaveApplLayer::handleLowerMsg(msg);
    }
}

void CarApp::handleSelfMsg(cMessage* msg) {
    if (WaveShortMessage* wsm = dynamic_cast<WaveShortMessage*>(msg)) {
        //send this message on the service channel until the counter is 3 or higher.
        //this code only runs when channel switching is enabled
        if (wsm->getKind() == PERIODIC_SELF_CHECK) {
            for (neighbors_t::iterator it = neighbors.begin(); it != neighbors.end();) {
                if (simTime() - it->second >= 5) {
                    it = neighbors.erase(it);
                } else {
                    it++;
                }
            }

            if (info_table.size() > 0 && cache_updated) {
                // generate new cache info msg
                CacheInfoMessage* cim = new CacheInfoMessage();
                cim->setInfoArraySize(info_table.size());
                for (int i = 0; i < info_table.size(); i++) {
                    cim->setInfo(i, *info_table[i]);
                }
                cim->setFileArraySize(file_table.size());
                for (int i = 0; i < file_table.size(); i++) {
                    cim->setFile(i, *file_table[i]);
                }
                populateWSM(cim);
                cim->setKind(CIM_MESSAGE);
                cim->setSenderAddress(myId);
                sendDown(cim->dup());
                stats_num_msg_sent++;
                delete(cim);
                cache_updated = false;
            }

            scheduleAt(simTime() + 1, wsm->dup());
            delete(wsm);
            return;
        }
        sendDown(wsm->dup());
        stats_num_msg_sent++;
        wsm->setSerial(wsm->getSerial() +1);
        if (wsm->getSerial() >= 3) {
            //stop service advertisements
            stopService();
            delete(wsm);
        }
        else {
            scheduleAt(simTime()+1, wsm);
        }
    }
    else {
        BaseWaveApplLayer::handleSelfMsg(msg);
    }
}

void CarApp::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);
}

void CarApp::printMessage(std::string msg, int type) {
    //if (type == PRM_DBG_MSG || type == TABLE_DBG_MSG || type == NCM_DBG_MSG)
    if (type == FILE_COMPLETE_MSG)
        std::cerr << "Car " + std::to_string(myId) + ": " + msg + '.' << std::endl;
}

void CarApp::writeFile(std::string filename, const unsigned char* content, size_t size) {
    //printf("writing file=%s\n",filename.c_str());
    int totalBytesWritten = 0;

    FILE* writeFile = fopen(filename.c_str(), "wb");
    if (!writeFile) {
        printf("Unable create file %s\n", filename.c_str());
        //ReportError("Unable create networkcoded block file\n");
        return;
    }
    totalBytesWritten = fwrite(content, 1, size, writeFile);
    fclose(writeFile);
}

void CarApp::getFile(std::string filename, unsigned char* content, size_t fileSize) {

    FILE* getFile = fopen(filename.c_str(), "rb");
    if (getFile == NULL) {
        printf("Unable to open file %s\n",
                filename.c_str());
        return;
    }

    fread(content, fileSize, 1, getFile);
    fclose(getFile);
    return;
}

std::string CarApp::gen_random_string(int length) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    std::string s = "";
    for (int i = 0; i < length; ++i) {
        s = s + alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return s;
}

void CarApp::refreshDisplay() const
{
    char buf[40];
    sprintf(buf, "rcvd: %ld, sent: %ld", stats_num_msg_received, stats_num_msg_sent);
    getDisplayString().setTagArg("t", 0, buf);
}
