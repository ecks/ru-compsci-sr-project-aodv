#include <aodv_geo_table_test.h>
#include <aodv_geo_table.h>

InetT_Address* generate_random_InetT_Address()
{
   InetT_Address *inetT_address = malloc(sizeof(InetT_Address));
   //only test IPv4 
   //TODO Not sure what to set this too
   inetT_address->addr_family = 0;
   inetT_address->address.ipv4_addr = rand();

   return inetT_address;
}

void aodv_geo_table_test ()
{
    //create aodv_geo_table and call the proper tests with it
	AodvT_Geo_Table* table;// = aodv_geo_table_create(InetC_Addr_Family_v4);
	//aodv_geo_table_entry_exists_test(table);
	table = aodv_geo_table_create(InetC_Addr_Family_v4);
	aodv_geo_table_update_test(table);
}

void aodv_geo_table_entry_exists_test(AodvT_Geo_Table* geo_table_ptr)
{
    int i;
    InetT_Address_Helper *inett_address_helper;
	
	inett_address_helper = malloc(sizeof(InetT_Address_Helper));

    // first test to ensure that it can find entries
    // that do exist
    for (i = 0; i < _ENTRY_EXISTS_TESTS; i++)
    {
        inett_address_helper->inett_address = generate_random_InetT_Address();
		inett_address_helper->x = rand();
		inett_address_helper->y = rand();
        printf("Adding IPv4 addr %d (%u)", i, inett_address_helper->inett_address->address.ipv4_addr);
        aodv_geo_table_insert(geo_table_ptr, *inett_address_helper->inett_address, inett_address_helper->x, inett_address_helper->y);
        //should always return true
        if (aodv_geo_table_entry_exists(geo_table_ptr, *inett_address_helper->inett_address))
        {
            printf("Entry does exist test (%d) passed!\n", i);
        }
        else
        {
            printf("Entry does exist test (%d) failed!\n", i);
        }
    }

    // here we are unsure of the outcome.
    for (i = 0; i < _ENTRY_EXISTS_TESTS; i++)
    {
        inett_address_helper->inett_address = generate_random_InetT_Address();
		
        if (aodv_geo_table_entry_exists(geo_table_ptr, *inett_address_helper->inett_address))
        {
            printf("The table does contain %u\n", inett_address_helper->inett_address->address.ipv4_addr);
        }
        else
        {
            printf("The table doesn't contain %u\n", inett_address_helper->inett_address->address.ipv4_addr);
        }
    }
}


void aodv_geo_table_update_test(AodvT_Geo_Table* geo_table_ptr)
{
	int i, j;
	InetT_Address_Helper	*inett_address_helper[_UPDATE_TESTS]; 
	AodvT_Geo_Entry 		*tmp_entry;
	char					ip_address[INETC_ADDR_STR_LEN];
//	InetT_Address_Helper *inett_address_helper;
	
	printf("\n\nStarting update tests\n\n");
	
	*inett_address_helper = malloc(_UPDATE_TESTS * sizeof(InetT_Address_Helper));
	
	for (i = 0; i < _UPDATE_TESTS; i++)
	{
		//inett_address_helper = inett_address_helpers[i];
		inett_address_helper[i]->inett_address = generate_random_InetT_Address();
		inett_address_helper[i]->x = rand();
		inett_address_helper[i]->y = rand();
		aodv_geo_table_insert(geo_table_ptr, *inett_address_helper[i]->inett_address, inett_address_helper[i]->x, inett_address_helper[i]->y);
		inet_address_print (ip_address, *inett_address_helper[i]->inett_address);	
		printf("Added %s with coordinate (%f, %f)\n", ip_address, inett_address_helper[i]->x, inett_address_helper[i]->y);
	}
	
	printf("\n\nFinished populating list, now running tests...\n\n");	
	
	for (i = 0; i < _UPDATE_TESTS; i++) 
	{
		for (j = rand() % 32; j > 0; j--)
		{
			// update the current ip address a random amount of times with random new x and y coordinates.
			inett_address_helper[i]->x = rand();
			inett_address_helper[i]->y = rand();
			//aodv_geo_table_update (AodvT_Geo_Table* geo_table_ptr, InetT_Address address,	double x, double y);
			aodv_geo_table_update (geo_table_ptr, *inett_address_helper[i]->inett_address, inett_address_helper[i]->x, inett_address_helper[i]->y);
			// now that we have made our update, we want to retrieve the the x and y coordinates that the table has
			
			
			//AodvT_Geo_Entry* aodv_geo_table_entry_get (AodvT_Geo_Table* geo_table_ptr, InetT_Address dst_address, Boolean remove)
			tmp_entry = aodv_geo_table_entry_get (geo_table_ptr, *inett_address_helper[i]->inett_address, OPC_FALSE);
			if (tmp_entry->dst_x == inett_address_helper[i]->x && tmp_entry->dst_y == inett_address_helper[i]->y)
			{
				printf("Test Passed!: ");
			}
			else
			{
				printf("Test failed!: ");
			}
			
			printf("was (%f, %f) is (%f, %f)\n", inett_address_helper[i]->x, inett_address_helper[i]->y, tmp_entry->dst_x, tmp_entry->dst_y);
				
		}
	}	
}
