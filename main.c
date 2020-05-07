#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

 #  Computer Networking Simulator with Stack and Queue


int main(int argc, char *argv[]) {
			
	struct Client {                                          /* Creates a struct for each client. */
		char* ID;
		char* IP;
		char* MAC;
		char** routing_table_last_receiver;
		char** routing_table_transmitter_receiver;
		
	};
		
	int number_of_clients;
	char *temporary  = (char*)malloc(11*atoi(argv[4])*sizeof(char));         /* A character array for taking the inputfiles' strings. */
	
		
	FILE* client_data = fopen(argv[1],"r");
	FILE* routing_data = fopen(argv[2],"r");
	fscanf(client_data,"%d",&number_of_clients);
	
	struct Client client_array[number_of_clients];					/* Creates structs for each client. */

		
	int i = 0;
	
	while(fscanf(client_data,"%s",temporary)==1){				/* Takes data from the first and the second input files to store clients' */
										/* ID, IP, MAC and routing table elements. Then stores them in the structs. */
		
		client_array[i].ID = malloc(2);
		strcpy(client_array[i].ID, temporary);
		fscanf(client_data,"%s",temporary);
		client_array[i].IP = malloc(8);
		strcpy(client_array[i].IP, temporary);
		fscanf(client_data,"%s",temporary);
		client_array[i].MAC = malloc(11);
		strcpy(client_array[i].MAC, temporary);
		
			int a ;
			
			client_array[i].routing_table_last_receiver = malloc(number_of_clients*4*sizeof(char*));
			client_array[i].routing_table_transmitter_receiver = malloc(number_of_clients*4*sizeof(char*));
				for (a=0; a<number_of_clients;a++){
					client_array[i].routing_table_last_receiver[a] =  malloc(number_of_clients*4*sizeof(char));
					client_array[i].routing_table_transmitter_receiver[a] =  malloc(number_of_clients*4*sizeof(char));
				}
			
			
				for (a=0; a<(number_of_clients); a++) {
						
					if (fscanf(routing_data,"%s",temporary) != EOF){
					
					
						if(!strcmp(temporary, "-") ){
							a = number_of_clients ;
						}
						else {
						
						strcpy((client_array[i].routing_table_last_receiver)[a],temporary);

						fscanf(routing_data,"%s",temporary);
							if(!strcmp(temporary, "-") ){
								strcpy((client_array[i].routing_table_transmitter_receiver)[a],"d");
								a = number_of_clients ;
							}
							else{
						
								strcpy((client_array[i].routing_table_transmitter_receiver)[a],temporary);
							}
						}
					}
					else {
						a = number_of_clients ;	
					}		
				}	
		i++;
	}		/* The storing parts ends here. */
		
	FILE *command_data = fopen(argv[3],"r");
	
	
	fscanf(command_data, "%s", temporary);
	
	
	int counter = atoi (temporary);			/* How many commands contains the third data file. */

	
	
	
	
	fscanf(command_data,"%s\n", temporary);
	
	char* sender_ID = malloc(2);			/* Holds sender's and receiver's ID info. */
	char* receiver_ID = malloc(2);
		

	char** log_info [(number_of_clients*2)];			/* For the PRINT_LOG command and holding each client's information during the SEND command in recursive_send function. */ 
		int log_count,log_count1;
			for(log_count=0; log_count<(number_of_clients*2); log_count++){
				log_info [log_count]=malloc(6);
				for(log_count1=0; log_count1<6; log_count1++){
					log_info [log_count][log_count1]=malloc(81);
				}
			}

	int success = 0;		/* Keeps the success of the SEND command. */
	int sifir = 0;
	int* hops_ptr;			/* Number of Hops. */
	hops_ptr = &sifir;
	int send_cont = 0;		/* Is there a SEND command in the commands.dat. */
	i = 0;	



	/*-----------------------------------------------------------------------------------------------*/
	/* Beginning of reading the commands of the third file and starting the operations respectively. */
	/*-----------------------------------------------------------------------------------------------*/



	while(i<counter){
		

		if (!strcmp(temporary, "MESSAGE") ){         /* If MESSAGE command comes. */
			
			printf("---------------------------------------------------------------------------------------\nCommand: %s ",temporary);
			i++;
			fscanf(command_data, "%s",temporary);					
			strcpy(sender_ID , temporary);
			printf("%s ",sender_ID);
			
			fscanf(command_data, "%s",temporary);
			
			strcpy(receiver_ID, temporary);
			printf("%s ",receiver_ID);
			
			
			char c;
					
			
			c = getc(command_data);           /* For the first whitespace */
		
			char** message_chunk_array = malloc(sizeof(char**));

			int number_of_frames = 0;
			
			while (c != '\n'){                            /* Reads the message part and breaks it into frames until the end of MESSAGE command. */
				
				message_chunk_array[number_of_frames] = malloc(atoi(argv[4])*sizeof(char*));
				
				int t;
				for (t =0; t<atoi(argv[4]);t++){
					
					c = getc(command_data);
					printf("%c",c);
					if (c == '\n'){
						break;
					}

					
					else if (c=='#'){
						t--;
					}
					else{
					
						message_chunk_array[number_of_frames][t]=c;
			
				
					}	
					
   				}
   				
				number_of_frames++;		
			}					/* The process of breaking the message into frames ends here. */
			
			printf("---------------------------------------------------------------------------------------\n");
			int k1,k2,k3;
		
   			int current_client_for_sender,current_client_for_receiver,last_client_for_receiver;
   			for (k1=0;k1<number_of_clients;k1++){
   		
   				if (!strcmp(client_array[k1].ID,sender_ID)){
   					current_client_for_sender = k1;
   				} 
   						
			}
			int for_sender_last_receiver;
			for (k2=0;k2<number_of_clients;k2++){
								
   					if (!strcmp(((client_array[current_client_for_sender].routing_table_last_receiver)[k2]),receiver_ID)){
   									
   						for (k3=0;k3<number_of_clients;k3++){
   							if(!strcmp(((client_array[current_client_for_sender].routing_table_last_receiver)[k2]),client_array[k3].ID)){
   								for_sender_last_receiver = k2;
   								last_client_for_receiver = k3;	
   							}
						}   						
						for (k3=0;k3<number_of_clients;k3++){
   							if(!strcmp(((client_array[current_client_for_sender].routing_table_transmitter_receiver)[k2]),client_array[k3].ID)){
   								int for_sender_transmitter_receiver = k2;	
   								current_client_for_receiver = k3;						
							}
   						}
   				
					}					
		    }
			printf("Message to be sent: ");	   
			for (k1=0; k1<number_of_frames;k1++){
					printf("%s",message_chunk_array[k1]);
			}
			
		
		
		
			/* Prints the MESSAGE commands outputs.*/
			
			
			printf("\n\n");	   
			for (k3=0;k3<number_of_frames;k3++){
			   
			printf("Frame #%d\nSender MAC address:%s, Receiver MAC address:%s\nSender IP address: %s, Receiver IP address: %s\nSender port number: %s, Receiver port number: %s\nSender ID: %s, Receiver ID: %s\nMessage chunk carried: %s\n--------\n",
																															(k3+1),
																															client_array[current_client_for_sender].MAC,
																															client_array[current_client_for_receiver].MAC,
																															client_array[current_client_for_sender].IP,
																															client_array[last_client_for_receiver].IP,
																															argv[5],argv[6],																															
																															client_array[current_client_for_sender].ID,
																															client_array[last_client_for_receiver].ID,
																															message_chunk_array[k3]);  
				   
				   
			}		   
				   
			struct frame_stack_info{				/* Creates a struct with layers. */
				int top;
   				char*  physical_layer_sender_mac;
   				char*  physical_layer_receiver_mac;
   				char*  network_layer_sender_ip;
   				char*  network_layer_receiver_ip;
   				char*  transport_layer_sender_port;
   				char*  transport_layer_receiver_port;
   				char*  application_layer_sender_id;
   				char*  application_layer_receiver_id;
   				char*  application_layer_message_chunk;
   			
			   };
				   
			struct frame_stack_info frames[number_of_frames];
				
			char** stack_array[number_of_frames];                    /* Creates stack arrays for each frame.*/
			
				
				
			void push(int* top, char** stack_array, char* new_element){		/* Push function for stacks. */			
				if(*top==9){
					printf("Stack is full");
				}
				else{
					*top = *top + 1 ;
					strcpy(stack_array[*top], new_element);					
													
				}					
			}
				
			char* pop(int* top, char** stack_array){				/* Pop function for stacks. */
					
				if(*top==0){
					printf("Stack is empty");
				}
				else{
					
					return stack_array[(*top)--];							
				}				
			}
				
			char** queue_array[number_of_frames];               			/* Creates queues. */
				
			int front = -1;
			int rear = -1;	
				
			void insert(int* rear, char*** queue_array, char** stack_array){	/* Insert function for queues. */
						
				if(*rear == number_of_frames - 1){
					
					printf("Queue is full");
				}
				else{
					*rear = *rear + 1;
					int k;
					for (k = 0; k<9; k++){			
						strcpy(queue_array[*rear][k], stack_array[k]);
						
					}			
									
												
				}					
			}
				
			char** remove(int* front, char*** queue_array){			/* Insert function for queues.*/
					*front = *front +1;
					return queue_array[*front];				
			}	
					



			/*-------------------------------------------------------------/	
 			/ Assigns the contents of the stacks(frames), then the queues./
			/------------------------------------------------------------*/



			int x;																
			for (x=0; x<number_of_frames; x++ ){              
						
				frames[x].physical_layer_sender_mac = malloc(strlen(client_array[current_client_for_sender].MAC)*sizeof(char));
				frames[x].physical_layer_receiver_mac = malloc(strlen(client_array[current_client_for_receiver].MAC)*sizeof(char)); 				
   				frames[x].network_layer_sender_ip = malloc(strlen(client_array[current_client_for_sender].IP)*sizeof(char));
   				frames[x].network_layer_receiver_ip = malloc(strlen(client_array[last_client_for_receiver].IP)*sizeof(char));
   		    		frames[x].transport_layer_sender_port = malloc(strlen(argv[5])*sizeof(char));		    
   				frames[x].transport_layer_receiver_port = malloc(strlen(argv[6])*sizeof(char));
   				frames[x].application_layer_sender_id = malloc(strlen(client_array[current_client_for_sender].ID)*sizeof(char));				
   				frames[x].application_layer_receiver_id = malloc(strlen(client_array[last_client_for_receiver].ID)*sizeof(char)); 					
   				frames[x].application_layer_message_chunk = malloc(strlen(message_chunk_array[x]));
   				
   				frames[x].physical_layer_sender_mac = client_array[current_client_for_sender].MAC;
   				frames[x].physical_layer_receiver_mac = client_array[current_client_for_receiver].MAC;
   				frames[x].network_layer_sender_ip = client_array[current_client_for_sender].IP;
   				frames[x].network_layer_receiver_ip = client_array[last_client_for_receiver].IP;
   				frames[x].transport_layer_sender_port = argv[5];
   				frames[x].transport_layer_receiver_port = argv[6];
   				frames[x].application_layer_sender_id = client_array[current_client_for_sender].ID;
   				frames[x].application_layer_receiver_id = client_array[last_client_for_receiver].ID;
   				frames[x].application_layer_message_chunk = message_chunk_array[x];
   				frames[x].top=-1;
   					
   				stack_array[x] = malloc(9*sizeof(char*));
   				queue_array[x] = malloc(9*sizeof(char*));
   					
   				int y;
				
				for(y=0;y<9;y++){
					
					stack_array[x][y] = malloc(atoi(argv[4])*11*sizeof(char));
					queue_array[x][y] = malloc(atoi(argv[4])*11*sizeof(char));
				}
									
   				push(&frames[x].top,stack_array[x],frames[x].application_layer_message_chunk);			
				push(&frames[x].top,stack_array[x],frames[x].application_layer_receiver_id);	
				push(&frames[x].top,stack_array[x],frames[x].application_layer_sender_id);			
				push(&frames[x].top,stack_array[x],frames[x].transport_layer_receiver_port);
				push(&frames[x].top,stack_array[x],frames[x].transport_layer_sender_port);			
				push(&frames[x].top,stack_array[x],frames[x].network_layer_receiver_ip);
				push(&frames[x].top,stack_array[x],frames[x].network_layer_sender_ip);			
				push(&frames[x].top,stack_array[x],frames[x].physical_layer_receiver_mac);
				push(&frames[x].top,stack_array[x],frames[x].physical_layer_sender_mac);	
				
				insert(&rear,queue_array,stack_array[x]);											
			}
				
			
			
			fscanf(command_data, "%s",temporary);
			
			while(strcmp(temporary, "MESSAGE") && feof(command_data)==0 && i<counter){   /* If the next command is not MESSAGE and not the end of the file and not exceeds the counter value. */
						

			
			if (!strcmp(temporary, "SHOW_Q_INFO") && i<counter){     /* For SHOW_FRAME_INFO command after the SEND command.*/
			
				i++;
				printf("---------------------------\nCommand: %s ",temporary);
				fscanf(command_data, "%s",temporary);
				printf("%s ",temporary);
				char* input = malloc(2);
				strcpy(input, temporary);				
				fscanf(command_data, "%s",temporary);
				printf("%s",temporary);
				printf("\n---------------------------\n");
					if(!strcmp(temporary,"out") && !strcmp(input, sender_ID) ){        	/* If the command contains "out" and the argument is sender client's ID.*/
						printf("Client %s Outgoing Queue Status\nCurrent total number of frames: %d\n",input,number_of_frames);
					}
					else if (!strcmp(temporary,"in") && !strcmp(input, receiver_ID) && success == 1){	/* If the command contains "in" and the argument is receiver client's ID.*/

						printf("Client %s Incoming Queue Status\nCurrent total number of frames: %d\n",input,number_of_frames);
					}
					else if(!strcmp(temporary,"in")){					/* If the command contains "in" and the argument is not receiver client's ID.*/

						printf("Client %s Incoming Queue Status\nCurrent total number of frames: 0\n",input);
					}
					else if(!strcmp(temporary,"out")){					/* If the command contains "out" and the argument is not sender client's ID.*/

						printf("Client %s Outgoing Queue Status\nCurrent total number of frames: 0\n",input);
					}
					else{
						printf("Unexpected parameters for SHOW_Q_INFO command");
					}
				fscanf(command_data, "%s",temporary);	
				free ( input);	
			}
		
					
		
			if (!strcmp(temporary, "SEND") && i<counter){		/* For SEND command after the MESSAGE command. */
				
				
				send_cont = 1;
				i++;
				
				printf("----------------\nCommand: %s ",temporary);
				
				fscanf(command_data, "%s",temporary);
				
				printf("%s",temporary);
				printf("\n----------------\n");
				
				
				char* last_sender_mac = malloc(11);	
		
			
				int recursive_send(int front, int rear, int top, int sender_number, int receiver_number,int* hops, char*** queue_array,char* last_sender_mac,char*** log_info,int* success){
						
						
						/* Holds the PRINT_LOG commands elements for each client in the route. */
						
						
						sprintf(log_info[sender_number+number_of_clients][0], "%d", *hops);
						sprintf(log_info[sender_number][0], "%d", *hops);		 			
			 			strcpy(log_info[sender_number+number_of_clients][1],sender_ID);
			 			strcpy(log_info[sender_number][1],sender_ID);
			 			strcpy(log_info[sender_number+number_of_clients][2],receiver_ID);
			 			strcpy(log_info[sender_number][2],receiver_ID);
			 						 		
			 			/* For the Timestamp information.*/
			 			
			 			time_t now;
    					struct tm ts;
    					char buf[80];
   						time(&now);			
 						ts = *localtime(&now);
 						strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S ", &ts);
	 					 				 			
			 			strcpy(log_info[sender_number][3],buf);	 			
						strcpy(log_info[sender_number+number_of_clients][3],buf);
						*success = 1;			
			 		
				
					if ( (*hops)>0){
						printf("A message received by client %s, but intended for client %s. Forwarding...\n",client_array[sender_number].ID,client_array[receiver_number].ID);
												
					}				
								
					if(!strcmp((client_array[sender_number].routing_table_last_receiver)[for_sender_last_receiver],client_array[receiver_number].ID)){
					
			
						
						int cntr,cntr1;
						int current_client_number;
						int last_client_number;
						
						for (cntr=0; cntr<number_of_clients; cntr++){
							
							
								
   							if (!strcmp(((client_array[sender_number].routing_table_last_receiver)[cntr]),client_array[receiver_number].ID)){
   									
   								for (cntr1=0;cntr1<number_of_clients;cntr1++){
   									if(!strcmp(((client_array[sender_number].routing_table_last_receiver)[cntr]),client_array[cntr1].ID)){
   										last_client_number = cntr1;	
   										
   									}
								}   						
								for (cntr1=0;cntr1<number_of_clients;cntr1++){				
												
									if(!strcmp(((client_array[sender_number].routing_table_transmitter_receiver)[cntr]),"d")){ 				/* If the SEND command fails.*/
										printf("Error: Unreachable destination. Packets are dropped after %d hops!\n",*hops);
										
										sprintf(log_info[sender_number+number_of_clients][5], "%d", *hops);

										*success = 0;		
											
										return 0;
									}
   									else if(!strcmp(((client_array[sender_number].routing_table_transmitter_receiver)[cntr]),client_array[cntr1].ID)){
   						
   										current_client_number = cntr1;						
									}
   								}
   						
							}					
			 		    }
			 		   
			 		    *hops = *hops + 1;						
			 		    
			 		    
			 		    /* Sends the outgoing queue to the new client's incoming queue.*/
			 		    
			 		  	char** new_receiver_queue_array[number_of_frames];
			 		   			 		   
			 		   	
			 		  	int b;
			 		  	int new_rear = -1;
			 			int new_front = -1;
			 		   	for (b=0; b<number_of_frames; b++ ){	
			 		   		top = 8;
			 		   		   		
   							new_receiver_queue_array[b] = malloc(9*sizeof(char*));
   					
   							int b1;
				
							for(b1=0;b1<9;b1++){
											
								new_receiver_queue_array[b][b1] = malloc(atoi(argv[4])*11*sizeof(char));
								
							}							
				
							insert(&new_rear,new_receiver_queue_array,remove(&front,queue_array));	
						
							
						
							pop(&top,new_receiver_queue_array[b]);
							pop(&top,new_receiver_queue_array[b]);			
							push(&top,new_receiver_queue_array[b],client_array[current_client_number].MAC);
							push(&top,new_receiver_queue_array[b],client_array[sender_number].MAC);
												
			 		
							if((*hops)>1){
														
								printf("Frame #%d MAC address change: New sender MAC %s, new receiver MAC %s\n",b+1,client_array[sender_number].MAC,client_array[current_client_number].MAC);
							}
						
			 			}
			 					 			
			 			
			 		    if(current_client_number == last_client_number){
							printf("A message received by client %s from client %s after a total of %d hops.\n",client_array[receiver_number].ID,client_array[current_client_for_sender].ID,*hops);
							strcpy(last_sender_mac,new_receiver_queue_array[0][8]);
							*success = 1;
							sprintf(log_info[current_client_number+number_of_clients][0], "%d", *hops);
							sprintf(log_info[current_client_number][0], "%d", *hops);	
							strcpy(log_info[current_client_number+number_of_clients][1],sender_ID);
			 				strcpy(log_info[current_client_number][1],sender_ID);
							return 0;
						}
			 		   recursive_send(new_front, new_rear, top, current_client_number, last_client_number,hops, new_receiver_queue_array, last_sender_mac, log_info,success);	/* Calls the recursive_send function .*/
			 		   
					}
					
					else{
						printf("else drop\n");
					}
				}
				
				if(!strcmp(client_array[current_client_for_sender].ID,temporary)){  
				
					recursive_send(front, rear, frames[0].top, current_client_for_sender,last_client_for_receiver,hops_ptr,queue_array, last_sender_mac, log_info,&success);
				}
				else{
					printf("%s hasn't outgiong queue\n",temporary);
				}	
				strcpy(queue_array[number_of_frames-1][8],last_sender_mac);	
				fscanf(command_data, "%s",temporary);
				
				
				free(last_sender_mac);
				
			}																/*End of the SEND command.*/
	
	
			/* SHOW_FRAME_INFO command after MESSAGE command.*/
	
	
			if (!strcmp(temporary, "SHOW_FRAME_INFO") && i<counter){			
			
				
				printf("---------------------------------\nCommand: %s ",temporary);
				i++;
				fscanf(command_data, "%s",temporary);
				if (!strcmp(sender_ID,temporary)){
					printf("%s ",temporary);
					fscanf(command_data, "%s",temporary);
					if (!strcmp(temporary,"out")){
						printf("%s ",temporary);				
						fscanf(command_data, "%s",temporary);
						printf("%s ",temporary);
						printf("\n---------------------------------\n");
						printf("Current Frame #%s on the outgoing queue of client %s\nCarried Message: \"%s\"\n",temporary,sender_ID,queue_array[atoi(temporary)-1][0]);
						printf("Layer 0 info: Sender ID: %s, Receiver ID: %s\nLayer 1 info: Sender port number: %s, Receiver port number: %s\nLayer 2 info: Sender IP address: %s, Receiver IP address: 0.0.1.1\n",client_array[current_client_for_sender].ID,client_array[last_client_for_receiver].ID, argv[5], argv[6],client_array[current_client_for_sender].IP,client_array[last_client_for_receiver].IP);
						printf("Layer 3 info: Sender MAC address: %s, Receiver MAC address: %s\nNumber of hops so far: 0\n",queue_array[atoi(temporary)-1][8],queue_array[atoi(temporary)-1][7]);
					}
					else if (!strcmp(temporary,"in")){
						printf("%s ",temporary);
						fscanf(command_data, "%s",temporary);
					
						printf("%s \n---------------------------------\n",temporary);
						printf("No Such Frame\n");
					}
				}
			
				else if (!strcmp(receiver_ID,temporary) && send_cont == 1){			/* If SEND command was called.*/
					printf("%s ",temporary);
					fscanf(command_data, "%s",temporary);
					if (!strcmp(temporary,"out")){						/* There is no queue at the receiver's outgoing queue.*/
						printf("%s ",temporary);
						fscanf(command_data, "%s",temporary);
						printf("%s ",temporary);
						printf("\n---------------------------------\n");
						printf("No Such Frame\n");	
					}
					else if (!strcmp(temporary,"in")&& success == 1 ){		/* If the SEND command is successfully done.*/
						printf("%s ",temporary);
						fscanf(command_data, "%s",temporary);
						printf("%s ",temporary);
						printf("\n---------------------------------\n");
						printf("Current Frame #%s on the incoming queue of client %s\nCarried Message: \"%s\"\n",temporary,receiver_ID,queue_array[atoi(temporary)-1][0]);
						printf("Layer 0 info: Sender ID: %s, Receiver ID: %s\nLayer 1 info: Sender port number: %s, Receiver port number: %s\nLayer 2 info: Sender IP address: %s, Receiver IP address: %s\n",
											client_array[current_client_for_sender].ID,client_array[last_client_for_receiver].ID, argv[5], argv[6],client_array[current_client_for_sender].IP,client_array[last_client_for_receiver].IP);
						printf("Layer 3 info: Sender MAC address: %s, Receiver MAC address: %s\nNumber of hops so far: %d\n",queue_array[number_of_frames-1][8],client_array[last_client_for_receiver].MAC,*hops_ptr);
						
					
					}
					else if (!strcmp(temporary,"in")&& success == 0){		/* If SEND command is called but its not succesful.*/
						printf("%s ",temporary);
						fscanf(command_data, "%s",temporary);
					
						printf("%s \n---------------------------------\n",temporary);
						printf("No Such Frame\n");
					
					}
				}
				
				else {
					printf("%s ",temporary);
					fscanf(command_data, "%s",temporary);
					printf("%s ",temporary);
					fscanf(command_data, "%s",temporary);
					printf("%s ",temporary);
					printf("\n---------------------------------\n");
					printf("No Such Frame\n");
				}
			
		
			fscanf(command_data, "%s",temporary);
			
			}						/* End of SHOW_FFRAME_INFO command.*/
			
			
					
			if (!strcmp(temporary, "PRINT_LOG") && i<counter && send_cont == 1){
				i++;
				
									
				printf("---------------------\nCommand: %s",temporary);
				fscanf(command_data, "%s",temporary);
				
				int search0;
				int client;
				for(search0=0; search0<number_of_clients; search0++){
					if(!strcmp(client_array[search0].ID,temporary)){
						client = search0;
					}
				}	
				if (!strcmp(client_array[client].ID,sender_ID)){
					printf(" %s\n---------------------\nClient %s Logs: \n--------------\n",temporary,temporary);
					printf("Log Entry #1:\nMessage: ");
					int k;
					for(k=0;k<number_of_frames;k++){
						printf("%s",message_chunk_array[k]);
					}
					printf("\nTimestamp: %s\nNumber of frames: %d\nNumber of hops: %s\nSender ID: %s\nReceiver ID: %s\nActivity: Message Forward\nSuccess: Yes\n--------------\n",log_info[client][3],number_of_frames,log_info[client][0],log_info[client][1],log_info[client][2]);
				
				}	
				
				else if(!strcmp(log_info[client][1],sender_ID)){
			
					
					printf(" %s\n---------------------\nClient %s Logs: \n--------------\n",temporary,temporary);
					printf("Log Entry #1:\nMessage: ");
					int k;
					for(k=0;k<number_of_frames;k++){
						printf("%s",message_chunk_array[k]);
					}
					printf("\nTimestamp: %s\nNumber of frames: %d\nNumber of hops: %s\nSender ID: %s\nReceiver ID: %s\nActivity: Message Received\nSuccess: Yes\n--------------\n",log_info[client][3],number_of_frames,log_info[client][0],log_info[client][1],log_info[client][2]);
				
					if(!strcmp(client_array[client].ID,receiver_ID)){
			    		
					}
					

					else if(success == 0 && !strcmp(log_info[client+number_of_clients][5],log_info[client+number_of_clients][0])){
						printf("Log Entry #2:\nMessage: ");
						for(k=0;k<number_of_frames;k++){
							printf("%s",message_chunk_array[k]);
						}
						printf("\nTimestamp: %s\nNumber of frames: %d\nNumber of hops: %s\nSender ID: %s\nReceiver ID: %s\nActivity: Message Forwarded\nSuccess: No\n",log_info[client+number_of_clients][3],number_of_frames,log_info[client+number_of_clients][0],log_info[client+number_of_clients][1],log_info[client+number_of_clients][2]);
					}
					else{
						printf("Log Entry #2:\nMessage: ");
						for(k=0;k<number_of_frames;k++){
							printf("%s",message_chunk_array[k]);
						}
						printf("\nTimestamp: %s\nNumber of frames: %d\nNumber of hops: %s\nSender ID: %s\nReceiver ID: %s\nActivity: Message Forwarded\nSuccess: Yes\n",log_info[client+number_of_clients][3],number_of_frames,log_info[client+number_of_clients][0],log_info[client+number_of_clients][1],log_info[client+number_of_clients][2]);

					}
    			}
				else
				
					printf(" %s\n---------------------\n",temporary);			
			
				fscanf(command_data, "%s",temporary);
	
			}
			else if (!strcmp(temporary, "PRINT_LOG") && i<counter){
				
				printf("---------------------\nCommand: %s ",temporary);
				fscanf(command_data, "%s",temporary);
				printf(" %s\n---------------------\n",temporary);
				i++;				
						
			
				fscanf(command_data, "%s",temporary);
			}
		
			if (strcmp(temporary, "MESSAGE") && strcmp(temporary, "SHOW_FRAME_INFO") && strcmp(temporary, "SHOW_Q_INFO") && strcmp(temporary, "SEND") && strcmp(temporary, "PRINT_LOG") && i<counter) { 
				i++;		
				printf("---------------------\nCommand: %s ",temporary);
				fscanf(command_data, "%s",temporary);
				int controller = -1;
				while (controller < 0){
			
					if (!strcmp(temporary, "MESSAGE") || !strcmp(temporary, "SHOW_FRAME_INFO") || !strcmp(temporary, "SHOW_Q_INFO") || !strcmp(temporary, "SEND") || !strcmp(temporary, "PRINT_LOG") ){
						controller++;
						
					}
		
					else{	
						printf("%s",temporary);
						char l;		
						l = getc(command_data);		
						while (l != '\n' && feof(command_data)==0 ){
							printf("%c",l);
							l = getc(command_data);
							
							
						}
						controller++;
					}
				}
				printf("\n---------------------");
				printf("\nInvalid command.\n");	
				fscanf(command_data, "%s",temporary);		
				
			}

			
			}	/* while loop in "MESSAGE" command, ends here. */
		
			int free1;
			for(free1=0; free1<number_of_frames;free1++){
				free(stack_array[free1]);
				free(queue_array[free1]);
				
			}
		
						
		}	/* If "MESSAGE" command comes first. Ends here*/
		
		if (!strcmp(temporary, "SHOW_FRAME_INFO") && i<counter){
			
			
			printf("---------------------------------\nCommand: %s ",temporary);
			i++;
			fscanf(command_data, "%s",temporary);
			printf("%s ",temporary);
			if (!strcmp(sender_ID,temporary)){	
				fscanf(command_data, "%s",temporary);
				if (!strcmp(temporary,"out")){
					printf("%s ",temporary);
					fscanf(command_data, "%s",temporary);
					printf("%s ",temporary);
					printf("\n---------------------------------\n");
					printf("No Such Frame\n");
				}
				else if (!strcmp(temporary,"in")){
					fscanf(command_data, "%s",temporary);
					
					printf("%s \n---------------------------------\n",temporary);
					printf("No Such Frame\n");
				}
			}
			
			else if (!strcmp(receiver_ID,temporary)){
				printf("receiver id in show frame info = %s\n",temporary);
				fscanf(command_data, "%s",temporary);
				if (!strcmp(temporary,"out")){
					fscanf(command_data, "%s",temporary);
					printf("\n---------------------------------\n");
					printf("No Such Frame\n");	
				}
				else if (!strcmp(temporary,"in")){
					fscanf(command_data, "%s",temporary);
					printf("\n---------------------------------\n");
					printf("No Such Frame\n");		
				}
			}
			
			else {
				fscanf(command_data, "%s",temporary);
				printf("%s",temporary);
				fscanf(command_data, "%s",temporary);
				printf(" %s",temporary);
				printf("\n---------------------------------\n");
				printf("No Such Frame\n");
			}
			
		
			fscanf(command_data, "%s",temporary);
		}
		
		if (!strcmp(temporary, "SHOW_Q_INFO") && i<counter){
			
			i++;
			printf("---------------------------\nCommand: %s ",temporary);
			fscanf(command_data, "%s",temporary);
			printf("%s ",temporary);
			char* input = malloc(2);
			strcpy(input, temporary);
			fscanf(command_data, "%s",temporary);
			printf("%s",temporary);
			printf("\n---------------------------\n");
			if(!strcmp(temporary,"in")){
					printf("Client %s Incoming Queue Status\nCurrent total number of frames: 0\n",input);
					}
					else if(!strcmp(temporary,"out")){
						printf("Client %s Outgoing Queue Status\nCurrent total number of frames: 0\n",input);
					}
					else{
						printf("Unexpected parameters for SHOW_Q_INFO command");
					}
			fscanf(command_data, "%s",temporary);
			free(input);
			
		}
		
		if (!strcmp(temporary, "SEND") && i<counter){
			i++;
			printf("----------------\nCommand: %s ",temporary);
			fscanf(command_data, "%s",temporary);
			printf("%s",temporary);
			printf("\n----------------\n");
			printf("%s hasn't outgiong queue\n",temporary);
			fscanf(command_data, "%s",temporary);
			
		}
		
		if (!strcmp(temporary, "PRINT_LOG") && i<counter){
			i++;
			printf("---------------------\nCommand: %s",temporary);
			fscanf(command_data, "%s",temporary);
			printf(" %s\n---------------------\n",temporary);
			fscanf(command_data, "%s",temporary);
	
		}
		
		
		if (strcmp(temporary, "MESSAGE") && strcmp(temporary, "SHOW_FRAME_INFO") && strcmp(temporary, "SHOW_Q_INFO") && strcmp(temporary, "SEND") && strcmp(temporary, "PRINT_LOG") && i<counter) { 
			i++;		
			printf("---------------------\nCommand: %s ",temporary);
			fscanf(command_data, "%s",temporary);
			
			int controller = -1;
			while (controller < 0){
			
				if (!strcmp(temporary, "MESSAGE") || !strcmp(temporary, "SHOW_FRAME_INFO") || !strcmp(temporary, "SHOW_Q_INFO") || !strcmp(temporary, "SEND") || !strcmp(temporary, "PRINT_LOG") ){
					controller++;
					
				}		
				else{	
						printf("%s",temporary);
						char l;		
						l = getc(command_data);		
						while (l != '\n' && feof(command_data)==0 ){
							printf("%c",l);
							l = getc(command_data);
							
							
						}
						controller++;
					}
			}
			printf("\n---------------------");
			printf("\nInvalid command.\n");
			fscanf(command_data, "%s",temporary);

		}
			
	}
	fclose(client_data);
	fclose(routing_data);
	fclose(command_data);
	free (temporary);		# free allocated spaces 
	free(sender_ID);
	free(receiver_ID);
	return 0;
}


