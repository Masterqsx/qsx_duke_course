
void squares(int size1, int x_offset, int y_offset, int size2)
{
	int y=0,x=0;
	int w;
	int h;
	if ( size1>=(x_offset+size2) )
	{
		w=size1;
	}
	else
	{
		w=x_offset+size2;
	}
	
	if ( size1>=(y_offset+size2) )
	{
		h=size1;
	}
	else
	{
		h=y_offset+size2;
	} 

	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{	
			if (
			 	(
				  ( (x<x_offset+size2) && (x>=x_offset) )
				&&
				  ( (y==y_offset)||(y==y_offset+size2-1) )
				)
				||
				(
				  ( (y<y_offset+size2) && (y>=y_offset) )
				&&
			          ( (x==x_offset)||(x==x_offset+size2-1) )	
				)
				
			   )	
			{
				printf("*");
			}
				
			else if (
				  (
					(
						x<size1
					)
					&&
					(
						( (y==0)||(y==size1-1))
					)	
			          )
				  ||
				  (
					(
						y<size1
					)
					&&
					(
						( (x==0)||(x==size1-1))
					)
				  )
				)
			
			{
				printf("#");
			}
			else
				printf(" ");
		}
		printf("\n");
		
	}
}


