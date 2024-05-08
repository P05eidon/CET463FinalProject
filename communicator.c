// communicator.c 
#include "msp430.h"
//#include "serial.h"
//#include "ring_buffer8.h"
#include "communicator.h"

RingBuffer8b_TypeDef payload_data;

unsigned char consumer_state = 0;

void MessageReceiver( void )
{ 
    unsigned char local_checksum;
    unsigned char my_address = 0;
    unsigned char src_address = 0;
    unsigned char sourcebyte;
    unsigned char msgbyte;
    unsigned char data;

    switch(consumer_state)
    {
    case 0:     // SOM
        local_checksum = 0;
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          if(data == 0xE3)
          {
              local_checksum += data;
              consumer_state = 0x01;
          }
        }
        break;          
    case 1:    // Address check
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          if(data == my_address)
          {
              consumer_state = 0x02;
              local_checksum += data;
          }
        }
        else 
        {
            consumer_state = 0;
        }
        break;   
    case 2:    // check source or check first message, depending on if there is a source address being sent
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          ringbuffer8b_dequeue(&rx_data_rb);
          consumer_state = 0x03;
          local_checksum += data;
          sourcebyte = data;
        }
          else 
        {
            consumer_state = 0;
        }
        break;  
    case 3:    //check message if there is one at this point
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          consumer_state = 0x04;
          local_checksum += data;
          msgbyte = data;
        }
          else 
        {
            consumer_state = 0;
        }
        break;  
     case 4:    //extra bit
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          local_checksum += data;
          consumer_state = 0x05;
        }
          else 
        {
            consumer_state = 0;
        }
        break;   
    case 5:    //extra bit
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          consumer_state = 0x06;
          local_checksum += data;
        }
          else 
        {
            consumer_state = 0;
        }
        break;  
    case 6:    //extra bit
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          consumer_state = 0x07;
          local_checksum += data;
        }
          else 
        {
            consumer_state = 0;
        }
        break;  
     case 7:    //extra bit
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          consumer_state = 0x08;
          local_checksum += data;
        }
          else 
        {
            consumer_state = 0;
        }
        break;   
    case 8:    //extra bit
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          consumer_state = 0x09;
          local_checksum += data;
        }
          else 
        {
            consumer_state = 0;
        }
        break;  
    case 9:    //Check sum of bits
        if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
        {
          data = ringbuffer8b_dequeue(&rx_data_rb);
          if(data == local_checksum)
          {
              consumer_state = 0x0A;
          }
        }
          else 
        {
            consumer_state = 0;
        }
        break;  
    case 10: // EOM
      if(ringbuffer8b_isempty(&rx_data_rb) == FALSE)
      {
        data = ringbuffer8b_dequeue(&rx_data_rb);
        if(data == 0xE3)
        {
            determine_src(sourcebyte);
            determine_msg(msgbyte);
            consumer_state = 0;
            sourcebyte = 0;
            msgbyte = 0;
        }
      }
      break;
    }
}
