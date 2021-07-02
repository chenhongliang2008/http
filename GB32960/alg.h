#pragma once
class CSort
{
public:
	CSort() = default;
	~CSort() = default;
public:
	static void Display(int arr[], int len);
	/*���ص�
	С�ѽڵ�N;arr[N] < arr[2N+1] && arr[N] < arr[2N+2]
	��Ҷ�ӽڵ�����N/2,Ҷ�ӽڵ���N+1/2
	������С�������ǰN / 2����Ҷ�ӽڵ�( [ 0 ~ n/2-1 ] )�������˼���
	*/
	static void MinHeapSort(int arr[], int len);
	static void MaxHeapSort(int arr[], int len);

	/*
	dfs/bfs
	*/
	static void Dfs();
};

void CSort::Display(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void CSort::MinHeapSort(int arr[], int len)
{
	printf("before MinHeapSort:");
	Display(arr, len);
	auto adjustHeap = [](int arr[], int len, int index) {
		int child = 2 * index + 1; //���ӽڵ�
		for (; child < len; child = 2 * child + 1) {
			//������ӽڵ���ڣ��ұ���ڵ�С�򽻻�λ��
			if (child + 1 < len && arr[child] < arr[child + 1]) {
				child++;
			}
			//�ж��ӽڵ�͸��ڵ��С
			if (arr[index] < arr[child]) {
				swap(arr[index], arr[child]);
				index = child;
			}
			else {
				break;
			}
		}
	};
	//��Ҷ�ӽڵ�ӵײ㿪ʼ���ϵ�����0��ʹ�Ѷ�Ԫ�����
	for (int i = len / 2 - 1; i >= 0; i--) {
		adjustHeap(arr, len, i);
	}
	//���Ѷ�Ԫ����ĩβԪ�ؽ��н�����ʹĩβԪ�����Ȼ�����������
	for (int i = len - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		adjustHeap(arr, i, 0);
	}
	printf("after MinHeapSort:");
	Display(arr, len);
}

void CSort::MaxHeapSort(int arr[], int len)
{
	printf("before MaxHeapSort:");
	Display(arr, len);
	auto adjustheap = [](int arr[], int len, int index) {
		int child = 2 * index + 1;
		for (; child < len; child = 2 * child + 1) {
			if (child + 1 < len && arr[child] > arr[child + 1]) {
				child++;
			}
			if (arr[index] > arr[child]) {
				swap(arr[index], arr[child]);
				index = child;
			}
			else {
				break;
			}
		}
	};
	for (int i = len / 2 - 1; i >= 0; i--) {
		adjustheap(arr, len, i);
	}
	for (int i = len - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		adjustheap(arr, i, 0);
	}
	printf("after MaxHeapSort:");
	Display(arr, len);
}