#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define m 5 // The number of receivers
#define n 5 // The number of packets
#define x 10000

int main()
{
    int i, j, k, index;
    int q, w, s, d, f, h;
    int a = 0;
    int N = 0;
    int sum = 0;
    int I[n] = {0}; //The array used to determine eligible columns
    int A[m] = {0}; //The array used to detect the second definition of the clique matrix
    int flag = 0;
    int count = 0;
    float p, T;
    float add = 0;
    float e = 0.35;  
    /* Input the initial state matrix as a matrix of all 0. */
    int C[m][n] = {0}; //State matrix
    srand((unsigned)time(NULL));
    
for (h = 0; h < x; h++)
{      
    do
    {
        flag=0;      
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
            {  
                if (C[i][j] == 0) 
                {
                	count ++;
                }
            }
	     }
	    		 
        if (count >= 1) // When there is 0 in the state matrix, execute Algorithm 3.
        {			
			N ++;  //Statistics loop times					
            for (k = n; k > 0; k--)
            {    
			   	  
 	            //printf("\nThe k is %d\n", k);
				index = rand()%k+1;
	            //printf("\nThe random number is %d\n", index);	    
	            for (q = 0; q < n; q++)
	            {
	    	        a ++;
	    	               
	                if (I[q] == 0)
	                {
	                    index --;

	    	            if (index == 0)
	    		        {
	    		            //printf("The selected column is %d\n", a);
	    		      	    I[q] = 1;
							for (w = 0; w < m; w++)  
							{
								sum = sum + C[w][a-1];
							}
				            //printf("The sum of all elements in this column is %d\n", sum);
					        if (sum == m) // Check definition 1 of the clique matrix.
				            {	
				                I[q] = 2;
							}
							else 
							{
							    I[q] = 1;	      
							}
									
							if (I[q] == 1) // Check definition 2 of the clique matrix.
							{	
								for (w = 0; w < n; w++)
		                        {
		
		                            if (w != a-1 )
		                            {
		                               I[w] = 2; //In this loop, except for the selected column, all other columns cannot be selected again.
									}
								}    
							}
						}
					}		
				}
                a = 0;
                sum = 0;
            }
                    
            for (w = 0; w < m; w++)
            {
               	p = (float) rand() / RAND_MAX;
               	         
               	if (p > e) //The random number is greater than the erasure probability, that is, the channel has not been erased.
               	{
               	    for (s = 0; s < n; s++)
               	    {  
               	    	if (I[s] == 1)
               	    	{	 
                            C[w][s] = 1;
						}
					}
			 	}    
			}
			     
			for (f = 0; f < n; f++)
			{
			    I[f] = 0; 
			}
								        
            flag = 1;
			count = 0;   
            }         
          
    } while (flag == 1 );
    
    add = add +1.0/N;
    N = 0; 
    for (i = 0; i < m; i++) //Reset the state matrix to 0, restart the algorithm, and calculate the new throughput.
    {
         for (j = 0; j < n; j++)
        {
            C[i][j] = 0;
        }    
    } 
}
    T = n*add*1.0/x;
	printf("%lf\n", T);
}