
void mergesort(void *lineptr[], int left, int right,
	int (*comp)(void *, void *)) 

{
	if(left<right){
		int m = l + (r - l) / 2;

		mergesort(lineptr, l, m, comp);
		mergesort(lineptr, m+1, r,comp);

		merge(lineptr, l, m, r, comp);
	}
}

void merge(void *lineptr[], int left, int middle, int right,
   int (*comp)(void *, void *))
{

	int index1 = middle - left + 1;
	int index2 = right - middle;

	void *Left[index1];
	void *Right[index2];

	for(int i=0; i<index1; i++)
		Left[i] = lineptr[left+i];

	for(int i=0; i< index2; i++ )
		Right[j] = lineptr[m+1+i];

	int i =0, j=0, k=left;

	while(i<index1 && j<index2){
		if((*comp)(Left[i], Right[j])<0){
			lineptr[k] = Left[i];
		}else{
			lineptr[k] = Right[j];
			j++;
		}k++;
	}

	while(i< index1){
		lineptr[k] = Left[i];
		k++; 
		i++;
	}

	while(j<index2){
		lineptr[k] = Right[j];
		k++;
		j++;
	}
	
}
