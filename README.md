Implement a simulator for page replacement algorithms, FIFO anf LRU. 

There are four arguments:
 - the size of virtual memory, in pages (name: virt)
 - the number of available "physical" page frames (name: phy)
 - the algorithm to simulate (name: alg)
 - a starting state of memory (name: state)

Simulator is named 'memsim' (source code "memsim.c" is attached
in the directory.) The output and invocation are in the following tyle:

$./memsim --virt 100 --phy 10 --alg FIFO --state COLD
page faults: 90068


Technical Details:
(1) Using the getopt_long(3) to parse the command line.

(2) Using atoi() and strdup() to get the values of optarg respectively
    and sotred them respectively in variables: "pageSize", "frameCount"
    and "alg". 

(3) Using random(3) to issue a random sequence of "memory references"
    to the set of virtual pages. (Each run proceeds for 100,000 random 
    page references.)

(4)  If starting state is "COLD", all physical frames are available,holding
     no virtual page.  If it is "HOT", then the simulator randomly maps 
     virtual pages to each and every physical page frame before the 
     simulation starts.

Output Report and Analysis:

Simulating 50 runs of each of the two algorithms FIFO and LRU, the mean, 
median, mode, and std. dev. of the number of page faults are reported as
following:

           FIFO(COLD)                LRU(COLD)     

mean         90001                     89984        

media        90027                     89966       

mode    90072, 90070, 89900            89956     

std.dev     78.16                      52.45
