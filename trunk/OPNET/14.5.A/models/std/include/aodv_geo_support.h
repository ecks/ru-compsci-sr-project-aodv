#include <opnet.h>
#include <aodv.h>
#include <aodv_ptypes.h>
#include <math.h>

static Boolean aodv_geo_rebroadcast(
						double orig_x, double orig_y,		// Coordinates of the node that originated RREQ
						double prev_x, double prev_y,		// Coordinates of the node that send RREQ
						double curr_x, double curr_y, 		// Coordinates of the node that received RREQ
						double dest_x, double dest_y,		// Coordinates of the destination node
						double flooding_angle,				// Angle in degrees of the flooding angle
						int	   aodv_type);

static int aodv_geo_compute_expand_flooding_angle( 
			InetT_Address_Hash_Table_Handle 	neighbor_connectivity_table, 	
			InetT_Address 						dest_addr, 
			int									src_x,
			int									src_y,
			int 								request_level, 
			AodvT_Geo_Table* 					geo_table_ptr,		
			int	   								aodv_type,
			int									dst_x, 
			int									dst_y);

static Boolean aodv_geo_LAR_distance (double start_x, double start_y,  double mid_x,   double mid_y,  double end_x,   double end_y);
static double  aodv_geo_compute_angle(double start_x, double start_y,  double mid_x,   double mid_y,  double end_x,   double end_y);
static Boolean aodv_rte_rreq_within_area(double computed_angle, int request_level);
static double  aodv_geo_vector_length(double start_x, double start_y,	double end_x,   double end_y);
static Boolean aodv_geo_find_neighbor(	AodvT_Geo_Table* geo_table_ptr,
										PrgT_List* 	     neighbor_list,	
										int 		     request_level,	
										int	src_x,       int src_y,
										int dest_x,      int dest_y);


const double PI = 3.141592653589793238462643383279502884197169399375;
const double MAX_ANGLE = 360;
