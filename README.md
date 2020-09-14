# Simplified-Computer-Networking-Protocol

**_A simple version of network communication between peers within
a network; that is, to implement a highly simplified computer networking protocol family
similar to the Internet protocol suite._**

The network protocol stack will consist of four layers each of which will have a different
purpose as shown in the Table below:

![Untitled](https://user-images.githubusercontent.com/32525636/61930796-8c409800-af87-11e9-8ed2-ff47c29a7b17.png)

The network has a peer-to-pear model. An example network topology is shown in the
figure below:

![2](https://user-images.githubusercontent.com/32525636/61930803-8fd41f00-af87-11e9-9fd2-7cbd8a8cd6fe.png)

The objective is to enable the peers (we’ll refer to them as clients) to communicate to each
other by exchanging messages while abiding by a set of protocols.


### Frames as Stacks:

Before data packets that carry message fragments can be sent, they will have to be encapsulated 
into Data Link/Physical layer frames which must be implemented as stacks of
information related to each network layer (e.g. message fragment with sender and receiver
IDs for the application layer, the sender and receiver’s IP addresses for network layer, port
numbers for transport layer, physical MAC addresses for the physical layer, etc.) as defined
by the network protocol stack. A frame structure is shown in the figure below.


![3](https://user-images.githubusercontent.com/32525636/61930918-e4779a00-af87-11e9-867e-8b5cd3bb4ae0.png)


### Outgoing and Incoming Queues:

Each client will have send and receive buffers (that must be implemented as queues) for
outgoing and incoming messages respectively (see the illustration below). We may assume
that the buffer size is infinite; i.e. no packets should ever be dropped because there is not
enough space on a queue; rather, the queue will expand as much as necessary to accommodate
any frames that need to be placed. We need to dynamically allocate and manage (reallocate
or free) memory used by all queues as necessary.

![4](https://user-images.githubusercontent.com/32525636/61930807-95ca0000-af87-11e9-8ea6-3117800a9642.png)


The figure above illustrates an example communication between a client A and a client B in
which A is messaging B. The message is first encapsulated in frames each of which carries a
message fragment (when the message size exceeds the maximum allowable message length,
one message will be sent in multiple frames). As a frame leaves the sender’s outgoing queue, it
is inserted onto the receiver’s incoming queue. Frames must follow the FIFO method (the first
message chunk will be sent in the first frame and received in the first frame on the receiver’s
side).


### Routing:

When a client receives message frames in its incoming queue, it must check who the intended
receiver is. If the frame is addressed to the receiving client, it can proceed to unpack the
message chunks as soon as the last message fragment has arrived, and pass them to the
application layer based on the port number of its listening socket in order to reassemble
the message. However, if the message is intended for someone else, the client must check its
routing table to determine the next hop that the frames should take to their destination.
Routing tables of each client will have the following format:


![5](https://user-images.githubusercontent.com/32525636/61930811-982c5a00-af87-11e9-9e29-0b5be15cf7b7.png)



Intended Destination Neighbor to which the packet should be forwarded
Routing tables will have multiple rows, one for each client in the network. For instance, the
entry | A | B | means that if a client needs to reach A, it should send the frame to B.
A routing example is illustrated in the figure below. In this scenario, client A is trying to send
a message client D. The message is longer than the maximum allowed message length, so it is
fragmented into four frames. A checks its routing table entry for D. Since A does not have a
direct link to D, the routing table specifies which client is on a path that can eventually reach
D, and if such client exists (in this case it is client B), A sends its message to that client for
forwarding. If the information about the next hop is missing for some reason, the message
will be dropped. When B receives the message intended for D, B must check its routing table
to determine the next destination for the message frames. In this case, D is a direct neighbor
of B (evident from B’s routing table entry), so B forwards the message to D.
Frames may have to make multiple hops over the network before they reach they final destination. The information about the total number of hops will also need to be saved in the
logs.

### Logs:

Every network activity must be logged. Thus, each client will have its own log which will
store the information about the sent, received, and forwarded messages. Each log entry should
store the following information:

• Timestamp: the date and time of the activity,

• Message that was carried in the frames,

• Total number of frames that carried the whole message,

• Total number of hops that frames have made so far through the network,

• Sender ID,

• Receiver ID,

• Activity type (message sent, received or forwarded),

• Activity success status (successful or failed).

![6](https://user-images.githubusercontent.com/32525636/61930817-9b274a80-af87-11e9-87b1-c1d1b2ea71bf.png)

