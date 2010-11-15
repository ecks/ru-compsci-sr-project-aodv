#include <opnet.h>
#include <aodv.h>
#include <aodv_ptypes.h>
#include <math.h>

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
void aodv_geo_LAR_update(int proc_id, double LAR_update_interval);

