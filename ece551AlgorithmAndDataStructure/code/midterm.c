#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void  myatoi(char * str,int *dest){
	*dest=0;int flag=0;
	while(*str!='\0'){
		
		if( ((*str-'0')>=0)&&((*str-'0')<=9) ){
			*dest=10*(*dest)+(*str-'0');
			if(flag==0)
				flag=1;
		}
		else if(flag==1)
			break;
    str++;
	}
}

int main(int args,char **argv){
	FILE *f=fopen(argv[1],"r");
	char **data=NULL;/*char *line=NULL;size_t sz=0;*/int n=0;
/*	while(getline(&line,&sz,f)>=0){
		n++;
		data=realloc(data,n*sizeof(*data));
		data[n-1]=strdup(line);
	}
	free(line);*/
	char c[]="a";int num=0;
	while((c[0]=fgetc(f))!=EOF){
		data=realloc(data,(n+1)*sizeof(*data));
		if(num==0)
			data[n]=NULL;
		num++;
		data[n]=realloc(data[n],num*sizeof(*data[n]));
		if(c[0]=='\n'){
			data[n]=realloc(data[n],(num+1)*sizeof(*data[n]));
			data[n][num-1]=c[0];
			data[n][num]='\0';
			n++;
			num=0;
			continue;
		}
		if(isalpha(c[0]))
			c[0]=toupper(c[0]);
		data[n][num-1]=c[0];
	}	
  int *dest=malloc(n*sizeof(*dest));
	for(int i=0;i<n;i++){
		myatoi(data[i],&dest[i]);
		printf("%d\n",dest[i]);
		free(data[i]);
	}
	free(dest);
	free(data);
	fclose(f);
	return EXIT_SUCCESS;
}
