#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


void swap(int *data, int x, int y);
void pivotChoice(int data[], int front, int rear);
int partition(int data[], int start, int end);
void quickSort(int data[], int start, int end);


int main(void)
{
	int info[3] = { 0, 0, 0 };
	int i, k, j = 0;
	char fileName[300];
	int *data, *mid;

	FILE *fpR = NULL, *fpW = NULL;
	fpR = fopen("input.txt", "r");
	fpW = fopen("output.txt", "w");


	if (fpR == NULL) {
		printf("fail to open the input file\n");
		exit(1);
	}
	if (fpW == NULL)
	{
		printf("fail to open the output file\n");
		exit(1);
	}

	fscanf(fpR, "%d %d %d", &info[0], &info[1], &info[2]);
	fclose(fpR);

	data = (int*)malloc(sizeof(int) * info[0] * info[1]);
	mid = (int*)malloc(sizeof(int) * info[0]);

	for (i = 0; i < info[0]; i++)
	{
		snprintf(fileName, 300, "input%d.txt", i + 1);

		fpR = fopen(fileName, "r");

		if (fpR == NULL)
		{
			printf("fail to open the input file\n");
			exit(1);
		}

		k = 0;

		while (fscanf(fpR, "%d", &j) != EOF)
		{
			data[i*info[1] + k] = j;
			k++;
		}
		fclose(fpR);
	}

	pivotChoice(data, info[1] / 2, (info[0] - 1) * info[1] + info[1] / 2);
	int pivot = partition(data, 0, info[0] * info[1] - 1);

	if (pivot + 1 < info[2])
	{
		quickSort(data, pivot + 1, info[0] * info[1]);
	}
	else
	{
		quickSort(data, 0, info[0] * info[1] - 1);
	}

	for (i = 1; info[2] * i < info[0] * info[1]; i++)
	{
		fprintf(fpW, "%d ", data[info[2] * i - 1]);
	}
	
	fclose(fpW);
	free(data);

	return 0;
}


void swap(int *data, int x, int y)
{
	int temp = data[y];
	data[y] = data[x];
	data[x] = temp;
}

void pivotChoice(int data[], int front, int rear)
{
	int mid = (front + rear) / 2;

	if (data[front] > data[mid]) swap(data, front, mid);
	if (data[mid] > data[rear]) swap(data, mid, rear);
	if (data[front] > data[mid]) swap(data, front, mid);
}

int partition(int data[], int start, int end)
{
	pivotChoice(data, start, end);
	int pivot = data[(start + end) / 2];

	if ((end - start + 1) > 3)
	{
		swap(data, start + 1, (start + end) / 2);

		int i = start + 1;
		int j;

		for (j = i + 1; j < end; j++)
		{
			if (data[j] <= pivot)
			{
				i++;
				swap(data, i, j);
			}
		}

		swap(data, start + 1, i);

		return i;
	}
	else return (start + end) / 2;
}

void quickSort(int data[], int start, int end)
{
	if (start < end)
	{
		int temp = partition(data, start, end);
		quickSort(data, start, temp - 1);
		quickSort(data, temp + 1, end);
	}
}
