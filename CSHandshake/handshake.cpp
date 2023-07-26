#include "handshake.h"

/*Device identification
  send_device_id: 
  Params to receive > device address
  it establishes the slaves' addresses
  check_device_address:
  Params to receive >  received_info, my_address
  Each byte begins and ends with a start and stop bit,
  following the UART standard. When the address bit is set to one by any of the nodes,
  it causes an interrupt in the other nodes on the bus. Each node then checks if the
  address matches its own. If it is not addressed, the node can ignore subsequent
  bytes (address bits being zero).
*/
int send_device_id(int device_address){

}

bool check_device_address(int received_info, int my_address){
  
}

