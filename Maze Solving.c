#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

struct nodeStruct
{
	int xValue;       // x co-ordinate.
	int yValue;       // y co-ordinate.
	char identity;    // Identity as either visited or unvisited.
	
	struct nodeStruct* next;     // Pointer structure that points to next structure in linked list.
};

typedef struct nodeStruct node;

typedef struct mazeStruct
{
 char **array;         // 2d dynamic array allocation.
 int xsize, ysize;
 int xstart, ystart;
 int xend, yend;
} maze;

// Pushes all locations of maze in head linkedlist.
void push( node**hd, int x, int y )      
{
	node*ptr= (node*) malloc (sizeof (node));
	ptr->xValue=x;
	ptr->yValue=y;
	ptr->next=*hd;
	*hd=ptr;
}

// Assigning UNVISITED to entire linkedlist of head.
void makeIdentityU( node*hd)     
{
	
	node*ptr =hd;
	
	while( ptr!=NULL)
	{
		ptr->identity='U';
		ptr=ptr-> next;
	}
	
	hd=ptr;
}

int display(node** hd)
{
	node*ptr=*hd;
	
	printf("All possible locations of maze and its respective identities are \n");
	
	while(ptr!=NULL)
	{
		printf("(%d,%d,%c) \n", ptr->xValue, ptr->yValue, ptr->identity);
		ptr=ptr->next;
    }
    
    if(ptr==NULL)
    {  
       return 0;
    }
		
}

void displayGame(node** hd)
{
	node*ptr=*hd;
	
	printf("The path of the maze is: \n");
	
	if(ptr==NULL)
	{
			printf(" There is no solution");
			exit(0);
	}

	
	while(ptr!=NULL)
	{
		printf("(%d,%d) \n", ptr->xValue, ptr->yValue);
		ptr=ptr->next;
    }	
}


// Assigning VISITED to vertical borders, horizontal borders,blocked positions, starting positions.
 void makeIdentityV ( node** hd, int x, int y, int debugMODE)
{
	node*ptr= *hd;
	
	while( ptr!=NULL)
	{
		if ( (ptr->xValue==x) && (ptr->yValue==y) )
		{
			if(debugMODE==TRUE)
			{
				printf(" Visited identities are (%d,%d)\n",ptr->xValue,ptr->yValue);
			}
			
			ptr->identity= 'V';
		}
		ptr= ptr->next;
	}

}

  char End(node**hd, int xend, int yend )
  {
  	node*ptr=*hd;
  	
  	if ( (ptr->xValue==xend) && (ptr->yValue==yend))
  	{
  		printf(" END HAS BEEN FOUND \n");
  		return 'e';
	}
  	
  	else
  	{
  	   return 'a';	
	}
	
	return 1;
  }
  
  int GameTopX ( node** hd)
  {
  	int a=0;
  	node*ptr=*hd;
  	a= ptr->xValue;
  	return a;
  }
  
  int GameTopY ( node** hd)
  {
  	int b=0;
  	node*ptr=*hd;
  	b= ptr->yValue;
  	return b;
  }
  
  char checkNeighbor ( node*hd, int xn, int yn)
  {
  	node*ptr= hd;
  	
  	while( ptr!=NULL)
  	{
  		
  		if( (ptr->xValue==xn) && (ptr-> yValue==yn)&&  (ptr-> identity== 'U'))
  		{
  		return 'u';
		}
	
		if ( (ptr->xValue==xn) && (ptr-> yValue==yn)&&  (ptr-> identity== 'V'))
		{
		return 'v';
		}
	
	ptr= ptr->next;
    }
	
	return 0;
   }
   
   void pop( node** hd)
   {
   	 	node*ptr= *hd;
   	 	
   	 	if(ptr!=NULL)
   	 	{
   	 		*hd=ptr->next;
   	 		free(ptr);
		}
		
   }
   
   void empty( node** hd)          // When the stack is empty, then it has no solution.
   {
   		node*ptr=*hd;

   		if (ptr==NULL)
   		{
   			printf(" The maze has no solution");
   			exit(0);           // Terminates the loop and ends the program.
		}
   }

	void makeEmpty (node** hd)
	{
		node* ptr=*hd;
		node* curr;
		while(ptr!=NULL)
			{
				curr=ptr->next;
				free(ptr);
				ptr=curr;
			}
		*hd=ptr;
		free(ptr);
	}



int main (int argc, char **argv)
{
  maze m1;            // Node for creating maze.

  int xpos, ypos;     // UserInput variable from file that blocks the path in the maze puzzle.
  
  int i,j;            // Variable used for "for loops" ahead.
  
  node*head=NULL;     // Head is a linked list, which access all possible locations of maze with its identity.
  
  node*game=NULL;     // Game is a linked list to find a way in a maze.
  
  int debugMODE;      // Variable to set up the debug mode.

  // Setting up the DEBUG MODE.
  for(i=0;i<argc;i++)
	{							
		if (argv[i][0]=='-')
		{
			if (argv[i][1]=='d')
			{
				debugMODE=TRUE;
			}
		}
	
		else
		{
			debugMODE=FALSE;
		}
	} 


  FILE *src;

  /* verify the proper number of command line arguments were given */
  if(argc == 1) {
     printf("Usage: %s <input file name>\n", argv[0]);
     exit(-1);
  }
   
  /* Try to open the input file. */
  if ( ( src = fopen( argv[1], "r" )) == NULL )  
  {
    printf ( "Can't open input file: %s", argv[1] );
    exit(-1);
  }

  /* read in the size, starting and ending positions in the maze */
  fscanf (src, "%d %d", &m1.xsize, &m1.ysize);
  fscanf (src, "%d %d", &m1.xstart, &m1.ystart);
  fscanf (src, "%d %d", &m1.xend, &m1.yend);
  /* print them out to verify the input */
  printf ("size: %d, %d\n", m1.xsize, m1.ysize);     // Suppouse size 3x3
  printf ("start: %d, %d\n", m1.xstart, m1.ystart);   // Suppose start (1,1)
  printf ("end: %d, %d\n", m1.xend, m1.yend);         // End (3,3).
  printf("\n");
  
  
  
  // Dynamic array of 2D Size [xsize+2][ysize+2]. Suppose 5x5.
  // char **array;
  m1.array= (char**)malloc( sizeof(char*)* (m1.xsize+2));      // Allocating memomry space for 5 rows.
  
  for (i=0;i< (m1.xsize+2);i++)
  {
	m1.array[i]= (char*)malloc( sizeof (char)*(m1.ysize+2));   // For each row, now there are 5 coloumns. 
															  // Now m1.array[5][5]. Just suppose.		
  }
  
  // Initaialize the maze to be empty. Assigning each position of maze to be '.'
  // Here we are pushing all locations of maze in the head link list.
  
  for (i = 0; i < m1.xsize+2; i++)
  {
  	for (j = 0; j < m1.ysize+2; j++)
  	{
       m1.array[i][j] = 250;        // Ascii value of '.'
       
       push( &head,i,j);          // Pushing each position of maze in head. Note it is pass by reference.
	} 
  }


	makeIdentityU(head);        // By function call, all locations of maze in head linked list will be marked as UNVISITED.
	
	if(debugMODE==TRUE)
	{
		display( &head);    // Display all locations of maze which are set to be UNVISITED.
		printf("\n");
	}



	// Marking Vertical borders to '*' and setting those positions to be visited.
	for (i=0;i<m1.xsize+2;i++)
	{ 
	m1.array[i][0]= '*';         // Ascii value of '*'= 254.      
	m1.array[i][m1.ysize+1]= '*';
	
	makeIdentityV (&head,i,0,debugMODE);              // All vertical borders called to assign as visited.
	makeIdentityV (&head, i , m1.ysize+1, debugMODE );
	
	}

	printf("\n");

	// Marking Horizontal border to '*' and setting those locations to be visited.

	for (i=0; i<m1.ysize+2; i++)
	{
	m1.array[0][i]= '*';          // Ascii value of '*'=254.
	m1.array[m1.xsize+1][i]= '*';
	
	makeIdentityV (&head,0,i, debugMODE); 
	makeIdentityV (&head, m1.xsize+1, i ,debugMODE);    // All horizontal borders called to assign as visited
	}
	
	printf ("\n");
	
	if( debugMODE==TRUE)
	{
		display( & head);
		printf("\n");
	}
	

/* mark the starting and ending positions in the maze and also pushing the starting position in node name game
   , then assigning it as visited. */
   
  	m1.array[m1.xstart][m1.ystart] = 's';
  
  	push( &game, m1.xstart,m1.ystart);
  
 	makeIdentityV (&head, m1.xstart, m1.ystart,debugMODE );       // Function called to assign started position as visited.
  
  
	m1.array[m1.xend][m1.yend] = 'e';
  
  /* mark the blocked positions in the maze with *'s */
  	while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)
    {
     m1.array[xpos][ypos] = '*';     // Ascii value of *
     
     makeIdentityV( &head, xpos, ypos, debugMODE);     // Assigning the block positions to be Visited.
    }
    
    if( debugMODE==TRUE)
    {
	display ( & head);    // displays the head linked list with borders,blocked positions and starting positon as VISITED 
	  					// 	and other locations as UNVISITED.
    }  

	printf("\n");
  /* print out the  maze */ 
  	for (i = 0; i < m1.xsize+2; i++)
    {
     for (j = 0; j < m1.ysize+2; j++)
     {
     	printf (" %c ", m1.array[i][j]);
	 }
	 printf( " \n");
       
    } 
    
    while( (End( &game,m1.xend,m1.yend)!='e' )  )
    {
    	int a= GameTopX (&game);
    	int b= GameTopY (&game);
    	
    	if(debugMODE==TRUE)
    	{
    		printf(" Top Values of game stack are %d, %d\n", a,b);
		}
    
    	if( checkNeighbor(head,a,b+1)=='u')     // Check neighbor on right. ( first priority).
    	{
    		push(&game,a,b+1);
    		makeIdentityV (&head,a,b+1,debugMODE);
		}
		
		else 
		{
			
			if (checkNeighbor(head,a+1,b)=='u')   // Check neightbor on down. (second priority).
			{
				push(&game,a+1,b);
    			makeIdentityV (&head,a+1,b,debugMODE);
			}
			
	    	else 
			{
				if((checkNeighbor(head,a,b-1)=='u'))    // Check neighbor on left. (third priority).
				{
					push(&game,a,b-1);
    				makeIdentityV (&head,a,b-1,debugMODE);	
				}
				
				else 
				{
					if ((checkNeighbor(head,a-1,b)=='u'))    // Check neighbor on up. (fourth priority).
					{
					push(&game,a-1,b);
    				makeIdentityV (&head,a-1,b,debugMODE);	
					}
					else 
					{
						pop(&game);                  // When all neighbors are visited. Then popped the top of the game.
						if (debugMODE==TRUE)
						{
							printf(" Values popped are %d %d \n",a,b);
						}
						
						empty(&game);
					}
			    }
		    }
        }
	}
	
	// This will display the solution of maze.
	displayGame( &game);
	
	// Function to reset the stack so that it can be used again.
	
	makeEmpty(&game);
	makeEmpty(&head);
			
	return 0;
       
}
  
  

  
  
