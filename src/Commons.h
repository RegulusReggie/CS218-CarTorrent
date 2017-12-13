/*
 * Commons.h
 *
 *  Created on: Nov 24, 2017
 *      Author: Reggie
 */

#ifndef SRC_COMMONS_H_
#define SRC_COMMONS_H_

int const RSU_BROADCAST_MESSAGE = 10;
int const SPM_MESSAGE = 11;
int const PRM_MESSAGE = 12;
int const CIM_MESSAGE = 13;
int const SELF_PRODUCE_CODING = 14;
int const NCM_MESSAGE = 15;
int const FILE_REQ_MESSAGE = 16;
int const FILE_FIN_MESSAGE = 17;
int const PERIODIC_SELF_CHECK = 18;

int const CACHE_DBG_MSG = 50;
int const TABLE_DBG_MSG = 51;
int const FILE_COMPLETE_MSG = 52;
int const RECEIVE_PKT_MSG = 53;
int const NCM_DBG_MSG = 54;
int const PRM_DBG_MSG = 55;

size_t const DEFAULT_BLOCK_SIZE = 32768;

#endif /* SRC_COMMONS_H_ */
