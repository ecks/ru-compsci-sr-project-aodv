#include <opnet.h>
#include <aodv.h>
#include <aodv_ptypes.h>
#include <math.h>

AodvT_Geo_Table* aodv_geo_table_create (InetT_Addr_Family hash_key_addr_family);
Boolean			 aodv_geo_table_entry_exists(AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address);
void			 aodv_geo_table_insert (AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address, double dst_x, double dst_y);
void 			 aodv_geo_table_update (AodvT_Geo_Table* geo_table_ptr, InetT_Address address,	double x, double y);
Compcode 		 aodv_geo_table_entry_remove (AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address);
AodvT_Geo_Entry* aodv_geo_table_entry_get (AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address, Boolean remove);
Compcode		 aodv_geo_table_entry_delete (AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address);
void			 aodv_geo_table_entry_mem_free (AodvT_Geo_Entry* geo_entry_ptr);

static AodvT_Geo_Entry* aodv_geo_table_entry_mem_alloc (void);
