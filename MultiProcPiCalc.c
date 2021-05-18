// Kalrav Srivastava
// ks874

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

//mostly derived from the thread example of Pi calc

int main(int argc, char *argv[])
{
	int status;
	double x;

	double calcPi = 0.0;

	int pid[atoi(argv[1])];
	int pd[atoi(argv[1])][2];
	
	for (int i = 0; i < atoi(argv[1]); i++)
	{
		pipe(pd[i]);
		pid[i] = fork();

		if (pid[i] != 0) //parent
	    	{
			double rd;
			while((pid[i] = waitpid(-1, &status, 0)) != -1)
	        	{
                		//wait for child process
	        	}
	        
	        	read(pd[i][0], &rd, sizeof(double));
	        	calcPi = calcPi + (rd / (double)atoi(argv[2]));
	    	}


		else if (pid[i] == 0) //child
		{
			close(pd[i][0]);

			double x;
			double total = 0.0;

			//directly from the slides
			int start = atoi(argv[2]) / atoi(argv[1]) * i + 1;
			int last = atoi(argv[2]) / atoi(argv[1]) * (i + 1);
			
			for(int j = start; j <= last; j++)
			{
				x = ((double)j - 0.5) / (double)atoi(argv[2]);
				total = total + 4.0 / (1.0 + x * x);
			}
			
			write(pd[i][1], &total, sizeof(double));
			close(pd[i][1]);
			exit(0);
		}
	}
	
	printf("\nActual Pi Val:\t\t3.141592653589793238462643\n");
	printf("Calculated Pi Val:\t%.24f\n", calcPi);
}
