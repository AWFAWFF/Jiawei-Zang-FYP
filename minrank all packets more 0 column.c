#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define m 5 // The number of receivers
#define n 5 // The number of packets
#define u 10

int rref(int M[m][n]) //The rref required by the encoding process.
{
	int lead = 0;
	int i, r, j, k;
	int d;
	
	for (r = 0; r < m; r++)
	{
		if (lead < n)
		{
			i = r;
			while (M[i][lead] == 0) //Scan the elements of each column from each column to see if it is 0.
			{
				i ++;
				if (m == i) //m = i means that if this column is all 0, lead++ will rescan from the next column.
				{
					i = r;
					lead ++;
				}
			}
			
			if (lead < n) //lead < n means that not all columns are all 0.
			{
			
			if (i != r) // i is not equal to r means that there is 0 in the detected column. This detection does not necessarily start from the top element of that column, because the 22-line for loop
			{
				for (k = 0; k < n; k++) /* The leftmost element of row i is not 0 but 1, because i can only be greater than r (row i is below row r), 
				                         so row i and row r are exchanged to ensure that the first element of row r (row r after replacement) The non-zero element 1 is relatively farther to the left. */
				{
					int temp;
					temp = M[i][k];
                    M[i][k] = M[r][k];
                    M[r][k] = temp;
				}
	        }
			
			for (j = 0; j < m; j++)
			{
				if (j != r) 
				{
                    if (M[j][lead] != 0) //For the row where the column where the beginning 1 is opposite to the r row is not 0.
                    {
					
		        	for (k = 0; k < n; k++)
		        	{
				        M[j][k] = (M[j][k] + M[r][k]) % 2; //modulo two.
				    }	
				    }
				}
			}
			
			lead ++;
		}
		}
	}  // The for loop, r loops from 0 to m, which means that the above operations are performed from the first row to the last row of the matrix.
}

int rref1(int M[2*m][n]) //The difference between the rref required in the decoding process and the rref in the encoding process is that here is a 2m*n matrix.
{
	int lead = 0;
	int i, r, j, k, d;
	
	
	for (r = 0; r < 2*m; r++)
	{
		if (lead < n)
		{
			i = r;
			while (M[i][lead] == 0) 
			{
				i ++;
				if (2*m == i) 
				{
					i = r;
					lead ++;
				}
			}
			
			if (lead < n) 
			{
			
			if (i != r) 
			{
				for (k = 0; k < n; k++) 
				{
					int temp;
					temp = M[i][k];
                    M[i][k] = M[r][k];
                    M[r][k] = temp;
				}
	        }
			
			for (j = 0; j < 2*m; j++)
			{
				if (j != r) 
				{
                    if (M[j][lead] != 0) 
                    {
					
		        	for (k = 0; k < n; k++)
		        	{
				        M[j][k] = (M[j][k] + M[r][k]) % 2;
				    }	
				    }
				}
			}
			
			lead ++;
		}
		}
	}  
}

int main()
{
	int s[m][n] = {0}; //state matrix
	int a[m][n] = {0}; //coding Matrix for Multiple Possibilities
	int b[m][n] = {0}; //coding Matrix for one possibility
	int y[m][n] = {0}; //The matrix after minrank coding matrix rref
	int z[2*m][n] = {0}; //decoding matrix
	int i, j, w, f, g, h, d, v, r, ran, q;
	int cnt = 0;
	int x = 0;
	int l = 0;
	int rank = 0;
	int minrank = m + 1;
	float p, T; 
	float add = 0;
	int o = 0;
	int sum = 0;
	int addd = 0;
	int flag = 0;
	int count = 0;
	int N = 0;
	float e = 0.1; /* The error probability that the Transmitter sends a packet to each receiver.*/
	
	srand((unsigned)time(NULL));
	
for (v = 0; v < u; v++)//This for loop is used to count the average throughput of changing the state matrix from all 0s to a state matrix that meets the requirements many times, such as 1000 times, 10000 times.
{
		
	do
	{
	flag=0;
	
	for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {  
            if (s[i][j] == 0) 
            {
                count ++;
            }
        }
	}
	
	if (count >= 1) //Start the algorithm when the slope in the state matrix has 0.
	{
		
   	for (j = 0; j < n; j++) //Convert the coding matrix according to the state matrix.
	{
		for (i = 0; i < m; i++)
		{
			if (s[i][j] == 0)
			{
				sum ++;
		    }
		}
		
		if (x < sum)
		{ 
		    x = sum;
		    r = j;
		}
		sum = 0;
    }
    
    for (i = 0; i < m; i++) //The column with the most 0s in the state matrix is recorded as the r column, and the position in the coding matrix corresponding to all 0s in this column is changed to 1.
	{
		a[i][r] = 1;
    }
    
    for (i = 0; i < m; i++)
	{
		if (s[i][r] == 1) //If there are 1s in the r column of the state matrix, the rows where these 1s are located are judged again.
		{
			for (j = 0; j < n; j++)
			{
				if (s[i][j] == 0)
				{
					sum ++;
				}
				
				if (s[i][j] == 1)
			    {
				    addd ++;
			    }
			}
			
				
		    if (addd < n) //Select 0 for rows with 0 in the these rows
		    {
			    ran =  rand()%sum+1;	        
	            for (j = 0; j < n; j++)
		        {
			        if (s[i][j] == 0)
			        {
				        ran --;
				        if (ran == 0)
				        {
					        a[i][j] = 1;
				        }				
			        }	    
		        }
		    }
		    sum = 0;
			addd = 0;	
		}
   }
   
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (s[i][j] == 1)
			{
				a[i][j] = 2; //Elements that are already 1 in the state matrix become 2 in the coding matrix.
			}
        }
    }
    
    for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (s[i][j] == 1)
			{
				sum ++;
			}
	    }
		
		if (sum == n)
		{
			for (j = 0; j < n; j++)
		    {  
		        a[i][j] = 0; //The rows of the state matrix with all 1s meet the requirements and do not participate in encoding, and the corresponding rows in the coding matrix are set to all 0s.
		    }
		}
		sum = 0;	
    }

	for (i = 0; i < m; i++) //scan the number of unknowns (2) in the matrix.
    {
        for (j = 0; j < n; j++)
        {
        	if (a[i][j] == 2)
        	{
        		cnt ++;
			}
	    }
    }
	
	int k = cnt;
	int c[cnt];
	 
	for(i = 0; i < k; i++)
	{
		c[i] = 0;
	}
	
	
	for (q = 0; q < pow(2, k); q++) //From 0 to pow(2, k), corresponding to 2^k possibilities, corresponding to the relative binary numbers, the binary numbers are in the array c.
	{
		w = q;
		
	    for (f = 0; f < k; f++)
	    {
	    	g = w % 2;
	    	h = w / 2;
	    	w = h;
	    	c[f] = g;  //c array is an array of binary numbers.
		}         

        for (i = 0; i < m; i++) //Every time 2 is scanned in matrix a, the element is replaced with the array corresponding to array c in matrix b.
	    { 
            for (j = 0; j < n; j++)
           {
           	    if (a[i][j] == 2)
           	    {
           	        b[i][j] = c[l++];  
				}
           } 
        }
        
        for (i = 0; i < m; i++) //Every time 1 is scanned in matrix a, the element is 1 in matrix b.
	    { 
            for (j = 0; j < n; j++)
           {
           	    if (a[i][j] == 1)
           	    {
           	        b[i][j] = 1;  
				}
           } 
	    }
	    
	    rref (b); //Perform modulo two operation rref on matrix a.
	    
        for (i = 0; i < m; i++)
        {
        	for (j = 0; j < n; j++)
        	{
        		if (b[i][j] == 1)
        		{
        			rank ++;
        			break;//Scan non-zero rows in the matrix, and break to the next row when a 1 is scanned. How many non-zero rows represent the rank of the original matrix.
				}
			}
		}
        
        if (rank < minrank)
        {
        	minrank = rank;
         
            for (i = 0; i < m; i++) //Save the rref matrix corresponding to minrank into the y matrix, which is used for encoding.
            {
                for (j = 0; j < n; j++)
                {
                    y[i][j] = b[i][j];
                }          
            }
        }     
        l = 0;
        rank = 0;
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
            {
                b[i][j] = 0;  
            } 
        }  	   
	} 
	N = N + minrank;    /* The value of minrank represents the number of transmission packets in this loop, 
	                    and the number is recorded in each loop until the state matrix meets the requirements after multiple loops,
						 and the total number of transmission packets is calculated. */
	cnt = 0;
	 
	for (q = 0; q < m; q++) //For each receiver, each row of the state matrix represents a receiver
	{
		for (i = 0; i < minrank; i++) /* Decoding, for each receiver, first determine the erasure of all the packets to be transmitted, 
		                                the for loop here is for each receiver for each row of the y matrix (non-zero rows, so the number is minrank). */
		{
			p = (float) rand() / RAND_MAX;//Each transmission packet is judged, that is, all non-zero rows in the y matrix, if the random number of this row is greater than e, the transmission is successful.	
			if (p > e)
			{
			   for (j = 0; j < n; j++)
			   {
			   	    if (y[i][j] == 1) //The decoding method is still rref. Here, the packet successfully received by the receiver needs to be placed in the upper m rows of the z matrix.
			   	    {
			   	    	z[i][j] = 1; //The y matrix corresponds to a 1 in that row, which also becomes a 1 in the z matrix.
				    }
			   }						 	   
		    }    
		}	
		
		for (j = 0; j < n; j++) //The existing packets of the receiver are placed in the m row below the z matrix.
		{
			if (s[q][j] == 1)
			{
				o++;
				z[m-1+o][j] = 1;
		   }
		}	
	    
	    rref1(z);//decoding
	    
	    for (i = 0; i < 2*m; i++) //After the z matrix rref represents the status of this receiver after decoding
	    {
	    	for (j = 0; j < n; j++)
	        {
	    	    if (z[i][j] == 1)
	    	    {
	    		    sum ++;
			    }
		    }
		    
		    if (sum == 1) /* If there is only one 1 in a row, it means that the receiver has received the corresponding uncoded packet and the decoding is successful. 
			                If there is more than one 1 in a row, it means that the receiver has received the corresponding coded packet, and the decoding has not been successful. */
	        {  
	    	    for (j = 0; j < n; j++)
	    	    {
	    		    if (z[i][j] == 1)
	    		    {
	    			    s[q][j] = 1; /* Update the packets corresponding to a row with only one 1 in the decoded z matrix to the row corresponding to the state matrix. 
						                A z matrix corresponds to a row, because a z matrix is a state of a receiver, corresponding to a row in the state matrix. */
				    } 
			    }
		    }
		    sum  = 0;
		}
   
	    for (i = 0; i < 2*m; i++)
        {
            for (j = 0; j < n; j++)
            {
                z[i][j] = 0;
            } 
        } 
		o = 0;	
    }
    
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            a[i][j] = 0;
        } 
    } 
    flag = 1;
	count = 0;
	minrank = m + 1;
	x = 0;

    }   
} while (flag == 1 );
   //printf("%d\n", N); 
   add = add +1.0/N; 
   N = 0; //After recording the value of this loop N, reset it to 0
  
   for (i = 0; i < m; i++)//Reset the state matrix to all 0s before the next loop.
   {
       for (j = 0; j < n; j++)
       {
            s[i][j] = 0;
       }  
   } 
  
}   
  
	printf("%lf\n", add); 
    T = n*add*1.0/u;
	printf("%lf\n", T);
	
}