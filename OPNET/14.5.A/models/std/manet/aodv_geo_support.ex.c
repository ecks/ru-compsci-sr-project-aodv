#include <opnet.h>
#include <aodv.h>
#include <aodv_ptypes.h>
#include <math.h>
//MKA 11/21/10
#include <aodv_geo_support.h>
#include <ip_rte_support.h>

const double PI = 3.141592653589793238462643383279502884197169399375;
const double MAX_ANGLE = 360;

// MKA 12/02/10
// This is here for use in get_node_ip. The other option was to
// change all the method signatures and pass it around, so I figured this
// would be easier.
static InetT_Addr_Family aodv_addressing_mode;
			   
// Purpose:	 Compute the length of the vector
// IN:	    	 start_x, start_y -- starting point of the vector
//			 	end_x, end_y	-- ending point of the vector
// OUT:		 length of the vector
double	aodv_geo_vector_length(double start_x, double start_y,	double end_x,   double end_y)
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
// 				we can forward the packet, otherwise drop it
//
// IN:			angle			-- angle in degrees formed by the 3 nodes (source, current, detination or previous, current, destination)
//				request_level	-- request angle in multiples of 90
Boolean	aodv_rte_rreq_within_area(double computed_angle, int request_level)
{	
    FIN (aodv_rte_rreq_within_area( <args> ));

	// Flooding angle starts from 0 and goes to 3
	// flooding angle = (request_level +1) *90

	// the flooding angle is being computed as the request level multiplied 
	// by 45 and not 90  degrees because the computed angle could be located
	// on either side of the line that equally divides floodingn angle
	if(computed_angle <= (request_level+1) * 45.0)
	{
	    FRET(OPC_TRUE)
	}

	FRET(OPC_FALSE);

}

// MHAVH 11/11/08 
// Purpose:   	Compute the angle SME formed by three points: start (S), middle (M), end (E)
//
// In:			start_x, start_y -- position of starting point S
//				mid_x, mid_y	 -- position of the middle point M
//				end_x, end_y	 -- position of ending point E	
//
// Out:			a value of the angle formed by the points S, M, E in units of degrees 
double aodv_geo_compute_angle(double start_x, double start_y, 
							  double mid_x, double mid_y, 
							  double end_x, double end_y)
{
	double vector_MS_x;
	double vector_MS_y;
	
	double vector_ME_x;
	double vector_ME_y;
			
	double angle_form_numer;
	double angle_form_denom;
	
	
	double angle;
	
		
	FIN (aodv_geo_compute_angle( <args> ));
	
	vector_MS_x = mid_x - start_x;
	vector_MS_y = mid_y - start_y;
	
	vector_ME_x = mid_x - end_x;
	vector_ME_y = mid_y - end_y;
	
		
	angle_form_numer = (vector_MS_x * vector_ME_x) + (vector_MS_y * vector_ME_y);
	angle_form_denom = aodv_geo_vector_length(mid_x, mid_y, start_x, start_y) *  
		               aodv_geo_vector_length(mid_x, mid_y, end_x, end_y);	
	
	angle = acos(angle_form_numer/angle_form_denom) * (180/PI);
	
	
// Debugging messages
//	printf("angle_form_numer -> %.f, angle_form_denom -> %.f\n", angle_form_numer,	angle_form_denom);
//	printf("acos(angle_form_numer/angle_form_denom) * (180/pi) -> %.f\n", angle);
	
	
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

	// go through the list of neighbors
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

// Purpose:	 Determine if the length of the vector formed by start-end  points(vector SE) is
//			 	 greater than the length of the vector formed by middle-end points(vector ME)
//
// IN:			 start_x, start_y	-- position of node where the RREQ was generated (e.g. previous node, not an originator)
//				 mid_x, mid_y		-- position of node that receives the RREQ
//				 end_x, end_y		-- position of the destination node
//
// OUT:		 True,  if length(SE) >= length (ME)
//			 False, otherwise
Boolean
aodv_geo_LAR_distance(double start_x, double start_y,
					  double mid_x,   double mid_y, 
					  double end_x,   double end_y)
{
		
	FIN (aodv_rte_rreq_within_distance( <args> ));
	
	
	if (aodv_geo_vector_length(start_x, start_y, end_x, end_y) >=
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
						int	   aodv_type, 					// Type of AODV being used
						double dest_velocity)				// The calculated velocity of the destination node (LAR)
{
	double angle;
	
	FIN (aodv_geo_rebroadcast( <args> ));
	
	switch(aodv_type)
	{
		case (AODV_TYPE_LAR_DISTANCE):
			// if current node is at least as close as the previous node from destination
			// then rebroadcast RREQ (return true), else drop (return false)
			// NOTE: in LAR distance the nodes compare the distances with the previous node.
			// LAR TODO
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
				
				
				// Use functions within the area if possible
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
			// LAR TODO!
			FRET(aodv_geo_LAR_within_request_zone(orig_x, orig_y, curr_x, curr_y, dest_x, dest_y, dest_velocity));
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
		
		case AODV_TYPE_LAR_DISTANCE:
		case AODV_TYPE_LAR_ZONE:
		// LAR TODO
			// MKA 12/08/10 - Both LAR Schemes can use the same code as GEO_ROTATE_01.
			//					But if the request_level > 1 (ie the first attempt failed)...
			//						should be flood or try again?
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

// MKA 11/25/10
// Retrieve the current node's IP and store it in ip_str.
void get_node_ip(char ip_str[], IpT_Rte_Module_Data* module_data, int output_intf_index)
{
	//Store this node's IP into ip_str.

	IpT_Interface_Info*	ifinfo;
	InetT_Address		inet_addr;
	
	FIN (get_node_ip (<args>));
	
	//IpT_Rte_Module_Data* module_data_ptr = (IpT_Rte_Module_Data*) op_pro_modmem_access ();
	
	//MKAVH	11/25/10
	ifinfo = inet_rte_intf_tbl_access(module_data, output_intf_index);
	inet_addr = inet_rte_intf_addr_get(ifinfo, aodv_addressing_mode);
	inet_address_print(ip_str, inet_addr);

#ifdef LAR_DEBUG
	printf("Retrieved IP: %s\n", ip_str);
#endif
	
	FOUT;
	
}


// MKA 11/23/10
// Print the given LAR_Data to stdout.
void print_lar_data(LAR_Data *lar_data)
{
	printf("LAR DATA\n");
	printf("--------\n");
	printf("Position: \t(%f, %f)\n", lar_data->x, lar_data->y);
	printf("Velocity: \t%f\n", lar_data->velocity);
	printf("Time:     \t%f\n", lar_data->time);
}

	
// VHRCMA	11/11/10
// TODO RC 11/22/2010 We need to ensure that this only runs when 
// LAR is active, i.e it shouldn't running unless it's needed.
// Maybe we can alter our interupt condition to include this.
//
// MKA 11/23/10	Finished implementing interrupt.
// NOTE: This function assumes that an entry exists in the global
//		 database to update, and always pulls the data using IF0 as a key.

void aodv_geo_LAR_update( int proc_id, double update_interval  )
{
	
	int 		node_id;				//This node's id.
	void*		data;					//Generic data storage pointer for when LAR_Data is retrieved from the database.
	LAR_Data*	lar_data;				//The data stored in the database
	double 		x,y, velocity, time;	//The node's current x, y, v, and t
	char		address[INETC_ADDR_STR_LEN]; 	// The node's IP address.
	IpT_Rte_Module_Data* module_data_ptr;		// The module data to use.
	
	FIN (aodv_geo_LAR_update( <args> ));
	
#ifdef LAR_DEBUG
	printf("=========================LAR UPDATE=========================\n");
#endif
	
	/* COLLECT ATTRIBUTES FROM NODE */
	node_id = op_topo_parent(proc_id);
	op_ima_obj_attr_get (node_id, "x position", &x);
	op_ima_obj_attr_get (node_id, "y position", &y);

	// the module_data_ptr should really be retrieved through the proc_id somehow...
	module_data_ptr = (IpT_Rte_Module_Data*) op_pro_modmem_access ();
	get_node_ip(address, module_data_ptr, 0);
	
	
	
	// -1. Create a struct to save x,y, velocity, and time
	// decalre data struct in aodv_geo_support.h
	// 1. Get IP address
	// 2. Convert IP address into string (char *): inet_address_print
	// 3. Compute Velocity
	// 4. Store: x,y, velocity, current time into global table using IP address as a key
	// oms_data_def_entry_insert()
	// oms_data_def_entry_access()
	
	
	/* RETRIEVE DATA FROM DATABASE */
	
	data = oms_data_def_entry_access(LAR_OMS_CATEGORY, address);
	if (data == OPC_NIL)
	{
		// We haven't stored data for this node!
		printf("No initial LAR_Data found in the global database!");
		FOUT;
	}
	else
	{
		//Previous data exists; alter it.
	
		lar_data = (LAR_Data*) data;
	
#ifdef LAR_DEBUG
		print_lar_data(lar_data);
#endif
		
		time = op_sim_time();
		velocity = aodv_geo_LAR_calc_velocity(lar_data->x, lar_data->y, x, y, lar_data->time, time);
		lar_data->x = x;
		lar_data->y = y;
		lar_data->velocity = (velocity < 0 ? -velocity : velocity);	//store only the magnitude of the velocity vector.
		lar_data->time = time;
	}

#ifdef LAR_DEBUG
	printf("\n==Coordinates at time %f for node with IP %s are (%f, %f)==\n",time, address, x, y);
	printf("\nCommitted ");
	print_lar_data(lar_data);
#endif

	//Schedule the next interrupt.
	op_intrpt_schedule_self (op_sim_time () + update_interval, AODVC_LAR_UPDATE);

#ifdef LAR_DEBUG
	printf("============================================================\n");
#endif
	
	FOUT;
}

// MKA 11/23/10
// Create and return a new LAR_Data data structure initialized with the given coordinates.
// and default velocity (0.0) and time (0.0).
LAR_Data* new_LAR_Data(double x, double y)
{
	LAR_Data *lar_data; 

#ifdef LAR_DEBUG
	printf("\n==Creating new LAR_Data with default values and position (%f, %f)==\n", x, y);
#endif
	
	lar_data = op_prg_mem_alloc( sizeof(LAR_Data) );
	lar_data->x = x;
	lar_data->y = y;
	lar_data->velocity = 0;
	lar_data->time = op_sim_time();
	return lar_data;
}

// MKA 12/02/10
// This function performs initializations for LAR, including inserting the initial
// LAR_Data entries for the global database.
void aodv_geo_LAR_init( IpT_Rte_Module_Data* module_data_ptr, InetT_Addr_Family address_mode, int x, int y )
{
	
	// MKA 11/28/10
	// The following variables are used to initialize
	// data for LAR updates.
	LAR_Data			*lar_data;
	int					num_interfaces;
	int					ifnum;
	char				address[INETC_ADDR_STR_LEN];
	
	FIN (aodv_geo_LAR_init( <args> ));
	
	aodv_addressing_mode = address_mode;
	
	// Store initial position
	// You want to store the following information:
	// 1. x, y coordinates
	// 2. time when they were recorded
	// 3. velocity
	
	// Use function oms_data_insert
	
	
	// MKA 11/28/10
	// Create the initial entry in the global databse which will be updated at each LAR interrupt.
	lar_data = new_LAR_Data(x, y);
	num_interfaces = inet_rte_num_interfaces_get (module_data_ptr);
	for (ifnum = 0; ifnum < num_interfaces; ifnum++)
	{
		//In case there are multiple interfaces at this node,
		//create an entry for each one referencing the same data
		//so that no matter which IP the data is pulled from, the data will
		//be the same.
		get_node_ip(address, module_data_ptr, ifnum);
		oms_data_def_entry_insert(LAR_OMS_CATEGORY, address, lar_data);
	}
	
	FOUT;
}

// MKA 12/02/10
// This method returns whether or not the current node is within the 
// request zone. The request zone will be as specified by LAR Scheme 1 (with Dan Urbano's alterations
// to take into account a source parallel to the destination).
Boolean aodv_geo_LAR_within_request_zone(double src_x, double src_y, double curr_x, double curr_y, double dest_x, double dest_y, double radius)
{
	Point2D ll, ul, ur, lr;
	Point2D currentLocation;
	
	Rectangle requestZone;
	
	Boolean contained;
	
	FIN (aodv_geo_LAR_within_request_zone( <args> ));
	
	currentLocation.x = curr_x;			currentLocation.y = curr_y;
	

	ll.x = min(src_x, dest_x - radius); ll.y = min(src_y, dest_y - radius);
	ul.x = ll.x; 						ul.y = max(src_y, dest_y + radius);
	ur.x = max(src_x, dest_x + radius); ur.y = ul.y;
	lr.x = ur.x;						lr.y = ll.y;
	
	requestZone.lower_left = ll;
	requestZone.upper_left = ul;
	requestZone.upper_right = ur;
	requestZone.lower_right = lr;
	
	contained = aodv_geo_LAR_is_point_contained(&currentLocation, &requestZone);
	
#ifdef LAR_DEBUG
	printf("=> aodv_geo_LAR_within_request_zone: Current node's coordinates: (%.2f, %.2f)\n", currentLocation.x, currentLocation.y);
	printf("=> aodv_geo_LAR_within_request_zone: Src: (%.2f, %.2f) Dest: (%.2f, %.2f) Dest velocity = %.2f\n", src_x, src_y, dest_x, dest_y, radius);
	printf("=> aodv_geo_LAR_within_request_zone: Calculated request zone: \n");
	printf("\t (%.2f, %.2f) \t	(%.2f, %.2f)\n", ul.x, ul.y, ur.x, ur.y);
	printf("\t (%.2f, %.2f) \t	(%.2f, %.2f)\n", ll.x, ll.y, lr.x, lr.y);
	printf("=> aodv_geo_LAR_within_request_zone: Contained = %s\n", contained == OPC_TRUE ? "True" : "False");
#endif
	
	FRET ( contained );	
}

// MKA 12/02/10
// Simple helper function that determines whether or not the given Point
// is within the bounds of the provided Rectangle.
Boolean aodv_geo_LAR_is_point_contained(Point2D *location, Rectangle *zone)
{
	FIN (aodv_geo_LAR_is_point_contained( <args> ));
	
	// assumes that all sides of the 
    // rectangle are parallel to their respective axes

    // left of rectangle
    if (location->x < zone->upper_left.x)
            FRET ( OPC_FALSE );
    
	// above the rectangle
    if (location->y > zone->upper_left.y)
            FRET ( OPC_FALSE );

    // right of the rectangle
    if (location->x > zone->upper_right.x)
            FRET ( OPC_FALSE );

    // below rectangle
    if (location->y < zone->lower_right.y)
            FRET ( OPC_FALSE );

    // Otherwise, it's in the rectangle.
	FRET (OPC_TRUE);
	
}

// MKA 12/02/10
// Retrieve LAR_Data from the global database using the given IP.
LAR_Data* aodv_geo_LAR_retrieve_data(char* ip)
{
	return (LAR_Data*) oms_data_def_entry_access(LAR_OMS_CATEGORY, ip);
}
