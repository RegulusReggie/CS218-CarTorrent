/*
 * RSU.cpp
 *
 *  Created on: Nov 20, 2017
 *      Author: Reggie
 */

#include <memory>
#include <math.h>

#include "CarTorrentRSU.h"

Define_Module(CarTorrentRSU);

CarTorrentRSU::~CarTorrentRSU() {
    delete [] spm_segs;
    delete encoderref;
}

void CarTorrentRSU::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);
    if (stage == 0) {

        WATCH(stats_num_msg_sent);

        std::string filename = par("packetId").stringValue();
        useNetworkCoding = par("useNC").boolValue();
        // check file
        std::string fpath = "../files/" + filename;
        FILE *filePtr = fopen(fpath.c_str(), "rb");
        if (!filePtr) {
            printf("Unable to open file");
            return;
        }

        fseek(filePtr, 0, SEEK_END);
        long fileSize = ftell(filePtr);
        fclose(filePtr);

        if (fileSize < 0) {
            printf("Unable to determine size of file %s\n", fpath.c_str());
            return;
        }

        if (useNetworkCoding) {
            encoderref = new codetorrentencoder(fpath.c_str(),DEFAULT_BLOCK_SIZE,fileSize);
            SegPacketMessage* spm = new SegPacketMessage();
            spm->setPacketId(filename.c_str());
            spm->setKind(SELF_PRODUCE_CODING);
            spm->setNumSegs(fileSize);
            scheduleAt(computeAsynchronousSendingTime(1,type_SCH),spm);
        } else {
            packet_size = ceil(float(fileSize) / DEFAULT_BLOCK_SIZE);
            packet_id = filename;
            spm_segs = new SegPacketMessage* [packet_size];
            FILE* readFile = fopen(fpath.c_str(), "rb");
            size_t bufferLen = fileSize + 1;
            unsigned char* content = (unsigned char*) malloc(bufferLen);
            memset(content, 0, bufferLen);
            fread(content, fileSize, 1, readFile);
            fclose(readFile);

            for (int i = 0; i < packet_size; i++) {
                spm_segs[i] = new SegPacketMessage();
                size_t sub_size = (i == packet_size - 1) ? fileSize % DEFAULT_BLOCK_SIZE
                        : DEFAULT_BLOCK_SIZE;
                unsigned char* sub_content = (unsigned char*) malloc(sub_size);
                memcpy(sub_content, content + i * DEFAULT_BLOCK_SIZE, sub_size);
                populateSPM(spm_segs[i], packet_size, packet_id, i, sub_content, sub_size);
                free(sub_content);
            }

            scheduleAt(computeAsynchronousSendingTime(1,type_SCH),spm_segs[0]);

            free(content);
            content = NULL;
        }
    }
}

void CarTorrentRSU::populateSPM(SegPacketMessage* spm, int numSegs, std::string packetId, int segNum, const unsigned char* data, size_t data_size) {
    spm->setPacketId(packetId.c_str());
    spm->setSegNum(segNum);
    spm->setNumSegs(numSegs);
    spm->setDataArraySize(data_size);
    for (int i = 0; i < data_size; i++) {
        spm->setData(i, data[i]);
    }
    populateWSM(spm);
    spm->setKind(RSU_BROADCAST_MESSAGE);
    spm->setSenderAddress(myId);
}

void CarTorrentRSU::onWSA(WaveServiceAdvertisment* wsa) {
}

void CarTorrentRSU::onWSM(WaveShortMessage* wsm) {
}

void CarTorrentRSU::handleSelfMsg(cMessage* msg) {
    if (SegPacketMessage* spm = dynamic_cast<SegPacketMessage*>(msg)) {
        //std::cerr << "RSU " + std::to_string(myId) + " sent packet_" + std::to_string(packet_id) + " seg_" + std::to_string(spm->getSegNum()) << std::endl;
        if (spm->getKind() == SELF_PRODUCE_CODING) {
            CodedBlockPtr block=encoderref->encode();
            if(block == NULL) {
                printf("Encoding failure\n");
            }
            printf("Encoded block\n");
            NetworkCodingMessage* ncm = new NetworkCodingMessage();
            coding_generated++;
            populateNCM(ncm, spm->getPacketId(), block, coding_generated, spm->getNumSegs());
            sendDown(ncm->dup());
            stats_num_msg_sent++;
            delete ncm;
            scheduleAt(simTime() + 1, spm);
        } else {
            sendDown(spm->dup());
            stats_num_msg_sent++;
            scheduleAt(simTime()+1, spm_segs[(spm->getSegNum() + 1) % packet_size]);
        }
    } else {
        BaseWaveApplLayer::handleSelfMsg(msg);
    }
}

void CarTorrentRSU::populateNCM(NetworkCodingMessage* ncm, const char* id, CodedBlockPtr block, int coding_num, size_t filesize) {
    ncm->setPacketId(id);
    ncm->setFileSize(filesize);
    ncm->setCodingNum(coding_num * 2 + myId % 2); // distinguish two RSUs
    ncm->setGen(block->gen);
    ncm->setBlockSize(block->block_size);
    ncm->setNumBlocksGen(block->num_blocks_gen);
    int numBlocksPerGen = 32;
    ncm->setCoeffsArraySize(numBlocksPerGen);
    for (int i = 0; i < numBlocksPerGen; i++)
        ncm->setCoeffs(i, block->coeffs[i]);
    ncm->setSumsArraySize(DEFAULT_BLOCK_SIZE);
    for (int i = 0; i < DEFAULT_BLOCK_SIZE; i++)
            ncm->setSums(i, block->sums[i]);
    populateWSM(ncm);
    ncm->setKind(RSU_BROADCAST_MESSAGE);
    ncm->setSenderAddress(myId);
}


void CarTorrentRSU::refreshDisplay() const
{
    char buf[40];
    sprintf(buf, "sent: %ld", stats_num_msg_sent);
    getDisplayString().setTagArg("t", 0, buf);
}
