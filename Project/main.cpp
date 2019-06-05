#include "skiplist.h"
using namespace std;
int main() {

#if DEBUG
	test();
#endif
#if !DEBUG
	//user programs
	int choose;
	SkipList *sl = NULL;
	int pfactor;
	char end = 'n';
	printf("\t\t ╭ ──────────────────────────────────── ╮\n");
	printf("\t\t │          实现跳跃表的各种操作        │\n");
	printf("\t\t │──────────────────────────────────────│\n");
	printf("\t\t │    1.创建跳跃表                      │\n");
	printf("\t\t │    2.插入元素                        │\n");
	printf("\t\t │    3.删除元素                        │\n");
	printf("\t\t │    4.查找给定关键字并打印路径        │\n");
	printf("\t\t │    5.打印跳跃表                      │\n");
	printf("\t\t │    6.销毁跳跃表                      │\n");
	printf("\t\t │    0.退出程序                        │\n");
	printf("\t\t ╰ ──────────────────────────────────── ╯\n");
	do
	{
		printf("\t\t Please choose one from above: ");
		scanf("%d", &choose);
		
		if (choose < 0 || choose > 6)
		{
			printf("\t\t No option exist!!!\n");
			printf("\t\t Choose one from above again: ");
			scanf("%d", &choose);
		}
		switch (choose)
		{
		case 1:
			printf("\t\t Please input the probabilty you set (only the denominator): ");
			scanf("%d", &pfactor);
			sl = CreateSL(pfactor);
			if (sl)
				printf("\t\t Successfully create a new Skip List!\n");
			else
				printf("\t\t Couldn't create the new Skip List!\n");
			break;
		case 2:
			if (sl == NULL)
			{
				printf("\t\t There isn't any available skip list!\n");
				printf("\t\t Please create a skip list first!\n");
			}
			else
			{
				int num;
				vector<ElementType> keys;
				printf("\t\t Please input your array to be inserted into the skip list\n");
				printf("\t\t P.S. The first number should be the size of the array.\n");
				printf("\t\t e.g. 10 1 2 3 4 5 6 7 8 9 10\n");
				printf("\t\t Your array: ");
				cin >> num;
				ElementType* arr = new ElementType[num];
				for (int j = 0; j < num; j++)
				{
					cin >> arr[j];
					//printf("%d ", arr[j]);
					keys.push_back(arr[j]);
					Insert(sl, arr[j]);
				}
			}
			break;
		case 3:
			if (sl == NULL)
			{
				printf("\t\t There isn't any available skip list!\n");
				printf("\t\t Please create a skip list first!\n");
			}
			else
			{
				int num;
				vector<ElementType> delkeys;
				printf("\t\t Please input your array to be deleted from the skip list\n");
				printf("\t\t P.S. The first number should be the size of the array.\n");
				printf("\t\t e.g. 10 1 2 3 4 5 6 7 8 9 10\n");
				printf("\t\t Your array: ");
				cin >> num;
				ElementType* arr = new ElementType[num];
				for (int j = 0; j < num; j++)
				{
					cin>>arr[j];
					delkeys.push_back(arr[j]);
					if (!Delete(sl, arr[j]))
					{
						printf("item with key %d can't be deleted.\n", arr[j]);
					}
				}
				break;
			}
		case 4:
			if (sl == NULL)
			{
				printf("\t\t There isn't any available skip list!\n");
				printf("\t\t Please create a skip list first!\n");
			}
			else
			{
				ElementType searchkey;
				printf("\t\t Please input your search Key: ");
				cin >> searchkey;
				Search(sl, searchkey);
			}
			break;
		case 5:
			if (sl == NULL)
			{
				printf("\t\t There isn't any available skip list!\n");
				printf("\t\t Please create a skip list first!\n");
			}
			else
			{
				Print(sl);
			}
			break;
		case 6:
			Free(sl);
			printf("\t\t Skip List sl has been destroyed.\n");
			sl = NULL;
			break;
		case 0:
			end = 'y';
			printf("\t\t Exit successfully!\n");
		default:
			break;
		}
	} while (end == 'n');

#endif
	system("PAUSE");
	return 0;

}
