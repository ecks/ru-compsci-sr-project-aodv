//#include <aodv_geo_support.h>
#include <opnet.h>
#include <aodv.h>
#include <aodv_ptypes.h>
#include <math.h>

const double PI = 3.141592653589793238462643383279502884197169399375;
const double MAX_ANGLE = 360;

			   
// Purpose:	 Compute the length of the vector
// IN:	    	 start_x, start_y -- starting point of the vector
//			 	end_x, end_y	-- ending point of the vector
// OUT:		 length of the vector
double
aodv_geo_vector_length(double start_x, double start_y,
						double end_x,   double end_y)
{
	double x, y;

	FIN (aodv_geo_vector_length( <args> ));
	
	x = end_x - start_x;
	y = end_y - start_y;
	
	FRET (sqrt(pow(x,2.0) + pow(y, 2.0)));
}

// MHAVH 11/11/08 -  THIS function is NOT needed yet!!!
// Purpose: 	determine if the current node is within the search area
//				
// Algorithm:	compute the angle between if the angle is smaller than the request level,
// we can forward the packet, otherwise drop it
// IN:			angle			-- angle in degrees formed by the 3 nodes (source, current, detination or previous, current, destination)
//				request_level	-- request angle in multiples of 90
Boolean
aodv_rte_rreq_within_area(double computed_angle, int request_level)
{	
    FIN (aodv_rte_rreq_within_area( <args> ));

	// Flooding angle starts from 0 and goes to 3
	// flooding angle = (request_level +1) *90

	// the flooding angle is being computed as the request level multiplied 
	// by 45 and not 90  degrees because the computed angle could be located
	// on either side of the line that equally divides floodingn angle
	if(computed_angle <= (request_level+1) * 45.0)
		{
	    FRET(OPC_TRUE);
		}

	FRET(OPC_FALSE);

}

// MHAVH 11/11/08 
// Purpose:   	Compute the angle SME formed by three points: start (S), middle (M), end (E)
// In:			start_x, start_y -- position of starting point S
//				mid_x, mid_y	 -- position of the middle point M
//				end_x, end_y	 -- position of ending point E	
// Out:			a value of the angle formed by the points S, M, E in units of degrees 

double aodv_geo_compute_angle(double start_x, double start_y, 
							  double mid_x, double mid_y, 
							  double end_x, double end_y)
{
	double vector_SE_x;
	double vector_SE_y;
	
	double vector_SM_x;
	double vector_SM_y;
			
	double angle_form_numer;
	double angle_form_denom;
	
	
	double angle;
	
		
	FIN (aodv_geo_compute_angle( <args> ));
	
	vector_SE_x = end_x - start_x;
	vector_SE_y = end_y - start_y;
	
	vector_SM_x = mid_x - start_x;
	vector_SM_y = mid_y - start_y;
	
		
	angle_form_numer = (vector_SE_x * vector_SM_x) + (vector_SE_y * vector_SM_y);
	angle_form_denom = aodv_geo_vector_length(start_x, start_y, end_x, end_y) *  
		               aodv_geo_vector_length(start_x, start_y, mid_x, mid_y);	
	
	angle = acos(angle_form_numer/angle_form_denom) * (180/PI);
	
	
	// Debugging messages
	printf("angle_form_numer -> %.f, angle_form_denom -> %.f\n", angle_form_numer,	angle_form_denom);
	printf("acos(angle_form_numer/angle_form_denom) * (180/pi) -> %.f\n", angle);
	
	

    FRET(angle);	

}



// Purpose:		find neighbors in current flooding angle
// IN:			neighbor_list	-- list of neighbors
//				request_level	-- request angle in multiples of 90
//				geo_entry_ptr	-- not sure if needed!!
// OUT:			TRUE: neighbor is found within flooding angle
//				FALSE: no neighbors found
Boolean aodv_geo_find_neighbor(	AodvT_Geo_Table* geo_table_ptr,
								PrgT_List* 	     neighbor_list,	// list of neighbors
								int 		     request_level,	// request level/flooding angle
								double	src_x,   double src_y,
								double dest_x,   double dest_y)
{
	double 				angle;
	AodvT_Geo_Entry* 	geo_neighbor;
	AodvT_Conn_Info* 	neighbor;
	int					i, size;

	FIN(aodv_geo_find_neighbor(<args>));
	
	size = prg_list_size(neighbor_list);

	// go through the lilst of neighbors
	for(i = 0; i < size; i++)
	{
		// get  neighbor
		neighbor = prg_list_access(neighbor_list, i);
		
		// get neighbour GeoTable entry
		geo_neighbor = aodv_geo_table_entry_get(geo_table_ptr, neighbor->neighbor_address, OPC_FALSE);
		
		// If neighbour exists then check if it is in the area defined  by the flooding anglee
		if(geo_neighbor != OPC_NIL)
		{
			// compute the angle formed by destination, previous node, and neighbor node
			angle = aodv_geo_compute_angle(	dest_x, dest_y, src_x, src_y,
											geo_neighbor->dst_x, geo_neighbor->dst_y);
			
			// Check if is within the area defined by the flooding angle/request level
			if(aodv_rte_rreq_within_area(angle, request_level));
			{
				FRET(OPC_TRUE);
			}
		}
	}

	FRET(OPC_FALSE);

}

// Purpose:	 Determine if the lenght of the vector formed by start-end  points(vector SE) is
//			 	 greater than the length of the vector formed by middle-end points(vector ME)
// IN:			 start_x, start_y	-- position of node where the RREQ was received
//				 mid_x, mid_y		-- position of node that received the RREQ
//				 end_x, end_y		-- position of the destination node
// OUT:		 True if length(SE) >= length (ME)
//			 	 False, otherwise
Boolean
aodv_geo_LAR_distance(double start_x, double start_y,
				  double mid_x,   double mid_y, 
				  double end_x,   double end_y)
{
		
	FIN (aodv_rte_rreq_within_distance( <args> ));
	
	
	if (aodv_geo_vector_length(start_x, start_y, end_x, end_y) <= 
		aodv_geo_vector_length(mid_x, mid_y, end_x, end_y))
	{
		FRET(OPC_TRUE);
	}
	
	FRET(OPC_FALSE);
}




Boolean aodv_geo_rebroadcast(
						double orig_x, double orig_y,		// Coordinates of the node that originated RREQ
						double prev_x, double prev_y,		// Coordinates of the node that send RREQ
						double curr_x, double curr_y, 		// Coordinates of the node that received RREQ
						double dest_x, double dest_y,		// Coordinates of the destination node
						double flooding_angle,				// Angle in degrees of the flooding angle
						int	   aodv_type)					// Type of AODV being used
{
	double angle;
	
	FIN (aodv_geo_rebroadcast( <args> ));
	
	switch(aodv_type)
	{
		case (AODV_TYPE_LAR_DISTANCE):
			// if current node is at least as close as the previous node from destination
			// then rebroadcast RREQ (return true), else drop (return false)
			// NOTE: in LAR distance the nodes compare the distances with the previous node.
			FRET(aodv_geo_LAR_distance(prev_x, prev_y, curr_x, curr_y, 	dest_x, dest_y));
				
	
		case AODV_TYPE_GEO_STATIC:
		case AODV_TYPE_GEO_EXPAND:
			// GeoAODV implementation:
			// Compute the angle formed by the destination, source and current nodes
			// if computed angle is not larger than flooding angle (e.g. the value is carried via request level)
			// then forward RREQ, else drop RREQ
			
			// NOTE: GEO_Expand operated the same way plus one additional condition which check if
			// there are any neighboring nodes within the search area defined by the flooding angle -- this is implemented
			// in aodv_rte process model
			
			// Check if this is not a broadcast
			if(flooding_angle < 360)
			{
				
				// Compute the angle formed by the destination node, originating node, and current node
				// Since the angle may be located on either side of the vector formed by the source-destination
				// nodes we need to multiple the computed value of angle by 2 before comparing it to the value of the
				// flooding angle, e.g. flooding angle is evenly devided by the line formed via source-destination nodes
				angle = 2*aodv_geo_compute_angle(dest_x, dest_y, orig_x, orig_y, curr_x, curr_y);
				
				if (angle > flooding_angle)
				{
					FRET(OPC_FALSE);
				}
				
				
			}
			
			// THis is NOT a brodcast or 
			//    the angle formed by orig, curr, and dest node is less than floodign angle
			//	
			FRET(OPC_TRUE);
		
		case AODV_TYPE_GEO_ROTATE:
			// GeoAODV Rotate_01 implementation:
			
			// Set flooding angle to intial value degrees, forward to all neighbours in the search 
			// area formed by the  flooding angle
			// if fails to find the route then increment flooding angle until it reaches 360 degrees 
			// and morphs into regular AODV
			
			//
			// NOTE: angle at the intermediate node is computed based on the previous node location
			
			// Check if this is not a broadcast
			if(flooding_angle < MAX_ANGLE)
			{
				// Compute the angle formed by the destination node, originating node, and previous node
				// Since the angle may be located on either side of the vector formed by the previous-destination
				// nodes we need to multiple the computed value of angle by 2 before comparing it to the value of the
				// flooding angle, e.g. flooding angle is evenly devided by the line formed via prev-destination nodes
				angle = 2*aodv_geo_compute_angle(dest_x, dest_y, prev_x, prev_y, curr_x, curr_y);
				
				if (angle > flooding_angle)
				{
					FRET(OPC_FALSE);
				}
				
				
			}
			
			// THis is NOT a brodcast or 
			//    the angle formed by orig, curr, and dest node is less than floodign angle
			//	
			FRET(OPC_TRUE);

	
		case AODV_TYPE_GEO_ROTATE_01:
			// GeoAODV Rotate_01 implementation:
			
			// Set angle to 180 degrees, forward to all neighbours in the search area formed by the 
			// flooding angle of 180 degrees, 
			// if fails to find the route then resort to regular AODV
			// NOTE: angle at the intermediate node is computed based on the previous node location
			
			// Check if this is not a broadcast
			if(flooding_angle < MAX_ANGLE)
			{
				// Compute the angle formed by the destination node, originating node, and previous node
				// Since the angle may be located on either side of the vector formed by the previous-destination
				// nodes we need to multiple the computed value of angle by 2 before comparing it to the value of the
				// flooding angle, e.g. flooding angle is evenly devided by the line formed via prev-destination nodes
				angle = 2*aodv_geo_compute_angle(dest_x, dest_y, prev_x, prev_y, curr_x, curr_y);
				
				if (angle > MAX_ANGLE/2)
				{
					FRET(OPC_FALSE);
				}
				
				
			}
			
			// THis is NOT a broadcast or 
			//    the angle formed by orig, curr, and dest node is less than floodign angle
			//	
			FRET(OPC_TRUE);
		
		case AODV_TYPE_LAR_ZONE:
			// NOT implemented yet
		case AODV_TYPE_REGULAR:		
			FRET(OPC_TRUE);
		}
	
	FRET (OPC_TRUE);
}


// Purpose:	Given positions of the nodes, flooding angle, and aodv type
//				determine if the current node should rebroadcast RREQ or not
// IN:			orig_x, orig_y -- position of the node that originated the RREQ
//				prev_x, prev_y -- position of the node where the RREQ was received from
//				curr_x, curr_y -- position of the node that received the RREQ
//				dest_x, dest_y -- position of the destination node
//				flooding_angle -- acceptable angle to forward the RREQ
//				aodv_type	   -- type of aodv being used
// Out:		TRUE if the current node should rebroadcase the RREQ
//				FALSE if the RREQ should be destroyed

// Purpose:	Decide to change the flooding angle based on geo table information of
//				neighboring nodes
// IN:			orig_x, orig_y -- position of the node that originated the RREQ
//				prev_x, prev_y -- position of the node where the RREQ was received from
//				curr_x, curr_y -- position of the node that received the RREQ
//				dest_x, dest_y -- position of the destination node
//				flooding_angle -- acceptable angle to forward the RREQ
//				aodv_type	   -- type of aodv being used
// Out:			return RREQ
int aodv_geo_compute_expand_flooding_angle( 
			InetT_Address_Hash_Table_Handle 	neighbor_connectivity_table, 	
			InetT_Address 						dest_addr, 
			double								src_x,
			double								src_y,
			int 								request_level, 
			AodvT_Geo_Table* 					geo_table_ptr,		
			int	   								aodv_type,
			double*								dst_x, //&dst_x
			double* 							dst_y)	//&dst_y		
{
	PrgT_List* 			neighbor_list;
	AodvT_Geo_Entry* 	geo_entry_ptr;

	FIN (aodv_geo_rreqsend( <args> ));


	// default destination coordinates and flood angle is brodacast angle.
	*dst_x = DEFAULT_X;
	*dst_y = DEFAULT_Y;
	
	switch(aodv_type)
		{
		case AODV_TYPE_GEO_STATIC:
		case AODV_TYPE_GEO_EXPAND:
		case AODV_TYPE_GEO_ROTATE:
		case AODV_TYPE_GEO_ROTATE_01:
		
			// handle via an outside function creating RREQ with Geo Information
			if(aodv_geo_table_entry_exists(geo_table_ptr, dest_addr) == OPC_FALSE)
			{
				// Destination is not in geoTable ==> BROADCAST)
				request_level = BROADCAST_REQUEST_LEVEL;
			}
			else
			{
			
				// RJ_VH 5/20/10
				// AODV_ROTATE_01 always starts and uses 180 degree flooding angle
				// unless there are no neighboring nodes within that area
				if (aodv_type == AODV_TYPE_GEO_ROTATE_01 && request_level == 0)
				{
					// This is the initial Route discover phase. First time request level is set to 180 
					request_level = 1; // initially flooding angle = 180 degrees
				}

			
			
				// Get Destination's info
				geo_entry_ptr = aodv_geo_table_entry_get(geo_table_ptr, dest_addr, OPC_FALSE);

				// get neighbor list
				neighbor_list = inet_addr_hash_table_item_list_get(neighbor_connectivity_table, inet_address_family_get(&dest_addr));
				
				while (request_level != BROADCAST_REQUEST_LEVEL)
				{
				
					if ((aodv_geo_find_neighbor (geo_table_ptr, neighbor_list, request_level,	
												src_x, src_y, geo_entry_ptr->dst_x, geo_entry_ptr->dst_y)) == OPC_TRUE)
					{
						// Broadcast is NOT neeeded, request level is found
						break;
					}
					// Check bigger angle
					request_level++;
				}
				
				// Set destination coordinates
				*dst_x = geo_entry_ptr->dst_x;
				*dst_y = geo_entry_ptr->dst_y;
			}
			break;
		
		
		case AODV_TYPE_LAR_DISTANCE:
		case AODV_TYPE_LAR_ZONE:
		case AODV_TYPE_REGULAR:
		default:
			// do not use or expland the flooding angle based on neightbor locations
			request_level = BROADCAST_REQUEST_LEVEL;
			break;
		
		}
	
	
	// Destination is not  in geoTable ==> BROADCAST)
	// or request level is computed to be broadcast
	FRET(request_level);

}
