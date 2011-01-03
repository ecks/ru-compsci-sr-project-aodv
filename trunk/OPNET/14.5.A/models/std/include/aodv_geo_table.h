#include <opnet.h>
#include <aodv.h>
#include <aodv_ptypes.h>
#include <math.h>

//MKA 01/02/11
int				 aodv_geo_table_entry_sequence_number(AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address);
void 			 aodv_geo_table_update (AodvT_Geo_Table* geo_table_ptr, InetT_Address address,	double x, double y, int sequence_number);
//END MKA

AodvT_Geo_Table* aodv_geo_table_create (InetT_Addr_Family hash_key_addr_family);
Boolean			 aodv_geo_table_entry_exists(AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address);
//void 			 aodv_geo_table_update (AodvT_Geo_Table* geo_table_ptr, InetT_Address address,	double x, double y);
Compcode 		 aodv_geo_table_entry_remove (AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address);
AodvT_Geo_Entry* aodv_geo_table_entry_get (AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address, Boolean remove);
void			 aodv_geo_table_entry_mem_free (AodvT_Geo_Entry* geo_entry_ptr);

static AodvT_Geo_Entry* aodv_geo_table_entry_mem_alloc (void);

// RCMK 2010/12/12
// Added #define for debugging, commenting this line will stop all debug statements
// NOTE: all debug statements should be surrounded by ...
// #ifdef GEO_AODV_TABLE_DEBUG
// debug statements
// #endif
//#define GEO_AODV_TABLE_DEBUG
