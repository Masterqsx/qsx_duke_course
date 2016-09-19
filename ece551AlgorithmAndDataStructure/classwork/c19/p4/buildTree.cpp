#include "node.h"

Node *  buildTree(uint64_t * counts) {
		priority_queue_t c_pq;
		Node* top0=NULL;Node* top1=NULL;
		for(int i=0;i<257;i++){
			if(counts[i]!=0){
				c_pq.push(new Node(i,counts[i]));
			}
		}
		if(c_pq.size()==0)
			return NULL;
		while(c_pq.size()>1){
			top0=c_pq.top();c_pq.pop();
			top1=c_pq.top();c_pq.pop();
			c_pq.push(new Node(top0,top1));
		}
		return c_pq.top();
}  
