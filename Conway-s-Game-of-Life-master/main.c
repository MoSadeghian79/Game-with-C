#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fx,fy,sx,sy,h=0;

void print(int row,int z,int a[row][row])
{
	int i,j;
	int b=0;
	for (i=0;i<z;i++)
		printf("=");
	printf("\n");
	for(i=0;i<row;i++)
	{
		for(j=0;j<row;j++)
		{
			if (a[i][j] > -1)
			{
				printf("|");
				b = 1;
			}				
			if (a[i][j] == 1)
				printf("*");
			else if(a[i][j] == 0)
				printf(" ");
		}
		if ( b == 1)
		{
			printf("|\n");
			b=0;	
		}
	}
	for (i=0;i<z;i++)
		printf("=");
}

void gol (int row,int p[row][row])
{
	int i,j,it,jt,sum=0;
	int p2[row][row];
	for (i=0;i<row;i++)
	{
		for (j=0;j<row;j++)
		{
			p2[i][j]=p[i][j];
		}	
	}	
	for (i=0;i<row;i++)
	{
		for(j=0;j<row;j++)
		{
			if (p[i][j] > -1)
			{
				for (it = i-1;it < i+2;it++)
				{
					for(jt = j-1;jt < j+2;jt++)
					{
						if ((it>-1) && (jt>-1) && (it<row) && (jt<row))
						{
								if (p[it][jt] == 1)
									sum++;
						}
					}
				}
				if (p[i][j] == 1)
				{
					if (sum <3)
						p2[i][j] = 0;
					else if (sum >4)
						p2[i][j] = 0;
				}
				else if (sum == 3)
					p2[i][j]=1;
			}
			sum =0;	
		}			
	}
	for (i=0;i<row;i++)
	{
		for (j=0;j<row;j++)
		{
			p[i][j]=p2[i][j];
		}	
	}	
}
void check(int row , int p[row][row])
{
	int i,j;
	for (i=fy;i<sy+1;i++)
		if (p[fx][i] == 1)
		{
			fx--;
			if (fx > -1)
				for (j=fy;j<sy+1;j++)
					p[fx][j] = 0;
			break;
		}
	for (i=fx;i<sx+1;i++)
		if (p[i][fy] == 1)
		{
			fy--;
			if (fy > -1)
				for (j=fx;j<sx+1;j++)
					p[j][fy] = 0;
			break;
		}
	for (i=fy;i<sy+1;i++)
		if (p[sx][i] == 1)
		{
			sx++;
			if (sx < row)
				for (j=fy;j<sy+1;j++)
					p[sx][j] = 0;
			break;
		}
	for (i=fx;i<sx+1;i++)
		if (p[i][sy] == 1)
		{
			sy++;
			if (sy < row)
				for (j=fx;j<sx+1;j++)
					p[j][sy] = 0;
			break;
		}
}
int main(int argc, char *argv[]) {
	int n,t,i,j,k,l;
	printf("Enter size of table & number of simulations: ");
	scanf("%d", &n);
   	scanf("%d", &t);
	fx = n;fy = n;sx = 2*n-1;sy=2*n-1;
	int p[3*n][3*n];
	for(i=0;i<3*n;i++)
	{
		for(j=0;j<3*n;j++)
		{
			if((i>=n && i<2*n)&&(j>=n && j<2*n))
				p[i][j] = 0;
			else 
				p[i][j] = -1;
		}
	}
	while (1)
	{
		int x,y;
		printf("Enter coordinate: ");
		scanf("%d%d",&x,&y);
		if(x<n && y<n)
			p[n+x][n+y] = 1;
		else 
			break;
	}
	for(k=0;k<t;k++)
	{
		system("@cls||clear");	
		printf("Level: %d\n",k+1);
		l = (sy-fy+1)*2+1;
		print(3*n,l,p);
		check(3*n,p);
		if ((fx == -1) && (fy == -1) && (sx == (3*n)) && (sy == (3*n)))	
			break;
		gol (3*n,p);
		sleep(1.5);
	}
	printf("\nThe End!!!!!");
	return 0;
}
