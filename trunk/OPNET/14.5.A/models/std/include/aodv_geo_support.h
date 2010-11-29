//RCMKA 11/22/2010
#ifndef _AODV_GEO_SUPPORT
#define _AODV_GEO_SUPPORT

#include <opnet.h>
#include <aodv.h>
#include <aodv_ptypes.h>
#include <math.h>
#include <stdio.h>


Boolean aodv_geo_rebroadcast(
						double orig_x, double orig_y,		
						double prev_x, double prev_y,		
						double curr_x, double curr_y, 		
						double dest_x, double dest_y,		
						double flooding_angle,				
						int	   aodv_type);


int aodv_geo_compute_expand_flooding_angle( 
			InetT_Address_Hash_Table_Handle 	neighbor_connectivity_table, 	
			InetT_Address 						dest_addr, 
			double								src_x,
			double								src_y,
			int 								request_level, 
			AodvT_Geo_Table* 					geo_table_ptr,		
			int	   								aodv_type,
			double*								dst_x, 
			double*								dst_y);

Boolean aodv_geo_LAR_distance(double start_x, double start_y,  double mid_x,   double mid_y,  double end_x,   double end_y);

double  aodv_geo_compute_angle(double start_x, double start_y,  double mid_x,   double mid_y,  double end_x,   double end_y);

Boolean aodv_rte_rreq_within_area(double computed_angle, int request_level);

double  aodv_geo_vector_length(double start_x, double start_y,	double end_x,   double end_y);

Boolean aodv_geo_find_neighbor(AodvT_Geo_Table* geo_table_ptr,
										PrgT_List* 	     neighbor_list,	
										int 		     request_level,	
										double	src_x,   double src_y,
										double dest_x,   double dest_y);
// VHRCMA	11/11/10
// This function will be called upon each LAR interrupt to update
// each node's LAR_Data information.
void aodv_geo_LAR_update(int proc_id, double LAR_update_interval);

//MKA	11/23/10
typedef struct LAR_Data
{
	double x;
	double y;
	double velocity;
	double time;
} LAR_Data;

// MKA 11/23/10
// This is the category in which the LAR_Data will
// be stored in the global database.
static const char* LAR_OMS_CATEGORY = "LAR_DATA";

// MKA 11/23/10
// This determines the size of the name attribute used
// as a key to pull LAR_Data in the database.
#define NAME_ATTR_SIZE 128

// MKA 11/23/10
// Comment out the following define to turn off LAR debug printing.
#define LAR_DEBUG

#endif

