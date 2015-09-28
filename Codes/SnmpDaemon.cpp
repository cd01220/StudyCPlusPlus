#include "SystemInclude.h"

#include "SnmpDocsIfUpChannelTable.h"
#include "SnmpDaemon.h"

using namespace std;

void CreateSnmpAgent()
{
    const char *appName = "controller";
	snmp_enable_stderrlog();

	/* Initialize tcpip, if necessary */
	SOCK_STARTUP;

	/* For Win7 + VC2012, net-snmp version must be 5.7.3 or later.
     * int init_agent(const char *app)
	 * Calls into init_agent_read_config to set the app's configuration file
	 * in the appropriate default storage space, NETSNMP_DS_LIB_APPTYPE.
	 * Need to call init_agent before calling init_snmp.
	*/
	if (init_agent(appName) != 0)
		cout << "init_agent() failed" << endl;    

	/* Calls the functions to do config file loading and mib
	 * module parsing in the correct order.
	 */
	init_snmp(appName);
    
	/* Initialize the Common MIB modules */
	init_mib_modules();

	/* init custom mib modules. */
	InitDocsIfUpChannelTable();

    init_master_agent();
	
	while(true)
	{
	    /* if you use select(), see snmp_select_info() in snmp_api(3) */
	    /*     --- OR ---  */
	    agent_check_and_process(1); /* 0 == don't block */
	}

}