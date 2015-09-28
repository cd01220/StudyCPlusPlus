/*
 * SnmpAgent.h
 *
 *  Created on: Sep 23, 2015
 *      Author: liuhao
 */

#ifndef _SnmpAgent_h_
#define _SnmpAgent_h_

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/*  docsIfUpstreamChannelTable */
void InitDocsIfUpChannelTable(void);
/*
 * function declarations..
 */
Netsnmp_Node_Handler      DocsIfUpChannelHandler;

Netsnmp_First_Data_Point  DocsIfUpChannelGetFirst;
Netsnmp_Next_Data_Point   DocsIfUpChannelGetNext;

#define ColumnDocsIfUpChannelId                1
#define ColumnDocsIFUpChannelFrequency         2
#define ColumnDocsIfUpChannelWidth             3
#define ColumnDocsIfUpChannelModulationProfile 4
#define ColumnDocsIfUpChannelSlotSize          5
#define ColumnDocsIfUpChannelTxTimingOffset    6
#define ColumnDocsIfUpChannelRangingBackoffStart    7
#define ColumnDocsIfUpChannelRangingBackOffend      8
#define ColumnDocsIfUpChannelTxBackoffStart    9
#define ColumnDocsIfUpChannelTxBackoffEnd      10
#define ColumnDocsIfUpChannelScdmaActivecodes  11
#define ColumnDocsIfUpChannelScdmaCodesperSlot 12
#define ColumnDocsIfUpChannelScdmaFrameSize    13
#define ColumnDocsIfUpChannelScdmaHoppingSeed  14
#define ColumnDocsIfUpChannelType              15
#define ColumnDocsIfUpChannelCloneFrom         16
#define ColumnDocsIfUpChannelUpDate            17
#define ColumnDocsIfUpChannelStatus            18
#define ColumnDocsIfUpChannelPreeqEnable       19

struct UsChannelCfg
{
	int id;
};

#endif // _SnmpAgent_h_ 
