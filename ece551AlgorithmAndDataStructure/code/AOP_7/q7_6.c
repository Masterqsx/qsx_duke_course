#include<stdlib.h>
#include<stdio.h>

unsigned mypower(unsigned x,unsigned y){
	if(y==0)
		return 1;
	else
		return x*mypower(x,y-1);
}

int main(int argc, char**argv){
	if(argc==3){
		if( ((argv[1][0]-'0')>=0)&&((argv[1][0]-'0')<=9)){
			printf("%u\n",mypower((unsigned)atoi(argv[1]),(unsigned)atoi(argv[2])));
			return EXIT_SUCCESS;
		}
		else{
			fprintf(stderr,"invalid input argument\n");
			return EXIT_FAILURE;
		}
	}
	else if(argc==2){
			
					FILE *f=fopen(argv[1],"r");
					if(f==NULL){
						fprintf(stderr,"can not open file\n");
						return EXIT_FAILURE;
					}
					char c=0;int n0=0,n1=0,flag=0;
					while((c=fgetc(f))!=EOF){
	
						if( ((c-'0')>=0)&&((c-'0')<=9)&&((flag==0)||(flag==1) )){
							n0=n0*10+(c-'0');
							if(flag==0)
								flag=1;
						}
						else if(flag==1){
							flag=2;
						}
						else if( ((c-'0')>=0)&&((c-'0')<=9)&&((flag==2)||(flag==3))){
							n1=n1*10+(c-'0');
							if(flag==2)
								flag=3;
						}
						else{ 
							printf("%u\n",mypower((unsigned)n0,(unsigned)n1));
							break;
						}
					}
					fclose(f);
					return EXIT_SUCCESS;
	}
	else{
		fprintf(stderr,"invalid input argument\n");
		return EXIT_FAILURE;
	}
}
