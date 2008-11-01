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
aodv_geo_table_create (
	//double expiry_time - not sure if we need it???
						)
	{
	AodvT_Geo_Table*		geo_table_ptr;
	
	/** Allocates and initializes the geo table	**/
	FIN (aodv_geo_table_create (<args>));
	
	/* Allocate memory.								*/
	geo_table_ptr = (AodvT_Geo_Table*) op_prg_mem_alloc (sizeof (AodvT_Geo_Table));
	
	/* Create the Hash tables.						*/
	geo_table_ptr->geo_table = prg_bin_hash_table_create (4, sizeof (int));
	
//	if (addr_family == InetC_Addr_Family_v4)
//		req_table_ptr->forward_request_table = inet_addr_hash_table_create (16, 0);
//	else
//		req_table_ptr->forward_request_table = inet_addr_hash_table_create (0, 16);
	
//	/* Set the remaining parameters.				*/
//	req_table_ptr->forward_request_expiry_time = expiry_time;
//	req_table_ptr->max_rreq_retries            = max_retries;
	
	FRET (geo_table_ptr);
	}

Boolean						
aodv_geo_table_entry_exists(AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address)
	{
	AodvT_Geo_Entry*			geo_entry_ptr;
	
    /** Checks if a specific destination address exists  **/
    /** in the geo table              **/
    FIN (aodv_geo_table__entry_exists (<args>));
    
	/* Check if there exists an entry for this address  */
    geo_entry_ptr = (AodvT_Geo_Entry *) prg_bin_hash_table_item_get (geo_table_ptr->geo_table, (void *) &dst_address);

    if ((geo_entry_ptr == OPC_NIL))
        FRET (OPC_FALSE);

	prg_mem_free(geo_entry_ptr);
	FRET(OPC_TRUE);
	
	}


void
aodv_geo_table_insert (AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address, 
										double dst_x, double dst_y)
	{
	AodvT_Geo_Entry*			geo_entry_ptr;
	void*						old_contents_ptr;
	InetT_Address*				addr_id_ptr;
	
	/** Inserts a new geo entry into the originating geo table	**/
	FIN (aodv_geo_table_insert (<args>));
	
	/* Create an entry for this new request	*/
	geo_entry_ptr = aodv_geo_table_entry_mem_alloc ();
	geo_entry_ptr->dst_address = inet_address_copy (dst_address);
	geo_entry_ptr->insert_time = op_sim_time ();
    geo_entry_ptr->dst_x = dst_x;
	geo_entry_ptr->dst_y = dst_y;
	
	/* Allocate memory for the address	pointing to x and y coordinates */
	addr_id_ptr = (InetT_Address*) op_prg_mem_alloc (sizeof (InetT_Address));
	*addr_id_ptr = dst_address;
	
//	req_entry_ptr->rreq_expiry_evhandle = 
//		op_intrpt_schedule_call (req_entry_ptr->insert_time + req_entry_ptr->current_request_expiry_time, 
//								AODVC_ROUTE_REQUEST_EXPIRY, aodv_rte_rreq_timer_expiry_handle, req_id_ptr);
			
	/* Insert this new request into the request table	*/
	prg_bin_hash_table_item_insert (geo_table_ptr->geo_table, (void *) &dst_address, 
									geo_entry_ptr, &old_contents_ptr);
	
	FOUT;
	}

AodvT_Geo_Entry*
aodv_geo_table_entry_get (AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address, Boolean remove)
	{
	AodvT_Geo_Entry*	geo_entry_ptr = OPC_NIL;
	
	/** Checks if a specific dst_address exists	**/
	/** in the route request table				**/
	FIN (aodv_geotable_entry_get (<args>));
	
	if (remove)
		geo_entry_ptr = (AodvT_Geo_Entry *) prg_bin_hash_table_item_remove (geo_table_ptr->geo_table, (void *) &dst_address);
	else
		geo_entry_ptr = (AodvT_Geo_Entry *) prg_bin_hash_table_item_get (geo_table_ptr->geo_table, (void *) &dst_address);
	
	FRET (geo_entry_ptr);
	}

void
aodv_geo_table_entry_delete (AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address)
	{
	AodvT_Geo_Entry*	geo_entry_ptr;
//	int							num_requests, count;
//	List*						requests_lptr; 
		
	/** Deletes all entries that have the target address	**/
	FIN (aodv_geo_table_entry_delete (<args>));
	
	/* Get the keys	*/
//	requests_lptr = (List *) prg_bin_hash_table_item_list_get (req_table_ptr->orig_request_table);	
//	num_requests = op_prg_list_size (requests_lptr);
	
//	for (count = 0; count < num_requests; count++)
//		{
		/* Check if there exists an entry for this address	*/
//		req_entry_ptr = (AodvT_Orig_Request_Entry *) op_prg_list_access (requests_lptr, count);
	
//		if (inet_address_equal (req_entry_ptr->target_address, dest_addr))
//			{
		geo_entry_ptr = (AodvT_Geo_Entry *) prg_bin_hash_table_item_remove (geo_table_ptr->geo_table, 
								(void *) &dst_address);
		
			/* Cancel the previously scheduled event	*/
//			op_ev_cancel (req_entry_ptr->rreq_expiry_evhandle);
	
			/* Free the request entry	*/
		aodv_geo_table_entry_mem_free (geo_entry_ptr);
//			}
//		}
	
	/* Destroy the list.	*/
//	prg_list_destroy (requests_lptr, OPC_FALSE);
	
	FOUT;
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
/************************ end modified from aodv_request_table *******************/

/********************* begin not modified from aodv_request_table *****************/
/*Boolean
aodv_geo_table_geo_entry_exists (AodvT_Geo_Table* geo_table_ptr, InetT_Address dest_address)
	{
	AodvT_Orig_Request_Entry*	req_entry_ptr;
	List*						requests_lptr;
	int							num_requests, count;
	Boolean						retval = OPC_FALSE;
	
	/** Checks if an entry exists in the originating	**/
	/** table with the specified target address			**/
//	FIN (aodv_geo_table_geo_entry_exists (<args>));
	
	/* Get the keys	*/
/*	requests_lptr = (List *) prg_bin_hash_table_item_list_get (geo_table_ptr->geo_table);
	num_requests = op_prg_list_size (requests_lptr);
	
	if (requests_lptr == OPC_NIL)
		FRET (OPC_FALSE);
	
	for (count = 0; count < num_requests; count++)
		{
		/* Get the current request.	*/
/*		req_entry_ptr = (AodvT_Orig_Request_Entry *) op_prg_list_access (requests_lptr, count);
		
		if (inet_address_equal (req_entry_ptr->target_address, dest_address))
			{
			/* An entry exists for this target address	**/
/*			retval = OPC_TRUE;
			break;
			}
		}
	
	/* Destroy the list.	*/
/*	prg_list_destroy (requests_lptr, OPC_FALSE);
	
	FRET (retval);
	}*/
 
/************************* end not modified from aodv_request_table ************/

/*** Internally callable function ***/

static AodvT_Geo_Entry*
aodv_geo_table_entry_mem_alloc (void)
	{
	static Pmohandle			geo_entry_pmh;
	AodvT_Geo_Entry*			geo_entry_ptr = OPC_NIL;
	static Boolean				geo_entry_pmh_defined = OPC_FALSE;
	
	/** Allocates pooled memory for every geo   	**/
	/** entry in the geo table          			**/
	FIN (aodv_request_table_orig_entry_mem_alloc (void));
	
	if (geo_entry_pmh_defined == OPC_FALSE)
		{
		/* Define the pool memory handle for geo table entry	*/
		geo_entry_pmh = op_prg_pmo_define ("Geo Table Entry", sizeof (AodvT_Geo_Entry), 32);
		geo_entry_pmh_defined = OPC_TRUE;
		}
	
	/* Allocate the geo entry from the pooled memory	*/
	geo_entry_ptr = (AodvT_Geo_Entry*) op_prg_pmo_alloc (geo_entry_pmh);
	
	FRET (geo_entry_ptr);
	}
