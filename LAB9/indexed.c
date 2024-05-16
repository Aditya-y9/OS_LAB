#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{

clock_t start, end;
double cpu_time_used;
start = clock();
int f[100], index[100],i, n, st, len, j, c, k, ind,count=0;
for(i=0;i<100;i++)
f[i]=0;
x:printf("Enter the index block: ");
scanf("%d",&ind);
if(f[ind]!=1)
{
   printf("Enter no of blocks needed and blocks for the index %d on the disk : \n", ind);
   scanf("%d",&n);
}
else
{
   printf("%d index is already allocated \n",ind);
   goto x;
}
y: 
    count = 0;
    for (i = 0; i < n; i++) // Iterate directly over index array
    {
        scanf("%d", &index[i]);
        if (f[index[i]] == 1)  // Check if the index block is already allocated
            count++;
    }
   if(count==0) // Check if all blocks are available
   {
	for(j=0;j<n;j++)
	f[index[j]]=1;
	printf("Allocated\n");
	printf("File Indexed\n");
	for(k=0;k<n;k++)
		printf("%d-------->%d : %d\n",ind,index[k],f[index[k]]);
   }
else
{
   printf("File in the index is already allocated \n");
   printf("Enter another file indexed");
   goto y;
}

printf("Do you want to enter more file(Yes - 1/No - 0)");
scanf("%d", &c);
if(c==1)
   goto x;
else
   end = clock();
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   printf("Time taken: %f\n", cpu_time_used);
   exit(0);


return 0;
}