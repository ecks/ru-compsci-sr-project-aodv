// MHAVH 10/25/08
/* aodv_geo_table.ex.c */

// modeled after aodv_request_table.ex.c

#include <opnet.h>
#include <aodv.h>
#include <aodv_ptypes.h>
#include <ip_addr_v4.h>
#include <prg_bin_hash.h>

static AodvT_Geo_Entry*		aodv_geo_table_entry_mem_alloc(void);

/************************ begin modified from aodv_request_table *******************/
AodvT_Geo_Table*
aodv_geo_table_create (InetT_Addr_Family hash_key_addr_family
	//double expiry_time - not sure if we need it???
						)
	{
	AodvT_Geo_Table*		geo_table_ptr;
	
	/** Allocates and initializes the geo table	**/
	FIN (aodv_geo_table_create (<args>));
	
	/* Allocate memory.								*/
	geo_table_ptr = (AodvT_Geo_Table*) op_prg_mem_alloc (sizeof (AodvT_Geo_Table));
	
	/* Create the Hash tables.						*/
	// 4 ==> The base-2 log of the desired size (in cells) of the hash table. 
	// sizeof (int) ==> The maximum number of bytes from the key that should be used when computing the hash value. 
	if (hash_key_addr_family == InetC_Addr_Family_v4)
		geo_table_ptr->geo_table = inet_addr_hash_table_create (100, 0);
	else
		geo_table_ptr->geo_table = inet_addr_hash_table_create (0, 100);
	//geo_table_ptr->geo_table = prg_bin_hash_table_create (4, sizeof (int));
	
	
	FRET (geo_table_ptr);
	}

Boolean						
aodv_geo_table_entry_exists(AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address)
	{
	AodvT_Geo_Entry*			geo_entry_ptr = OPC_NIL;
	
    /** Checks if a specific destination address exists  **/
    /** in the geo table              **/
    FIN (aodv_geo_table_entry_exists (<args>));
    
	/* Check if there exists an entry for this address  */
    geo_entry_ptr = (AodvT_Geo_Entry *) inet_addr_hash_table_item_get(geo_table_ptr->geo_table, &dst_address);
	//prg_bin_hash_table_item_get (geo_table_ptr->geo_table, (void *) &dst_address);
	
	if ((geo_entry_ptr == PRGC_NIL))
        FRET (OPC_FALSE);
	
	FRET(OPC_TRUE);
	
	}


void
aodv_geo_table_insert (AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address, 
										double dst_x, double dst_y)
	{
	AodvT_Geo_Entry*			geo_entry_ptr;
	char						addr_str [INETC_ADDR_STR_LEN];
	
	
	/** Inserts a new geo entry into the originating geo table	**/
	FIN (aodv_geo_table_insert (<args>));
	
	
	// Print dest address for debugging
	inet_address_print (addr_str, dst_address);
	
	if (aodv_geo_table_entry_exists(geo_table_ptr, dst_address))
		{
			printf("^^^^^^^^^^^^^^^^Entry for %s Exists. Insert is omitted!!!\n",addr_str);
		//	printf("^^^^^^^^^^^^^^^^Currently we have %d items in GEO TABLE!!!\n",
		//		prg_bin_hash_table_num_items_get(geo_table_ptr->geo_table));
		}
	else
		{
		/* Create an entry for this new request	*/
		geo_entry_ptr = aodv_geo_table_entry_mem_alloc ();
		geo_entry_ptr->dst_address = inet_address_copy (dst_address);
		geo_entry_ptr->insert_time = op_sim_time ();
		geo_entry_ptr->dst_x = dst_x;
		geo_entry_ptr->dst_y = dst_y;
		
		/* Insert this new request into the request table	*/
		printf("^^^^^^^^^^^^^^^^Storing Dest %s with key %d\n", addr_str, (int) &dst_address);
		inet_addr_hash_table_item_insert(geo_table_ptr->geo_table, &dst_address, geo_entry_ptr, PRGC_NIL);
//		prg_bin_hash_table_item_insert (geo_table_ptr->geo_table,  &(dst_address.address.ipv4_addr), 
//										geo_entry_ptr, PRGC_NIL);
		}
	

			
	
	FOUT;
	}


// Purpose: Overwrites an entry in the GeoTable if exist
//			if not, simply inserts the entry
// In:		geo_table_prt -- pointer to the GeoTable
//			address -- IP address of the node to be added into the GeoTable
//			x,y     -- coordinates of the node to be added into the GeoTable
// Out: 	NONE
// Uses:	aodv_geo_table_entry_exists
//			aodv_geo_table_entry_delete
//			aodv_geo_table_insert
void aodv_geo_table_update (AodvT_Geo_Table* geo_table_ptr, 
							InetT_Address address,	double x, double y)
{
		
	/** Inserts a new geo entry into the originating geo table	**/
	FIN (aodv_geo_table_update (<args>));
	
		
	// Delete old entry if exists
	if (aodv_geo_table_entry_exists(geo_table_ptr, address))
	{
			aodv_geo_table_entry_delete(geo_table_ptr, address);
	}
	

	// add a new entry
	aodv_geo_table_insert(geo_table_ptr, address, x, y);
					
	
	FOUT;
}


// Purpose: remove entry from geoTable if exists
// In:		geo_table_prt -- pointer to the GeoTable
//			address -- IP address of the node to be added into the GeoTable
// Out: 	NONE
// Uses:	aodv_geo_table_entry_exists
//			aodv_geo_table_entry_delete
Compcode
aodv_geo_table_entry_remove (AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address)
{
	
	/** Deletes all entries that have the target address	**/
	FIN (aodv_geo_table_entry_remove (<args>));
	

	// Delete old entry if exists
	if (aodv_geo_table_entry_exists(geo_table_ptr, dst_address))
	{
			aodv_geo_table_entry_delete(geo_table_ptr, dst_address);
			FRET (OPC_COMPCODE_SUCCESS);
	}
	FRET (OPC_COMPCODE_FAILURE);
}


AodvT_Geo_Entry*
aodv_geo_table_entry_get (AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address, Boolean remove)
	{
	AodvT_Geo_Entry*	geo_entry_ptr = OPC_NIL;
	char				addr_str [INETC_ADDR_STR_LEN];
	
	/** Checks if a specific dst_address exists	**/
	/** in the route request table				**/
	FIN (aodv_geo_table_entry_get (<args>));
	
	inet_address_print (addr_str, dst_address);
	
	if (remove)
		{
		printf("^^^^^^^^^^^^^^^^REMOVING Dest %s with key %d\n", addr_str, (int) &dst_address);
		geo_entry_ptr = (AodvT_Geo_Entry *) inet_addr_hash_table_item_get(geo_table_ptr->geo_table, &dst_address);
		// prg_bin_hash_table_item_remove (geo_table_ptr->geo_table, (void *) &dst_address);
		}
	else
		{
		printf("^^^^^^^^^^^^^^^^GETTING Dest %s with key %d\n", addr_str, (int) &dst_address);
		geo_entry_ptr = (AodvT_Geo_Entry *) inet_addr_hash_table_item_get(geo_table_ptr->geo_table, &dst_address);
		//prg_bin_hash_table_item_get (geo_table_ptr->geo_table, (void *) &dst_address);
		}

	inet_address_print (addr_str, geo_entry_ptr->dst_address);
	printf("^^^^^^^^^^^^^^^^OBTAINED Dest %s \n", addr_str);
	FRET (geo_entry_ptr);
	}

Compcode
aodv_geo_table_entry_delete (AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address)
	{
	AodvT_Geo_Entry*	geo_entry_ptr;
	char				addr_str [INETC_ADDR_STR_LEN];
	
	/** Deletes all entries that have the target address	**/
	FIN (aodv_geo_table_entry_delete (<args>));
	
	// Print dest address for debugging
	inet_address_print (addr_str, dst_address);	
	printf("^^^^^^^^^^^^^^^^Deleting Dest %s with key %d\n", addr_str, (int) &dst_address);
	
	geo_entry_ptr = (AodvT_Geo_Entry *) inet_addr_hash_table_item_remove(geo_table_ptr->geo_table, &dst_address);
	// prg_bin_hash_table_item_remove (geo_table_ptr->geo_table, 	(void *) &dst_address);

	if (geo_entry_ptr == OPC_NIL)
		FRET (OPC_COMPCODE_FAILURE);
	
	/* Free the request entry	*/
	aodv_geo_table_entry_mem_free (geo_entry_ptr);
	
	FRET (OPC_COMPCODE_SUCCESS);
	}
		

void
aodv_geo_table_entry_mem_free (AodvT_Geo_Entry* geo_entry_ptr)
	{
	/** Frees the memory associated with the	**/
	/** geo table entry						**/
	FIN (aodv_geo_table_entry_mem_free (<args>));
	
	/* Destroy the IP address	*/
	inet_address_destroy (geo_entry_ptr->dst_address);
	
	/* Free the memory	*/
	op_prg_mem_free (geo_entry_ptr);
	
	FOUT;
	} 


/*** Internally callable function ***/

static AodvT_Geo_Entry*
aodv_geo_table_entry_mem_alloc (void)
	{
	static Pmohandle		geo_entry_pmh;
	AodvT_Geo_Entry*		geo_entry_ptr = OPC_NIL;
	
	/** Allocates pooled memory for every geo   	**/
	/** entry in the geo table          			**/
	FIN (aodv_geo_table_entry_mem_alloc (void));

	/* Define the pool memory handle for geo table entry	*/
	geo_entry_pmh = op_prg_pmo_define ("Geo Table Entry", sizeof (AodvT_Geo_Entry), 32);
	
	/* Allocate the geo entry from the pooled memory	*/
	geo_entry_ptr = (AodvT_Geo_Entry*) op_prg_pmo_alloc (geo_entry_pmh);
	
	FRET (geo_entry_ptr);
	}
