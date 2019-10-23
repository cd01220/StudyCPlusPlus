#include "SystemInclude.h"
#include "SnmpDocsIfUpChannelTable.h"
using namespace std;

#ifdef SnmpModule
static UsChannelCfg usChannelCfg[5] =
{
	{1}, {2}, {3}, {4}, {0},
};

typedef int(*SnmpOperationHandler)(netsnmp_mib_handler*, netsnmp_handler_registration*,
                                   netsnmp_agent_request_info*, netsnmp_request_info*);
static int DocsIfUpChannelGet(netsnmp_mib_handler*, netsnmp_handler_registration*,
                              netsnmp_agent_request_info*, netsnmp_request_info*);
static int DocsIfUpChannelSetReserve1(netsnmp_mib_handler*,
                                      netsnmp_handler_registration*,
                                      netsnmp_agent_request_info*,
                                      netsnmp_request_info*);
static int DocsIfUpChannelSetReserve2(netsnmp_mib_handler*,
                                      netsnmp_handler_registration*,
                                      netsnmp_agent_request_info*,
                                      netsnmp_request_info*);
static int DocsIfUpChannelSetFree(netsnmp_mib_handler*,
                                  netsnmp_handler_registration*,
                                  netsnmp_agent_request_info*,
                                  netsnmp_request_info*);
static int DocsIfUpChannelSetAction(netsnmp_mib_handler*,
                                    netsnmp_handler_registration*,
                                    netsnmp_agent_request_info*,
                                    netsnmp_request_info*);
static int DocsIfUpChannelSetUndo(netsnmp_mib_handler*,
                                  netsnmp_handler_registration*,
                                  netsnmp_agent_request_info*,
                                  netsnmp_request_info*);
static int DocsIfUpChannelSetCommit(netsnmp_mib_handler*,
                                    netsnmp_handler_registration*,
                                    netsnmp_agent_request_info*,
                                    netsnmp_request_info*);

typedef void(*SnmpSetValueToPktHandler)(netsnmp_agent_request_info*,
                                   netsnmp_request_info*,
                                   UsChannelCfg*);
static void SnmpSetValueToReqestId(netsnmp_agent_request_info *reqInfo,
                                   netsnmp_request_info       *request,
                                   UsChannelCfg       *entry);
static void SnmpSetValueToReqestFrequency(netsnmp_agent_request_info *reqInfo,
                                          netsnmp_request_info       *request,
                                          UsChannelCfg       *entry);
static void SnmpSetValueToReqestWidth(netsnmp_agent_request_info *reqInfo,
                                      netsnmp_request_info       *request,
                                      UsChannelCfg       *entry);
static void SnmpSetValueToReqestModulationProfile(netsnmp_agent_request_info *reqInfo,
                                                  netsnmp_request_info       *request,
                                                  UsChannelCfg       *entry);
static void SnmpSetValueToReqestSlotSize(netsnmp_agent_request_info *reqInfo,
                                         netsnmp_request_info       *request,
                                         UsChannelCfg       *entry);
static void SnmpSetValueToReqestTxTimingOffset (netsnmp_agent_request_info *reqInfo,
                                                netsnmp_request_info       *request,
                                                UsChannelCfg       *entry);
static void SnmpSetValueToReqestRangingBackoffStart(netsnmp_agent_request_info *reqInfo,
                                                    netsnmp_request_info       *request,
                                                    UsChannelCfg       *entry);
static void SnmpSetValueToReqestRangingBackOffend(netsnmp_agent_request_info *reqInfo,
                                                  netsnmp_request_info       *request,
                                                  UsChannelCfg       *entry);
static void SnmpSetValueToReqestTxBackoffStart(netsnmp_agent_request_info *reqInfo,
                                               netsnmp_request_info       *request,
                                               UsChannelCfg       *entry);
static void SnmpSetValueToReqestTxBackoffEnd(netsnmp_agent_request_info *reqInfo,
                                             netsnmp_request_info       *request,
                                             UsChannelCfg       *entry);
static void SnmpSetValueToReqestScdmaActivecodes(netsnmp_agent_request_info *reqInfo,
                                                 netsnmp_request_info       *request,
                                                 UsChannelCfg       *entry);
static void SnmpSetValueToReqestScdmaCodesperSlot(netsnmp_agent_request_info *reqInfo,
                                                  netsnmp_request_info       *request,
                                                  UsChannelCfg       *entry);
static void SnmpSetValueToReqestScdmaFrameSize(netsnmp_agent_request_info *reqInfo,
                                               netsnmp_request_info       *request,
                                               UsChannelCfg       *entry);
static void SnmpSetValueToReqestScdmaHoppingSeed(netsnmp_agent_request_info *reqInfo,
                                                 netsnmp_request_info       *request,
                                                 UsChannelCfg       *entry);
static void SnmpSetValueToReqestType(netsnmp_agent_request_info *reqInfo,
                                     netsnmp_request_info       *request,
                                     UsChannelCfg       *entry);
static void SnmpSetValueToReqestCloneFrom(netsnmp_agent_request_info *reqInfo,
                                          netsnmp_request_info       *request,
                                          UsChannelCfg       *entry);
static void SnmpSetValueToReqestUpDate(netsnmp_agent_request_info *reqInfo,
                                       netsnmp_request_info       *request,
                                       UsChannelCfg       *entry);
static void SnmpSetValueToReqestStatus(netsnmp_agent_request_info *reqInfo,
                                       netsnmp_request_info       *request,
                                       UsChannelCfg       *entry);
static void SnmpSetValueToReqestPreeqEnable(netsnmp_agent_request_info *reqInfo,
                                            netsnmp_request_info       *request,
                                            UsChannelCfg       *entry);

static map<int, SnmpOperationHandler> snmpHandler;
static map<int, SnmpSetValueToPktHandler>  snmpSetValueHandler;

void InitDocsIfUpChannelTable(void)
{
    const oid    tableOid[] = {1,3,6,1,2,1,10,127,1,1,2};
    const size_t oidLen     = OID_LENGTH(tableOid);
    netsnmp_handler_registration    *reg;
    netsnmp_iterator_info           *iinfo;

    reg = netsnmp_create_handler_registration("docsIfUpstreamChannelTable",
                                              DocsIfUpChannelHandler,
                                              tableOid,
                                              oidLen,
											  HANDLER_CAN_RONLY);

    netsnmp_table_registration_info *tableInfo;
    tableInfo = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    netsnmp_table_helper_add_indexes(tableInfo,
                                     ASN_INTEGER,  /* index: ifIndex */
                                     0);
    tableInfo->min_column = ColumnDocsIfUpChannelId;
    tableInfo->max_column = ColumnDocsIfUpChannelPreeqEnable;

    iinfo = SNMP_MALLOC_TYPEDEF( netsnmp_iterator_info );
    iinfo->get_first_data_point = DocsIfUpChannelGetFirst;
    iinfo->get_next_data_point  = DocsIfUpChannelGetNext;
    iinfo->table_reginfo        = tableInfo;

    netsnmp_register_table_iterator(reg, iinfo);

    /* Initialize the contents of the table here */
    snmpHandler.insert(make_pair(MODE_GET, DocsIfUpChannelGet));
    snmpHandler.insert(make_pair(MODE_SET_RESERVE1, DocsIfUpChannelSetReserve1));
    snmpHandler.insert(make_pair(MODE_SET_RESERVE2, DocsIfUpChannelSetReserve2));
    snmpHandler.insert(make_pair(MODE_SET_FREE, DocsIfUpChannelSetFree));
    snmpHandler.insert(make_pair(MODE_SET_ACTION, DocsIfUpChannelSetAction));
    snmpHandler.insert(make_pair(MODE_SET_UNDO, DocsIfUpChannelSetUndo));
    snmpHandler.insert(make_pair(MODE_SET_COMMIT, DocsIfUpChannelSetCommit));

    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelId, SnmpSetValueToReqestId));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIFUpChannelFrequency, SnmpSetValueToReqestFrequency));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelWidth, SnmpSetValueToReqestWidth));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelModulationProfile, SnmpSetValueToReqestModulationProfile));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelSlotSize, SnmpSetValueToReqestSlotSize));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelTxTimingOffset, SnmpSetValueToReqestTxTimingOffset));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelRangingBackoffStart, SnmpSetValueToReqestRangingBackoffStart));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelRangingBackOffend, SnmpSetValueToReqestRangingBackOffend));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelTxBackoffStart, SnmpSetValueToReqestTxBackoffStart));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelTxBackoffEnd, SnmpSetValueToReqestTxBackoffEnd));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelScdmaActivecodes, SnmpSetValueToReqestScdmaActivecodes));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelScdmaCodesperSlot, SnmpSetValueToReqestScdmaCodesperSlot));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelScdmaFrameSize, SnmpSetValueToReqestScdmaFrameSize));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelScdmaHoppingSeed, SnmpSetValueToReqestScdmaHoppingSeed));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelType, SnmpSetValueToReqestType));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelCloneFrom, SnmpSetValueToReqestCloneFrom));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelUpDate, SnmpSetValueToReqestUpDate));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelStatus, SnmpSetValueToReqestStatus));
    snmpSetValueHandler.insert(make_pair(ColumnDocsIfUpChannelPreeqEnable, SnmpSetValueToReqestPreeqEnable));
}

/* Example iterator hook routines - using 'get_next' to do most of the work */
netsnmp_variable_list* DocsIfUpChannelGetFirst(void **loopContext,
    void **dataContext,
    netsnmp_variable_list *indexData,
    netsnmp_iterator_info *data)
{
	snmp_set_var_value(indexData, &usChannelCfg[0].id, sizeof(int));
    *loopContext = *dataContext = &usChannelCfg[0];
    return indexData;
}

netsnmp_variable_list* DocsIfUpChannelGetNext(void **loopContext,
                                              void **dataContext,
                                              netsnmp_variable_list *indexData,
                                              netsnmp_iterator_info *data)
{
	UsChannelCfg *cfg = (UsChannelCfg *)*loopContext + 1;
    if (cfg->id != 0)
    {
        snmp_set_var_value(indexData, &cfg->id, sizeof(int));
        *loopContext = *dataContext = cfg;
        return indexData;
    }

    *loopContext = NULL;
    *dataContext = NULL;
    return NULL;
}


/* The GetNext() function is called by net-snmp library to iterate all table index,
 * terminate loop by return NULL.
 */
void SnmpSetValueToReqestId(netsnmp_agent_request_info *reqInfo,
                            netsnmp_request_info       *request,
                            UsChannelCfg       *entry)
{
    int32_t value = entry->id;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestFrequency(netsnmp_agent_request_info *reqInfo,
                                   netsnmp_request_info       *request,
                                   UsChannelCfg       *entry)
{
    int32_t value = 5400000;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestWidth(netsnmp_agent_request_info *reqInfo,
                               netsnmp_request_info       *request,
                               UsChannelCfg       *entry)
{
    int32_t value = entry->id;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestModulationProfile(netsnmp_agent_request_info *reqInfo,
                                           netsnmp_request_info       *request,
                                           UsChannelCfg       *entry)
{
    int32_t value = entry->id;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestSlotSize(netsnmp_agent_request_info *reqInfo,
                                  netsnmp_request_info       *request,
                                  UsChannelCfg       *entry)
{
    int32_t value = entry->id;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestTxTimingOffset (netsnmp_agent_request_info *reqInfo,
                                         netsnmp_request_info       *request,
                                         UsChannelCfg       *entry)
{
    int32_t value = entry->id;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestRangingBackoffStart(netsnmp_agent_request_info *reqInfo,
                                             netsnmp_request_info       *request,
                                             UsChannelCfg       *entry)
{
    int32_t value = entry->id;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestRangingBackOffend(netsnmp_agent_request_info *reqInfo,
                                           netsnmp_request_info       *request,
                                           UsChannelCfg       *entry)
{
    int32_t value = entry->id;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestTxBackoffStart(netsnmp_agent_request_info *reqInfo,
                                        netsnmp_request_info       *request,
                                        UsChannelCfg       *entry)
{
    int32_t value = entry->id;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestTxBackoffEnd(netsnmp_agent_request_info *reqInfo,
                                      netsnmp_request_info       *request,
                                      UsChannelCfg       *entry)
{
    int32_t value = entry->id;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestScdmaActivecodes(netsnmp_agent_request_info *reqInfo,
                                          netsnmp_request_info       *request,
                                          UsChannelCfg       *entry)
{
    int32_t value = entry->id;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestScdmaCodesperSlot(netsnmp_agent_request_info *reqInfo,
                                           netsnmp_request_info       *request,
                                           UsChannelCfg       *entry)
{
    int32_t value = entry->id;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestScdmaFrameSize(netsnmp_agent_request_info *reqInfo,
                                        netsnmp_request_info       *request,
                                        UsChannelCfg       *entry)
{
    int32_t value = entry->id;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestScdmaHoppingSeed(netsnmp_agent_request_info *reqInfo,
                                          netsnmp_request_info       *request,
                                          UsChannelCfg       *entry)
{
    int32_t value = entry->id;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestType(netsnmp_agent_request_info *reqInfo,
                              netsnmp_request_info       *request,
                              UsChannelCfg       *entry)
{
    int32_t value = entry->id;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestCloneFrom(netsnmp_agent_request_info *reqInfo,
                                   netsnmp_request_info       *request,
                                   UsChannelCfg       *entry)
{
    int32_t value = 0;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestUpDate(netsnmp_agent_request_info *reqInfo,
                                netsnmp_request_info       *request,
                                UsChannelCfg       *entry)
{
    int32_t value = 1;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestStatus(netsnmp_agent_request_info *reqInfo,
                                netsnmp_request_info       *request,
                                UsChannelCfg       *entry)
{
    int32_t value = 0;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

void SnmpSetValueToReqestPreeqEnable(netsnmp_agent_request_info *reqInfo,
                                     netsnmp_request_info       *request,
                                     UsChannelCfg       *entry)
{
    int32_t value = 1;
    snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                             &value, sizeof(int32_t));
}

int DocsIfUpChannelGet(netsnmp_mib_handler               *handler,
                       netsnmp_handler_registration      *regInfo,
                       netsnmp_agent_request_info        *reqInfo,
                       netsnmp_request_info              *requests)
{
    netsnmp_request_info       *request;
    netsnmp_table_request_info *tableInfo;
    UsChannelCfg* entry;

    for (request=requests; request != nullptr; request=request->next)
    {
        entry = (UsChannelCfg*)netsnmp_extract_iterator_context(request);
        if (entry == NULL)
        {
        	cout << "DocsIfUpChannelGet> entry == NULL" << endl;
            netsnmp_set_request_error(reqInfo, request, SNMP_NOSUCHINSTANCE);
            continue;
        }
        tableInfo  = netsnmp_extract_table_info(request);

        map<int, SnmpSetValueToPktHandler>::iterator iter;
        iter = snmpSetValueHandler.find(tableInfo->colnum);
        if(iter != snmpSetValueHandler.end())
        {
            iter->second(reqInfo, request, entry);
        }
        else
        {
        	cout << "DocsIfUpChannelGet> wrong colnum" << endl;
            netsnmp_set_request_error(reqInfo, request, SNMP_NOSUCHOBJECT);
        }
    }

    return SNMP_ERR_NOERROR;
}

int DocsIfUpChannelSetReserve1(netsnmp_mib_handler               *handler,
                               netsnmp_handler_registration      *regInfo,
                               netsnmp_agent_request_info        *reqInfo,
                               netsnmp_request_info              *requests)
{
    return SNMP_ERR_NOERROR;
}

/* MODE_SET_RESERVE2:
 *    When create new entry, this function allocate resource for new entry.
 *    When modify or query entry,  do nothing.
 */
int DocsIfUpChannelSetReserve2(netsnmp_mib_handler               *handler,
                               netsnmp_handler_registration      *regInfo,
                               netsnmp_agent_request_info        *reqInfo,
                               netsnmp_request_info              *requests)
{
    return SNMP_ERR_NOERROR;
}

int DocsIfUpChannelSetFree(netsnmp_mib_handler               *handler,
                            netsnmp_handler_registration      *regInfo,
                            netsnmp_agent_request_info        *reqInfo,
                            netsnmp_request_info              *requests)
{
    return SNMP_ERR_NOERROR;
}

/*
 * When modify table,  the program flow is:
 *      SetReserve1()
 *      SetReserve2()
 *      SetAction()
 *      SetCommit()
 */
int DocsIfUpChannelSetCommit(netsnmp_mib_handler               *handler,
                             netsnmp_handler_registration      *regInfo,
                             netsnmp_agent_request_info        *reqInfo,
                             netsnmp_request_info              *requests)
{
    return SNMP_ERR_NOERROR;
}

int DocsIfUpChannelSetAction(netsnmp_mib_handler               *handler,
                             netsnmp_handler_registration      *regInfo,
                             netsnmp_agent_request_info        *reqInfo,
                             netsnmp_request_info              *requests)
{
    return SNMP_ERR_NOERROR;
}

int DocsIfUpChannelSetUndo(netsnmp_mib_handler               *handler,
                           netsnmp_handler_registration      *regInfo,
                           netsnmp_agent_request_info        *reqInfo,
                           netsnmp_request_info              *requests)
{
    return SNMP_ERR_NOERROR;
}

/** handles requests for the netSnmpIETFWGTable table */
int DocsIfUpChannelHandler(netsnmp_mib_handler               *handler,
                           netsnmp_handler_registration      *regInfo,
                           netsnmp_agent_request_info        *reqInfo,
                           netsnmp_request_info              *requests)
{
    map<int, SnmpOperationHandler>::iterator iter;
    iter = snmpHandler.find(reqInfo->mode);
    assert(iter != snmpHandler.end());
    iter->second(handler, regInfo, reqInfo, requests);

    return SNMP_ERR_NOERROR;
}

#endif


