#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define m 5 // The number of receivers
#define n 5 //The number of packets
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
    float e = 0.1; //erasure probability   
    
    /* Input the initial state matrix as a matrix of all 0. */
    int C[m][n] = {0}; //State matrix
    srand((unsigned)time(NULL));

for (h = 0; h < x; h++) //loop multiple calculations to average throughput.
{    
    do
    {
        flag=0;
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
            {  
                if (C[i][i] == 0) 
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
					        if (C[a-1][a-1] == 0) // Check definition 1 of the clique matrix.
				            {	
				                I[q] = 1;
							}
							else 
							{
							    I[q] = 2;	      
							}
									
							if (I[q] == 1) // Check definition 2 of the clique matrix.
							{	
								for (w = 0; w < m; w++)
		                        {
		
		                            if (I[w] == 1)
		                            {

		                                for (s = 0; s < n; s++)
		                                {
										
		                                    if (I[s] == 1)
		                                    {
		                                    	if (C[w][s] == 0)
		                                    	{
		                                    		A[w] ++;
		                                    		if (A[w] > 1)
		                                            {
		                                                I[q] = 3;	                                 
							        	            }   
												}	
											}
									    }  
									}	
                               }   
						    }
			
							for (w = 0; w < m; w++)
		                    {
								A[w] = 0;      
							}
							
		                    
		                    if (I[q] == 1)
		    	            {
		                    	//printf("The selected column is %d\n", a);	
							}
						}
					}		
				}
                a = 0;
            }
               
            for (w = 0; w < m; w++)
            {
                p = (float) rand() / RAND_MAX;
                //printf("The probability is %f\n", p);
               	         
                if (p > e) //The random number is greater than the erasure probability, that is, the channel has not been erased.
                {  
                    if (I[w] == 1) //Two cases of decoding
                    {
               	        
						for (s = 0; s < n; s++) //The row corresponding to the selected column
               	        {
				
               	    	    if (I[s] == 1) 
               	            {    	 
                               C[w][s] = 1;
						    }
			         	} 
					}
					else //Rows corresponding to unselected columns
                    {
                        for (s = 0; s < n; s++)
		                {
										
		                    if (I[s] == 1)
		                    {
		                    	if ( C[w][s] == 0)
		                    	{
		                    		sum ++;
								}
							}	
					    }
						
						if (sum <= 1 )
		                {
		                   for (s = 0; s < n; s++)
		                   {
                                if (I[s] == 1)
		                        {
		                            C[w][s] = 1;
		                        }
		                    }
						}
						
					    sum = 0;	  
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
