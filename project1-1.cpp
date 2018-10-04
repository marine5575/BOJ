/* sorting by quick sort */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void swap(int data[], int x, int y);
int pivotChoice(int data[], int front, int rear);
int partition(int data[], int start, int end);
void quickSort(int data[], int start, int end);


int main(void)
{
	int size, i, j = 0;
	int pivot;
	int *data;

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

	fscanf(fpR, "%d", &size);
	data = (int*)malloc(sizeof(int) * size);

	while (fscanf(fpR, "%d", &i) != EOF) {
		data[j] = i;
		j++;
	}
	fclose(fpR);

	quickSort(data, 0, size - 1);

	for (j = 0; j < size; j++)
	{
		fprintf(fpW, "%d ", data[j]);
	}
	fclose(fpW);
	free(data);

	return 0;
}


void swap(int data[], int x, int y)
{
	int t = data[y];
	data[y] = data[x];
	data[x] = t;
}

int pivotChoice(int data[], int front, int rear)
{
	int mid = (front + rear) / 2;

	if (data[front] > data[mid]) swap(data, front, mid);
	if (data[mid] > data[rear]) swap(data, mid, rear);
	if (data[front] > data[mid]) swap(data, front, mid);

	return data[mid];
}

int partition(int data[], int start, int end)
{
	int pivot = pivotChoice(data, start, end);

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
